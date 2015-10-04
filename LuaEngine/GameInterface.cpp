#include "stdafx.h"
#include "GameInterface.h"
#include "Addresses.h"
#include "Detours.h"
#include "LuaScript.h"

CGameInterface* This = nullptr;
CJassInterface* pJassInterface = nullptr;
HWND CGameInterface::wnd = nullptr;
std::vector <LPVOID> CGameInterface::m_Memory;
LPSTR ChatText;
bool bChatEvent;

typedef int(__fastcall *LookupNative_)(LPSTR);
LookupNative_ fLookupNative = (LookupNative_)_LookupNative;

typedef int(__fastcall *CGameUI__Constructor_)(GameUI*, LPVOID);
CGameUI__Constructor_ fCGameUI__Constructor = (CGameUI__Constructor_)_CGameUI__Constructor;

typedef Ability*(__fastcall *GetAbility_)(Unit*, LPVOID, int, BOOL, BOOL, BOOL, BOOL);
GetAbility_ fGetAbility = (GetAbility_)_GetAbility;

CGameInterface::CGameInterface()
{
	This = this;
	GetTlsValue();
	InitHooks();
	InitNativeHooks();

	wnd = FindWindow(_T("Warcraft III"), NULL);
}

CGameInterface::~CGameInterface()
{
#ifdef DEBUG
	uint32 nMemoriesFreed = 0;
	CHAR szOut[128];
#endif

	try
	{
		for (auto memory : m_Memory)
			if (memory){
				delete memory;
#ifdef DEBUG
				nMemoriesFreed++;
#endif
			}
	}
	catch (...){ OutputDebugStringA("CGameInterface::~CGameInterface ==> delete failed."); }

#ifdef DEBUG
	sprintf_s(szOut, "CGameInterface::~CGameInterface ==> nMemoriesFreed ==> %i", nMemoriesFreed);
	OutputDebugStringA(szOut);
#endif
}


void CGameInterface::Init(LPVOID pParent)
{
	pJassInterface = (CJassInterface*)pParent;
}

// ----------------------------------
// |		Hooked Functions	    |
// ----------------------------------

int CGameInterface::LookupNative_Hooked(LPSTR FuncName)
{
	int nRet = fLookupNative(FuncName);
	
	if (InGame(true))
		return nRet;

	auto origLen = strlen(FuncName);

	decltype(origLen) newLen = 0;

	for (auto &it : This->m_NativeHooks)
	{
		newLen = strlen(it.FuncName);
		if ((_strnicmp(it.FuncName, FuncName, newLen) == 0) && (newLen == origLen))
		{
			LPSTR funcSig = it.FuncSig;
			LPSTR funcName = it.FuncName;
			LPVOID funcAddr = it.FuncAddr;

			__asm
			{
				push funcSig;
				mov edx, funcName;
				mov ecx, funcAddr;
				call _BindNative;
			}
		}
	}

	return nRet;
}

int CGameInterface::CGameUI__Constructor_Hooked(GameUI *ui /* _ecx */, LPVOID _edx)
{
	int nRet = fCGameUI__Constructor(ui, _edx);

	// ---------------------------------
	// A bit tricky, but it works :)
	// This function is originally __thiscall and since we cannot hook __thiscall functions we use the __fastcall trick to get our variable from stack
	// https://en.wikipedia.org/wiki/X86_calling_conventions#thiscall
	// https://en.wikipedia.org/wiki/X86_calling_conventions#Microsoft_fastcall
	// ---------------------------------

	This->m_GameUI = ui;

	return nRet;
}

void __declspec(naked) HookChatFunc()
{
	__asm
	{
		MOV ESI, EAX;
		TEST ESI, ESI;
		JE orije;
		PUSHAD;
		MOV ChatText, EAX;
	}

	bChatEvent = false;

	if (_strnicmp(ChatText, "/about", strlen("/about")) == 0)
	{
		This->WriteAbout();
		goto popback;
	}
	
	for (auto script : This->m_Scripts)
	{
		if (script != nullptr)
		{
			if (((CLuaScript*)script)->OnChatEvent(ChatText))
				bChatEvent = true;
		}
	}

	if (bChatEvent)
		goto popback;
		
	__asm
	{
		POPAD;
		JMP _MessageFuncBack;
	}

orije:
	__asm JMP _MessageFuncOriJmp;

popback:
	__asm
	{
		POPAD;
		JMP _MessageFuncOriJmp;
	}
}

// ----------------------------------
// |  Our functions to use in lua	|
// ----------------------------------

// ----------------------------------
// |		Custom Functions		|
// ----------------------------------

bool CGameInterface::InGame(bool bPause)
{
	int32 State = This->GetGameStateValue();
	
	if (State == GS_INGAME)
		return true;
	else if (State == GS_PAUSED && bPause)
		return true;

	return false;
}

bool CGameInterface::InGameOrLoadingscreen(bool bPause)
{
	int32 State = This->GetGameStateValue();

	if (State == GS_INGAME || State == GS_LOADING)
		return true;
	else if (State == GS_PAUSED && bPause)
		return true;
	
	return false;
}

void CGameInterface::WriteText(LPCSTR message, int32 frame, float duration)
{
	if (!InGame(true))
		return;

	SimpleMessageFrame *pFrame = nullptr;
	DWORD dwColor = 0xFFFFFFFF;
	DWORD dwDur = *((DWORD*)&duration);

	if (!message)
		message = "(null)";

	switch (frame)
	{
	case FRAME_MESSAGE:
		pFrame = This->m_GameUI->Message;
		break;
	case FRAME_UNIT:
		pFrame = This->m_GameUI->UnitMessage;
		break;
	case FRAME_CHAT:
		pFrame = This->m_GameUI->ChatMessage;
		break;
	case FRAME_TOP:
		pFrame = This->m_GameUI->TopMessage;
		break;
	default:
		pFrame = This->m_GameUI->Message;
	}

	__asm
	{
		push 0;
		push dwDur;
		lea eax, dwColor;
		push eax;
		push message;
		mov ecx, pFrame;
		call _CSimpleMessageFrame__WriteLine;
	}
}

void CGameInterface::ExecuteCmd(unit ounit, DWORD cmdId, float X, float Y, unit target)
{
	if (!InGame(false))
		return;

	Unit* unt = GetSelectedUnit();
	Unit* pOUnit = nullptr;
	Unit* pTarUnit = nullptr;

	if (ounit){
		pOUnit = GetUnitFromHandle(ounit);
		SelectUnit(pOUnit);
	}

	if (!target)
	{
		__asm
		{
			PUSH 0;
			PUSH 6;
			PUSH 0;
			MOV ECX, DWORD PTR DS : [_W3XGlobalClass]
			MOV ECX, DWORD PTR DS : [ECX]
			MOV ECX, DWORD PTR DS : [ECX + 0x1B4];
			PUSH Y;
			PUSH X;
			PUSH 0;
			PUSH cmdId;
			CALL _MoveAttackCmd;
		}
	}
	else
	{
		pTarUnit = GetUnitFromHandle(target);
		__asm
		{
			PUSH 0;
			PUSH 4;
			PUSH pTarUnit;
			PUSH 0;
			PUSH cmdId;
			MOV ECX, DWORD PTR DS : [_W3XGlobalClass]
			MOV ECX, DWORD PTR DS : [ECX]
			MOV ECX, DWORD PTR DS : [ECX + 0x1B4];
			CALL _MoveTargetCmd;
		}
	}

	if (ounit)
		SelectUnit(unt);
}

LPCSTR CGameInterface::GetMapName()
{
	LPCSTR ret = (LPCSTR)_MapName;

	if (ret == NULL)
		return "(null)";
	else if (strcmp(ret, "") == 0)
		return "(null)";

	return ret;
}

luabridge::LuaRef CGameInterface::GetPlugins(lua_State* L)
{
	LuaRef ret = newTable(L);
	int count = 1;

	for (auto script : This->m_Scripts){
		if (script != nullptr){
			ret[count++] = (CLuaScript*)script;
		}
	}
	
	return ret;
}

LPCSTR CGameInterface::jStr2cStr(string JSID)
{
	LPCSTR cRet = nullptr;

	__asm
	{
		push JSID;
		mov ecx, 1;
		call _GetCurrentJassEnvironment;
		mov ecx, eax;
		call _Js2Cs;
		mov ecx, dword ptr ds : [eax + 0x08];
		mov eax, dword ptr ds : [ecx + 0x1C];
		mov cRet, eax;
	}

	if (cRet == nullptr)
		cRet = "(null)";

	return cRet;
}

LPCSTR CGameInterface::jParamStr2cStr(handle hStr)
{
	if (hStr == NULL)
		return "(null)";

	JassString* jString = (JassString*)hStr;

	return (LPCSTR)jString->Value->String;
}

handle CGameInterface::cStr2jStr_lua(LPCSTR szString)
{
	JassString *jStr = new JassString();
	m_Memory.push_back(jStr);

	cStr2jStr(szString, jStr);

	return (handle)jStr;
}

void CGameInterface::cStr2jStr(LPCSTR szString, JassString* String)
{
	__asm
	{
		push szString;
		mov ecx, String;
		call _Cs2Js;
	}
}

float CGameInterface::GetFloat(handle pF)
{
	return *(float*)pF;
}

handle CGameInterface::MakeFloat(float f)
{
	float *pFloat = new float(f);
	m_Memory.push_back(pFloat);

	return (handle)pFloat;
}

int32 CGameInterface::GetAbilityState(unit unt, int abilityID)
{
	Unit* pUnit = GetUnitFromHandle(unt);

	if (pUnit == nullptr)
		return ABILITY_STATE_INVALID;

	Ability* ability = fGetAbility(pUnit, 0, abilityID, FALSE, TRUE, TRUE, TRUE);

	if (ability == nullptr)
		return ABILITY_STATE_INVALID;

	int state = ability->State;

	if (state == 6 || state == 7)
		return ABILITY_STATE_READY;
	else
		return ABILITY_STATE_COOLDOWN;
}

bool CGameInterface::SendChat(std::string message, bool bSendAll)
{
	bool bIsWindowsActive = *(bool*)(_WindowActive);
	bool bIsChatBoxOpen = *(bool*)(_ChatBox);
	DWORD chatOffset = *(DWORD*)_ChatTextPtr;
	void* chatMemory = (void*)(chatOffset + 0x88);

	if (!InGame(true))
		return false;

	if (message.length() > 127)
		message = message.substr(0, 126);

	if (wnd == nullptr)
		return false;

	if (!bIsChatBoxOpen)
	{
		if (bSendAll)
			PostMessage(wnd, WM_KEYDOWN, VK_SHIFT, 0);

		PostMessage(wnd, WM_KEYDOWN, VK_RETURN, 0);

		if (bSendAll)
			PostMessage(wnd, WM_KEYUP, VK_SHIFT, 0);

		PostMessage(wnd, WM_KEYUP, VK_RETURN, 0);
	}

	strcpy_s((char*)chatMemory, 127, message.c_str());

	PostMessage(wnd, WM_KEYDOWN, VK_RETURN, 0);
	PostMessage(wnd, WM_KEYUP, VK_RETURN, 0);

	Sleep(100);

	return true;
}

LPCSTR CGameInterface::GetVersion()
{
	return APP_VERSION_A;
}

// ----------------------------------
// |		  Other Stuff	        |
// ----------------------------------


Unit* CGameInterface::GetUnitFromHandle(unit hUnit)
{
	Unit* pUnit = nullptr;

	__asm
	{
		mov ecx, hUnit;
		call _GetUnitFromHandle; // Unit* __fastcall _GetUnitFromHandle(unit unit_jass_handle)
		mov pUnit, eax;
	}

	return pUnit;
}

Unit* CGameInterface::GetSelectedUnit()
{
	DWORD plr = GetPlayer();
	DWORD rt;
	__asm
	{
		MOV EAX, plr;
		MOV ECX, DWORD PTR DS : [EAX + 0x34];
		MOV EAX, DWORD PTR DS : [ECX + 0x1E0];
		MOV rt, EAX;
	}
	return (Unit*)rt;
}

DWORD CGameInterface::GetPlayerNumber()
{
	DWORD rt;

	__asm
	{
		MOV EAX, DWORD PTR DS : [_W3XPlayerData];
		MOV EAX, DWORD PTR DS : [EAX]
		TEST EAX, EAX;
		JE err;
		MOVZX EAX, WORD PTR DS : [EAX + 0x28];
		MOV rt, EAX;
	}
	return (DWORD)rt;
err:
	return 0;
}

DWORD CGameInterface::GetPlayerByNumber(DWORD plNum)
{
	DWORD rt = 0;
	__asm
	{
		MOV ECX, DWORD PTR DS : [_W3XPlayerData]
			MOV ECX, DWORD PTR DS : [ECX]
			PUSH plNum;
		CALL _GetHPlayerByNumber;
		MOV rt, EAX;
	}
	return rt;
}

DWORD CGameInterface::GetPlayer()
{
	return GetPlayerByNumber(GetPlayerNumber());
}

void CGameInterface::SelectUnit(Unit* unit)
{
	__asm
	{
		MOV EAX, DWORD PTR DS : [_W3XGlobalClass]
		MOV EAX, DWORD PTR DS : [EAX]
		MOV ESI, DWORD PTR DS : [EAX + 0x24C];
		PUSH 0;
		PUSH 0;
		PUSH 0;
		PUSH unit;
		MOV ECX, ESI;
		CALL _UnitSelect;
	}
}

void CGameInterface::WriteAbout()
{
	CStringA out;
	out.Format("|c007EBFF1Warcraft Lua Engine|r |c00FF7F00%s|r by Shahriyar", APP_VERSION_A);
	WriteText(out, FRAME_TOP, 10);
}

int32 CGameInterface::GetGameStateValue(void)
{
	int32 rt = -1;

	auto hProcess = GetCurrentProcess();

	if (!ReadProcessMemory(hProcess, (LPVOID)(TlsValue + 4 * 0x0D), (LPVOID)&rt, 4, NULL))
		return -1;
	if (!ReadProcessMemory(hProcess, (LPVOID)(rt + 0x10), (LPVOID)&rt, 4, NULL))
		return -1;
	if (!ReadProcessMemory(hProcess, (LPVOID)(rt + 0x8), (LPVOID)&rt, 4, NULL))
		return -1;
	if (!ReadProcessMemory(hProcess, (LPVOID)(rt + 0x278), (LPVOID)&rt, 4, NULL))
		return -1;

	return rt;
}

DWORD CGameInterface::GetW3TlsForIndex(DWORD index)
{
	DWORD pid = GetCurrentProcessId();
	THREADENTRY32 te32;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
	te32.dwSize = sizeof(THREADENTRY32);

	if (Thread32First(hSnap, &te32))
	{
		do
		{
			if (te32.th32OwnerProcessID == pid)
			{
				HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, false, te32.th32ThreadID);
				if (hThread == NULL)
					continue;
				CONTEXT ctx = { CONTEXT_SEGMENTS };
				LDT_ENTRY ldt;
				GetThreadContext(hThread, &ctx);
				GetThreadSelectorEntry(hThread, ctx.SegFs, &ldt);
				DWORD dwThreadBase = ldt.BaseLow | (ldt.HighWord.Bytes.BaseMid <<
					16) | (ldt.HighWord.Bytes.BaseHi << 24);
				CloseHandle(hThread);
				if (dwThreadBase == NULL)
					continue;
				DWORD* dwTLS = *(DWORD**)(dwThreadBase + 0xE10 + 4 * index);
				if (dwTLS == NULL)
					continue;
				return (DWORD)dwTLS;
			}
		} while (Thread32Next(hSnap, &te32));
	}

	return NULL;
}

void CGameInterface::GetTlsValue(void)
{
	TlsIndex = *(DWORD*)(_W3XTlsIndex);
	LPVOID tls = (LPVOID)GetW3TlsForIndex(TlsIndex);
	TlsSetValue(TlsIndex, tls);
	TlsValue = (DWORD)tls;
}

