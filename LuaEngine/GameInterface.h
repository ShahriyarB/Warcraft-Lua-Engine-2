#pragma once

#include "Structures.h"
#include "JassDefinitions.h"
#include <vector>
#include <tlhelp32.h>

class CGameInterface;

extern CGameInterface* This;
extern LPSTR ChatText;
extern bool bChatEvent;

class CGameInterface
{
public:
	CGameInterface();
	~CGameInterface();

	void AddScript(LPVOID pScript);
	void RemoveScript(LPVOID pScript);
	void Init(LPVOID pParent);
//	-------------------------------------
//	|			Hook Stuff				|
//	-------------------------------------
public:
	static int __fastcall LookupNative_Hooked(LPSTR FuncName);
	static int __fastcall CGameUI__Constructor_Hooked(GameUI *ui, LPVOID _edx);

	HANDLE hGameUI;
	HANDLE hLookupNative;

	GameUI *m_GameUI;

// ----------------------------------
// |  Our functions to use in lua	|
// ----------------------------------
///////////////////////////////////////////////////
	static bool InGame(bool bPause);
	static bool InGameOrLoadingscreen(bool bPause);
	static void WriteText(LPCSTR message, int32 frame, float duration);
	static void ExecuteCmd(unit ounit, DWORD cmdId, float X, float Y, unit target);
	static LPCSTR GetMapName();
	static luabridge::LuaRef GetPlugins(lua_State* L);
	static LPCSTR jStr2cStr(string JSID);
	static LPCSTR jParamStr2cStr(handle hStr);
	static void cStr2jStr(LPCSTR szString, JassString* String);
	static handle cStr2jStr_lua(LPCSTR szString);
	static float GetFloat(handle pF);
	static handle MakeFloat(float f);
	static int32 GetAbilityState(unit unt, int abilityID);
	static bool SendChat(std::string message, bool bSendAll);
	static LPCSTR GetVersion();

///////////////////////////////////////////////////
// ------------------------------------
// | Functions that we do not export  |
// ------------------------------------

	static Unit* GetUnitFromHandle(unit hUnit);
	static Unit* GetSelectedUnit();
	static DWORD GetPlayerNumber();
	static DWORD GetPlayerByNumber(DWORD plNum);
	static DWORD GetPlayer();
	static void SelectUnit(Unit* unit);
	void WriteAbout();
	int32 GetGameStateValue(void);

	std::vector <JassNative> m_NativeHooks;
	std::vector <LPVOID> m_Scripts;
private:
	void InitNativeHooks(void);
	void InitHooks(void);	

	static std::vector <LPVOID> m_Memory;
	static HWND wnd;
	DWORD TlsValue, TlsIndex;
	DWORD GetW3TlsForIndex(DWORD index);
	CCriticalSection critSect;

	void GetTlsValue(void);
};