void CGameInterface::InitNativeHooks(void)
{
	This->m_NativeHooks.clear();

	This->m_NativeHooks.push_back(JassNative("DebugS", "(S)V", pJassInterface->Jass_DebugS_Hooked));
	This->m_NativeHooks.push_back(JassNative("DebugFI", "(SI)V", pJassInterface->Jass_DebugFI_Hooked));
	This->m_NativeHooks.push_back(JassNative("DebugUnitID", "(SI)V", pJassInterface->Jass_DebugUnitID_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisplayText", "(IS)V", pJassInterface->Jass_DisplayText_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisplayTextI", "(ISI)V", pJassInterface->Jass_DisplayTextI_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisplayTextII", "(ISII)V", pJassInterface->Jass_DisplayTextII_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisplayTextIII", "(ISIII)V", pJassInterface->Jass_DisplayTextIII_Hooked));
	This->m_NativeHooks.push_back(JassNative("SuicideUnit", "(II)V", pJassInterface->Jass_SuicideUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("SuicideUnitEx", "(III)V", pJassInterface->Jass_SuicideUnitEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("Sleep", "(R)V", pJassInterface->Jass_Sleep_Hooked));
	This->m_NativeHooks.push_back(JassNative("StartThread", "(C)V", pJassInterface->Jass_StartThread_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetAiPlayer", "()I", pJassInterface->Jass_GetAiPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("DoAiScriptDebug", "()B", pJassInterface->Jass_DoAiScriptDebug_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHeroId", "()I", pJassInterface->Jass_GetHeroId_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHeroLevelAI", "()I", pJassInterface->Jass_GetHeroLevelAI_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetHeroLevels", "(C)V", pJassInterface->Jass_SetHeroLevels_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetNewHeroes", "(B)V", pJassInterface->Jass_SetNewHeroes_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitCount", "(I)I", pJassInterface->Jass_GetUnitCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerUnitTypeCount", "(Hplayer;I)I", pJassInterface->Jass_GetPlayerUnitTypeCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTownUnitCount", "(IIB)I", pJassInterface->Jass_GetTownUnitCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitCountDone", "(I)I", pJassInterface->Jass_GetUnitCountDone_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUpgradeLevel", "(I)I", pJassInterface->Jass_GetUpgradeLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitGoldCost", "(I)I", pJassInterface->Jass_GetUnitGoldCost_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitWoodCost", "(I)I", pJassInterface->Jass_GetUnitWoodCost_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitBuildTime", "(I)I", pJassInterface->Jass_GetUnitBuildTime_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUpgradeGoldCost", "(I)I", pJassInterface->Jass_GetUpgradeGoldCost_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUpgradeWoodCost", "(I)I", pJassInterface->Jass_GetUpgradeWoodCost_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEnemyPower", "()I", pJassInterface->Jass_GetEnemyPower_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetMinesOwned", "()I", pJassInterface->Jass_GetMinesOwned_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetGoldOwned", "()I", pJassInterface->Jass_GetGoldOwned_Hooked));
	This->m_NativeHooks.push_back(JassNative("TownWithMine", "()I", pJassInterface->Jass_TownWithMine_Hooked));
	This->m_NativeHooks.push_back(JassNative("TownHasMine", "(I)B", pJassInterface->Jass_TownHasMine_Hooked));
	This->m_NativeHooks.push_back(JassNative("TownHasHall", "(I)B", pJassInterface->Jass_TownHasHall_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetNextExpansion", "()I", pJassInterface->Jass_GetNextExpansion_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetExpansionPeon", "()Hunit;", pJassInterface->Jass_GetExpansionPeon_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEnemyExpansion", "()Hunit;", pJassInterface->Jass_GetEnemyExpansion_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetExpansion", "(Hunit;I)B", pJassInterface->Jass_SetExpansion_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetBuilding", "(Hplayer;)Hunit;", pJassInterface->Jass_GetBuilding_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetAllianceTarget", "(Hunit;)V", pJassInterface->Jass_SetAllianceTarget_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetAllianceTarget", "()Hunit;", pJassInterface->Jass_GetAllianceTarget_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetProduce", "(III)B", pJassInterface->Jass_SetProduce_Hooked));
	This->m_NativeHooks.push_back(JassNative("MergeUnits", "(IIII)B", pJassInterface->Jass_MergeUnits_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertUnits", "(II)B", pJassInterface->Jass_ConvertUnits_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUpgrade", "(I)B", pJassInterface->Jass_SetUpgrade_Hooked));
	This->m_NativeHooks.push_back(JassNative("Unsummon", "(Hunit;)V", pJassInterface->Jass_Unsummon_Hooked));
	This->m_NativeHooks.push_back(JassNative("ClearHarvestAI", "()V", pJassInterface->Jass_ClearHarvestAI_Hooked));
	This->m_NativeHooks.push_back(JassNative("HarvestGold", "(II)V", pJassInterface->Jass_HarvestGold_Hooked));
	This->m_NativeHooks.push_back(JassNative("HarvestWood", "(II)V", pJassInterface->Jass_HarvestWood_Hooked));
	This->m_NativeHooks.push_back(JassNative("StopGathering", "()V", pJassInterface->Jass_StopGathering_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddGuardPost", "(IRR)V", pJassInterface->Jass_AddGuardPost_Hooked));
	This->m_NativeHooks.push_back(JassNative("FillGuardPosts", "()V", pJassInterface->Jass_FillGuardPosts_Hooked));
	This->m_NativeHooks.push_back(JassNative("ReturnGuardPosts", "()V", pJassInterface->Jass_ReturnGuardPosts_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateCaptains", "()V", pJassInterface->Jass_CreateCaptains_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCaptainHome", "(IRR)V", pJassInterface->Jass_SetCaptainHome_Hooked));
	This->m_NativeHooks.push_back(JassNative("ResetCaptainLocs", "()V", pJassInterface->Jass_ResetCaptainLocs_Hooked));
	This->m_NativeHooks.push_back(JassNative("ShiftTownSpot", "(RR)V", pJassInterface->Jass_ShiftTownSpot_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCaptainChanges", "(B)V", pJassInterface->Jass_SetCaptainChanges_Hooked));
	This->m_NativeHooks.push_back(JassNative("TeleportCaptain", "(RR)V", pJassInterface->Jass_TeleportCaptain_Hooked));
	This->m_NativeHooks.push_back(JassNative("ClearCaptainTargets", "()V", pJassInterface->Jass_ClearCaptainTargets_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainVsUnits", "(Hplayer;)V", pJassInterface->Jass_CaptainVsUnits_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainVsPlayer", "(Hplayer;)V", pJassInterface->Jass_CaptainVsPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainAttack", "(RR)V", pJassInterface->Jass_CaptainAttack_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupTimedLife", "(B)V", pJassInterface->Jass_GroupTimedLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainGoHome", "()V", pJassInterface->Jass_CaptainGoHome_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainIsHome", "()B", pJassInterface->Jass_CaptainIsHome_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainRetreating", "()B", pJassInterface->Jass_CaptainRetreating_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainIsFull", "()B", pJassInterface->Jass_CaptainIsFull_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainIsEmpty", "()B", pJassInterface->Jass_CaptainIsEmpty_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainGroupSize", "()I", pJassInterface->Jass_CaptainGroupSize_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainReadiness", "()I", pJassInterface->Jass_CaptainReadiness_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainReadinessHP", "()I", pJassInterface->Jass_CaptainReadinessHP_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainReadinessMa", "()I", pJassInterface->Jass_CaptainReadinessMa_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainInCombat", "(B)B", pJassInterface->Jass_CaptainInCombat_Hooked));
	This->m_NativeHooks.push_back(JassNative("TownThreatened", "()B", pJassInterface->Jass_TownThreatened_Hooked));
	This->m_NativeHooks.push_back(JassNative("CaptainAtGoal", "()B", pJassInterface->Jass_CaptainAtGoal_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreepsOnMap", "()B", pJassInterface->Jass_CreepsOnMap_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveInjuries", "()V", pJassInterface->Jass_RemoveInjuries_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveSiege", "()V", pJassInterface->Jass_RemoveSiege_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsTowered", "(Hunit;)B", pJassInterface->Jass_IsTowered_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisablePathing", "()V", pJassInterface->Jass_DisablePathing_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetAmphibious", "()V", pJassInterface->Jass_SetAmphibious_Hooked));
	This->m_NativeHooks.push_back(JassNative("InitAssault", "()V", pJassInterface->Jass_InitAssault_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddAssault", "(II)B", pJassInterface->Jass_AddAssault_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddDefenders", "(II)B", pJassInterface->Jass_AddDefenders_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCreepCamp", "(IIB)Hunit;", pJassInterface->Jass_GetCreepCamp_Hooked));
	This->m_NativeHooks.push_back(JassNative("StartGetEnemyBase", "()V", pJassInterface->Jass_StartGetEnemyBase_Hooked));
	This->m_NativeHooks.push_back(JassNative("WaitGetEnemyBase", "()B", pJassInterface->Jass_WaitGetEnemyBase_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetMegaTarget", "()Hunit;", pJassInterface->Jass_GetMegaTarget_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEnemyBase", "()Hunit;", pJassInterface->Jass_GetEnemyBase_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetExpansionFoe", "()Hunit;", pJassInterface->Jass_GetExpansionFoe_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetExpansionX", "()I", pJassInterface->Jass_GetExpansionX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetExpansionY", "()I", pJassInterface->Jass_GetExpansionY_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetStagePoint", "(RR)V", pJassInterface->Jass_SetStagePoint_Hooked));
	This->m_NativeHooks.push_back(JassNative("AttackMoveKill", "(Hunit;)V", pJassInterface->Jass_AttackMoveKill_Hooked));
	This->m_NativeHooks.push_back(JassNative("AttackMoveXY", "(II)V", pJassInterface->Jass_AttackMoveXY_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadZepWave", "(II)V", pJassInterface->Jass_LoadZepWave_Hooked));
	This->m_NativeHooks.push_back(JassNative("SuicidePlayer", "(Hplayer;B)B", pJassInterface->Jass_SuicidePlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("SuicidePlayerUnits", "(Hplayer;B)B", pJassInterface->Jass_SuicidePlayerUnits_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitAlive", "(Hunit;)B", pJassInterface->Jass_UnitAlive_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitInvis", "(Hunit;)B", pJassInterface->Jass_UnitInvis_Hooked));
	This->m_NativeHooks.push_back(JassNative("IgnoredUnits", "(I)I", pJassInterface->Jass_IgnoredUnits_Hooked));
	This->m_NativeHooks.push_back(JassNative("CommandsWaiting", "()I", pJassInterface->Jass_CommandsWaiting_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLastCommand", "()I", pJassInterface->Jass_GetLastCommand_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLastData", "()I", pJassInterface->Jass_GetLastData_Hooked));
	This->m_NativeHooks.push_back(JassNative("PopLastCommand", "()V", pJassInterface->Jass_PopLastCommand_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCampaignAI", "()V", pJassInterface->Jass_SetCampaignAI_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetMeleeAI", "()V", pJassInterface->Jass_SetMeleeAI_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTargetHeroes", "(B)V", pJassInterface->Jass_SetTargetHeroes_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetHeroesFlee", "(B)V", pJassInterface->Jass_SetHeroesFlee_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetHeroesBuyItems", "(B)V", pJassInterface->Jass_SetHeroesBuyItems_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetIgnoreInjured", "(B)V", pJassInterface->Jass_SetIgnoreInjured_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPeonsRepair", "(B)V", pJassInterface->Jass_SetPeonsRepair_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetRandomPaths", "(B)V", pJassInterface->Jass_SetRandomPaths_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDefendPlayer", "(B)V", pJassInterface->Jass_SetDefendPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetHeroesTakeItems", "(B)V", pJassInterface->Jass_SetHeroesTakeItems_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitsFlee", "(B)V", pJassInterface->Jass_SetUnitsFlee_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetGroupsFlee", "(B)V", pJassInterface->Jass_SetGroupsFlee_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSlowChopping", "(B)V", pJassInterface->Jass_SetSlowChopping_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSmartArtillery", "(B)V", pJassInterface->Jass_SetSmartArtillery_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetWatchMegaTargets", "(B)V", pJassInterface->Jass_SetWatchMegaTargets_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetReplacementCount", "(I)V", pJassInterface->Jass_SetReplacementCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("PurchaseZeppelin", "()V", pJassInterface->Jass_PurchaseZeppelin_Hooked));
	This->m_NativeHooks.push_back(JassNative("MeleeDifficulty", "()I", pJassInterface->Jass_MeleeDifficulty_Hooked));
	This->m_NativeHooks.push_back(JassNative("DebugBreak", "(I)V", pJassInterface->Jass_DebugBreak_Hooked));
	This->m_NativeHooks.push_back(JassNative("Deg2Rad", "(R)R", pJassInterface->Jass_Deg2Rad_Hooked));
	This->m_NativeHooks.push_back(JassNative("Rad2Deg", "(R)R", pJassInterface->Jass_Rad2Deg_Hooked));
	This->m_NativeHooks.push_back(JassNative("Sin", "(R)R", pJassInterface->Jass_Sin_Hooked));
	This->m_NativeHooks.push_back(JassNative("Cos", "(R)R", pJassInterface->Jass_Cos_Hooked));
	This->m_NativeHooks.push_back(JassNative("Tan", "(R)R", pJassInterface->Jass_Tan_Hooked));
	This->m_NativeHooks.push_back(JassNative("Asin", "(R)R", pJassInterface->Jass_Asin_Hooked));
	This->m_NativeHooks.push_back(JassNative("Acos", "(R)R", pJassInterface->Jass_Acos_Hooked));
	This->m_NativeHooks.push_back(JassNative("Atan", "(R)R", pJassInterface->Jass_Atan_Hooked));
	This->m_NativeHooks.push_back(JassNative("Atan2", "(RR)R", pJassInterface->Jass_Atan2_Hooked));
	This->m_NativeHooks.push_back(JassNative("SquareRoot", "(R)R", pJassInterface->Jass_SquareRoot_Hooked));
	This->m_NativeHooks.push_back(JassNative("Pow", "(RR)R", pJassInterface->Jass_Pow_Hooked));
	This->m_NativeHooks.push_back(JassNative("I2R", "(I)R", pJassInterface->Jass_I2R_Hooked));
	This->m_NativeHooks.push_back(JassNative("R2I", "(R)I", pJassInterface->Jass_R2I_Hooked));
	This->m_NativeHooks.push_back(JassNative("I2S", "(I)S", pJassInterface->Jass_I2S_Hooked));
	This->m_NativeHooks.push_back(JassNative("R2S", "(R)S", pJassInterface->Jass_R2S_Hooked));
	This->m_NativeHooks.push_back(JassNative("R2SW", "(RII)S", pJassInterface->Jass_R2SW_Hooked));
	This->m_NativeHooks.push_back(JassNative("S2I", "(S)I", pJassInterface->Jass_S2I_Hooked));
	This->m_NativeHooks.push_back(JassNative("S2R", "(S)R", pJassInterface->Jass_S2R_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHandleId", "(Hhandle;)I", pJassInterface->Jass_GetHandleId_Hooked));
	This->m_NativeHooks.push_back(JassNative("SubString", "(SII)S", pJassInterface->Jass_SubString_Hooked));
	This->m_NativeHooks.push_back(JassNative("StringLength", "(S)I", pJassInterface->Jass_StringLength_Hooked));
	This->m_NativeHooks.push_back(JassNative("StringCase", "(SB)S", pJassInterface->Jass_StringCase_Hooked));
	This->m_NativeHooks.push_back(JassNative("StringHash", "(S)I", pJassInterface->Jass_StringHash_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLocalizedString", "(S)S", pJassInterface->Jass_GetLocalizedString_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLocalizedHotkey", "(S)I", pJassInterface->Jass_GetLocalizedHotkey_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertRace", "(I)Hrace;", pJassInterface->Jass_ConvertRace_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertAllianceType", "(I)Halliancetype;", pJassInterface->Jass_ConvertAllianceType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertRacePref", "(I)Hracepreference;", pJassInterface->Jass_ConvertRacePref_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertIGameState", "(I)Higamestate;", pJassInterface->Jass_ConvertIGameState_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertFGameState", "(I)Hfgamestate;", pJassInterface->Jass_ConvertFGameState_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertPlayerState", "(I)Hplayerstate;", pJassInterface->Jass_ConvertPlayerState_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertPlayerScore", "(I)Hplayerscore;", pJassInterface->Jass_ConvertPlayerScore_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertStartLocPrio", "(I)Hstartlocprio;", pJassInterface->Jass_ConvertStartLocPrio_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertPlayerGameResult", "(I)Hplayergameresult;", pJassInterface->Jass_ConvertPlayerGameResult_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertUnitState", "(I)Hunitstate;", pJassInterface->Jass_ConvertUnitState_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertAIDifficulty", "(I)Haidifficulty;", pJassInterface->Jass_ConvertAIDifficulty_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertGameEvent", "(I)Hgameevent;", pJassInterface->Jass_ConvertGameEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertPlayerEvent", "(I)Hplayerevent;", pJassInterface->Jass_ConvertPlayerEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertPlayerUnitEvent", "(I)Hplayerunitevent;", pJassInterface->Jass_ConvertPlayerUnitEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertUnitEvent", "(I)Hunitevent;", pJassInterface->Jass_ConvertUnitEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertWidgetEvent", "(I)Hwidgetevent;", pJassInterface->Jass_ConvertWidgetEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertDialogEvent", "(I)Hdialogevent;", pJassInterface->Jass_ConvertDialogEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertLimitOp", "(I)Hlimitop;", pJassInterface->Jass_ConvertLimitOp_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertUnitType", "(I)Hunittype;", pJassInterface->Jass_ConvertUnitType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertGameSpeed", "(I)Hgamespeed;", pJassInterface->Jass_ConvertGameSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertPlacement", "(I)Hplacement;", pJassInterface->Jass_ConvertPlacement_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertGameDifficulty", "(I)Hgamedifficulty;", pJassInterface->Jass_ConvertGameDifficulty_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertGameType", "(I)Hgametype;", pJassInterface->Jass_ConvertGameType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertMapFlag", "(I)Hmapflag;", pJassInterface->Jass_ConvertMapFlag_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertMapVisibility", "(I)Hmapvisibility;", pJassInterface->Jass_ConvertMapVisibility_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertMapSetting", "(I)Hmapsetting;", pJassInterface->Jass_ConvertMapSetting_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertMapDensity", "(I)Hmapdensity;", pJassInterface->Jass_ConvertMapDensity_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertMapControl", "(I)Hmapcontrol;", pJassInterface->Jass_ConvertMapControl_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertPlayerColor", "(I)Hplayercolor;", pJassInterface->Jass_ConvertPlayerColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertPlayerSlotState", "(I)Hplayerslotstate;", pJassInterface->Jass_ConvertPlayerSlotState_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertVolumeGroup", "(I)Hvolumegroup;", pJassInterface->Jass_ConvertVolumeGroup_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertCameraField", "(I)Hcamerafield;", pJassInterface->Jass_ConvertCameraField_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertBlendMode", "(I)Hblendmode;", pJassInterface->Jass_ConvertBlendMode_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertRarityControl", "(I)Hraritycontrol;", pJassInterface->Jass_ConvertRarityControl_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertTexMapFlags", "(I)Htexmapflags;", pJassInterface->Jass_ConvertTexMapFlags_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertFogState", "(I)Hfogstate;", pJassInterface->Jass_ConvertFogState_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertEffectType", "(I)Heffecttype;", pJassInterface->Jass_ConvertEffectType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertVersion", "(I)Hversion;", pJassInterface->Jass_ConvertVersion_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertItemType", "(I)Hitemtype;", pJassInterface->Jass_ConvertItemType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertAttackType", "(I)Hattacktype;", pJassInterface->Jass_ConvertAttackType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertDamageType", "(I)Hdamagetype;", pJassInterface->Jass_ConvertDamageType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertWeaponType", "(I)Hweapontype;", pJassInterface->Jass_ConvertWeaponType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertSoundType", "(I)Hsoundtype;", pJassInterface->Jass_ConvertSoundType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ConvertPathingType", "(I)Hpathingtype;", pJassInterface->Jass_ConvertPathingType_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetMapName", "(S)V", pJassInterface->Jass_SetMapName_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetMapDescription", "(S)V", pJassInterface->Jass_SetMapDescription_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTeams", "(I)V", pJassInterface->Jass_SetTeams_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayers", "(I)V", pJassInterface->Jass_SetPlayers_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetGameTypeSupported", "(Hgametype;B)V", pJassInterface->Jass_SetGameTypeSupported_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetMapFlag", "(Hmapflag;B)V", pJassInterface->Jass_SetMapFlag_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetGameSpeed", "(Hgamespeed;)V", pJassInterface->Jass_SetGameSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetGamePlacement", "(Hplacement;)V", pJassInterface->Jass_SetGamePlacement_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetGameDifficulty", "(Hgamedifficulty;)V", pJassInterface->Jass_SetGameDifficulty_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetResourceDensity", "(Hmapdensity;)V", pJassInterface->Jass_SetResourceDensity_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCreatureDensity", "(Hmapdensity;)V", pJassInterface->Jass_SetCreatureDensity_Hooked));
	This->m_NativeHooks.push_back(JassNative("DefineStartLocation", "(IRR)V", pJassInterface->Jass_DefineStartLocation_Hooked));
	This->m_NativeHooks.push_back(JassNative("DefineStartLocationLoc", "(IHlocation;)V", pJassInterface->Jass_DefineStartLocationLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetStartLocPrioCount", "(II)V", pJassInterface->Jass_SetStartLocPrioCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetStartLocPrio", "(IIIHstartlocprio;)V", pJassInterface->Jass_SetStartLocPrio_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetStartLocPrioSlot", "(II)I", pJassInterface->Jass_GetStartLocPrioSlot_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetStartLocPrio", "(II)Hstartlocprio;", pJassInterface->Jass_GetStartLocPrio_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTeams", "()I", pJassInterface->Jass_GetTeams_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayers", "()I", pJassInterface->Jass_GetPlayers_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsGameTypeSupported", "(Hgametype;)B", pJassInterface->Jass_IsGameTypeSupported_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsMapFlagSet", "(Hmapflag;)B", pJassInterface->Jass_IsMapFlagSet_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetGameTypeSelected", "()Hgametype;", pJassInterface->Jass_GetGameTypeSelected_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetGamePlacement", "()Hplacement;", pJassInterface->Jass_GetGamePlacement_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetGameSpeed", "()Hgamespeed;", pJassInterface->Jass_GetGameSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetGameDifficulty", "()Hgamedifficulty;", pJassInterface->Jass_GetGameDifficulty_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetResourceDensity", "()Hmapdensity;", pJassInterface->Jass_GetResourceDensity_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCreatureDensity", "()Hmapdensity;", pJassInterface->Jass_GetCreatureDensity_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetStartLocationX", "(I)R", pJassInterface->Jass_GetStartLocationX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetStartLocationY", "(I)R", pJassInterface->Jass_GetStartLocationY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetStartLocationLoc", "(I)Hlocation;", pJassInterface->Jass_GetStartLocationLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerTeam", "(Hplayer;I)V", pJassInterface->Jass_SetPlayerTeam_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerStartLocation", "(Hplayer;I)V", pJassInterface->Jass_SetPlayerStartLocation_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForcePlayerStartLocation", "(Hplayer;I)V", pJassInterface->Jass_ForcePlayerStartLocation_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerAlliance", "(Hplayer;Hplayer;Halliancetype;B)V", pJassInterface->Jass_SetPlayerAlliance_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerTaxRate", "(Hplayer;Hplayer;Hplayerstate;I)V", pJassInterface->Jass_SetPlayerTaxRate_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerRacePreference", "(Hplayer;Hracepreference;)V", pJassInterface->Jass_SetPlayerRacePreference_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerRaceSelectable", "(Hplayer;B)V", pJassInterface->Jass_SetPlayerRaceSelectable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerController", "(Hplayer;Hmapcontrol;)V", pJassInterface->Jass_SetPlayerController_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerColor", "(Hplayer;Hplayercolor;)V", pJassInterface->Jass_SetPlayerColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerOnScoreScreen", "(Hplayer;B)V", pJassInterface->Jass_SetPlayerOnScoreScreen_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerName", "(Hplayer;S)V", pJassInterface->Jass_SetPlayerName_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerTeam", "(Hplayer;)I", pJassInterface->Jass_GetPlayerTeam_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerName", "(Hplayer;)S", pJassInterface->Jass_GetPlayerName_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerStartLocation", "(Hplayer;)I", pJassInterface->Jass_GetPlayerStartLocation_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerStartLocationX", "(Hplayer;)R", pJassInterface->Jass_GetPlayerStartLocationX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerStartLocationY", "(Hplayer;)R", pJassInterface->Jass_GetPlayerStartLocationY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerColor", "(Hplayer;)Hplayercolor;", pJassInterface->Jass_GetPlayerColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerSelectable", "(Hplayer;)B", pJassInterface->Jass_GetPlayerSelectable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerController", "(Hplayer;)Hmapcontrol;", pJassInterface->Jass_GetPlayerController_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerSlotState", "(Hplayer;)Hplayerslotstate;", pJassInterface->Jass_GetPlayerSlotState_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerTaxRate", "(Hplayer;Hplayer;Hplayerstate;)I", pJassInterface->Jass_GetPlayerTaxRate_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsPlayerRacePrefSet", "(Hplayer;Hracepreference;)B", pJassInterface->Jass_IsPlayerRacePrefSet_Hooked));
	This->m_NativeHooks.push_back(JassNative("Location", "(RR)Hlocation;", pJassInterface->Jass_Location_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveLocation", "(Hlocation;)V", pJassInterface->Jass_RemoveLocation_Hooked));
	This->m_NativeHooks.push_back(JassNative("MoveLocation", "(Hlocation;RR)V", pJassInterface->Jass_MoveLocation_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLocationX", "(Hlocation;)R", pJassInterface->Jass_GetLocationX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLocationY", "(Hlocation;)R", pJassInterface->Jass_GetLocationY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLocationZ", "(Hlocation;)R", pJassInterface->Jass_GetLocationZ_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateTimer", "()Htimer;", pJassInterface->Jass_CreateTimer_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyTimer", "(Htimer;)V", pJassInterface->Jass_DestroyTimer_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerStart", "(Htimer;RBC)V", pJassInterface->Jass_TimerStart_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerGetTimeout", "(Htimer;)R", pJassInterface->Jass_TimerGetTimeout_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerGetElapsed", "(Htimer;)R", pJassInterface->Jass_TimerGetElapsed_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerGetRemaining", "(Htimer;)R", pJassInterface->Jass_TimerGetRemaining_Hooked));
	This->m_NativeHooks.push_back(JassNative("PauseTimer", "(Htimer;)V", pJassInterface->Jass_PauseTimer_Hooked));
	This->m_NativeHooks.push_back(JassNative("ResumeTimer", "(Htimer;)V", pJassInterface->Jass_ResumeTimer_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetExpiredTimer", "()Htimer;", pJassInterface->Jass_GetExpiredTimer_Hooked));
	This->m_NativeHooks.push_back(JassNative("Condition", "(C)Hconditionfunc;", pJassInterface->Jass_Condition_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyCondition", "(Hconditionfunc;)V", pJassInterface->Jass_DestroyCondition_Hooked));
	This->m_NativeHooks.push_back(JassNative("Filter", "(C)Hfilterfunc;", pJassInterface->Jass_Filter_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyFilter", "(Hfilterfunc;)V", pJassInterface->Jass_DestroyFilter_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyBoolExpr", "(Hboolexpr;)V", pJassInterface->Jass_DestroyBoolExpr_Hooked));
	This->m_NativeHooks.push_back(JassNative("And", "(Hboolexpr;Hboolexpr;)Hboolexpr;", pJassInterface->Jass_And_Hooked));
	This->m_NativeHooks.push_back(JassNative("Or", "(Hboolexpr;Hboolexpr;)Hboolexpr;", pJassInterface->Jass_Or_Hooked));
	This->m_NativeHooks.push_back(JassNative("Not", "(Hboolexpr;)Hboolexpr;", pJassInterface->Jass_Not_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateRegion", "()Hregion;", pJassInterface->Jass_CreateRegion_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveRegion", "(Hregion;)V", pJassInterface->Jass_RemoveRegion_Hooked));
	This->m_NativeHooks.push_back(JassNative("RegionAddRect", "(Hregion;Hrect;)V", pJassInterface->Jass_RegionAddRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("RegionClearRect", "(Hregion;Hrect;)V", pJassInterface->Jass_RegionClearRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("RegionAddCell", "(Hregion;RR)V", pJassInterface->Jass_RegionAddCell_Hooked));
	This->m_NativeHooks.push_back(JassNative("RegionAddCellAtLoc", "(Hregion;Hlocation;)V", pJassInterface->Jass_RegionAddCellAtLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("RegionClearCell", "(Hregion;RR)V", pJassInterface->Jass_RegionClearCell_Hooked));
	This->m_NativeHooks.push_back(JassNative("RegionClearCellAtLoc", "(Hregion;Hlocation;)V", pJassInterface->Jass_RegionClearCellAtLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitInRegion", "(Hregion;Hunit;)B", pJassInterface->Jass_IsUnitInRegion_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsPointInRegion", "(Hregion;RR)B", pJassInterface->Jass_IsPointInRegion_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsLocationInRegion", "(Hregion;Hlocation;)B", pJassInterface->Jass_IsLocationInRegion_Hooked));
	This->m_NativeHooks.push_back(JassNative("Rect", "(RRRR)Hrect;", pJassInterface->Jass_Rect_Hooked));
	This->m_NativeHooks.push_back(JassNative("RectFromLoc", "(Hlocation;Hlocation;)Hrect;", pJassInterface->Jass_RectFromLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveRect", "(Hrect;)V", pJassInterface->Jass_RemoveRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetRect", "(Hrect;RRRR)V", pJassInterface->Jass_SetRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetRectFromLoc", "(Hrect;Hlocation;Hlocation;)V", pJassInterface->Jass_SetRectFromLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRectCenterX", "(Hrect;)R", pJassInterface->Jass_GetRectCenterX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRectCenterY", "(Hrect;)R", pJassInterface->Jass_GetRectCenterY_Hooked));
	This->m_NativeHooks.push_back(JassNative("MoveRectTo", "(Hrect;RR)V", pJassInterface->Jass_MoveRectTo_Hooked));
	This->m_NativeHooks.push_back(JassNative("MoveRectToLoc", "(Hrect;Hlocation;)V", pJassInterface->Jass_MoveRectToLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRectMinX", "(Hrect;)R", pJassInterface->Jass_GetRectMinX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRectMinY", "(Hrect;)R", pJassInterface->Jass_GetRectMinY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRectMaxX", "(Hrect;)R", pJassInterface->Jass_GetRectMaxX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRectMaxY", "(Hrect;)R", pJassInterface->Jass_GetRectMaxY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetWorldBounds", "()Hrect;", pJassInterface->Jass_GetWorldBounds_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetFogStateRect", "(Hplayer;Hfogstate;Hrect;B)V", pJassInterface->Jass_SetFogStateRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetFogStateRadius", "(Hplayer;Hfogstate;RRRB)V", pJassInterface->Jass_SetFogStateRadius_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetFogStateRadiusLoc", "(Hplayer;Hfogstate;Hlocation;RB)V", pJassInterface->Jass_SetFogStateRadiusLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("FogMaskEnable", "(B)V", pJassInterface->Jass_FogMaskEnable_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsFogMaskEnabled", "()B", pJassInterface->Jass_IsFogMaskEnabled_Hooked));
	This->m_NativeHooks.push_back(JassNative("FogEnable", "(B)V", pJassInterface->Jass_FogEnable_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsFogEnabled", "()B", pJassInterface->Jass_IsFogEnabled_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateFogModifierRect", "(Hplayer;Hfogstate;Hrect;BB)Hfogmodifier;", pJassInterface->Jass_CreateFogModifierRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateFogModifierRadius", "(Hplayer;Hfogstate;RRRBB)Hfogmodifier;", pJassInterface->Jass_CreateFogModifierRadius_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateFogModifierRadiusLoc", "(Hplayer;Hfogstate;Hlocation;RBB)Hfogmodifier;", pJassInterface->Jass_CreateFogModifierRadiusLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyFogModifier", "(Hfogmodifier;)V", pJassInterface->Jass_DestroyFogModifier_Hooked));
	This->m_NativeHooks.push_back(JassNative("FogModifierStart", "(Hfogmodifier;)V", pJassInterface->Jass_FogModifierStart_Hooked));
	This->m_NativeHooks.push_back(JassNative("FogModifierStop", "(Hfogmodifier;)V", pJassInterface->Jass_FogModifierStop_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateTrigger", "()Htrigger;", pJassInterface->Jass_CreateTrigger_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyTrigger", "(Htrigger;)V", pJassInterface->Jass_DestroyTrigger_Hooked));
	This->m_NativeHooks.push_back(JassNative("ResetTrigger", "(Htrigger;)V", pJassInterface->Jass_ResetTrigger_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnableTrigger", "(Htrigger;)V", pJassInterface->Jass_EnableTrigger_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisableTrigger", "(Htrigger;)V", pJassInterface->Jass_DisableTrigger_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsTriggerEnabled", "(Htrigger;)B", pJassInterface->Jass_IsTriggerEnabled_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerWaitOnSleeps", "(Htrigger;B)V", pJassInterface->Jass_TriggerWaitOnSleeps_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsTriggerWaitOnSleeps", "(Htrigger;)B", pJassInterface->Jass_IsTriggerWaitOnSleeps_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterVariableEvent", "(Htrigger;SHlimitop;R)Hevent;", pJassInterface->Jass_TriggerRegisterVariableEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterTimerEvent", "(Htrigger;RB)Hevent;", pJassInterface->Jass_TriggerRegisterTimerEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterTimerExpireEvent", "(Htrigger;Htimer;)Hevent;", pJassInterface->Jass_TriggerRegisterTimerExpireEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterGameStateEvent", "(Htrigger;Hgamestate;Hlimitop;R)Hevent;", pJassInterface->Jass_TriggerRegisterGameStateEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEventGameState", "()Hgamestate;", pJassInterface->Jass_GetEventGameState_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterDialogEvent", "(Htrigger;Hdialog;)Hevent;", pJassInterface->Jass_TriggerRegisterDialogEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterDialogButtonEvent", "(Htrigger;Hbutton;)Hevent;", pJassInterface->Jass_TriggerRegisterDialogButtonEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetClickedButton", "()Hbutton;", pJassInterface->Jass_GetClickedButton_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetClickedDialog", "()Hdialog;", pJassInterface->Jass_GetClickedDialog_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTournamentFinishSoonTimeRemaining", "()R;", pJassInterface->Jass_GetTournamentFinishSoonTimeRemaining_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTournamentFinishNowRule", "()I;", pJassInterface->Jass_GetTournamentFinishNowRule_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTournamentFinishNowPlayer", "()Hplayer;", pJassInterface->Jass_GetTournamentFinishNowPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTournamentScore", "(Hplayer;)I", pJassInterface->Jass_GetTournamentScore_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSaveBasicFilename", "()S", pJassInterface->Jass_GetSaveBasicFilename_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterGameEvent", "(Htrigger;Hgameevent;)Hevent;", pJassInterface->Jass_TriggerRegisterGameEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetWinningPlayer", "()Hplayer;", pJassInterface->Jass_GetWinningPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterPlayerStateEvent", "(Htrigger;Hplayer;Hplayerstate;Hlimitop;R)Hevent;", pJassInterface->Jass_TriggerRegisterPlayerStateEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEventPlayerState", "()Hplayerstate;", pJassInterface->Jass_GetEventPlayerState_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterPlayerEvent", "(Htrigger;Hplayer;Hplayerevent;)Hevent;", pJassInterface->Jass_TriggerRegisterPlayerEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterPlayerUnitEvent", "(Htrigger;Hplayer;Hplayerunitevent;Hboolexpr;)Hevent;", pJassInterface->Jass_TriggerRegisterPlayerUnitEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetAttacker", "()Hunit;", pJassInterface->Jass_GetAttacker_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRescuer", "()Hunit;", pJassInterface->Jass_GetRescuer_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDyingUnit", "()Hunit;", pJassInterface->Jass_GetDyingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetKillingUnit", "()Hunit;", pJassInterface->Jass_GetKillingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDecayingUnit", "()Hunit;", pJassInterface->Jass_GetDecayingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetConstructingStructure", "()Hunit;", pJassInterface->Jass_GetConstructingStructure_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCancelledStructure", "()Hunit;", pJassInterface->Jass_GetCancelledStructure_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetConstructedStructure", "()Hunit;", pJassInterface->Jass_GetConstructedStructure_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTrainedUnitType", "()I", pJassInterface->Jass_GetTrainedUnitType_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetResearchingUnit", "()Hunit;", pJassInterface->Jass_GetResearchingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetResearched", "()I", pJassInterface->Jass_GetResearched_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTrainedUnit", "()Hunit;", pJassInterface->Jass_GetTrainedUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSellingUnit", "()Hunit;", pJassInterface->Jass_GetSellingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSoldUnit", "()Hunit;", pJassInterface->Jass_GetSoldUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetBuyingUnit", "()Hunit;", pJassInterface->Jass_GetBuyingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSoldItem", "()Hitem;", pJassInterface->Jass_GetSoldItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetChangingUnit", "()Hunit;", pJassInterface->Jass_GetChangingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetChangingUnitPrevOwner", "()Hplayer;", pJassInterface->Jass_GetChangingUnitPrevOwner_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDetectedUnit", "()Hunit;", pJassInterface->Jass_GetDetectedUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetOrderedUnit", "()Hunit;", pJassInterface->Jass_GetOrderedUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("OrderId", "(S)I", pJassInterface->Jass_OrderId_Hooked));
	This->m_NativeHooks.push_back(JassNative("OrderId2String", "(I)S", pJassInterface->Jass_OrderId2String_Hooked));
	This->m_NativeHooks.push_back(JassNative("AbilityId", "(S)I", pJassInterface->Jass_AbilityId_Hooked));
	This->m_NativeHooks.push_back(JassNative("AbilityId2String", "(I)S", pJassInterface->Jass_AbilityId2String_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitId", "(S)I", pJassInterface->Jass_UnitId_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitId2String", "(I)S", pJassInterface->Jass_UnitId2String_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetObjectName", "(I)S", pJassInterface->Jass_GetObjectName_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetIssuedOrderId", "()I", pJassInterface->Jass_GetIssuedOrderId_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetOrderPointX", "()R", pJassInterface->Jass_GetOrderPointX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetOrderPointY", "()R", pJassInterface->Jass_GetOrderPointY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetOrderPointLoc", "()Hlocation;", pJassInterface->Jass_GetOrderPointLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetOrderTarget", "()Hwidget;", pJassInterface->Jass_GetOrderTarget_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetOrderTargetDestructable", "()Hdestructable;", pJassInterface->Jass_GetOrderTargetDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetOrderTargetItem", "()Hitem;", pJassInterface->Jass_GetOrderTargetItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetOrderTargetUnit", "()Hunit;", pJassInterface->Jass_GetOrderTargetUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSpellAbilityUnit", "()Hunit;", pJassInterface->Jass_GetSpellAbilityUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSpellAbilityId", "()I", pJassInterface->Jass_GetSpellAbilityId_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSpellAbility", "()Hability;", pJassInterface->Jass_GetSpellAbility_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSpellTargetLoc", "()Hlocation;", pJassInterface->Jass_GetSpellTargetLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSpellTargetX", "()R", pJassInterface->Jass_GetSpellTargetX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSpellTargetY", "()R", pJassInterface->Jass_GetSpellTargetY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSpellTargetDestructable", "()Hdestructable;", pJassInterface->Jass_GetSpellTargetDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSpellTargetItem", "()Hitem;", pJassInterface->Jass_GetSpellTargetItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSpellTargetUnit", "()Hunit;", pJassInterface->Jass_GetSpellTargetUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLevelingUnit", "()Hunit;", pJassInterface->Jass_GetLevelingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLearningUnit", "()Hunit;", pJassInterface->Jass_GetLearningUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLearnedSkill", "()I", pJassInterface->Jass_GetLearnedSkill_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLearnedSkillLevel", "()I", pJassInterface->Jass_GetLearnedSkillLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRevivableUnit", "()Hunit;", pJassInterface->Jass_GetRevivableUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRevivingUnit", "()Hunit;", pJassInterface->Jass_GetRevivingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSummoningUnit", "()Hunit;", pJassInterface->Jass_GetSummoningUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSummonedUnit", "()Hunit;", pJassInterface->Jass_GetSummonedUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTransportUnit", "()Hunit;", pJassInterface->Jass_GetTransportUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLoadedUnit", "()Hunit;", pJassInterface->Jass_GetLoadedUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetManipulatingUnit", "()Hunit;", pJassInterface->Jass_GetManipulatingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetManipulatedItem", "()Hitem;", pJassInterface->Jass_GetManipulatedItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterPlayerAllianceChange", "(Htrigger;Hplayer;Halliancetype;)Hevent;", pJassInterface->Jass_TriggerRegisterPlayerAllianceChange_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterPlayerChatEvent", "(Htrigger;Hplayer;SB)Hevent;", pJassInterface->Jass_TriggerRegisterPlayerChatEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEventPlayerChatString", "()S", pJassInterface->Jass_GetEventPlayerChatString_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEventPlayerChatStringMatched", "()S", pJassInterface->Jass_GetEventPlayerChatStringMatched_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterUnitStateEvent", "(Htrigger;Hunit;Hunitstate;Hlimitop;R)Hevent;", pJassInterface->Jass_TriggerRegisterUnitStateEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEventUnitState", "()Hunitstate;", pJassInterface->Jass_GetEventUnitState_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterDeathEvent", "(Htrigger;Hwidget;)Hevent;", pJassInterface->Jass_TriggerRegisterDeathEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterUnitEvent", "(Htrigger;Hunit;Hunitevent;)Hevent;", pJassInterface->Jass_TriggerRegisterUnitEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEventDamage", "()R", pJassInterface->Jass_GetEventDamage_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEventDamageSource", "()Hunit;", pJassInterface->Jass_GetEventDamageSource_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEventDetectingPlayer", "()Hplayer;", pJassInterface->Jass_GetEventDetectingPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEventTargetUnit", "()Hunit;", pJassInterface->Jass_GetEventTargetUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterFilterUnitEvent", "(Htrigger;Hunit;Hunitevent;Hboolexpr;)Hevent;", pJassInterface->Jass_TriggerRegisterFilterUnitEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterUnitInRange", "(Htrigger;Hunit;RHboolexpr;)Hevent;", pJassInterface->Jass_TriggerRegisterUnitInRange_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterEnterRegion", "(Htrigger;Hregion;Hboolexpr;)Hevent;", pJassInterface->Jass_TriggerRegisterEnterRegion_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterLeaveRegion", "(Htrigger;Hregion;Hboolexpr;)Hevent;", pJassInterface->Jass_TriggerRegisterLeaveRegion_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggeringRegion", "()Hregion;", pJassInterface->Jass_GetTriggeringRegion_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEnteringUnit", "()Hunit;", pJassInterface->Jass_GetEnteringUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLeavingUnit", "()Hunit;", pJassInterface->Jass_GetLeavingUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerAddCondition", "(Htrigger;Hboolexpr;)Htriggercondition;", pJassInterface->Jass_TriggerAddCondition_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRemoveCondition", "(Htrigger;Htriggercondition;)V", pJassInterface->Jass_TriggerRemoveCondition_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerClearConditions", "(Htrigger;)V", pJassInterface->Jass_TriggerClearConditions_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerAddAction", "(Htrigger;C)Htriggeraction;", pJassInterface->Jass_TriggerAddAction_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRemoveAction", "(Htrigger;Htriggeraction;)V", pJassInterface->Jass_TriggerRemoveAction_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerClearActions", "(Htrigger;)V", pJassInterface->Jass_TriggerClearActions_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerSleepAction", "(R)V", pJassInterface->Jass_TriggerSleepAction_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerWaitForSound", "(Hsound;R)V", pJassInterface->Jass_TriggerWaitForSound_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerExecute", "(Htrigger;)V", pJassInterface->Jass_TriggerExecute_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerExecuteWait", "(Htrigger;)V", pJassInterface->Jass_TriggerExecuteWait_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerEvaluate", "(Htrigger;)B", pJassInterface->Jass_TriggerEvaluate_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerSyncStart", "()V", pJassInterface->Jass_TriggerSyncStart_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerSyncReady", "()V", pJassInterface->Jass_TriggerSyncReady_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggerWidget", "()Hwidget;", pJassInterface->Jass_GetTriggerWidget_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggerDestructable", "()Hdestructable;", pJassInterface->Jass_GetTriggerDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggerUnit", "()Hunit;", pJassInterface->Jass_GetTriggerUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggerPlayer", "()Hplayer;", pJassInterface->Jass_GetTriggerPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggeringTrigger", "()Htrigger;", pJassInterface->Jass_GetTriggeringTrigger_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggerEventId", "()Heventid;", pJassInterface->Jass_GetTriggerEventId_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggerEvalCount", "(Htrigger;)I", pJassInterface->Jass_GetTriggerEvalCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggerExecCount", "(Htrigger;)I", pJassInterface->Jass_GetTriggerExecCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetFilterUnit", "()Hunit;", pJassInterface->Jass_GetFilterUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEnumUnit", "()Hunit;", pJassInterface->Jass_GetEnumUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEnumPlayer", "()Hplayer;", pJassInterface->Jass_GetEnumPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetFilterPlayer", "()Hplayer;", pJassInterface->Jass_GetFilterPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetFilterDestructable", "()Hdestructable;", pJassInterface->Jass_GetFilterDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEnumDestructable", "()Hdestructable;", pJassInterface->Jass_GetEnumDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetFilterItem", "()Hitem;", pJassInterface->Jass_GetFilterItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetEnumItem", "()Hitem;", pJassInterface->Jass_GetEnumItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateGroup", "()Hgroup;", pJassInterface->Jass_CreateGroup_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyGroup", "(Hgroup;)V", pJassInterface->Jass_DestroyGroup_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupAddUnit", "(Hgroup;Hunit;)V", pJassInterface->Jass_GroupAddUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupRemoveUnit", "(Hgroup;Hunit;)V", pJassInterface->Jass_GroupRemoveUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupClear", "(Hgroup;)V", pJassInterface->Jass_GroupClear_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsOfType", "(Hgroup;SHboolexpr;)V", pJassInterface->Jass_GroupEnumUnitsOfType_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsOfTypeCounted", "(Hgroup;SHboolexpr;I)V", pJassInterface->Jass_GroupEnumUnitsOfTypeCounted_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsInRect", "(Hgroup;Hrect;Hboolexpr;)V", pJassInterface->Jass_GroupEnumUnitsInRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsInRectCounted", "(Hgroup;Hrect;Hboolexpr;I)V", pJassInterface->Jass_GroupEnumUnitsInRectCounted_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsOfPlayer", "(Hgroup;Hplayer;Hboolexpr;)V", pJassInterface->Jass_GroupEnumUnitsOfPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsInRange", "(Hgroup;RRRHboolexpr;)V", pJassInterface->Jass_GroupEnumUnitsInRange_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsInRangeOfLoc", "(Hgroup;Hlocation;RHboolexpr;)V", pJassInterface->Jass_GroupEnumUnitsInRangeOfLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsInRangeCounted", "(Hgroup;RRRHboolexpr;I)V", pJassInterface->Jass_GroupEnumUnitsInRangeCounted_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsInRangeOfLocCounted", "(Hgroup;Hlocation;RHboolexpr;I)V", pJassInterface->Jass_GroupEnumUnitsInRangeOfLocCounted_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupEnumUnitsSelected", "(Hgroup;Hplayer;Hboolexpr;)V", pJassInterface->Jass_GroupEnumUnitsSelected_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupImmediateOrder", "(Hgroup;S)B", pJassInterface->Jass_GroupImmediateOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupImmediateOrderById", "(Hgroup;I)B", pJassInterface->Jass_GroupImmediateOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupPointOrder", "(Hgroup;SRR)B", pJassInterface->Jass_GroupPointOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupPointOrderLoc", "(Hgroup;SHlocation;)B", pJassInterface->Jass_GroupPointOrderLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupPointOrderById", "(Hgroup;IRR)B", pJassInterface->Jass_GroupPointOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupPointOrderByIdLoc", "(Hgroup;IHlocation;)B", pJassInterface->Jass_GroupPointOrderByIdLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupTargetOrder", "(Hgroup;SHwidget;)B", pJassInterface->Jass_GroupTargetOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("GroupTargetOrderById", "(Hgroup;IHwidget;)B", pJassInterface->Jass_GroupTargetOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForGroup", "(Hgroup;C)V", pJassInterface->Jass_ForGroup_Hooked));
	This->m_NativeHooks.push_back(JassNative("FirstOfGroup", "(Hgroup;)Hunit;", pJassInterface->Jass_FirstOfGroup_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateForce", "()Hforce;", pJassInterface->Jass_CreateForce_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyForce", "(Hforce;)V", pJassInterface->Jass_DestroyForce_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceAddPlayer", "(Hforce;Hplayer;)V", pJassInterface->Jass_ForceAddPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceRemovePlayer", "(Hforce;Hplayer;)V", pJassInterface->Jass_ForceRemovePlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceClear", "(Hforce;)V", pJassInterface->Jass_ForceClear_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceEnumPlayers", "(Hforce;Hboolexpr;)V", pJassInterface->Jass_ForceEnumPlayers_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceEnumPlayersCounted", "(Hforce;Hboolexpr;I)V", pJassInterface->Jass_ForceEnumPlayersCounted_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceEnumAllies", "(Hforce;Hplayer;Hboolexpr;)V", pJassInterface->Jass_ForceEnumAllies_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceEnumEnemies", "(Hforce;Hplayer;Hboolexpr;)V", pJassInterface->Jass_ForceEnumEnemies_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForForce", "(Hforce;C)V", pJassInterface->Jass_ForForce_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetWidgetLife", "(Hwidget;)R", pJassInterface->Jass_GetWidgetLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetWidgetLife", "(Hwidget;R)V", pJassInterface->Jass_SetWidgetLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetWidgetX", "(Hwidget;)R", pJassInterface->Jass_GetWidgetX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetWidgetY", "(Hwidget;)R", pJassInterface->Jass_GetWidgetY_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateDestructable", "(IRRRRI)Hdestructable;", pJassInterface->Jass_CreateDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateDestructableZ", "(IRRRRRI)Hdestructable;", pJassInterface->Jass_CreateDestructableZ_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateDeadDestructable", "(IRRRRI)Hdestructable;", pJassInterface->Jass_CreateDeadDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateDeadDestructableZ", "(IRRRRRI)Hdestructable;", pJassInterface->Jass_CreateDeadDestructableZ_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveDestructable", "(Hdestructable;)V", pJassInterface->Jass_RemoveDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("KillDestructable", "(Hdestructable;)V", pJassInterface->Jass_KillDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDestructableInvulnerable", "(Hdestructable;B)V", pJassInterface->Jass_SetDestructableInvulnerable_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsDestructableInvulnerable", "(Hdestructable;)B", pJassInterface->Jass_IsDestructableInvulnerable_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnumDestructablesInRect", "(Hrect;Hboolexpr;C)V", pJassInterface->Jass_EnumDestructablesInRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDestructableTypeId", "(Hdestructable;)I", pJassInterface->Jass_GetDestructableTypeId_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDestructableX", "(Hdestructable;)R", pJassInterface->Jass_GetDestructableX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDestructableY", "(Hdestructable;)R", pJassInterface->Jass_GetDestructableY_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDestructableLife", "(Hdestructable;R)V", pJassInterface->Jass_SetDestructableLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDestructableLife", "(Hdestructable;)R", pJassInterface->Jass_GetDestructableLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDestructableMaxLife", "(Hdestructable;R)V", pJassInterface->Jass_SetDestructableMaxLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDestructableMaxLife", "(Hdestructable;)R", pJassInterface->Jass_GetDestructableMaxLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestructableRestoreLife", "(Hdestructable;RB)V", pJassInterface->Jass_DestructableRestoreLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("QueueDestructableAnimation", "(Hdestructable;S)V", pJassInterface->Jass_QueueDestructableAnimation_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDestructableAnimation", "(Hdestructable;S)V", pJassInterface->Jass_SetDestructableAnimation_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDestructableAnimationSpeed", "(Hdestructable;R)V", pJassInterface->Jass_SetDestructableAnimationSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("ShowDestructable", "(Hdestructable;B)V", pJassInterface->Jass_ShowDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDestructableOccluderHeight", "(Hdestructable;)R", pJassInterface->Jass_GetDestructableOccluderHeight_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDestructableOccluderHeight", "(Hdestructable;R)V", pJassInterface->Jass_SetDestructableOccluderHeight_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDestructableName", "(Hdestructable;)S", pJassInterface->Jass_GetDestructableName_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateUnit", "(Hplayer;IRRR)Hunit;", pJassInterface->Jass_CreateUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateUnitByName", "(Hplayer;SRRR)Hunit;", pJassInterface->Jass_CreateUnitByName_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateUnitAtLoc", "(Hplayer;IHlocation;R)Hunit;", pJassInterface->Jass_CreateUnitAtLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateUnitAtLocByName", "(Hplayer;SHlocation;R)Hunit;", pJassInterface->Jass_CreateUnitAtLocByName_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateCorpse", "(Hplayer;IRRR)Hunit;", pJassInterface->Jass_CreateCorpse_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitState", "(Hunit;Hunitstate;)R", pJassInterface->Jass_GetUnitState_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitFoodUsed", "(Hunit;)I", pJassInterface->Jass_GetUnitFoodUsed_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitFoodMade", "(Hunit;)I", pJassInterface->Jass_GetUnitFoodMade_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetFoodMade", "(I)I", pJassInterface->Jass_GetFoodMade_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetFoodUsed", "(I)I", pJassInterface->Jass_GetFoodUsed_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitUseFood", "(Hunit;B)V", pJassInterface->Jass_SetUnitUseFood_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitX", "(Hunit;)R", pJassInterface->Jass_GetUnitX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitY", "(Hunit;)R", pJassInterface->Jass_GetUnitY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitLoc", "(Hunit;)Hlocation;", pJassInterface->Jass_GetUnitLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitRallyPoint", "(Hunit;)Hlocation;", pJassInterface->Jass_GetUnitRallyPoint_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitRallyUnit", "(Hunit;)Hunit;", pJassInterface->Jass_GetUnitRallyUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitRallyDestructable", "(Hunit;)Hdestructable;", pJassInterface->Jass_GetUnitRallyDestructable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitFacing", "(Hunit;)R", pJassInterface->Jass_GetUnitFacing_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitMoveSpeed", "(Hunit;)R", pJassInterface->Jass_GetUnitMoveSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitDefaultMoveSpeed", "(Hunit;)R", pJassInterface->Jass_GetUnitDefaultMoveSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitTypeId", "(Hunit;)I", pJassInterface->Jass_GetUnitTypeId_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitRace", "(Hunit;)Hrace;", pJassInterface->Jass_GetUnitRace_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitName", "(Hunit;)S", pJassInterface->Jass_GetUnitName_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitPointValue", "(Hunit;)I", pJassInterface->Jass_GetUnitPointValue_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitPointValueByType", "(I)I", pJassInterface->Jass_GetUnitPointValueByType_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitX", "(Hunit;R)V", pJassInterface->Jass_SetUnitX_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitY", "(Hunit;R)V", pJassInterface->Jass_SetUnitY_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitPosition", "(Hunit;RR)V", pJassInterface->Jass_SetUnitPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitPositionLoc", "(Hunit;Hlocation;)V", pJassInterface->Jass_SetUnitPositionLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitFacing", "(Hunit;R)V", pJassInterface->Jass_SetUnitFacing_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitFacingTimed", "(Hunit;RR)V", pJassInterface->Jass_SetUnitFacingTimed_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitFlyHeight", "(Hunit;RR)V", pJassInterface->Jass_SetUnitFlyHeight_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitMoveSpeed", "(Hunit;R)V", pJassInterface->Jass_SetUnitMoveSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitTurnSpeed", "(Hunit;R)V", pJassInterface->Jass_SetUnitTurnSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitPropWindow", "(Hunit;R)V", pJassInterface->Jass_SetUnitPropWindow_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitCreepGuard", "(Hunit;B)V", pJassInterface->Jass_SetUnitCreepGuard_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitAcquireRange", "(Hunit;)R", pJassInterface->Jass_GetUnitAcquireRange_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitTurnSpeed", "(Hunit;)R", pJassInterface->Jass_GetUnitTurnSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitPropWindow", "(Hunit;)R", pJassInterface->Jass_GetUnitPropWindow_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitFlyHeight", "(Hunit;)R", pJassInterface->Jass_GetUnitFlyHeight_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitDefaultAcquireRange", "(Hunit;)R", pJassInterface->Jass_GetUnitDefaultAcquireRange_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitDefaultTurnSpeed", "(Hunit;)R", pJassInterface->Jass_GetUnitDefaultTurnSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitDefaultPropWindow", "(Hunit;)R", pJassInterface->Jass_GetUnitDefaultPropWindow_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitDefaultFlyHeight", "(Hunit;)R", pJassInterface->Jass_GetUnitDefaultFlyHeight_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitAcquireRange", "(Hunit;R)V", pJassInterface->Jass_SetUnitAcquireRange_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitState", "(Hunit;Hunitstate;R)V", pJassInterface->Jass_SetUnitState_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitOwner", "(Hunit;Hplayer;B)V", pJassInterface->Jass_SetUnitOwner_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitRescuable", "(Hunit;Hplayer;B)V", pJassInterface->Jass_SetUnitRescuable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitRescueRange", "(Hunit;R)V", pJassInterface->Jass_SetUnitRescueRange_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitColor", "(Hunit;Hplayercolor;)V", pJassInterface->Jass_SetUnitColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("QueueUnitAnimation", "(Hunit;S)V", pJassInterface->Jass_QueueUnitAnimation_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitAnimation", "(Hunit;S)V", pJassInterface->Jass_SetUnitAnimation_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitAnimationWithRarity", "(Hunit;SHraritycontrol;)V", pJassInterface->Jass_SetUnitAnimationWithRarity_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitAnimationByIndex", "(Hunit;I)V", pJassInterface->Jass_SetUnitAnimationByIndex_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddUnitAnimationProperties", "(Hunit;SB)V", pJassInterface->Jass_AddUnitAnimationProperties_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitScale", "(Hunit;RRR)V", pJassInterface->Jass_SetUnitScale_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitTimeScale", "(Hunit;R)V", pJassInterface->Jass_SetUnitTimeScale_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitBlendTime", "(Hunit;R)V", pJassInterface->Jass_SetUnitBlendTime_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitVertexColor", "(Hunit;IIII)V", pJassInterface->Jass_SetUnitVertexColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitLookAt", "(Hunit;SHunit;RRR)V", pJassInterface->Jass_SetUnitLookAt_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitPathing", "(Hunit;B)V", pJassInterface->Jass_SetUnitPathing_Hooked));
	This->m_NativeHooks.push_back(JassNative("ResetUnitLookAt", "(Hunit;)V", pJassInterface->Jass_ResetUnitLookAt_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetHeroStr", "(Hunit;IB)V", pJassInterface->Jass_SetHeroStr_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetHeroAgi", "(Hunit;IB)V", pJassInterface->Jass_SetHeroAgi_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetHeroInt", "(Hunit;IB)V", pJassInterface->Jass_SetHeroInt_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHeroStr", "(Hunit;B)I", pJassInterface->Jass_GetHeroStr_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHeroAgi", "(Hunit;B)I", pJassInterface->Jass_GetHeroAgi_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHeroInt", "(Hunit;B)I", pJassInterface->Jass_GetHeroInt_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHeroSkillPoints", "(Hunit;)I", pJassInterface->Jass_GetHeroSkillPoints_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitStripHeroLevel", "(Hunit;I)B", pJassInterface->Jass_UnitStripHeroLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitModifySkillPoints", "(Hunit;I)B", pJassInterface->Jass_UnitModifySkillPoints_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHeroXP", "(Hunit;)I", pJassInterface->Jass_GetHeroXP_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetHeroXP", "(Hunit;IB)V", pJassInterface->Jass_SetHeroXP_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddHeroXP", "(Hunit;IB)V", pJassInterface->Jass_AddHeroXP_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetHeroLevel", "(Hunit;IB)V", pJassInterface->Jass_SetHeroLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHeroLevel", "(Hunit;)I", pJassInterface->Jass_GetHeroLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitLevel", "(Hunit;)I", pJassInterface->Jass_GetUnitLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetHeroProperName", "(Hunit;)S", pJassInterface->Jass_GetHeroProperName_Hooked));
	This->m_NativeHooks.push_back(JassNative("SuspendHeroXP", "(Hunit;B)V", pJassInterface->Jass_SuspendHeroXP_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsSuspendedXP", "(Hunit;)B", pJassInterface->Jass_IsSuspendedXP_Hooked));
	This->m_NativeHooks.push_back(JassNative("SelectHeroSkill", "(Hunit;I)V", pJassInterface->Jass_SelectHeroSkill_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitAbilityLevel", "(Hunit;I)I", pJassInterface->Jass_GetUnitAbilityLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("ReviveHero", "(Hunit;RRB)B", pJassInterface->Jass_ReviveHero_Hooked));
	This->m_NativeHooks.push_back(JassNative("ReviveHeroLoc", "(Hunit;Hlocation;B)B", pJassInterface->Jass_ReviveHeroLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitExploded", "(Hunit;B)V", pJassInterface->Jass_SetUnitExploded_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitInvulnerable", "(Hunit;B)V", pJassInterface->Jass_SetUnitInvulnerable_Hooked));
	This->m_NativeHooks.push_back(JassNative("PauseUnit", "(Hunit;B)V", pJassInterface->Jass_PauseUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitPaused", "(Hunit;)B", pJassInterface->Jass_IsUnitPaused_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitAddItem", "(Hunit;Hitem;)B", pJassInterface->Jass_UnitAddItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitAddItemById", "(Hunit;I)Hitem;", pJassInterface->Jass_UnitAddItemById_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitAddItemToSlotById", "(Hunit;II)B", pJassInterface->Jass_UnitAddItemToSlotById_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitRemoveItem", "(Hunit;Hitem;)V", pJassInterface->Jass_UnitRemoveItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitRemoveItemFromSlot", "(Hunit;I)Hitem;", pJassInterface->Jass_UnitRemoveItemFromSlot_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitHasItem", "(Hunit;Hitem;)B", pJassInterface->Jass_UnitHasItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitItemInSlot", "(Hunit;I)Hitem;", pJassInterface->Jass_UnitItemInSlot_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitInventorySize", "(Hunit;)I", pJassInterface->Jass_UnitInventorySize_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitDropItemPoint", "(Hunit;Hitem;RR)B", pJassInterface->Jass_UnitDropItemPoint_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitDropItemSlot", "(Hunit;Hitem;I)B", pJassInterface->Jass_UnitDropItemSlot_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitDropItemTarget", "(Hunit;Hitem;Hwidget;)B", pJassInterface->Jass_UnitDropItemTarget_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitUseItem", "(Hunit;Hitem;)B", pJassInterface->Jass_UnitUseItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitUseItemPoint", "(Hunit;Hitem;RR)B", pJassInterface->Jass_UnitUseItemPoint_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitUseItemTarget", "(Hunit;Hitem;Hwidget;)B", pJassInterface->Jass_UnitUseItemTarget_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitCurrentOrder", "(Hunit;)I", pJassInterface->Jass_GetUnitCurrentOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetResourceAmount", "(Hunit;I)V", pJassInterface->Jass_SetResourceAmount_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddResourceAmount", "(Hunit;I)V", pJassInterface->Jass_AddResourceAmount_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetResourceAmount", "(Hunit;)I", pJassInterface->Jass_GetResourceAmount_Hooked));
	This->m_NativeHooks.push_back(JassNative("SelectUnit", "(Hunit;B)V", pJassInterface->Jass_SelectUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("ClearSelection", "()V", pJassInterface->Jass_ClearSelection_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitAddIndicator", "(Hunit;IIII)V", pJassInterface->Jass_UnitAddIndicator_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddIndicator", "(Hwidget;IIII)V", pJassInterface->Jass_AddIndicator_Hooked));
	This->m_NativeHooks.push_back(JassNative("KillUnit", "(Hunit;)V", pJassInterface->Jass_KillUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveUnit", "(Hunit;)V", pJassInterface->Jass_RemoveUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("ShowUnit", "(Hunit;B)V", pJassInterface->Jass_ShowUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitInForce", "(Hunit;Hforce;)B", pJassInterface->Jass_IsUnitInForce_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitInGroup", "(Hunit;Hgroup;)B", pJassInterface->Jass_IsUnitInGroup_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitOwnedByPlayer", "(Hunit;Hplayer;)B", pJassInterface->Jass_IsUnitOwnedByPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitAlly", "(Hunit;Hplayer;)B", pJassInterface->Jass_IsUnitAlly_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitEnemy", "(Hunit;Hplayer;)B", pJassInterface->Jass_IsUnitEnemy_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitVisible", "(Hunit;Hplayer;)B", pJassInterface->Jass_IsUnitVisible_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitDetected", "(Hunit;Hplayer;)B", pJassInterface->Jass_IsUnitDetected_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitInvisible", "(Hunit;Hplayer;)B", pJassInterface->Jass_IsUnitInvisible_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitFogged", "(Hunit;Hplayer;)B", pJassInterface->Jass_IsUnitFogged_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitMasked", "(Hunit;Hplayer;)B", pJassInterface->Jass_IsUnitMasked_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitSelected", "(Hunit;Hplayer;)B", pJassInterface->Jass_IsUnitSelected_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitRace", "(Hunit;Hrace;)B", pJassInterface->Jass_IsUnitRace_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitType", "(Hunit;Hunittype;)B", pJassInterface->Jass_IsUnitType_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnit", "(Hunit;Hunit;)B", pJassInterface->Jass_IsUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitInRange", "(Hunit;Hunit;R)B", pJassInterface->Jass_IsUnitInRange_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitInRangeXY", "(Hunit;RRR)B", pJassInterface->Jass_IsUnitInRangeXY_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitInRangeLoc", "(Hunit;Hlocation;R)B", pJassInterface->Jass_IsUnitInRangeLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitHidden", "(Hunit;)B", pJassInterface->Jass_IsUnitHidden_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitIllusion", "(Hunit;)B", pJassInterface->Jass_IsUnitIllusion_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitInTransport", "(Hunit;Hunit;)B", pJassInterface->Jass_IsUnitInTransport_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitLoaded", "(Hunit;)B", pJassInterface->Jass_IsUnitLoaded_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsHeroUnitId", "(I)B", pJassInterface->Jass_IsHeroUnitId_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsUnitIdType", "(IHunittype;)B", pJassInterface->Jass_IsUnitIdType_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetOwningPlayer", "(Hunit;)Hplayer;", pJassInterface->Jass_GetOwningPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitShareVision", "(Hunit;Hplayer;B)V", pJassInterface->Jass_UnitShareVision_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitSuspendDecay", "(Hunit;B)V", pJassInterface->Jass_UnitSuspendDecay_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitAddType", "(Hunit;Hunittype;)B", pJassInterface->Jass_UnitAddType_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitRemoveType", "(Hunit;Hunittype;)B", pJassInterface->Jass_UnitRemoveType_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitAddAbility", "(Hunit;I)B", pJassInterface->Jass_UnitAddAbility_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitRemoveAbility", "(Hunit;I)B", pJassInterface->Jass_UnitRemoveAbility_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitMakeAbilityPermanent", "(Hunit;BI)B", pJassInterface->Jass_UnitMakeAbilityPermanent_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitHasBuffsEx", "(Hunit;BBBBBBB)B", pJassInterface->Jass_UnitHasBuffsEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitCountBuffsEx", "(Hunit;BBBBBBB)I", pJassInterface->Jass_UnitCountBuffsEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitRemoveBuffs", "(Hunit;BB)V", pJassInterface->Jass_UnitRemoveBuffs_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitRemoveBuffsEx", "(Hunit;BBBBBBB)V", pJassInterface->Jass_UnitRemoveBuffsEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitAddSleep", "(Hunit;B)V", pJassInterface->Jass_UnitAddSleep_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitCanSleep", "(Hunit;)B", pJassInterface->Jass_UnitCanSleep_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitAddSleepPerm", "(Hunit;B)V", pJassInterface->Jass_UnitAddSleepPerm_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitCanSleepPerm", "(Hunit;)B", pJassInterface->Jass_UnitCanSleepPerm_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitIsSleeping", "(Hunit;)B", pJassInterface->Jass_UnitIsSleeping_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitWakeUp", "(Hunit;)V", pJassInterface->Jass_UnitWakeUp_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitApplyTimedLife", "(Hunit;IR)V", pJassInterface->Jass_UnitApplyTimedLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitIgnoreAlarm", "(Hunit;B)B", pJassInterface->Jass_UnitIgnoreAlarm_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitIgnoreAlarmToggled", "(Hunit;)B", pJassInterface->Jass_UnitIgnoreAlarmToggled_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitDamagePoint", "(Hunit;RRRRRBBHattacktype;Hdamagetype;Hweapontype;)B", pJassInterface->Jass_UnitDamagePoint_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitDamageTarget", "(Hunit;Hwidget;RBBHattacktype;Hdamagetype;Hweapontype;)B", pJassInterface->Jass_UnitDamageTarget_Hooked));
	This->m_NativeHooks.push_back(JassNative("DecUnitAbilityLevel", "(Hunit;I)I", pJassInterface->Jass_DecUnitAbilityLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("IncUnitAbilityLevel", "(Hunit;I)I", pJassInterface->Jass_IncUnitAbilityLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitAbilityLevel", "(Hunit;II)I", pJassInterface->Jass_SetUnitAbilityLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitResetCooldown", "(Hunit;)V", pJassInterface->Jass_UnitResetCooldown_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitSetConstructionProgress", "(Hunit;I)V", pJassInterface->Jass_UnitSetConstructionProgress_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitSetUpgradeProgress", "(Hunit;I)V", pJassInterface->Jass_UnitSetUpgradeProgress_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitPauseTimedLife", "(Hunit;B)V", pJassInterface->Jass_UnitPauseTimedLife_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitSetUsesAltIcon", "(Hunit;B)V", pJassInterface->Jass_UnitSetUsesAltIcon_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueImmediateOrderById", "(Hunit;I)B", pJassInterface->Jass_IssueImmediateOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssuePointOrderById", "(Hunit;IRR)B", pJassInterface->Jass_IssuePointOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssuePointOrderByIdLoc", "(Hunit;IHlocation;)B", pJassInterface->Jass_IssuePointOrderByIdLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueTargetOrderById", "(Hunit;IHwidget;)B", pJassInterface->Jass_IssueTargetOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueInstantPointOrderById", "(Hunit;IRRHwidget;)B", pJassInterface->Jass_IssueInstantPointOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueInstantTargetOrderById", "(Hunit;IHwidget;Hwidget;)B", pJassInterface->Jass_IssueInstantTargetOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueBuildOrderById", "(Hunit;IRR)B", pJassInterface->Jass_IssueBuildOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueNeutralImmediateOrderById", "(Hplayer;Hunit;I)B", pJassInterface->Jass_IssueNeutralImmediateOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueNeutralPointOrderById", "(Hplayer;Hunit;IRR)B", pJassInterface->Jass_IssueNeutralPointOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueNeutralTargetOrderById", "(Hplayer;Hunit;IHwidget;)B", pJassInterface->Jass_IssueNeutralTargetOrderById_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueImmediateOrder", "(Hunit;S)B", pJassInterface->Jass_IssueImmediateOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssuePointOrder", "(Hunit;SRR)B", pJassInterface->Jass_IssuePointOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssuePointOrderLoc", "(Hunit;SHlocation;)B", pJassInterface->Jass_IssuePointOrderLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueTargetOrder", "(Hunit;SHwidget;)B", pJassInterface->Jass_IssueTargetOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueInstantPointOrder", "(Hunit;SRRHwidget;)B", pJassInterface->Jass_IssueInstantPointOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueInstantTargetOrder", "(Hunit;SHwidget;Hwidget;)B", pJassInterface->Jass_IssueInstantTargetOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueBuildOrder", "(Hunit;SRR)B", pJassInterface->Jass_IssueBuildOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueNeutralImmediateOrder", "(Hplayer;Hunit;S)B", pJassInterface->Jass_IssueNeutralImmediateOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueNeutralPointOrder", "(Hplayer;Hunit;SRR)B", pJassInterface->Jass_IssueNeutralPointOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("IssueNeutralTargetOrder", "(Hplayer;Hunit;SHwidget;)B", pJassInterface->Jass_IssueNeutralTargetOrder_Hooked));
	This->m_NativeHooks.push_back(JassNative("WaygateGetDestinationX", "(Hunit;)R", pJassInterface->Jass_WaygateGetDestinationX_Hooked));
	This->m_NativeHooks.push_back(JassNative("WaygateGetDestinationY", "(Hunit;)R", pJassInterface->Jass_WaygateGetDestinationY_Hooked));
	This->m_NativeHooks.push_back(JassNative("WaygateSetDestination", "(Hunit;RR)V", pJassInterface->Jass_WaygateSetDestination_Hooked));
	This->m_NativeHooks.push_back(JassNative("WaygateActivate", "(Hunit;B)V", pJassInterface->Jass_WaygateActivate_Hooked));
	This->m_NativeHooks.push_back(JassNative("WaygateIsActive", "(Hunit;)B", pJassInterface->Jass_WaygateIsActive_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddItemToAllStock", "(III)V", pJassInterface->Jass_AddItemToAllStock_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddItemToStock", "(Hunit;III)V", pJassInterface->Jass_AddItemToStock_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddUnitToAllStock", "(III)V", pJassInterface->Jass_AddUnitToAllStock_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddUnitToStock", "(Hunit;III)V", pJassInterface->Jass_AddUnitToStock_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveItemFromAllStock", "(I)V", pJassInterface->Jass_RemoveItemFromAllStock_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveItemFromStock", "(Hunit;I)V", pJassInterface->Jass_RemoveItemFromStock_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveUnitFromAllStock", "(I)V", pJassInterface->Jass_RemoveUnitFromAllStock_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveUnitFromStock", "(Hunit;I)V", pJassInterface->Jass_RemoveUnitFromStock_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetAllItemTypeSlots", "(I)V", pJassInterface->Jass_SetAllItemTypeSlots_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetAllUnitTypeSlots", "(I)V", pJassInterface->Jass_SetAllUnitTypeSlots_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemTypeSlots", "(Hunit;I)V", pJassInterface->Jass_SetItemTypeSlots_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitTypeSlots", "(Hunit;I)V", pJassInterface->Jass_SetUnitTypeSlots_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetUnitUserData", "(Hunit;)I", pJassInterface->Jass_GetUnitUserData_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitUserData", "(Hunit;I)V", pJassInterface->Jass_SetUnitUserData_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateItem", "(IRR)Hitem;", pJassInterface->Jass_CreateItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveItem", "(Hitem;)V", pJassInterface->Jass_RemoveItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetItemPlayer", "(Hitem;)Hplayer;", pJassInterface->Jass_GetItemPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetItemTypeId", "(Hitem;)I", pJassInterface->Jass_GetItemTypeId_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetItemX", "(Hitem;)R", pJassInterface->Jass_GetItemX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetItemY", "(Hitem;)R", pJassInterface->Jass_GetItemY_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemPosition", "(Hitem;RR)V", pJassInterface->Jass_SetItemPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemDropOnDeath", "(Hitem;B)V", pJassInterface->Jass_SetItemDropOnDeath_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemDroppable", "(Hitem;B)V", pJassInterface->Jass_SetItemDroppable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemPawnable", "(Hitem;B)V", pJassInterface->Jass_SetItemPawnable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemPlayer", "(Hitem;Hplayer;B)V", pJassInterface->Jass_SetItemPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemInvulnerable", "(Hitem;B)V", pJassInterface->Jass_SetItemInvulnerable_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsItemInvulnerable", "(Hitem;)B", pJassInterface->Jass_IsItemInvulnerable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetItemLevel", "(Hitem;)I", pJassInterface->Jass_GetItemLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetItemType", "(Hitem;)Hitemtype;", pJassInterface->Jass_GetItemType_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemVisible", "(Hitem;B)V", pJassInterface->Jass_SetItemVisible_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsItemVisible", "(Hitem;)B", pJassInterface->Jass_IsItemVisible_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnumItemsInRect", "(Hrect;Hboolexpr;C)V", pJassInterface->Jass_EnumItemsInRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsItemOwned", "(Hitem;)B", pJassInterface->Jass_IsItemOwned_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsItemPowerup", "(Hitem;)B", pJassInterface->Jass_IsItemPowerup_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsItemSellable", "(Hitem;)B", pJassInterface->Jass_IsItemSellable_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsItemPawnable", "(Hitem;)B", pJassInterface->Jass_IsItemPawnable_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsItemIdPowerup", "(I)B", pJassInterface->Jass_IsItemIdPowerup_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsItemIdSellable", "(I)B", pJassInterface->Jass_IsItemIdSellable_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsItemIdPawnable", "(I)B", pJassInterface->Jass_IsItemIdPawnable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemDropID", "(Hitem;I)V", pJassInterface->Jass_SetItemDropID_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetItemName", "(Hitem;)S", pJassInterface->Jass_GetItemName_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetItemCharges", "(Hitem;)I", pJassInterface->Jass_GetItemCharges_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemCharges", "(Hitem;I)V", pJassInterface->Jass_SetItemCharges_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetItemUserData", "(Hitem;)I", pJassInterface->Jass_GetItemUserData_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetItemUserData", "(Hitem;I)V", pJassInterface->Jass_SetItemUserData_Hooked));
	This->m_NativeHooks.push_back(JassNative("Player", "(I)Hplayer;", pJassInterface->Jass_Player_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLocalPlayer", "()Hplayer;", pJassInterface->Jass_GetLocalPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsPlayerAlly", "(Hplayer;Hplayer;)B", pJassInterface->Jass_IsPlayerAlly_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsPlayerEnemy", "(Hplayer;Hplayer;)B", pJassInterface->Jass_IsPlayerEnemy_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsPlayerInForce", "(Hplayer;Hforce;)B", pJassInterface->Jass_IsPlayerInForce_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsPlayerObserver", "(Hplayer;)B", pJassInterface->Jass_IsPlayerObserver_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerRace", "(Hplayer;)Hrace;", pJassInterface->Jass_GetPlayerRace_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerId", "(Hplayer;)I", pJassInterface->Jass_GetPlayerId_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerTechMaxAllowed", "(Hplayer;II)V", pJassInterface->Jass_SetPlayerTechMaxAllowed_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerTechMaxAllowed", "(Hplayer;I)I", pJassInterface->Jass_GetPlayerTechMaxAllowed_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddPlayerTechResearched", "(Hplayer;II)V", pJassInterface->Jass_AddPlayerTechResearched_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerTechResearched", "(Hplayer;II)V", pJassInterface->Jass_SetPlayerTechResearched_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerTechResearched", "(Hplayer;IB)B", pJassInterface->Jass_GetPlayerTechResearched_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerTechCount", "(Hplayer;IB)I", pJassInterface->Jass_GetPlayerTechCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerAbilityAvailable", "(Hplayer;IB)V", pJassInterface->Jass_SetPlayerAbilityAvailable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerUnitCount", "(Hplayer;B)I", pJassInterface->Jass_GetPlayerUnitCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerTypedUnitCount", "(Hplayer;SBB)I", pJassInterface->Jass_GetPlayerTypedUnitCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerStructureCount", "(Hplayer;B)I", pJassInterface->Jass_GetPlayerStructureCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsVisibleToPlayer", "(RRHplayer;)B", pJassInterface->Jass_IsVisibleToPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsLocationVisibleToPlayer", "(Hlocation;Hplayer;)B", pJassInterface->Jass_IsLocationVisibleToPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsFoggedToPlayer", "(RRHplayer;)B", pJassInterface->Jass_IsFoggedToPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsLocationFoggedToPlayer", "(Hlocation;Hplayer;)B", pJassInterface->Jass_IsLocationFoggedToPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsMaskedToPlayer", "(RRHplayer;)B", pJassInterface->Jass_IsMaskedToPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsLocationMaskedToPlayer", "(Hlocation;Hplayer;)B", pJassInterface->Jass_IsLocationMaskedToPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerState", "(Hplayer;Hplayerstate;I)V", pJassInterface->Jass_SetPlayerState_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerState", "(Hplayer;Hplayerstate;)I", pJassInterface->Jass_GetPlayerState_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerScore", "(Hplayer;Hplayerscore;)I", pJassInterface->Jass_GetPlayerScore_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerAlliance", "(Hplayer;Hplayer;Halliancetype;)B", pJassInterface->Jass_GetPlayerAlliance_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemovePlayer", "(Hplayer;Hplayergameresult;)V", pJassInterface->Jass_RemovePlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("CachePlayerHeroData", "(Hplayer;)V", pJassInterface->Jass_CachePlayerHeroData_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerHandicap", "(Hplayer;)R", pJassInterface->Jass_GetPlayerHandicap_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerHandicap", "(Hplayer;R)V", pJassInterface->Jass_SetPlayerHandicap_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetPlayerHandicapXP", "(Hplayer;)R", pJassInterface->Jass_GetPlayerHandicapXP_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerHandicapXP", "(Hplayer;R)V", pJassInterface->Jass_SetPlayerHandicapXP_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetPlayerUnitsOwner", "(Hplayer;I)V", pJassInterface->Jass_SetPlayerUnitsOwner_Hooked));
	This->m_NativeHooks.push_back(JassNative("CripplePlayer", "(Hplayer;Hforce;B)V", pJassInterface->Jass_CripplePlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("VersionGet", "()Hversion;", pJassInterface->Jass_VersionGet_Hooked));
	This->m_NativeHooks.push_back(JassNative("VersionCompatible", "(Hversion;)B", pJassInterface->Jass_VersionCompatible_Hooked));
	This->m_NativeHooks.push_back(JassNative("VersionSupported", "(Hversion;)B", pJassInterface->Jass_VersionSupported_Hooked));
	This->m_NativeHooks.push_back(JassNative("EndGame", "(B)V", pJassInterface->Jass_EndGame_Hooked));
	This->m_NativeHooks.push_back(JassNative("ChangeLevel", "(SB)V", pJassInterface->Jass_ChangeLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("RestartGame", "(B)V", pJassInterface->Jass_RestartGame_Hooked));
	This->m_NativeHooks.push_back(JassNative("ReloadGame", "()V", pJassInterface->Jass_ReloadGame_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadGame", "(SB)V", pJassInterface->Jass_LoadGame_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveGame", "(S)V", pJassInterface->Jass_SaveGame_Hooked));
	This->m_NativeHooks.push_back(JassNative("RenameSaveDirectory", "(SS)B", pJassInterface->Jass_RenameSaveDirectory_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveSaveDirectory", "(S)B", pJassInterface->Jass_RemoveSaveDirectory_Hooked));
	This->m_NativeHooks.push_back(JassNative("CopySaveGame", "(SS)B", pJassInterface->Jass_CopySaveGame_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveGameExists", "(S)B", pJassInterface->Jass_SaveGameExists_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetFloatGameState", "(Hfgamestate;R)V", pJassInterface->Jass_SetFloatGameState_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetFloatGameState", "(Hfgamestate;)R", pJassInterface->Jass_GetFloatGameState_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetIntegerGameState", "(Higamestate;I)V", pJassInterface->Jass_SetIntegerGameState_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetIntegerGameState", "(Higamestate;)I", pJassInterface->Jass_GetIntegerGameState_Hooked));
	This->m_NativeHooks.push_back(JassNative("SyncSelections", "()V", pJassInterface->Jass_SyncSelections_Hooked));
	This->m_NativeHooks.push_back(JassNative("DialogCreate", "()Hdialog;", pJassInterface->Jass_DialogCreate_Hooked));
	This->m_NativeHooks.push_back(JassNative("DialogDestroy", "(Hdialog;)V", pJassInterface->Jass_DialogDestroy_Hooked));
	This->m_NativeHooks.push_back(JassNative("DialogSetAsync", "(Hdialog;)V", pJassInterface->Jass_DialogSetAsync_Hooked));
	This->m_NativeHooks.push_back(JassNative("DialogClear", "(Hdialog;)V", pJassInterface->Jass_DialogClear_Hooked));
	This->m_NativeHooks.push_back(JassNative("DialogSetMessage", "(Hdialog;S)V", pJassInterface->Jass_DialogSetMessage_Hooked));
	This->m_NativeHooks.push_back(JassNative("DialogAddButton", "(Hdialog;SI)Hbutton;", pJassInterface->Jass_DialogAddButton_Hooked));
	This->m_NativeHooks.push_back(JassNative("DialogAddQuitButton", "(Hdialog;BSI)Hbutton;", pJassInterface->Jass_DialogAddQuitButton_Hooked));
	This->m_NativeHooks.push_back(JassNative("DialogDisplay", "(Hplayer;Hdialog;B)V", pJassInterface->Jass_DialogDisplay_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetMissionAvailable", "(IIB)V", pJassInterface->Jass_SetMissionAvailable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCampaignAvailable", "(IB)V", pJassInterface->Jass_SetCampaignAvailable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCampaignMenuRace", "(Hrace;)V", pJassInterface->Jass_SetCampaignMenuRace_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCampaignMenuRaceEx", "(I)V", pJassInterface->Jass_SetCampaignMenuRaceEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceCampaignSelectScreen", "()V", pJassInterface->Jass_ForceCampaignSelectScreen_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetOpCinematicAvailable", "(IB)V", pJassInterface->Jass_SetOpCinematicAvailable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetEdCinematicAvailable", "(IB)V", pJassInterface->Jass_SetEdCinematicAvailable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTutorialCleared", "(B)V", pJassInterface->Jass_SetTutorialCleared_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetDefaultDifficulty", "()Hgamedifficulty;", pJassInterface->Jass_GetDefaultDifficulty_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDefaultDifficulty", "(Hgamedifficulty;)V", pJassInterface->Jass_SetDefaultDifficulty_Hooked));
	This->m_NativeHooks.push_back(JassNative("ReloadGameCachesFromDisk", "()B", pJassInterface->Jass_ReloadGameCachesFromDisk_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCustomCampaignButtonVisible", "(IB)V", pJassInterface->Jass_SetCustomCampaignButtonVisible_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCustomCampaignButtonVisible", "(I)B", pJassInterface->Jass_GetCustomCampaignButtonVisible_Hooked));
	This->m_NativeHooks.push_back(JassNative("DoNotSaveReplay", "()V", pJassInterface->Jass_DoNotSaveReplay_Hooked));
	This->m_NativeHooks.push_back(JassNative("InitGameCache", "(S)Hgamecache;", pJassInterface->Jass_InitGameCache_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveGameCache", "(Hgamecache;)B", pJassInterface->Jass_SaveGameCache_Hooked));
	This->m_NativeHooks.push_back(JassNative("StoreInteger", "(Hgamecache;SSI)V", pJassInterface->Jass_StoreInteger_Hooked));
	This->m_NativeHooks.push_back(JassNative("StoreReal", "(Hgamecache;SSR)V", pJassInterface->Jass_StoreReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("StoreBoolean", "(Hgamecache;SSB)V", pJassInterface->Jass_StoreBoolean_Hooked));
	This->m_NativeHooks.push_back(JassNative("StoreUnit", "(Hgamecache;SSHunit;)B", pJassInterface->Jass_StoreUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("StoreString", "(Hgamecache;SSS)B", pJassInterface->Jass_StoreString_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveInteger", "(Hhashtable;III)V", pJassInterface->Jass_SaveInteger_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveReal", "(Hhashtable;IIR)V", pJassInterface->Jass_SaveReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveBoolean", "(Hhashtable;IIB)V", pJassInterface->Jass_SaveBoolean_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveStr", "(Hhashtable;IIS)B", pJassInterface->Jass_SaveStr_Hooked));
	This->m_NativeHooks.push_back(JassNative("SavePlayerHandle", "(Hhashtable;IIHplayer;)B", pJassInterface->Jass_SavePlayerHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveWidgetHandle", "(Hhashtable;IIHwidget;)B", pJassInterface->Jass_SaveWidgetHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveDestructableHandle", "(Hhashtable;IIHdestructable;)B", pJassInterface->Jass_SaveDestructableHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveItemHandle", "(Hhashtable;IIHitem;)B", pJassInterface->Jass_SaveItemHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveUnitHandle", "(Hhashtable;IIHunit;)B", pJassInterface->Jass_SaveUnitHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveAbilityHandle", "(Hhashtable;IIHability;)B", pJassInterface->Jass_SaveAbilityHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveTimerHandle", "(Hhashtable;IIHtimer;)B", pJassInterface->Jass_SaveTimerHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveRegionHandle", "(Hhashtable;IIHregion;)B", pJassInterface->Jass_SaveRegionHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveTriggerHandle", "(Hhashtable;IIHtrigger;)B", pJassInterface->Jass_SaveTriggerHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveTriggerConditionHandle", "(Hhashtable;IIHtriggercondition;)B", pJassInterface->Jass_SaveTriggerConditionHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveTriggerActionHandle", "(Hhashtable;IIHtriggeraction;)B", pJassInterface->Jass_SaveTriggerActionHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveTriggerEventHandle", "(Hhashtable;IIHevent;)B", pJassInterface->Jass_SaveTriggerEventHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveForceHandle", "(Hhashtable;IIHforce;)B", pJassInterface->Jass_SaveForceHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveGroupHandle", "(Hhashtable;IIHgroup;)B", pJassInterface->Jass_SaveGroupHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveLocationHandle", "(Hhashtable;IIHlocation;)B", pJassInterface->Jass_SaveLocationHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveRectHandle", "(Hhashtable;IIHrect;)B", pJassInterface->Jass_SaveRectHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveBooleanExprHandle", "(Hhashtable;IIHboolexpr;)B", pJassInterface->Jass_SaveBooleanExprHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveSoundHandle", "(Hhashtable;IIHsound;)B", pJassInterface->Jass_SaveSoundHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveEffectHandle", "(Hhashtable;IIHeffect;)B", pJassInterface->Jass_SaveEffectHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveUnitPoolHandle", "(Hhashtable;IIHunitpool;)B", pJassInterface->Jass_SaveUnitPoolHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveItemPoolHandle", "(Hhashtable;IIHitempool;)B", pJassInterface->Jass_SaveItemPoolHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveQuestHandle", "(Hhashtable;IIHquest;)B", pJassInterface->Jass_SaveQuestHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveQuestItemHandle", "(Hhashtable;IIHquestitem;)B", pJassInterface->Jass_SaveQuestItemHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveDefeatConditionHandle", "(Hhashtable;IIHdefeatcondition;)B", pJassInterface->Jass_SaveDefeatConditionHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveTimerDialogHandle", "(Hhashtable;IIHtimerdialog;)B", pJassInterface->Jass_SaveTimerDialogHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveLeaderboardHandle", "(Hhashtable;IIHleaderboard;)B", pJassInterface->Jass_SaveLeaderboardHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveMultiboardHandle", "(Hhashtable;IIHmultiboard;)B", pJassInterface->Jass_SaveMultiboardHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveMultiboardItemHandle", "(Hhashtable;IIHmultiboarditem;)B", pJassInterface->Jass_SaveMultiboardItemHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveTrackableHandle", "(Hhashtable;IIHtrackable;)B", pJassInterface->Jass_SaveTrackableHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveDialogHandle", "(Hhashtable;IIHdialog;)B", pJassInterface->Jass_SaveDialogHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveButtonHandle", "(Hhashtable;IIHbutton;)B", pJassInterface->Jass_SaveButtonHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveTextTagHandle", "(Hhashtable;IIHtexttag;)B", pJassInterface->Jass_SaveTextTagHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveLightningHandle", "(Hhashtable;IIHlightning;)B", pJassInterface->Jass_SaveLightningHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveImageHandle", "(Hhashtable;IIHimage;)B", pJassInterface->Jass_SaveImageHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveUbersplatHandle", "(Hhashtable;IIHubersplat;)B", pJassInterface->Jass_SaveUbersplatHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveFogStateHandle", "(Hhashtable;IIHfogstate;)B", pJassInterface->Jass_SaveFogStateHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveFogModifierHandle", "(Hhashtable;IIHfogmodifier;)B", pJassInterface->Jass_SaveFogModifierHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveAgentHandle", "(Hhashtable;IIHagent;)B", pJassInterface->Jass_SaveAgentHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SaveHashtableHandle", "(Hhashtable;IIHhashtable;)B", pJassInterface->Jass_SaveHashtableHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("SyncStoredInteger", "(Hgamecache;SS)V", pJassInterface->Jass_SyncStoredInteger_Hooked));
	This->m_NativeHooks.push_back(JassNative("SyncStoredReal", "(Hgamecache;SS)V", pJassInterface->Jass_SyncStoredReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("SyncStoredBoolean", "(Hgamecache;SS)V", pJassInterface->Jass_SyncStoredBoolean_Hooked));
	This->m_NativeHooks.push_back(JassNative("SyncStoredUnit", "(Hgamecache;SS)V", pJassInterface->Jass_SyncStoredUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("SyncStoredString", "(Hgamecache;SS)V", pJassInterface->Jass_SyncStoredString_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetStoredInteger", "(Hgamecache;SS)I", pJassInterface->Jass_GetStoredInteger_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetStoredReal", "(Hgamecache;SS)R", pJassInterface->Jass_GetStoredReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetStoredBoolean", "(Hgamecache;SS)B", pJassInterface->Jass_GetStoredBoolean_Hooked));
	This->m_NativeHooks.push_back(JassNative("RestoreUnit", "(Hgamecache;SSHplayer;RRR)Hunit;", pJassInterface->Jass_RestoreUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetStoredString", "(Hgamecache;SS)S", pJassInterface->Jass_GetStoredString_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveStoredInteger", "(Hgamecache;SS)B", pJassInterface->Jass_HaveStoredInteger_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveStoredReal", "(Hgamecache;SS)B", pJassInterface->Jass_HaveStoredReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveStoredBoolean", "(Hgamecache;SS)B", pJassInterface->Jass_HaveStoredBoolean_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveStoredUnit", "(Hgamecache;SS)B", pJassInterface->Jass_HaveStoredUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveStoredString", "(Hgamecache;SS)B", pJassInterface->Jass_HaveStoredString_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlushGameCache", "(Hgamecache;)V", pJassInterface->Jass_FlushGameCache_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlushStoredMission", "(Hgamecache;S)V", pJassInterface->Jass_FlushStoredMission_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlushStoredInteger", "(Hgamecache;SS)V", pJassInterface->Jass_FlushStoredInteger_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlushStoredReal", "(Hgamecache;SS)V", pJassInterface->Jass_FlushStoredReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlushStoredBoolean", "(Hgamecache;SS)V", pJassInterface->Jass_FlushStoredBoolean_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlushStoredUnit", "(Hgamecache;SS)V", pJassInterface->Jass_FlushStoredUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlushStoredString", "(Hgamecache;SS)V", pJassInterface->Jass_FlushStoredString_Hooked));
	This->m_NativeHooks.push_back(JassNative("InitHashtable", "()Hhashtable;", pJassInterface->Jass_InitHashtable_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadInteger", "(Hhashtable;II)I;", pJassInterface->Jass_LoadInteger_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadReal", "(Hhashtable;II)R;", pJassInterface->Jass_LoadReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadBoolean", "(Hhashtable;II)B;", pJassInterface->Jass_LoadBoolean_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadStr", "(Hhashtable;II)S;", pJassInterface->Jass_LoadStr_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadPlayerHandle", "(Hhashtable;II)Hplayer;", pJassInterface->Jass_LoadPlayerHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadWidgetHandle", "(Hhashtable;II)Hwidget;", pJassInterface->Jass_LoadWidgetHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadDestructableHandle", "(Hhashtable;II)Hdestructable;", pJassInterface->Jass_LoadDestructableHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadItemHandle", "(Hhashtable;II)Hitem;", pJassInterface->Jass_LoadItemHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadUnitHandle", "(Hhashtable;II)Hunit;", pJassInterface->Jass_LoadUnitHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadAbilityHandle", "(Hhashtable;II)Hability;", pJassInterface->Jass_LoadAbilityHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadTimerHandle", "(Hhashtable;II)Htimer;", pJassInterface->Jass_LoadTimerHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadRegionHandle", "(Hhashtable;II)Hregion;", pJassInterface->Jass_LoadRegionHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadTriggerHandle", "(Hhashtable;II)Htrigger;", pJassInterface->Jass_LoadTriggerHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadTriggerConditionHandle", "(Hhashtable;II)Htriggercondition;", pJassInterface->Jass_LoadTriggerConditionHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadTriggerActionHandle", "(Hhashtable;II)Htriggeraction;", pJassInterface->Jass_LoadTriggerActionHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadTriggerEventHandle", "(Hhashtable;II)Hevent;", pJassInterface->Jass_LoadTriggerEventHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadForceHandle", "(Hhashtable;II)Hforce;", pJassInterface->Jass_LoadForceHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadGroupHandle", "(Hhashtable;II)Hgroup;", pJassInterface->Jass_LoadGroupHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadLocationHandle", "(Hhashtable;II)Hlocation;", pJassInterface->Jass_LoadLocationHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadRectHandle", "(Hhashtable;II)Hrect;", pJassInterface->Jass_LoadRectHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadBooleanExprHandle", "(Hhashtable;II)Hboolexpr;", pJassInterface->Jass_LoadBooleanExprHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadSoundHandle", "(Hhashtable;II)Hsound;", pJassInterface->Jass_LoadSoundHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadEffectHandle", "(Hhashtable;II)Heffect;", pJassInterface->Jass_LoadEffectHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadUnitPoolHandle", "(Hhashtable;II)Hunitpool;", pJassInterface->Jass_LoadUnitPoolHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadItemPoolHandle", "(Hhashtable;II)Hitempool;", pJassInterface->Jass_LoadItemPoolHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadQuestHandle", "(Hhashtable;II)Hquest;", pJassInterface->Jass_LoadQuestHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadQuestItemHandle", "(Hhashtable;II)Hquestitem;", pJassInterface->Jass_LoadQuestItemHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadDefeatConditionHandle", "(Hhashtable;II)Hdefeatcondition;", pJassInterface->Jass_LoadDefeatConditionHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadTimerDialogHandle", "(Hhashtable;II)Htimerdialog;", pJassInterface->Jass_LoadTimerDialogHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadLeaderboardHandle", "(Hhashtable;II)Hleaderboard;", pJassInterface->Jass_LoadLeaderboardHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadMultiboardHandle", "(Hhashtable;II)Hmultiboard;", pJassInterface->Jass_LoadMultiboardHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadMultiboardItemHandle", "(Hhashtable;II)Hmultiboarditem;", pJassInterface->Jass_LoadMultiboardItemHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadTrackableHandle", "(Hhashtable;II)Htrackable;", pJassInterface->Jass_LoadTrackableHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadDialogHandle", "(Hhashtable;II)Hdialog;", pJassInterface->Jass_LoadDialogHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadButtonHandle", "(Hhashtable;II)Hbutton;", pJassInterface->Jass_LoadButtonHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadTextTagHandle", "(Hhashtable;II)Htexttag;", pJassInterface->Jass_LoadTextTagHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadLightningHandle", "(Hhashtable;II)Hlightning;", pJassInterface->Jass_LoadLightningHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadImageHandle", "(Hhashtable;II)Himage;", pJassInterface->Jass_LoadImageHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadUbersplatHandle", "(Hhashtable;II)Hubersplat;", pJassInterface->Jass_LoadUbersplatHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadFogStateHandle", "(Hhashtable;II)Hfogstate;", pJassInterface->Jass_LoadFogStateHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadFogModifierHandle", "(Hhashtable;II)Hfogmodifier;", pJassInterface->Jass_LoadFogModifierHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LoadHashtableHandle", "(Hhashtable;II)Hhashtable;", pJassInterface->Jass_LoadHashtableHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveSavedInteger", "(Hhashtable;II)B", pJassInterface->Jass_HaveSavedInteger_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveSavedReal", "(Hhashtable;II)B", pJassInterface->Jass_HaveSavedReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveSavedBoolean", "(Hhashtable;II)B", pJassInterface->Jass_HaveSavedBoolean_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveSavedString", "(Hhashtable;II)B", pJassInterface->Jass_HaveSavedString_Hooked));
	This->m_NativeHooks.push_back(JassNative("HaveSavedHandle", "(Hhashtable;II)B", pJassInterface->Jass_HaveSavedHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveSavedInteger", "(Hhashtable;II)V", pJassInterface->Jass_RemoveSavedInteger_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveSavedReal", "(Hhashtable;II)V", pJassInterface->Jass_RemoveSavedReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveSavedBoolean", "(Hhashtable;II)V", pJassInterface->Jass_RemoveSavedBoolean_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveSavedString", "(Hhashtable;II)V", pJassInterface->Jass_RemoveSavedString_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveSavedHandle", "(Hhashtable;II)V", pJassInterface->Jass_RemoveSavedHandle_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlushParentHashtable", "(Hhashtable;)V", pJassInterface->Jass_FlushParentHashtable_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlushChildHashtable", "(Hhashtable;I)V", pJassInterface->Jass_FlushChildHashtable_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRandomInt", "(II)I", pJassInterface->Jass_GetRandomInt_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetRandomReal", "(RR)R", pJassInterface->Jass_GetRandomReal_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateUnitPool", "()Hunitpool;", pJassInterface->Jass_CreateUnitPool_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyUnitPool", "(Hunitpool;)V", pJassInterface->Jass_DestroyUnitPool_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitPoolAddUnitType", "(Hunitpool;IR)V", pJassInterface->Jass_UnitPoolAddUnitType_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnitPoolRemoveUnitType", "(Hunitpool;I)V", pJassInterface->Jass_UnitPoolRemoveUnitType_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlaceRandomUnit", "(Hunitpool;Hplayer;RRR)Hunit;", pJassInterface->Jass_PlaceRandomUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateItemPool", "()Hitempool;", pJassInterface->Jass_CreateItemPool_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyItemPool", "(Hitempool;)V", pJassInterface->Jass_DestroyItemPool_Hooked));
	This->m_NativeHooks.push_back(JassNative("ItemPoolAddItemType", "(Hitempool;IR)V", pJassInterface->Jass_ItemPoolAddItemType_Hooked));
	This->m_NativeHooks.push_back(JassNative("ItemPoolRemoveItemType", "(Hitempool;I)V", pJassInterface->Jass_ItemPoolRemoveItemType_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlaceRandomItem", "(Hitempool;RR)Hitem;", pJassInterface->Jass_PlaceRandomItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("ChooseRandomCreep", "(I)I", pJassInterface->Jass_ChooseRandomCreep_Hooked));
	This->m_NativeHooks.push_back(JassNative("ChooseRandomNPBuilding", "()I", pJassInterface->Jass_ChooseRandomNPBuilding_Hooked));
	This->m_NativeHooks.push_back(JassNative("ChooseRandomItem", "(I)I", pJassInterface->Jass_ChooseRandomItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("ChooseRandomItemEx", "(Hitemtype;I)I", pJassInterface->Jass_ChooseRandomItemEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetRandomSeed", "(I)V", pJassInterface->Jass_SetRandomSeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisplayTextToPlayer", "(Hplayer;RRS)V", pJassInterface->Jass_DisplayTextToPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisplayTimedTextToPlayer", "(Hplayer;RRRS)V", pJassInterface->Jass_DisplayTimedTextToPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisplayTimedTextFromPlayer", "(Hplayer;RRRS)V", pJassInterface->Jass_DisplayTimedTextFromPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("ClearTextMessages", "()V", pJassInterface->Jass_ClearTextMessages_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnableUserControl", "(B)V", pJassInterface->Jass_EnableUserControl_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnableUserUI", "(B)V", pJassInterface->Jass_EnableUserUI_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisableRestartMission", "(B)V", pJassInterface->Jass_DisableRestartMission_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceUIKey", "(S)V", pJassInterface->Jass_ForceUIKey_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceUICancel", "()V", pJassInterface->Jass_ForceUICancel_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisplayLoadDialog", "()V", pJassInterface->Jass_DisplayLoadDialog_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTerrainFog", "(RRRRR)V", pJassInterface->Jass_SetTerrainFog_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUnitFog", "(RRRRR)V", pJassInterface->Jass_SetUnitFog_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTerrainFogEx", "(IRRRRRR)V", pJassInterface->Jass_SetTerrainFogEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("ResetTerrainFog", "()V", pJassInterface->Jass_ResetTerrainFog_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDayNightModels", "(SS)V", pJassInterface->Jass_SetDayNightModels_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSkyModel", "(S)V", pJassInterface->Jass_SetSkyModel_Hooked));
	This->m_NativeHooks.push_back(JassNative("SuspendTimeOfDay", "(B)V", pJassInterface->Jass_SuspendTimeOfDay_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTimeOfDayScale", "(R)V", pJassInterface->Jass_SetTimeOfDayScale_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTimeOfDayScale", "()R", pJassInterface->Jass_GetTimeOfDayScale_Hooked));
	This->m_NativeHooks.push_back(JassNative("ShowInterface", "(BR)V", pJassInterface->Jass_ShowInterface_Hooked));
	This->m_NativeHooks.push_back(JassNative("PauseGame", "(B)V", pJassInterface->Jass_PauseGame_Hooked));
	This->m_NativeHooks.push_back(JassNative("PingMinimap", "(RRR)V", pJassInterface->Jass_PingMinimap_Hooked));
	This->m_NativeHooks.push_back(JassNative("PingMinimapEx", "(RRRIIIB)V", pJassInterface->Jass_PingMinimapEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetIntroShotText", "(S)V", pJassInterface->Jass_SetIntroShotText_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetIntroShotModel", "(S)V", pJassInterface->Jass_SetIntroShotModel_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnableOcclusion", "(B)V", pJassInterface->Jass_EnableOcclusion_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnableWorldFogBoundary", "(B)V", pJassInterface->Jass_EnableWorldFogBoundary_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlayModelCinematic", "(S)V", pJassInterface->Jass_PlayModelCinematic_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlayCinematic", "(S)V", pJassInterface->Jass_PlayCinematic_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetAltMinimapIcon", "(S)V", pJassInterface->Jass_SetAltMinimapIcon_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateTextTag", "()Htexttag;", pJassInterface->Jass_CreateTextTag_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyTextTag", "(Htexttag;)V", pJassInterface->Jass_DestroyTextTag_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagText", "(Htexttag;SR)V", pJassInterface->Jass_SetTextTagText_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagPos", "(Htexttag;RRR)V", pJassInterface->Jass_SetTextTagPos_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagPosUnit", "(Htexttag;Hunit;R)V", pJassInterface->Jass_SetTextTagPosUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagColor", "(Htexttag;IIII)V", pJassInterface->Jass_SetTextTagColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagVelocity", "(Htexttag;RR)V", pJassInterface->Jass_SetTextTagVelocity_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagVisibility", "(Htexttag;B)V", pJassInterface->Jass_SetTextTagVisibility_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagSuspended", "(Htexttag;B)V", pJassInterface->Jass_SetTextTagSuspended_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagPermanent", "(Htexttag;B)V", pJassInterface->Jass_SetTextTagPermanent_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagAge", "(Htexttag;R)V", pJassInterface->Jass_SetTextTagAge_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagLifespan", "(Htexttag;R)V", pJassInterface->Jass_SetTextTagLifespan_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTextTagFadepoint", "(Htexttag;R)V", pJassInterface->Jass_SetTextTagFadepoint_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetReservedLocalHeroButtons", "(I)V", pJassInterface->Jass_SetReservedLocalHeroButtons_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetAllyColorFilterState", "()I", pJassInterface->Jass_GetAllyColorFilterState_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetAllyColorFilterState", "(I)V", pJassInterface->Jass_SetAllyColorFilterState_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCreepCampFilterState", "()B", pJassInterface->Jass_GetCreepCampFilterState_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCreepCampFilterState", "(B)V", pJassInterface->Jass_SetCreepCampFilterState_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnableMinimapFilterButtons", "(BB)V", pJassInterface->Jass_EnableMinimapFilterButtons_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnableDragSelect", "(BB)V", pJassInterface->Jass_EnableDragSelect_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnablePreSelect", "(BB)V", pJassInterface->Jass_EnablePreSelect_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnableSelect", "(BB)V", pJassInterface->Jass_EnableSelect_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateTrackable", "(SRRR)Htrackable;", pJassInterface->Jass_CreateTrackable_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterTrackableHitEvent", "(Htrigger;Htrackable;)Hevent;", pJassInterface->Jass_TriggerRegisterTrackableHitEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("TriggerRegisterTrackableTrackEvent", "(Htrigger;Htrackable;)Hevent;", pJassInterface->Jass_TriggerRegisterTrackableTrackEvent_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTriggeringTrackable", "()Htrackable;", pJassInterface->Jass_GetTriggeringTrackable_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateQuest", "()Hquest;", pJassInterface->Jass_CreateQuest_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyQuest", "(Hquest;)V", pJassInterface->Jass_DestroyQuest_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestSetTitle", "(Hquest;S)V", pJassInterface->Jass_QuestSetTitle_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestSetDescription", "(Hquest;S)V", pJassInterface->Jass_QuestSetDescription_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestSetIconPath", "(Hquest;S)V", pJassInterface->Jass_QuestSetIconPath_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestSetRequired", "(Hquest;B)V", pJassInterface->Jass_QuestSetRequired_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestSetCompleted", "(Hquest;B)V", pJassInterface->Jass_QuestSetCompleted_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestSetDiscovered", "(Hquest;B)V", pJassInterface->Jass_QuestSetDiscovered_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestSetFailed", "(Hquest;B)V", pJassInterface->Jass_QuestSetFailed_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestSetEnabled", "(Hquest;B)V", pJassInterface->Jass_QuestSetEnabled_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsQuestRequired", "(Hquest;)B", pJassInterface->Jass_IsQuestRequired_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsQuestCompleted", "(Hquest;)B", pJassInterface->Jass_IsQuestCompleted_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsQuestDiscovered", "(Hquest;)B", pJassInterface->Jass_IsQuestDiscovered_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsQuestFailed", "(Hquest;)B", pJassInterface->Jass_IsQuestFailed_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsQuestEnabled", "(Hquest;)B", pJassInterface->Jass_IsQuestEnabled_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestCreateItem", "(Hquest;)Hquestitem;", pJassInterface->Jass_QuestCreateItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestItemSetDescription", "(Hquestitem;S)V", pJassInterface->Jass_QuestItemSetDescription_Hooked));
	This->m_NativeHooks.push_back(JassNative("QuestItemSetCompleted", "(Hquestitem;B)V", pJassInterface->Jass_QuestItemSetCompleted_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsQuestItemCompleted", "(Hquestitem;)B", pJassInterface->Jass_IsQuestItemCompleted_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateDefeatCondition", "()Hdefeatcondition;", pJassInterface->Jass_CreateDefeatCondition_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyDefeatCondition", "(Hdefeatcondition;)V", pJassInterface->Jass_DestroyDefeatCondition_Hooked));
	This->m_NativeHooks.push_back(JassNative("DefeatConditionSetDescription", "(Hdefeatcondition;S)V", pJassInterface->Jass_DefeatConditionSetDescription_Hooked));
	This->m_NativeHooks.push_back(JassNative("FlashQuestDialogButton", "()V", pJassInterface->Jass_FlashQuestDialogButton_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceQuestDialogUpdate", "()V", pJassInterface->Jass_ForceQuestDialogUpdate_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateTimerDialog", "(Htimer;)Htimerdialog;", pJassInterface->Jass_CreateTimerDialog_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyTimerDialog", "(Htimerdialog;)V", pJassInterface->Jass_DestroyTimerDialog_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerDialogSetTitle", "(Htimerdialog;S)V", pJassInterface->Jass_TimerDialogSetTitle_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerDialogSetTitleColor", "(Htimerdialog;IIII)V", pJassInterface->Jass_TimerDialogSetTitleColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerDialogSetTimeColor", "(Htimerdialog;IIII)V", pJassInterface->Jass_TimerDialogSetTimeColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerDialogSetSpeed", "(Htimerdialog;R)V", pJassInterface->Jass_TimerDialogSetSpeed_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerDialogDisplay", "(Htimerdialog;B)V", pJassInterface->Jass_TimerDialogDisplay_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsTimerDialogDisplayed", "(Htimerdialog;)B", pJassInterface->Jass_IsTimerDialogDisplayed_Hooked));
	This->m_NativeHooks.push_back(JassNative("TimerDialogSetRealTimeRemaining", "(Htimerdialog;R)V", pJassInterface->Jass_TimerDialogSetRealTimeRemaining_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateLeaderboard", "()Hleaderboard;", pJassInterface->Jass_CreateLeaderboard_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyLeaderboard", "(Hleaderboard;)V", pJassInterface->Jass_DestroyLeaderboard_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardGetItemCount", "(Hleaderboard;)I", pJassInterface->Jass_LeaderboardGetItemCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetSizeByItemCount", "(Hleaderboard;I)V", pJassInterface->Jass_LeaderboardSetSizeByItemCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardAddItem", "(Hleaderboard;SIHplayer;)V", pJassInterface->Jass_LeaderboardAddItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardRemoveItem", "(Hleaderboard;I)V", pJassInterface->Jass_LeaderboardRemoveItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardRemovePlayerItem", "(Hleaderboard;Hplayer;)V", pJassInterface->Jass_LeaderboardRemovePlayerItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSortItemsByValue", "(Hleaderboard;B)V", pJassInterface->Jass_LeaderboardSortItemsByValue_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSortItemsByPlayer", "(Hleaderboard;B)V", pJassInterface->Jass_LeaderboardSortItemsByPlayer_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSortItemsByLabel", "(Hleaderboard;B)V", pJassInterface->Jass_LeaderboardSortItemsByLabel_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardClear", "(Hleaderboard;)V", pJassInterface->Jass_LeaderboardClear_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardDisplay", "(Hleaderboard;B)V", pJassInterface->Jass_LeaderboardDisplay_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsLeaderboardDisplayed", "(Hleaderboard;)B", pJassInterface->Jass_IsLeaderboardDisplayed_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardGetLabelText", "(Hleaderboard;)S", pJassInterface->Jass_LeaderboardGetLabelText_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlayerSetLeaderboard", "(Hplayer;Hleaderboard;)V", pJassInterface->Jass_PlayerSetLeaderboard_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlayerGetLeaderboard", "(Hplayer;)Hleaderboard;", pJassInterface->Jass_PlayerGetLeaderboard_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardHasPlayerItem", "(Hleaderboard;Hplayer;)B", pJassInterface->Jass_LeaderboardHasPlayerItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardGetPlayerIndex", "(Hleaderboard;Hplayer;)I", pJassInterface->Jass_LeaderboardGetPlayerIndex_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetLabel", "(Hleaderboard;S)V", pJassInterface->Jass_LeaderboardSetLabel_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetLabelColor", "(Hleaderboard;IIII)V", pJassInterface->Jass_LeaderboardSetLabelColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetValueColor", "(Hleaderboard;IIII)V", pJassInterface->Jass_LeaderboardSetValueColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetStyle", "(Hleaderboard;BBBB)V", pJassInterface->Jass_LeaderboardSetStyle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetItemValue", "(Hleaderboard;II)V", pJassInterface->Jass_LeaderboardSetItemValue_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetItemLabel", "(Hleaderboard;IS)V", pJassInterface->Jass_LeaderboardSetItemLabel_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetItemStyle", "(Hleaderboard;IBBB)V", pJassInterface->Jass_LeaderboardSetItemStyle_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetItemLabelColor", "(Hleaderboard;IIIII)V", pJassInterface->Jass_LeaderboardSetItemLabelColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("LeaderboardSetItemValueColor", "(Hleaderboard;IIIII)V", pJassInterface->Jass_LeaderboardSetItemValueColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateMultiboard", "()Hmultiboard;", pJassInterface->Jass_CreateMultiboard_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyMultiboard", "(Hmultiboard;)V", pJassInterface->Jass_DestroyMultiboard_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardDisplay", "(Hmultiboard;B)V", pJassInterface->Jass_MultiboardDisplay_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardMinimize", "(Hmultiboard;B)V", pJassInterface->Jass_MultiboardMinimize_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsMultiboardDisplayed", "(Hmultiboard;)B", pJassInterface->Jass_IsMultiboardDisplayed_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsMultiboardMinimized", "(Hmultiboard;)B", pJassInterface->Jass_IsMultiboardMinimized_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardClear", "(Hmultiboard;)V", pJassInterface->Jass_MultiboardClear_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetTitleText", "(Hmultiboard;S)V", pJassInterface->Jass_MultiboardSetTitleText_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardGetTitleText", "(Hmultiboard;)S", pJassInterface->Jass_MultiboardGetTitleText_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetTitleTextColor", "(Hmultiboard;IIII)V", pJassInterface->Jass_MultiboardSetTitleTextColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardGetRowCount", "(Hmultiboard;)I", pJassInterface->Jass_MultiboardGetRowCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardGetColumnCount", "(Hmultiboard;)I", pJassInterface->Jass_MultiboardGetColumnCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetColumnCount", "(Hmultiboard;I)V", pJassInterface->Jass_MultiboardSetColumnCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetRowCount", "(Hmultiboard;I)V", pJassInterface->Jass_MultiboardSetRowCount_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemsStyle", "(Hmultiboard;BB)V", pJassInterface->Jass_MultiboardSetItemsStyle_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemsValueColor", "(Hmultiboard;IIII)V", pJassInterface->Jass_MultiboardSetItemsValueColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemsValue", "(Hmultiboard;S)V", pJassInterface->Jass_MultiboardSetItemsValue_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemsWidth", "(Hmultiboard;R)V", pJassInterface->Jass_MultiboardSetItemsWidth_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemsIcon", "(Hmultiboard;S)V", pJassInterface->Jass_MultiboardSetItemsIcon_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardGetItem", "(Hmultiboard;II)Hmultiboarditem;", pJassInterface->Jass_MultiboardGetItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardReleaseItem", "(Hmultiboarditem;)V", pJassInterface->Jass_MultiboardReleaseItem_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemStyle", "(Hmultiboarditem;BB)V", pJassInterface->Jass_MultiboardSetItemStyle_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemValue", "(Hmultiboarditem;S)V", pJassInterface->Jass_MultiboardSetItemValue_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemValueColor", "(Hmultiboarditem;IIII)V", pJassInterface->Jass_MultiboardSetItemValueColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemWidth", "(Hmultiboarditem;R)V", pJassInterface->Jass_MultiboardSetItemWidth_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSetItemIcon", "(Hmultiboarditem;S)V", pJassInterface->Jass_MultiboardSetItemIcon_Hooked));
	This->m_NativeHooks.push_back(JassNative("MultiboardSuppressDisplay", "(B)V", pJassInterface->Jass_MultiboardSuppressDisplay_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCameraBounds", "(RRRRRRRR)V", pJassInterface->Jass_SetCameraBounds_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCameraPosition", "(RR)V", pJassInterface->Jass_SetCameraPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCameraQuickPosition", "(RR)V", pJassInterface->Jass_SetCameraQuickPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("ResetToGameCamera", "(R)V", pJassInterface->Jass_ResetToGameCamera_Hooked));
	This->m_NativeHooks.push_back(JassNative("StopCamera", "()V", pJassInterface->Jass_StopCamera_Hooked));
	This->m_NativeHooks.push_back(JassNative("PanCameraTo", "(RR)V", pJassInterface->Jass_PanCameraTo_Hooked));
	This->m_NativeHooks.push_back(JassNative("PanCameraToTimed", "(RRR)V", pJassInterface->Jass_PanCameraToTimed_Hooked));
	This->m_NativeHooks.push_back(JassNative("PanCameraToWithZ", "(RRR)V", pJassInterface->Jass_PanCameraToWithZ_Hooked));
	This->m_NativeHooks.push_back(JassNative("PanCameraToTimedWithZ", "(RRRR)V", pJassInterface->Jass_PanCameraToTimedWithZ_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCinematicCamera", "(S)V", pJassInterface->Jass_SetCinematicCamera_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCameraField", "(Hcamerafield;RR)V", pJassInterface->Jass_SetCameraField_Hooked));
	This->m_NativeHooks.push_back(JassNative("AdjustCameraField", "(Hcamerafield;RR)V", pJassInterface->Jass_AdjustCameraField_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCameraTargetController", "(Hunit;RRB)V", pJassInterface->Jass_SetCameraTargetController_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCameraOrientController", "(Hunit;RR)V", pJassInterface->Jass_SetCameraOrientController_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCameraRotateMode", "(RRRR)V", pJassInterface->Jass_SetCameraRotateMode_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateCameraSetup", "()Hcamerasetup;", pJassInterface->Jass_CreateCameraSetup_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupSetField", "(Hcamerasetup;Hcamerafield;RR)V", pJassInterface->Jass_CameraSetupSetField_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupGetField", "(Hcamerasetup;Hcamerafield;)R", pJassInterface->Jass_CameraSetupGetField_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupSetDestPosition", "(Hcamerasetup;RRR)V", pJassInterface->Jass_CameraSetupSetDestPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupGetDestPositionLoc", "(Hcamerasetup;)Hlocation;", pJassInterface->Jass_CameraSetupGetDestPositionLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupGetDestPositionX", "(Hcamerasetup;)R", pJassInterface->Jass_CameraSetupGetDestPositionX_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupGetDestPositionY", "(Hcamerasetup;)R", pJassInterface->Jass_CameraSetupGetDestPositionY_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupApply", "(Hcamerasetup;BB)V", pJassInterface->Jass_CameraSetupApply_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupApplyWithZ", "(Hcamerasetup;R)V", pJassInterface->Jass_CameraSetupApplyWithZ_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupApplyForceDuration", "(Hcamerasetup;BR)V", pJassInterface->Jass_CameraSetupApplyForceDuration_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetupApplyForceDurationWithZ", "(Hcamerasetup;RR)V", pJassInterface->Jass_CameraSetupApplyForceDurationWithZ_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetTargetNoise", "(RR)V", pJassInterface->Jass_CameraSetTargetNoise_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetSourceNoise", "(RR)V", pJassInterface->Jass_CameraSetSourceNoise_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetTargetNoiseEx", "(RRB)V", pJassInterface->Jass_CameraSetTargetNoiseEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetSourceNoiseEx", "(RRB)V", pJassInterface->Jass_CameraSetSourceNoiseEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("CameraSetSmoothingFactor", "(R)V", pJassInterface->Jass_CameraSetSmoothingFactor_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraMargin", "(I)R", pJassInterface->Jass_GetCameraMargin_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraBoundMinX", "()R", pJassInterface->Jass_GetCameraBoundMinX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraBoundMinY", "()R", pJassInterface->Jass_GetCameraBoundMinY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraBoundMaxX", "()R", pJassInterface->Jass_GetCameraBoundMaxX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraBoundMaxY", "()R", pJassInterface->Jass_GetCameraBoundMaxY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraField", "(Hcamerafield;)R", pJassInterface->Jass_GetCameraField_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraTargetPositionX", "()R", pJassInterface->Jass_GetCameraTargetPositionX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraTargetPositionY", "()R", pJassInterface->Jass_GetCameraTargetPositionY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraTargetPositionZ", "()R", pJassInterface->Jass_GetCameraTargetPositionZ_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraTargetPositionLoc", "()Hlocation;", pJassInterface->Jass_GetCameraTargetPositionLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraEyePositionX", "()R", pJassInterface->Jass_GetCameraEyePositionX_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraEyePositionY", "()R", pJassInterface->Jass_GetCameraEyePositionY_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraEyePositionZ", "()R", pJassInterface->Jass_GetCameraEyePositionZ_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetCameraEyePositionLoc", "()Hlocation;", pJassInterface->Jass_GetCameraEyePositionLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCineFilterTexture", "(S)V", pJassInterface->Jass_SetCineFilterTexture_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCineFilterBlendMode", "(Hblendmode;)V", pJassInterface->Jass_SetCineFilterBlendMode_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCineFilterTexMapFlags", "(Htexmapflags;)V", pJassInterface->Jass_SetCineFilterTexMapFlags_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCineFilterStartUV", "(RRRR)V", pJassInterface->Jass_SetCineFilterStartUV_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCineFilterEndUV", "(RRRR)V", pJassInterface->Jass_SetCineFilterEndUV_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCineFilterStartColor", "(IIII)V", pJassInterface->Jass_SetCineFilterStartColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCineFilterEndColor", "(IIII)V", pJassInterface->Jass_SetCineFilterEndColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCineFilterDuration", "(R)V", pJassInterface->Jass_SetCineFilterDuration_Hooked));
	This->m_NativeHooks.push_back(JassNative("DisplayCineFilter", "(B)V", pJassInterface->Jass_DisplayCineFilter_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsCineFilterDisplayed", "()B", pJassInterface->Jass_IsCineFilterDisplayed_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetCinematicScene", "(IHplayercolor;SSRR)V", pJassInterface->Jass_SetCinematicScene_Hooked));
	This->m_NativeHooks.push_back(JassNative("EndCinematicScene", "()V", pJassInterface->Jass_EndCinematicScene_Hooked));
	This->m_NativeHooks.push_back(JassNative("ForceCinematicSubtitles", "(B)V", pJassInterface->Jass_ForceCinematicSubtitles_Hooked));
	This->m_NativeHooks.push_back(JassNative("NewSoundEnvironment", "(S)V", pJassInterface->Jass_NewSoundEnvironment_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateSound", "(SBBBIIS)Hsound;", pJassInterface->Jass_CreateSound_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateSoundFilenameWithLabel", "(SBBBIIS)Hsound;", pJassInterface->Jass_CreateSoundFilenameWithLabel_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateSoundFromLabel", "(SBBBII)Hsound;", pJassInterface->Jass_CreateSoundFromLabel_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateMIDISound", "(SII)Hsound;", pJassInterface->Jass_CreateMIDISound_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetStackedSound", "(SRR)V", pJassInterface->Jass_SetStackedSound_Hooked));
	This->m_NativeHooks.push_back(JassNative("ClearStackedSound", "(SRR)V", pJassInterface->Jass_ClearStackedSound_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetStackedSoundRect", "(SHrect;)V", pJassInterface->Jass_SetStackedSoundRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("ClearStackedSoundRect", "(SHrect;)V", pJassInterface->Jass_ClearStackedSoundRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundParamsFromLabel", "(Hsound;S)V", pJassInterface->Jass_SetSoundParamsFromLabel_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundChannel", "(Hsound;I)V", pJassInterface->Jass_SetSoundChannel_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundVolume", "(Hsound;I)V", pJassInterface->Jass_SetSoundVolume_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundPitch", "(Hsound;R)V", pJassInterface->Jass_SetSoundPitch_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundPlayPosition", "(Hsound;I)V", pJassInterface->Jass_SetSoundPlayPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundDistances", "(Hsound;RR)V", pJassInterface->Jass_SetSoundDistances_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundDistanceCutoff", "(Hsound;R)V", pJassInterface->Jass_SetSoundDistanceCutoff_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundConeAngles", "(Hsound;RRI)V", pJassInterface->Jass_SetSoundConeAngles_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundConeOrientation", "(Hsound;RRR)V", pJassInterface->Jass_SetSoundConeOrientation_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundPosition", "(Hsound;RRR)V", pJassInterface->Jass_SetSoundPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundVelocity", "(Hsound;RRR)V", pJassInterface->Jass_SetSoundVelocity_Hooked));
	This->m_NativeHooks.push_back(JassNative("AttachSoundToUnit", "(Hsound;Hunit;)V", pJassInterface->Jass_AttachSoundToUnit_Hooked));
	This->m_NativeHooks.push_back(JassNative("StartSound", "(Hsound;)V", pJassInterface->Jass_StartSound_Hooked));
	This->m_NativeHooks.push_back(JassNative("StopSound", "(Hsound;BB)V", pJassInterface->Jass_StopSound_Hooked));
	This->m_NativeHooks.push_back(JassNative("KillSoundWhenDone", "(Hsound;)V", pJassInterface->Jass_KillSoundWhenDone_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetMapMusic", "(SBI)V", pJassInterface->Jass_SetMapMusic_Hooked));
	This->m_NativeHooks.push_back(JassNative("ClearMapMusic", "()V", pJassInterface->Jass_ClearMapMusic_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlayMusic", "(S)V", pJassInterface->Jass_PlayMusic_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlayMusicEx", "(SII)V", pJassInterface->Jass_PlayMusicEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("StopMusic", "(B)V", pJassInterface->Jass_StopMusic_Hooked));
	This->m_NativeHooks.push_back(JassNative("ResumeMusic", "()V", pJassInterface->Jass_ResumeMusic_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlayThematicMusic", "(S)V", pJassInterface->Jass_PlayThematicMusic_Hooked));
	This->m_NativeHooks.push_back(JassNative("PlayThematicMusicEx", "(SI)V", pJassInterface->Jass_PlayThematicMusicEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("EndThematicMusic", "()V", pJassInterface->Jass_EndThematicMusic_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetMusicVolume", "(I)V", pJassInterface->Jass_SetMusicVolume_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetMusicPlayPosition", "(I)V", pJassInterface->Jass_SetMusicPlayPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetThematicMusicPlayPosition", "(I)V", pJassInterface->Jass_SetThematicMusicPlayPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetSoundDuration", "(Hsound;I)V", pJassInterface->Jass_SetSoundDuration_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSoundDuration", "(Hsound;)I", pJassInterface->Jass_GetSoundDuration_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSoundFileDuration", "(S)I", pJassInterface->Jass_GetSoundFileDuration_Hooked));
	This->m_NativeHooks.push_back(JassNative("VolumeGroupSetVolume", "(Hvolumegroup;R)V", pJassInterface->Jass_VolumeGroupSetVolume_Hooked));
	This->m_NativeHooks.push_back(JassNative("VolumeGroupReset", "()V", pJassInterface->Jass_VolumeGroupReset_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSoundIsPlaying", "(Hsound;)B", pJassInterface->Jass_GetSoundIsPlaying_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetSoundIsLoading", "(Hsound;)B", pJassInterface->Jass_GetSoundIsLoading_Hooked));
	This->m_NativeHooks.push_back(JassNative("RegisterStackedSound", "(Hsound;BRR)V", pJassInterface->Jass_RegisterStackedSound_Hooked));
	This->m_NativeHooks.push_back(JassNative("UnregisterStackedSound", "(Hsound;BRR)V", pJassInterface->Jass_UnregisterStackedSound_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddWeatherEffect", "(Hrect;I)Hweathereffect;", pJassInterface->Jass_AddWeatherEffect_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveWeatherEffect", "(Hweathereffect;)V", pJassInterface->Jass_RemoveWeatherEffect_Hooked));
	This->m_NativeHooks.push_back(JassNative("EnableWeatherEffect", "(Hweathereffect;B)V", pJassInterface->Jass_EnableWeatherEffect_Hooked));
	This->m_NativeHooks.push_back(JassNative("TerrainDeformCrater", "(RRRRIB)Hterraindeformation;", pJassInterface->Jass_TerrainDeformCrater_Hooked));
	This->m_NativeHooks.push_back(JassNative("TerrainDeformRipple", "(RRRRIIRRRB)Hterraindeformation;", pJassInterface->Jass_TerrainDeformRipple_Hooked));
	This->m_NativeHooks.push_back(JassNative("TerrainDeformWave", "(RRRRRRRRII)Hterraindeformation;", pJassInterface->Jass_TerrainDeformWave_Hooked));
	This->m_NativeHooks.push_back(JassNative("TerrainDeformRandom", "(RRRRRII)Hterraindeformation;", pJassInterface->Jass_TerrainDeformRandom_Hooked));
	This->m_NativeHooks.push_back(JassNative("TerrainDeformStop", "(Hterraindeformation;I)V", pJassInterface->Jass_TerrainDeformStop_Hooked));
	This->m_NativeHooks.push_back(JassNative("TerrainDeformStopAll", "()V", pJassInterface->Jass_TerrainDeformStopAll_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyEffect", "(Heffect;)V", pJassInterface->Jass_DestroyEffect_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddSpecialEffect", "(SRR)Heffect;", pJassInterface->Jass_AddSpecialEffect_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddSpecialEffectLoc", "(SHlocation;)Heffect;", pJassInterface->Jass_AddSpecialEffectLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddSpecialEffectTarget", "(SHwidget;S)Heffect;", pJassInterface->Jass_AddSpecialEffectTarget_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddSpellEffect", "(SHeffecttype;RR)Heffect;", pJassInterface->Jass_AddSpellEffect_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddSpellEffectLoc", "(SHeffecttype;Hlocation;)Heffect;", pJassInterface->Jass_AddSpellEffectLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddSpellEffectById", "(IHeffecttype;RR)Heffect;", pJassInterface->Jass_AddSpellEffectById_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddSpellEffectByIdLoc", "(IHeffecttype;Hlocation;)Heffect;", pJassInterface->Jass_AddSpellEffectByIdLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddSpellEffectTarget", "(SHeffecttype;Hwidget;S)Heffect;", pJassInterface->Jass_AddSpellEffectTarget_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddSpellEffectTargetById", "(IHeffecttype;Hwidget;S)Heffect;", pJassInterface->Jass_AddSpellEffectTargetById_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddLightning", "(SBRRRR)Hlightning;", pJassInterface->Jass_AddLightning_Hooked));
	This->m_NativeHooks.push_back(JassNative("AddLightningEx", "(SBRRRRRR)Hlightning;", pJassInterface->Jass_AddLightningEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyLightning", "(Hlightning;)B", pJassInterface->Jass_DestroyLightning_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLightningColorA", "(Hlightning;)R", pJassInterface->Jass_GetLightningColorA_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLightningColorR", "(Hlightning;)R", pJassInterface->Jass_GetLightningColorR_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLightningColorG", "(Hlightning;)R", pJassInterface->Jass_GetLightningColorG_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetLightningColorB", "(Hlightning;)R", pJassInterface->Jass_GetLightningColorB_Hooked));
	This->m_NativeHooks.push_back(JassNative("MoveLightning", "(Hlightning;BRRRR)B", pJassInterface->Jass_MoveLightning_Hooked));
	This->m_NativeHooks.push_back(JassNative("MoveLightningEx", "(Hlightning;BRRRRRR)B", pJassInterface->Jass_MoveLightningEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetLightningColor", "(Hlightning;RRRR)B", pJassInterface->Jass_SetLightningColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetAbilityEffect", "(SHeffecttype;I)S", pJassInterface->Jass_GetAbilityEffect_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetAbilityEffectById", "(IHeffecttype;I)S", pJassInterface->Jass_GetAbilityEffectById_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetAbilitySound", "(SHsoundtype;)S", pJassInterface->Jass_GetAbilitySound_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetAbilitySoundById", "(IHsoundtype;)S", pJassInterface->Jass_GetAbilitySoundById_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTerrainCliffLevel", "(RR)I", pJassInterface->Jass_GetTerrainCliffLevel_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetWaterBaseColor", "(IIII)V", pJassInterface->Jass_SetWaterBaseColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetWaterDeforms", "(B)V", pJassInterface->Jass_SetWaterDeforms_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTerrainType", "(RR)I", pJassInterface->Jass_GetTerrainType_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetTerrainVariance", "(RR)I", pJassInterface->Jass_GetTerrainVariance_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTerrainType", "(RRIIII)V", pJassInterface->Jass_SetTerrainType_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsTerrainPathable", "(RRHpathingtype;)B", pJassInterface->Jass_IsTerrainPathable_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetTerrainPathable", "(RRHpathingtype;B)V", pJassInterface->Jass_SetTerrainPathable_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateImage", "(SRRRRRRRRRI)Himage;", pJassInterface->Jass_CreateImage_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyImage", "(Himage;)V", pJassInterface->Jass_DestroyImage_Hooked));
	This->m_NativeHooks.push_back(JassNative("ShowImage", "(Himage;B)V", pJassInterface->Jass_ShowImage_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetImageConstantHeight", "(Himage;BR)V", pJassInterface->Jass_SetImageConstantHeight_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetImagePosition", "(Himage;RRR)V", pJassInterface->Jass_SetImagePosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetImageColor", "(Himage;IIII)V", pJassInterface->Jass_SetImageColor_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetImageRender", "(Himage;B)V", pJassInterface->Jass_SetImageRender_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetImageRenderAlways", "(Himage;B)V", pJassInterface->Jass_SetImageRenderAlways_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetImageAboveWater", "(Himage;BB)V", pJassInterface->Jass_SetImageAboveWater_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetImageType", "(Himage;I)V", pJassInterface->Jass_SetImageType_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateUbersplat", "(RRSIIIIBB)Hubersplat;", pJassInterface->Jass_CreateUbersplat_Hooked));
	This->m_NativeHooks.push_back(JassNative("DestroyUbersplat", "(Hubersplat;)V", pJassInterface->Jass_DestroyUbersplat_Hooked));
	This->m_NativeHooks.push_back(JassNative("ResetUbersplat", "(Hubersplat;)V", pJassInterface->Jass_ResetUbersplat_Hooked));
	This->m_NativeHooks.push_back(JassNative("FinishUbersplat", "(Hubersplat;)V", pJassInterface->Jass_FinishUbersplat_Hooked));
	This->m_NativeHooks.push_back(JassNative("ShowUbersplat", "(Hubersplat;B)V", pJassInterface->Jass_ShowUbersplat_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUbersplatRender", "(Hubersplat;B)V", pJassInterface->Jass_SetUbersplatRender_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetUbersplatRenderAlways", "(Hubersplat;B)V", pJassInterface->Jass_SetUbersplatRenderAlways_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetBlight", "(Hplayer;RRRB)V", pJassInterface->Jass_SetBlight_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetBlightLoc", "(Hplayer;Hlocation;RB)V", pJassInterface->Jass_SetBlightLoc_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetBlightRect", "(Hplayer;Hrect;B)V", pJassInterface->Jass_SetBlightRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetBlightPoint", "(Hplayer;RRB)V", pJassInterface->Jass_SetBlightPoint_Hooked));
	This->m_NativeHooks.push_back(JassNative("CreateBlightedGoldmine", "(Hplayer;RRR)Hunit;", pJassInterface->Jass_CreateBlightedGoldmine_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsPointBlighted", "(RR)B", pJassInterface->Jass_IsPointBlighted_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDoodadAnimation", "(RRRIBSB)V", pJassInterface->Jass_SetDoodadAnimation_Hooked));
	This->m_NativeHooks.push_back(JassNative("SetDoodadAnimationRect", "(Hrect;ISB)V", pJassInterface->Jass_SetDoodadAnimationRect_Hooked));
	This->m_NativeHooks.push_back(JassNative("StartMeleeAI", "(Hplayer;S)V", pJassInterface->Jass_StartMeleeAI_Hooked));
	This->m_NativeHooks.push_back(JassNative("StartCampaignAI", "(Hplayer;S)V", pJassInterface->Jass_StartCampaignAI_Hooked));
	This->m_NativeHooks.push_back(JassNative("CommandAI", "(Hplayer;II)V", pJassInterface->Jass_CommandAI_Hooked));
	This->m_NativeHooks.push_back(JassNative("PauseCompAI", "(Hplayer;B)V", pJassInterface->Jass_PauseCompAI_Hooked));
	This->m_NativeHooks.push_back(JassNative("GetAIDifficulty", "(Hplayer;)Haidifficulty;", pJassInterface->Jass_GetAIDifficulty_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveGuardPosition", "(Hunit;)V", pJassInterface->Jass_RemoveGuardPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("RecycleGuardPosition", "(Hunit;)V", pJassInterface->Jass_RecycleGuardPosition_Hooked));
	This->m_NativeHooks.push_back(JassNative("RemoveAllGuardPositions", "(Hplayer;)V", pJassInterface->Jass_RemoveAllGuardPositions_Hooked));
	This->m_NativeHooks.push_back(JassNative("ExecuteFunc", "(S)V", pJassInterface->Jass_ExecuteFunc_Hooked));
	This->m_NativeHooks.push_back(JassNative("Cheat", "(S)V", pJassInterface->Jass_Cheat_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsNoVictoryCheat", "()B", pJassInterface->Jass_IsNoVictoryCheat_Hooked));
	This->m_NativeHooks.push_back(JassNative("IsNoDefeatCheat", "()B", pJassInterface->Jass_IsNoDefeatCheat_Hooked));
	This->m_NativeHooks.push_back(JassNative("Preload", "(S)V", pJassInterface->Jass_Preload_Hooked));
	This->m_NativeHooks.push_back(JassNative("PreloadEnd", "(R)V", pJassInterface->Jass_PreloadEnd_Hooked));
	This->m_NativeHooks.push_back(JassNative("PreloadStart", "()V", pJassInterface->Jass_PreloadStart_Hooked));
	This->m_NativeHooks.push_back(JassNative("PreloadRefresh", "()V", pJassInterface->Jass_PreloadRefresh_Hooked));
	This->m_NativeHooks.push_back(JassNative("PreloadEndEx", "()V", pJassInterface->Jass_PreloadEndEx_Hooked));
	This->m_NativeHooks.push_back(JassNative("PreloadGenStart", "()V", pJassInterface->Jass_PreloadGenStart_Hooked));
	This->m_NativeHooks.push_back(JassNative("PreloadGenClear", "()V", pJassInterface->Jass_PreloadGenClear_Hooked));
	This->m_NativeHooks.push_back(JassNative("PreloadGenEnd", "(S)V", pJassInterface->Jass_PreloadGenEnd_Hooked));
	This->m_NativeHooks.push_back(JassNative("Preloader", "(S)V", pJassInterface->Jass_Preloader_Hooked));

}

void CGameInterface::InitHooks(void)
{
	if (MH_Initialize() != MH_OK)
	{
		MessageBoxA(NULL, "Unable to initialize MinHook library.", "Warcraft Lua Engine", MB_OK | MB_ICONERROR);
		return;
	}

	if (Detours::MH_CreateHookEx((LPVOID)_LookupNative, &LookupNative_Hooked, &fLookupNative) != MH_OK)
	{
		MessageBoxA(NULL, "Unable to hook LookupNative function.", "Warcraft Lua Engine", MB_OK | MB_ICONERROR);
		return;
	}

	if (Detours::MH_CreateHookEx((LPVOID)_CGameUI__Constructor, &CGameUI__Constructor_Hooked, &fCGameUI__Constructor) != MH_OK)
	{
		MessageBoxA(NULL, "Unable to hook CGameUI__Constructor function.", "Warcraft Lua Engine", MB_OK | MB_ICONERROR);
		return;
	}

	Detours::PlantDetourJMP((BYTE*)(_ChatFunc), (BYTE*)HookChatFunc, 10);
}

void CGameInterface::AddScript(LPVOID pScript)
{
	if (pScript == nullptr)
		return;

	m_Scripts.push_back(pScript);
}

void CGameInterface::RemoveScript(LPVOID pScript)
{
	critSect.Lock();

	for (int i = 0; i < m_Scripts.size(); i++)
	{
		if (m_Scripts[i] == pScript)
		{
			m_Scripts.erase(m_Scripts.begin() + i);
			break;
		}
	}

	critSect.Unlock();
}