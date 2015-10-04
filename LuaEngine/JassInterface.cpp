#include "stdafx.h"
#include "GameInterface.h"
#include "JassInterface.h"
#include "LuaScript.h"

LPVOID CJassInterface::lpParent = nullptr;

CJassInterface::CJassInterface()
{
}

CJassInterface::~CJassInterface()
{
}

void CJassInterface::Init(LPVOID pParent)
{
	lpParent = pParent;
}

bool CJassInterface::InGameOrLoadingscreen(bool bPause)
{
	return ((CGameInterface*)lpParent)->InGameOrLoadingscreen(bPause);
}

LPCSTR CJassInterface::jStr2cStr(string JSID)
{
	return ((CGameInterface*)lpParent)->jStr2cStr(JSID);
}

std::vector<handle> CJassInterface::OnNativeCalled_Pre(std::string name, int paramCount, handle p1, handle p2, handle p3, handle p4, handle p5, handle p6, handle p7, handle p8, handle p9, handle p10, handle p11)
{
	std::vector<handle> finalRet;

	for (auto script : ((CGameInterface*)lpParent)->m_Scripts){
		if (script != nullptr){
			auto ret = ((CLuaScript*)script)->OnNativeCalled_Pre(name, paramCount, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
			if (!ret.empty())
				finalRet = ret;
		}
	}

	return finalRet;
}

/* Jass Hooks */

#pragma region Native Hooks

nothing CJassInterface::Jass_DebugS_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DebugS", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DebugS;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DebugS", 0);

	return;
}

nothing CJassInterface::Jass_DebugFI_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("DebugFI", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _DebugFI;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("DebugFI", 0);

	return;
}

nothing CJassInterface::Jass_DebugUnitID_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("DebugUnitID", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _DebugUnitID;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("DebugUnitID", 0);

	return;
}

nothing CJassInterface::Jass_DisplayText_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("DisplayText", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _DisplayText;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("DisplayText", 0);

	return;
}

nothing CJassInterface::Jass_DisplayTextI_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("DisplayTextI", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DisplayTextI;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("DisplayTextI", 0);

	return;
}

nothing CJassInterface::Jass_DisplayTextII_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("DisplayTextII", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DisplayTextII;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("DisplayTextII", 0);

	return;
}

nothing CJassInterface::Jass_DisplayTextIII_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("DisplayTextIII", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DisplayTextIII;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("DisplayTextIII", 0);

	return;
}

nothing CJassInterface::Jass_SuicideUnit_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SuicideUnit", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SuicideUnit;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SuicideUnit", 0);

	return;
}

nothing CJassInterface::Jass_SuicideUnitEx_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SuicideUnitEx", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SuicideUnitEx;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SuicideUnitEx", 0);

	return;
}

nothing CJassInterface::Jass_Sleep_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("Sleep", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Sleep;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("Sleep", 0);

	return;
}

nothing CJassInterface::Jass_StartThread_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("StartThread", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _StartThread;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("StartThread", 0);

	return;
}

integer CJassInterface::Jass_GetAiPlayer_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetAiPlayer", 0);

	__asm call _GetAiPlayer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetAiPlayer", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_DoAiScriptDebug_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("DoAiScriptDebug", 0);

	__asm call _DoAiScriptDebug;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("DoAiScriptDebug", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetHeroId_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetHeroId", 0);

	__asm call _GetHeroId;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetHeroId", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetHeroLevelAI_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetHeroLevelAI", 0);

	__asm call _GetHeroLevelAI;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetHeroLevelAI", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetHeroLevels_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetHeroLevels", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetHeroLevels;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetHeroLevels", 0);

	return;
}

nothing CJassInterface::Jass_SetNewHeroes_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetNewHeroes", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetNewHeroes;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetNewHeroes", 0);

	return;
}

integer CJassInterface::Jass_GetUnitCount_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitCount", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitCount", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetPlayerUnitTypeCount_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerUnitTypeCount", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerUnitTypeCount;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetPlayerUnitTypeCount", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetTownUnitCount_Hooked(handle P1, handle P2, handle P3)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTownUnitCount", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetTownUnitCount;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetTownUnitCount", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitCountDone_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitCountDone", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitCountDone;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitCountDone", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUpgradeLevel_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUpgradeLevel", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUpgradeLevel;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUpgradeLevel", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitGoldCost_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitGoldCost", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitGoldCost;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitGoldCost", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitWoodCost_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitWoodCost", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitWoodCost;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitWoodCost", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitBuildTime_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitBuildTime", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitBuildTime;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitBuildTime", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUpgradeGoldCost_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUpgradeGoldCost", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUpgradeGoldCost;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUpgradeGoldCost", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUpgradeWoodCost_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUpgradeWoodCost", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUpgradeWoodCost;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUpgradeWoodCost", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetEnemyPower_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetEnemyPower", 0);

	__asm call _GetEnemyPower;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEnemyPower", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetMinesOwned_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetMinesOwned", 0);

	__asm call _GetMinesOwned;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetMinesOwned", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetGoldOwned_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetGoldOwned", 0);

	__asm call _GetGoldOwned;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetGoldOwned", retValue);

	return retValue;
}

integer CJassInterface::Jass_TownWithMine_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("TownWithMine", 0);

	__asm call _TownWithMine;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("TownWithMine", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_TownHasMine_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("TownHasMine", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TownHasMine;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("TownHasMine", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_TownHasHall_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("TownHasHall", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TownHasHall;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("TownHasHall", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetNextExpansion_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetNextExpansion", 0);

	__asm call _GetNextExpansion;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetNextExpansion", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetExpansionPeon_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetExpansionPeon", 0);

	__asm call _GetExpansionPeon;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetExpansionPeon", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEnemyExpansion_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEnemyExpansion", 0);

	__asm call _GetEnemyExpansion;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEnemyExpansion", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SetExpansion_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SetExpansion", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetExpansion;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("SetExpansion", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetBuilding_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetBuilding", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetBuilding;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetBuilding", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetAllianceTarget_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetAllianceTarget", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetAllianceTarget;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetAllianceTarget", 0);

	return;
}

handle CJassInterface::Jass_GetAllianceTarget_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetAllianceTarget", 0);

	__asm call _GetAllianceTarget;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetAllianceTarget", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SetProduce_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SetProduce", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetProduce;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("SetProduce", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_MergeUnits_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("MergeUnits", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MergeUnits;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("MergeUnits", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_ConvertUnits_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("ConvertUnits", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ConvertUnits;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("ConvertUnits", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SetUpgrade_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SetUpgrade", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetUpgrade;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("SetUpgrade", retValue);

	return retValue;
}

nothing CJassInterface::Jass_Unsummon_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("Unsummon", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Unsummon;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("Unsummon", 0);

	return;
}

nothing CJassInterface::Jass_ClearHarvestAI_Hooked()
{
	auto params = OnNativeCalled_Pre("ClearHarvestAI", 0);

	__asm call _ClearHarvestAI;

	OnNativeCalled_Post_NoParam("ClearHarvestAI", 0);

	return;
}

nothing CJassInterface::Jass_HarvestGold_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("HarvestGold", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _HarvestGold;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("HarvestGold", 0);

	return;
}

nothing CJassInterface::Jass_HarvestWood_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("HarvestWood", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _HarvestWood;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("HarvestWood", 0);

	return;
}

nothing CJassInterface::Jass_StopGathering_Hooked()
{
	auto params = OnNativeCalled_Pre("StopGathering", 0);

	__asm call _StopGathering;

	OnNativeCalled_Post_NoParam("StopGathering", 0);

	return;
}

nothing CJassInterface::Jass_AddGuardPost_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("AddGuardPost", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddGuardPost;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("AddGuardPost", 0);

	return;
}

nothing CJassInterface::Jass_FillGuardPosts_Hooked()
{
	auto params = OnNativeCalled_Pre("FillGuardPosts", 0);

	__asm call _FillGuardPosts;

	OnNativeCalled_Post_NoParam("FillGuardPosts", 0);

	return;
}

nothing CJassInterface::Jass_ReturnGuardPosts_Hooked()
{
	auto params = OnNativeCalled_Pre("ReturnGuardPosts", 0);

	__asm call _ReturnGuardPosts;

	OnNativeCalled_Post_NoParam("ReturnGuardPosts", 0);

	return;
}

nothing CJassInterface::Jass_CreateCaptains_Hooked()
{
	auto params = OnNativeCalled_Pre("CreateCaptains", 0);

	__asm call _CreateCaptains;

	OnNativeCalled_Post_NoParam("CreateCaptains", 0);

	return;
}

nothing CJassInterface::Jass_SetCaptainHome_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetCaptainHome", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCaptainHome;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetCaptainHome", 0);

	return;
}

nothing CJassInterface::Jass_ResetCaptainLocs_Hooked()
{
	auto params = OnNativeCalled_Pre("ResetCaptainLocs", 0);

	__asm call _ResetCaptainLocs;

	OnNativeCalled_Post_NoParam("ResetCaptainLocs", 0);

	return;
}

nothing CJassInterface::Jass_ShiftTownSpot_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ShiftTownSpot", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ShiftTownSpot;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ShiftTownSpot", 0);

	return;
}

nothing CJassInterface::Jass_SetCaptainChanges_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCaptainChanges", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCaptainChanges;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCaptainChanges", 0);

	return;
}

nothing CJassInterface::Jass_TeleportCaptain_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TeleportCaptain", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TeleportCaptain;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TeleportCaptain", 0);

	return;
}

nothing CJassInterface::Jass_ClearCaptainTargets_Hooked()
{
	auto params = OnNativeCalled_Pre("ClearCaptainTargets", 0);

	__asm call _ClearCaptainTargets;

	OnNativeCalled_Post_NoParam("ClearCaptainTargets", 0);

	return;
}

nothing CJassInterface::Jass_CaptainVsUnits_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("CaptainVsUnits", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _CaptainVsUnits;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("CaptainVsUnits", 0);

	return;
}

nothing CJassInterface::Jass_CaptainVsPlayer_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("CaptainVsPlayer", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _CaptainVsPlayer;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("CaptainVsPlayer", 0);

	return;
}

nothing CJassInterface::Jass_CaptainAttack_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("CaptainAttack", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _CaptainAttack;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("CaptainAttack", 0);

	return;
}

nothing CJassInterface::Jass_GroupTimedLife_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("GroupTimedLife", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GroupTimedLife;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("GroupTimedLife", 0);

	return;
}

nothing CJassInterface::Jass_CaptainGoHome_Hooked()
{
	auto params = OnNativeCalled_Pre("CaptainGoHome", 0);

	__asm call _CaptainGoHome;

	OnNativeCalled_Post_NoParam("CaptainGoHome", 0);

	return;
}

jboolean CJassInterface::Jass_CaptainIsHome_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("CaptainIsHome", 0);

	__asm call _CaptainIsHome;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CaptainIsHome", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_CaptainRetreating_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("CaptainRetreating", 0);

	__asm call _CaptainRetreating;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CaptainRetreating", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_CaptainIsFull_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("CaptainIsFull", 0);

	__asm call _CaptainIsFull;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CaptainIsFull", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_CaptainIsEmpty_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("CaptainIsEmpty", 0);

	__asm call _CaptainIsEmpty;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CaptainIsEmpty", retValue);

	return retValue;
}

integer CJassInterface::Jass_CaptainGroupSize_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("CaptainGroupSize", 0);

	__asm call _CaptainGroupSize;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CaptainGroupSize", retValue);

	return retValue;
}

integer CJassInterface::Jass_CaptainReadiness_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("CaptainReadiness", 0);

	__asm call _CaptainReadiness;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CaptainReadiness", retValue);

	return retValue;
}

integer CJassInterface::Jass_CaptainReadinessHP_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("CaptainReadinessHP", 0);

	__asm call _CaptainReadinessHP;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CaptainReadinessHP", retValue);

	return retValue;
}

integer CJassInterface::Jass_CaptainReadinessMa_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("CaptainReadinessMa", 0);

	__asm call _CaptainReadinessMa;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CaptainReadinessMa", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_CaptainInCombat_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("CaptainInCombat", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _CaptainInCombat;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("CaptainInCombat", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_TownThreatened_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("TownThreatened", 0);

	__asm call _TownThreatened;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("TownThreatened", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_CaptainAtGoal_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("CaptainAtGoal", 0);

	__asm call _CaptainAtGoal;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CaptainAtGoal", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_CreepsOnMap_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("CreepsOnMap", 0);

	__asm call _CreepsOnMap;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreepsOnMap", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemoveInjuries_Hooked()
{
	auto params = OnNativeCalled_Pre("RemoveInjuries", 0);

	__asm call _RemoveInjuries;

	OnNativeCalled_Post_NoParam("RemoveInjuries", 0);

	return;
}

nothing CJassInterface::Jass_RemoveSiege_Hooked()
{
	auto params = OnNativeCalled_Pre("RemoveSiege", 0);

	__asm call _RemoveSiege;

	OnNativeCalled_Post_NoParam("RemoveSiege", 0);

	return;
}

jboolean CJassInterface::Jass_IsTowered_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsTowered", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsTowered;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsTowered", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DisablePathing_Hooked()
{
	auto params = OnNativeCalled_Pre("DisablePathing", 0);

	__asm call _DisablePathing;

	OnNativeCalled_Post_NoParam("DisablePathing", 0);

	return;
}

nothing CJassInterface::Jass_SetAmphibious_Hooked()
{
	auto params = OnNativeCalled_Pre("SetAmphibious", 0);

	__asm call _SetAmphibious;

	OnNativeCalled_Post_NoParam("SetAmphibious", 0);

	return;
}

nothing CJassInterface::Jass_InitAssault_Hooked()
{
	auto params = OnNativeCalled_Pre("InitAssault", 0);

	__asm call _InitAssault;

	OnNativeCalled_Post_NoParam("InitAssault", 0);

	return;
}

jboolean CJassInterface::Jass_AddAssault_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("AddAssault", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _AddAssault;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("AddAssault", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_AddDefenders_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("AddDefenders", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _AddDefenders;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("AddDefenders", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetCreepCamp_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetCreepCamp", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetCreepCamp;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetCreepCamp", retValue);

	return retValue;
}

nothing CJassInterface::Jass_StartGetEnemyBase_Hooked()
{
	auto params = OnNativeCalled_Pre("StartGetEnemyBase", 0);

	__asm call _StartGetEnemyBase;

	OnNativeCalled_Post_NoParam("StartGetEnemyBase", 0);

	return;
}

jboolean CJassInterface::Jass_WaitGetEnemyBase_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("WaitGetEnemyBase", 0);

	__asm call _WaitGetEnemyBase;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("WaitGetEnemyBase", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetMegaTarget_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetMegaTarget", 0);

	__asm call _GetMegaTarget;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetMegaTarget", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEnemyBase_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEnemyBase", 0);

	__asm call _GetEnemyBase;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEnemyBase", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetExpansionFoe_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetExpansionFoe", 0);

	__asm call _GetExpansionFoe;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetExpansionFoe", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetExpansionX_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetExpansionX", 0);

	__asm call _GetExpansionX;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetExpansionX", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetExpansionY_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetExpansionY", 0);

	__asm call _GetExpansionY;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetExpansionY", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetStagePoint_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetStagePoint", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetStagePoint;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetStagePoint", 0);

	return;
}

nothing CJassInterface::Jass_AttackMoveKill_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("AttackMoveKill", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _AttackMoveKill;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("AttackMoveKill", 0);

	return;
}

nothing CJassInterface::Jass_AttackMoveXY_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("AttackMoveXY", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _AttackMoveXY;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("AttackMoveXY", 0);

	return;
}

nothing CJassInterface::Jass_LoadZepWave_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LoadZepWave", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LoadZepWave;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LoadZepWave", 0);

	return;
}

jboolean CJassInterface::Jass_SuicidePlayer_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SuicidePlayer", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SuicidePlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("SuicidePlayer", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SuicidePlayerUnits_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SuicidePlayerUnits", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SuicidePlayerUnits;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("SuicidePlayerUnits", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitAlive_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitAlive", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitAlive;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("UnitAlive", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitInvis_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitInvis", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitInvis;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("UnitInvis", retValue);

	return retValue;
}

integer CJassInterface::Jass_IgnoredUnits_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("IgnoredUnits", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IgnoredUnits;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IgnoredUnits", retValue);

	return retValue;
}

integer CJassInterface::Jass_CommandsWaiting_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("CommandsWaiting", 0);

	__asm call _CommandsWaiting;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CommandsWaiting", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetLastCommand_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetLastCommand", 0);

	__asm call _GetLastCommand;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetLastCommand", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetLastData_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetLastData", 0);

	__asm call _GetLastData;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetLastData", retValue);

	return retValue;
}

nothing CJassInterface::Jass_PopLastCommand_Hooked()
{
	auto params = OnNativeCalled_Pre("PopLastCommand", 0);

	__asm call _PopLastCommand;

	OnNativeCalled_Post_NoParam("PopLastCommand", 0);

	return;
}

nothing CJassInterface::Jass_SetCampaignAI_Hooked()
{
	auto params = OnNativeCalled_Pre("SetCampaignAI", 0);

	__asm call _SetCampaignAI;

	OnNativeCalled_Post_NoParam("SetCampaignAI", 0);

	return;
}

nothing CJassInterface::Jass_SetMeleeAI_Hooked()
{
	auto params = OnNativeCalled_Pre("SetMeleeAI", 0);

	__asm call _SetMeleeAI;

	OnNativeCalled_Post_NoParam("SetMeleeAI", 0);

	return;
}

nothing CJassInterface::Jass_SetTargetHeroes_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetTargetHeroes", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetTargetHeroes;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetTargetHeroes", 0);

	return;
}

nothing CJassInterface::Jass_SetHeroesFlee_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetHeroesFlee", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetHeroesFlee;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetHeroesFlee", 0);

	return;
}

nothing CJassInterface::Jass_SetHeroesBuyItems_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetHeroesBuyItems", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetHeroesBuyItems;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetHeroesBuyItems", 0);

	return;
}

nothing CJassInterface::Jass_SetIgnoreInjured_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetIgnoreInjured", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetIgnoreInjured;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetIgnoreInjured", 0);

	return;
}

nothing CJassInterface::Jass_SetPeonsRepair_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetPeonsRepair", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetPeonsRepair;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetPeonsRepair", 0);

	return;
}

nothing CJassInterface::Jass_SetRandomPaths_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetRandomPaths", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetRandomPaths;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetRandomPaths", 0);

	return;
}

nothing CJassInterface::Jass_SetDefendPlayer_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetDefendPlayer", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetDefendPlayer;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetDefendPlayer", 0);

	return;
}

nothing CJassInterface::Jass_SetHeroesTakeItems_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetHeroesTakeItems", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetHeroesTakeItems;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetHeroesTakeItems", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitsFlee_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetUnitsFlee", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetUnitsFlee;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetUnitsFlee", 0);

	return;
}

nothing CJassInterface::Jass_SetGroupsFlee_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetGroupsFlee", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetGroupsFlee;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetGroupsFlee", 0);

	return;
}

nothing CJassInterface::Jass_SetSlowChopping_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetSlowChopping", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetSlowChopping;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetSlowChopping", 0);

	return;
}

nothing CJassInterface::Jass_SetSmartArtillery_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetSmartArtillery", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetSmartArtillery;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetSmartArtillery", 0);

	return;
}

nothing CJassInterface::Jass_SetWatchMegaTargets_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetWatchMegaTargets", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetWatchMegaTargets;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetWatchMegaTargets", 0);

	return;
}

nothing CJassInterface::Jass_SetReplacementCount_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetReplacementCount", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetReplacementCount;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetReplacementCount", 0);

	return;
}

nothing CJassInterface::Jass_PurchaseZeppelin_Hooked()
{
	auto params = OnNativeCalled_Pre("PurchaseZeppelin", 0);

	__asm call _PurchaseZeppelin;

	OnNativeCalled_Post_NoParam("PurchaseZeppelin", 0);

	return;
}

integer CJassInterface::Jass_MeleeDifficulty_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("MeleeDifficulty", 0);

	__asm call _MeleeDifficulty;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("MeleeDifficulty", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DebugBreak_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DebugBreak", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DebugBreak;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DebugBreak", 0);

	return;
}

real CJassInterface::Jass_Deg2Rad_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Deg2Rad", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Deg2Rad;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Deg2Rad", retValue);

	return retValue;
}

real CJassInterface::Jass_Rad2Deg_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Rad2Deg", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Rad2Deg;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Rad2Deg", retValue);

	return retValue;
}

real CJassInterface::Jass_Sin_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Sin", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call __Sin;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Sin", retValue);

	return retValue;
}

real CJassInterface::Jass_Cos_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Cos", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Cos;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Cos", retValue);

	return retValue;
}

real CJassInterface::Jass_Tan_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Tan", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Tan;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Tan", retValue);

	return retValue;
}

real CJassInterface::Jass_Asin_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Asin", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Asin;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Asin", retValue);

	return retValue;
}

real CJassInterface::Jass_Acos_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Acos", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Acos;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Acos", retValue);

	return retValue;
}

real CJassInterface::Jass_Atan_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Atan", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Atan;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Atan", retValue);

	return retValue;
}

real CJassInterface::Jass_Atan2_Hooked(handle P1, handle P2)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Atan2", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _Atan2;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("Atan2", retValue);

	return retValue;
}

real CJassInterface::Jass_SquareRoot_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("SquareRoot", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SquareRoot;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("SquareRoot", retValue);

	return retValue;
}

real CJassInterface::Jass_Pow_Hooked(handle P1, handle P2)
{
	real retValue;

	auto params = OnNativeCalled_Pre("Pow", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _Pow;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("Pow", retValue);

	return retValue;
}

real CJassInterface::Jass_I2R_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("I2R", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _I2R;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("I2R", retValue);

	return retValue;
}

integer CJassInterface::Jass_R2I_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("R2I", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _R2I;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("R2I", retValue);

	return retValue;
}

string CJassInterface::Jass_I2S_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("I2S", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _I2S;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("I2S", retValue);

	return retValue;
}

string CJassInterface::Jass_R2S_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("R2S", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _R2S;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("R2S", retValue);

	return retValue;
}

string CJassInterface::Jass_R2SW_Hooked(handle P1, handle P2, handle P3)
{
	string retValue;

	auto params = OnNativeCalled_Pre("R2SW", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _R2SW;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("R2SW", retValue);

	return retValue;
}

integer CJassInterface::Jass_S2I_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("S2I", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _S2I;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("S2I", retValue);

	return retValue;
}

real CJassInterface::Jass_S2R_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("S2R", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _S2R;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("S2R", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetHandleId_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetHandleId", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetHandleId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetHandleId", retValue);

	return retValue;
}

string CJassInterface::Jass_SubString_Hooked(handle P1, handle P2, handle P3)
{
	string retValue;

	auto params = OnNativeCalled_Pre("SubString", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SubString;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("SubString", retValue);

	return retValue;
}

integer CJassInterface::Jass_StringLength_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("StringLength", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _StringLength;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("StringLength", retValue);

	return retValue;
}

string CJassInterface::Jass_StringCase_Hooked(handle P1, handle P2)
{
	string retValue;

	auto params = OnNativeCalled_Pre("StringCase", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _StringCase;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("StringCase", retValue);

	return retValue;
}

integer CJassInterface::Jass_StringHash_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("StringHash", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _StringHash;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("StringHash", retValue);

	return retValue;
}

string CJassInterface::Jass_GetLocalizedString_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetLocalizedString", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetLocalizedString;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetLocalizedString", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetLocalizedHotkey_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetLocalizedHotkey", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetLocalizedHotkey;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetLocalizedHotkey", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertRace_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertRace", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertRace;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertRace", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertAllianceType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertAllianceType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertAllianceType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertAllianceType", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertRacePref_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertRacePref", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertRacePref;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertRacePref", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertIGameState_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertIGameState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertIGameState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertIGameState", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertFGameState_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertFGameState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertFGameState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertFGameState", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerState_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertPlayerState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertPlayerState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertPlayerState", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerScore_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertPlayerScore", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertPlayerScore;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertPlayerScore", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertStartLocPrio_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertStartLocPrio", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertStartLocPrio;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertStartLocPrio", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerGameResult_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertPlayerGameResult", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertPlayerGameResult;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertPlayerGameResult", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertUnitState_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertUnitState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertUnitState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertUnitState", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertAIDifficulty_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertAIDifficulty", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertAIDifficulty;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertAIDifficulty", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertGameEvent_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertGameEvent", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertGameEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertGameEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerEvent_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertPlayerEvent", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertPlayerEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertPlayerEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerUnitEvent_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertPlayerUnitEvent", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertPlayerUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertPlayerUnitEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertUnitEvent_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertUnitEvent", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertUnitEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertWidgetEvent_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertWidgetEvent", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertWidgetEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertWidgetEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertDialogEvent_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertDialogEvent", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertDialogEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertDialogEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertLimitOp_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertLimitOp", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertLimitOp;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertLimitOp", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertUnitType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertUnitType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertUnitType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertUnitType", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertGameSpeed_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertGameSpeed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertGameSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertGameSpeed", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertPlacement_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertPlacement", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertPlacement;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertPlacement", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertGameDifficulty_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertGameDifficulty", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertGameDifficulty;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertGameDifficulty", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertGameType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertGameType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertGameType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertGameType", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertMapFlag_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertMapFlag", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertMapFlag;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertMapFlag", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertMapVisibility_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertMapVisibility", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertMapVisibility;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertMapVisibility", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertMapSetting_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertMapSetting", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertMapSetting;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertMapSetting", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertMapDensity_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertMapDensity", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertMapDensity;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertMapDensity", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertMapControl_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertMapControl", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertMapControl;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertMapControl", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerColor_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertPlayerColor", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertPlayerColor;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertPlayerColor", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerSlotState_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertPlayerSlotState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertPlayerSlotState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertPlayerSlotState", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertVolumeGroup_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertVolumeGroup", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertVolumeGroup;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertVolumeGroup", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertCameraField_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertCameraField", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertCameraField;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertCameraField", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertBlendMode_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertBlendMode", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertBlendMode;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertBlendMode", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertRarityControl_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertRarityControl", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertRarityControl;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertRarityControl", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertTexMapFlags_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertTexMapFlags", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertTexMapFlags;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertTexMapFlags", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertFogState_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertFogState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertFogState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertFogState", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertEffectType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertEffectType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertEffectType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertEffectType", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertVersion_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertVersion", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertVersion;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertVersion", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertItemType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertItemType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertItemType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertItemType", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertAttackType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertAttackType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertAttackType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertAttackType", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertDamageType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertDamageType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertDamageType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertDamageType", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertWeaponType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertWeaponType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertWeaponType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertWeaponType", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertSoundType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertSoundType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertSoundType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertSoundType", retValue);

	return retValue;
}

handle CJassInterface::Jass_ConvertPathingType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("ConvertPathingType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ConvertPathingType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ConvertPathingType", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetMapName_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetMapName", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetMapName;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetMapName", 0);

	return;
}

nothing CJassInterface::Jass_SetMapDescription_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetMapDescription", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetMapDescription;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetMapDescription", 0);

	return;
}

nothing CJassInterface::Jass_SetTeams_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetTeams", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetTeams;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetTeams", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayers_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetPlayers", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetPlayers;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetPlayers", 0);

	return;
}

nothing CJassInterface::Jass_SetGameTypeSupported_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetGameTypeSupported", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetGameTypeSupported;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetGameTypeSupported", 0);

	return;
}

nothing CJassInterface::Jass_SetMapFlag_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetMapFlag", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetMapFlag;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetMapFlag", 0);

	return;
}

nothing CJassInterface::Jass_SetGameSpeed_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetGameSpeed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetGameSpeed;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetGameSpeed", 0);

	return;
}

nothing CJassInterface::Jass_SetGamePlacement_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetGamePlacement", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetGamePlacement;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetGamePlacement", 0);

	return;
}

nothing CJassInterface::Jass_SetGameDifficulty_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetGameDifficulty", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetGameDifficulty;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetGameDifficulty", 0);

	return;
}

nothing CJassInterface::Jass_SetResourceDensity_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetResourceDensity", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetResourceDensity;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetResourceDensity", 0);

	return;
}

nothing CJassInterface::Jass_SetCreatureDensity_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCreatureDensity", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCreatureDensity;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCreatureDensity", 0);

	return;
}

nothing CJassInterface::Jass_DefineStartLocation_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("DefineStartLocation", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DefineStartLocation;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("DefineStartLocation", 0);

	return;
}

nothing CJassInterface::Jass_DefineStartLocationLoc_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("DefineStartLocationLoc", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _DefineStartLocationLoc;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("DefineStartLocationLoc", 0);

	return;
}

nothing CJassInterface::Jass_SetStartLocPrioCount_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetStartLocPrioCount", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetStartLocPrioCount;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetStartLocPrioCount", 0);

	return;
}

nothing CJassInterface::Jass_SetStartLocPrio_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetStartLocPrio", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetStartLocPrio;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetStartLocPrio", 0);

	return;
}

integer CJassInterface::Jass_GetStartLocPrioSlot_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetStartLocPrioSlot", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetStartLocPrioSlot;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetStartLocPrioSlot", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetStartLocPrio_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetStartLocPrio", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetStartLocPrio;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetStartLocPrio", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetTeams_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTeams", 0);

	__asm call _GetTeams;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTeams", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetPlayers_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayers", 0);

	__asm call _GetPlayers;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetPlayers", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsGameTypeSupported_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsGameTypeSupported", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsGameTypeSupported;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsGameTypeSupported", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsMapFlagSet_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsMapFlagSet", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsMapFlagSet;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsMapFlagSet", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetGameTypeSelected_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetGameTypeSelected", 0);

	__asm call _GetGameTypeSelected;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetGameTypeSelected", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetGamePlacement_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetGamePlacement", 0);

	__asm call _GetGamePlacement;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetGamePlacement", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetGameSpeed_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetGameSpeed", 0);

	__asm call _GetGameSpeed;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetGameSpeed", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetGameDifficulty_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetGameDifficulty", 0);

	__asm call _GetGameDifficulty;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetGameDifficulty", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetResourceDensity_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetResourceDensity", 0);

	__asm call _GetResourceDensity;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetResourceDensity", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetCreatureDensity_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetCreatureDensity", 0);

	__asm call _GetCreatureDensity;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCreatureDensity", retValue);

	return retValue;
}

real CJassInterface::Jass_GetStartLocationX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetStartLocationX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetStartLocationX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetStartLocationX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetStartLocationY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetStartLocationY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetStartLocationY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetStartLocationY", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetStartLocationLoc_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetStartLocationLoc", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetStartLocationLoc;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetStartLocationLoc", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerTeam_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerTeam", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerTeam;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerTeam", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerStartLocation_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerStartLocation", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerStartLocation;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerStartLocation", 0);

	return;
}

nothing CJassInterface::Jass_ForcePlayerStartLocation_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ForcePlayerStartLocation", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ForcePlayerStartLocation;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ForcePlayerStartLocation", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerAlliance_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetPlayerAlliance", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerAlliance;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetPlayerAlliance", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerTaxRate_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetPlayerTaxRate", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerTaxRate;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetPlayerTaxRate", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerRacePreference_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerRacePreference", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerRacePreference;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerRacePreference", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerRaceSelectable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerRaceSelectable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerRaceSelectable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerRaceSelectable", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerController_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerController", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerController;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerController", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerColor_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerColor", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerColor;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerColor", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerOnScoreScreen_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerOnScoreScreen", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerOnScoreScreen;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerOnScoreScreen", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerName_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerName", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerName;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerName", 0);

	return;
}

integer CJassInterface::Jass_GetPlayerTeam_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerTeam", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerTeam;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerTeam", retValue);

	return retValue;
}

string CJassInterface::Jass_GetPlayerName_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetPlayerName", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerName", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetPlayerStartLocation_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerStartLocation", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerStartLocation;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerStartLocation", retValue);

	return retValue;
}

real CJassInterface::Jass_GetPlayerStartLocationX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetPlayerStartLocationX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerStartLocationX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerStartLocationX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetPlayerStartLocationY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetPlayerStartLocationY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerStartLocationY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerStartLocationY", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetPlayerColor_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetPlayerColor", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerColor;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerColor", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GetPlayerSelectable_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GetPlayerSelectable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerSelectable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerSelectable", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetPlayerController_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetPlayerController", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerController;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerController", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetPlayerSlotState_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetPlayerSlotState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerSlotState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerSlotState", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetPlayerTaxRate_Hooked(handle P1, handle P2, handle P3)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerTaxRate", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerTaxRate;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetPlayerTaxRate", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsPlayerRacePrefSet_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsPlayerRacePrefSet", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsPlayerRacePrefSet;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsPlayerRacePrefSet", retValue);

	return retValue;
}

handle CJassInterface::Jass_Location_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("Location", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _Location;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("Location", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemoveLocation_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveLocation", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveLocation;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveLocation", 0);

	return;
}

nothing CJassInterface::Jass_MoveLocation_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("MoveLocation", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MoveLocation;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("MoveLocation", 0);

	return;
}

real CJassInterface::Jass_GetLocationX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetLocationX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetLocationX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetLocationX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetLocationY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetLocationY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetLocationY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetLocationY", retValue);

	return retValue;
}

real CJassInterface::Jass_GetLocationZ_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetLocationZ", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetLocationZ;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetLocationZ", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateTimer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateTimer", 0);

	__asm call _CreateTimer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateTimer", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyTimer_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyTimer", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyTimer;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyTimer", 0);

	return;
}

nothing CJassInterface::Jass_TimerStart_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("TimerStart", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TimerStart;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("TimerStart", 0);

	return;
}

real CJassInterface::Jass_TimerGetTimeout_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("TimerGetTimeout", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TimerGetTimeout;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("TimerGetTimeout", retValue);

	return retValue;
}

real CJassInterface::Jass_TimerGetElapsed_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("TimerGetElapsed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TimerGetElapsed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("TimerGetElapsed", retValue);

	return retValue;
}

real CJassInterface::Jass_TimerGetRemaining_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("TimerGetRemaining", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TimerGetRemaining;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("TimerGetRemaining", retValue);

	return retValue;
}

nothing CJassInterface::Jass_PauseTimer_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("PauseTimer", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _PauseTimer;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("PauseTimer", 0);

	return;
}

nothing CJassInterface::Jass_ResumeTimer_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("ResumeTimer", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ResumeTimer;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("ResumeTimer", 0);

	return;
}

handle CJassInterface::Jass_GetExpiredTimer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetExpiredTimer", 0);

	__asm call _GetExpiredTimer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetExpiredTimer", retValue);

	return retValue;
}

handle CJassInterface::Jass_Condition_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("Condition", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Condition;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Condition", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyCondition_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyCondition", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyCondition;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyCondition", 0);

	return;
}

handle CJassInterface::Jass_Filter_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("Filter", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Filter;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Filter", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyFilter_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyFilter", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyFilter;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyFilter", 0);

	return;
}

nothing CJassInterface::Jass_DestroyBoolExpr_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyBoolExpr", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyBoolExpr;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyBoolExpr", 0);

	return;
}

handle CJassInterface::Jass_And_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("And", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _And;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("And", retValue);

	return retValue;
}

handle CJassInterface::Jass_Or_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("Or", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _Or;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("Or", retValue);

	return retValue;
}

handle CJassInterface::Jass_Not_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("Not", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Not;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Not", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateRegion_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateRegion", 0);

	__asm call _CreateRegion;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateRegion", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemoveRegion_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveRegion", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveRegion;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveRegion", 0);

	return;
}

nothing CJassInterface::Jass_RegionAddRect_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("RegionAddRect", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _RegionAddRect;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("RegionAddRect", 0);

	return;
}

nothing CJassInterface::Jass_RegionClearRect_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("RegionClearRect", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _RegionClearRect;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("RegionClearRect", 0);

	return;
}

nothing CJassInterface::Jass_RegionAddCell_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("RegionAddCell", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RegionAddCell;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("RegionAddCell", 0);

	return;
}

nothing CJassInterface::Jass_RegionAddCellAtLoc_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("RegionAddCellAtLoc", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _RegionAddCellAtLoc;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("RegionAddCellAtLoc", 0);

	return;
}

nothing CJassInterface::Jass_RegionClearCell_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("RegionClearCell", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RegionClearCell;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("RegionClearCell", 0);

	return;
}

nothing CJassInterface::Jass_RegionClearCellAtLoc_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("RegionClearCellAtLoc", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _RegionClearCellAtLoc;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("RegionClearCellAtLoc", 0);

	return;
}

jboolean CJassInterface::Jass_IsUnitInRegion_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitInRegion", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInRegion;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitInRegion", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsPointInRegion_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsPointInRegion", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IsPointInRegion;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IsPointInRegion", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsLocationInRegion_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsLocationInRegion", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsLocationInRegion;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsLocationInRegion", retValue);

	return retValue;
}

handle CJassInterface::Jass_Rect_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("Rect", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _Rect;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("Rect", retValue);

	return retValue;
}

handle CJassInterface::Jass_RectFromLoc_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("RectFromLoc", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _RectFromLoc;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("RectFromLoc", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemoveRect_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveRect", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveRect;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveRect", 0);

	return;
}

nothing CJassInterface::Jass_SetRect_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("SetRect", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetRect;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("SetRect", 0);

	return;
}

nothing CJassInterface::Jass_SetRectFromLoc_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetRectFromLoc", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetRectFromLoc;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetRectFromLoc", 0);

	return;
}

real CJassInterface::Jass_GetRectCenterX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetRectCenterX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetRectCenterX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetRectCenterX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetRectCenterY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetRectCenterY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetRectCenterY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetRectCenterY", retValue);

	return retValue;
}

nothing CJassInterface::Jass_MoveRectTo_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("MoveRectTo", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MoveRectTo;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("MoveRectTo", 0);

	return;
}

nothing CJassInterface::Jass_MoveRectToLoc_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MoveRectToLoc", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MoveRectToLoc;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MoveRectToLoc", 0);

	return;
}

real CJassInterface::Jass_GetRectMinX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetRectMinX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetRectMinX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetRectMinX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetRectMinY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetRectMinY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetRectMinY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetRectMinY", retValue);

	return retValue;
}

real CJassInterface::Jass_GetRectMaxX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetRectMaxX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetRectMaxX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetRectMaxX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetRectMaxY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetRectMaxY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetRectMaxY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetRectMaxY", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetWorldBounds_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetWorldBounds", 0);

	__asm call _GetWorldBounds;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetWorldBounds", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetFogStateRect_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetFogStateRect", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetFogStateRect;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetFogStateRect", 0);

	return;
}

nothing CJassInterface::Jass_SetFogStateRadius_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	auto params = OnNativeCalled_Pre("SetFogStateRadius", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetFogStateRadius;
	__asm add esp, 24;

	OnNativeCalled_Post_NoParam("SetFogStateRadius", 0);

	return;
}

nothing CJassInterface::Jass_SetFogStateRadiusLoc_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("SetFogStateRadiusLoc", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetFogStateRadiusLoc;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("SetFogStateRadiusLoc", 0);

	return;
}

nothing CJassInterface::Jass_FogMaskEnable_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("FogMaskEnable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _FogMaskEnable;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("FogMaskEnable", 0);

	return;
}

jboolean CJassInterface::Jass_IsFogMaskEnabled_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsFogMaskEnabled", 0);

	__asm call _IsFogMaskEnabled;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("IsFogMaskEnabled", retValue);

	return retValue;
}

nothing CJassInterface::Jass_FogEnable_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("FogEnable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _FogEnable;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("FogEnable", 0);

	return;
}

jboolean CJassInterface::Jass_IsFogEnabled_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsFogEnabled", 0);

	__asm call _IsFogEnabled;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("IsFogEnabled", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateFogModifierRect_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateFogModifierRect", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateFogModifierRect;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("CreateFogModifierRect", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateFogModifierRadius_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateFogModifierRadius", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateFogModifierRadius;
	__asm mov retValue, eax;
	__asm add esp, 28;

	retValue = OnNativeCalled_Post("CreateFogModifierRadius", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateFogModifierRadiusLoc_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateFogModifierRadiusLoc", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateFogModifierRadiusLoc;
	__asm mov retValue, eax;
	__asm add esp, 24;

	retValue = OnNativeCalled_Post("CreateFogModifierRadiusLoc", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyFogModifier_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyFogModifier", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyFogModifier;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyFogModifier", 0);

	return;
}

nothing CJassInterface::Jass_FogModifierStart_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("FogModifierStart", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _FogModifierStart;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("FogModifierStart", 0);

	return;
}

nothing CJassInterface::Jass_FogModifierStop_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("FogModifierStop", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _FogModifierStop;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("FogModifierStop", 0);

	return;
}

handle CJassInterface::Jass_CreateTrigger_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateTrigger", 0);

	__asm call _CreateTrigger;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateTrigger", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyTrigger_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyTrigger", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyTrigger;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyTrigger", 0);

	return;
}

nothing CJassInterface::Jass_ResetTrigger_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("ResetTrigger", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ResetTrigger;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("ResetTrigger", 0);

	return;
}

nothing CJassInterface::Jass_EnableTrigger_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("EnableTrigger", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _EnableTrigger;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("EnableTrigger", 0);

	return;
}

nothing CJassInterface::Jass_DisableTrigger_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DisableTrigger", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DisableTrigger;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DisableTrigger", 0);

	return;
}

jboolean CJassInterface::Jass_IsTriggerEnabled_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsTriggerEnabled", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsTriggerEnabled;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsTriggerEnabled", retValue);

	return retValue;
}

nothing CJassInterface::Jass_TriggerWaitOnSleeps_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TriggerWaitOnSleeps", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerWaitOnSleeps;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TriggerWaitOnSleeps", 0);

	return;
}

jboolean CJassInterface::Jass_IsTriggerWaitOnSleeps_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsTriggerWaitOnSleeps", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsTriggerWaitOnSleeps;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsTriggerWaitOnSleeps", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterVariableEvent_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterVariableEvent", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterVariableEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("TriggerRegisterVariableEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterTimerEvent_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterTimerEvent", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterTimerEvent;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("TriggerRegisterTimerEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterTimerExpireEvent_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterTimerExpireEvent", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterTimerExpireEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("TriggerRegisterTimerExpireEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterGameStateEvent_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterGameStateEvent", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterGameStateEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("TriggerRegisterGameStateEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEventGameState_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEventGameState", 0);

	__asm call _GetEventGameState;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEventGameState", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterDialogEvent_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterDialogEvent", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterDialogEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("TriggerRegisterDialogEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterDialogButtonEvent_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterDialogButtonEvent", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterDialogButtonEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("TriggerRegisterDialogButtonEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetClickedButton_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetClickedButton", 0);

	__asm call _GetClickedButton;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetClickedButton", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetClickedDialog_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetClickedDialog", 0);

	__asm call _GetClickedDialog;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetClickedDialog", retValue);

	return retValue;
}

real CJassInterface::Jass_GetTournamentFinishSoonTimeRemaining_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetTournamentFinishSoonTimeRemaining", 0);

	__asm call _GetTournamentFinishSoonTimeRemaining;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTournamentFinishSoonTimeRemaining", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetTournamentFinishNowRule_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTournamentFinishNowRule", 0);

	__asm call _GetTournamentFinishNowRule;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTournamentFinishNowRule", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTournamentFinishNowPlayer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTournamentFinishNowPlayer", 0);

	__asm call _GetTournamentFinishNowPlayer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTournamentFinishNowPlayer", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetTournamentScore_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTournamentScore", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetTournamentScore;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetTournamentScore", retValue);

	return retValue;
}

string CJassInterface::Jass_GetSaveBasicFilename_Hooked()
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetSaveBasicFilename", 0);

	__asm call _GetSaveBasicFilename;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSaveBasicFilename", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterGameEvent_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterGameEvent", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterGameEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("TriggerRegisterGameEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetWinningPlayer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetWinningPlayer", 0);

	__asm call _GetWinningPlayer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetWinningPlayer", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerStateEvent_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterPlayerStateEvent", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerStateEvent;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("TriggerRegisterPlayerStateEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEventPlayerState_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEventPlayerState", 0);

	__asm call _GetEventPlayerState;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEventPlayerState", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerEvent_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterPlayerEvent", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerEvent;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("TriggerRegisterPlayerEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerUnitEvent_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterPlayerUnitEvent", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("TriggerRegisterPlayerUnitEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetAttacker_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetAttacker", 0);

	__asm call _GetAttacker;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetAttacker", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetRescuer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetRescuer", 0);

	__asm call _GetRescuer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetRescuer", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetDyingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetDyingUnit", 0);

	__asm call _GetDyingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetDyingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetKillingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetKillingUnit", 0);

	__asm call _GetKillingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetKillingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetDecayingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetDecayingUnit", 0);

	__asm call _GetDecayingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetDecayingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetConstructingStructure_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetConstructingStructure", 0);

	__asm call _GetConstructingStructure;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetConstructingStructure", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetCancelledStructure_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetCancelledStructure", 0);

	__asm call _GetCancelledStructure;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCancelledStructure", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetConstructedStructure_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetConstructedStructure", 0);

	__asm call _GetConstructedStructure;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetConstructedStructure", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetTrainedUnitType_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTrainedUnitType", 0);

	__asm call _GetTrainedUnitType;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTrainedUnitType", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetResearchingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetResearchingUnit", 0);

	__asm call _GetResearchingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetResearchingUnit", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetResearched_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetResearched", 0);

	__asm call _GetResearched;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetResearched", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTrainedUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTrainedUnit", 0);

	__asm call _GetTrainedUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTrainedUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSellingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSellingUnit", 0);

	__asm call _GetSellingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSellingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSoldUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSoldUnit", 0);

	__asm call _GetSoldUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSoldUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetBuyingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetBuyingUnit", 0);

	__asm call _GetBuyingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetBuyingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSoldItem_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSoldItem", 0);

	__asm call _GetSoldItem;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSoldItem", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetChangingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetChangingUnit", 0);

	__asm call _GetChangingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetChangingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetChangingUnitPrevOwner_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetChangingUnitPrevOwner", 0);

	__asm call _GetChangingUnitPrevOwner;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetChangingUnitPrevOwner", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetDetectedUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetDetectedUnit", 0);

	__asm call _GetDetectedUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetDetectedUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetOrderedUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetOrderedUnit", 0);

	__asm call _GetOrderedUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetOrderedUnit", retValue);

	return retValue;
}

integer CJassInterface::Jass_OrderId_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("OrderId", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _OrderId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("OrderId", retValue);

	return retValue;
}

string CJassInterface::Jass_OrderId2String_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("OrderId2String", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _OrderId2String;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("OrderId2String", retValue);

	return retValue;
}

integer CJassInterface::Jass_AbilityId_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("AbilityId", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _AbilityId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("AbilityId", retValue);

	return retValue;
}

string CJassInterface::Jass_AbilityId2String_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("AbilityId2String", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _AbilityId2String;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("AbilityId2String", retValue);

	return retValue;
}

integer CJassInterface::Jass_UnitId_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("UnitId", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("UnitId", retValue);

	return retValue;
}

string CJassInterface::Jass_UnitId2String_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("UnitId2String", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitId2String;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("UnitId2String", retValue);

	return retValue;
}

string CJassInterface::Jass_GetObjectName_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetObjectName", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetObjectName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetObjectName", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetIssuedOrderId_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetIssuedOrderId", 0);

	__asm call _GetIssuedOrderId;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetIssuedOrderId", retValue);

	return retValue;
}

real CJassInterface::Jass_GetOrderPointX_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetOrderPointX", 0);

	__asm call _GetOrderPointX;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetOrderPointX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetOrderPointY_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetOrderPointY", 0);

	__asm call _GetOrderPointY;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetOrderPointY", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetOrderPointLoc_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetOrderPointLoc", 0);

	__asm call _GetOrderPointLoc;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetOrderPointLoc", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetOrderTarget_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetOrderTarget", 0);

	__asm call _GetOrderTarget;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetOrderTarget", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetOrderTargetDestructable_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetOrderTargetDestructable", 0);

	__asm call _GetOrderTargetDestructable;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetOrderTargetDestructable", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetOrderTargetItem_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetOrderTargetItem", 0);

	__asm call _GetOrderTargetItem;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetOrderTargetItem", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetOrderTargetUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetOrderTargetUnit", 0);

	__asm call _GetOrderTargetUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetOrderTargetUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSpellAbilityUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSpellAbilityUnit", 0);

	__asm call _GetSpellAbilityUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSpellAbilityUnit", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetSpellAbilityId_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetSpellAbilityId", 0);

	__asm call _GetSpellAbilityId;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSpellAbilityId", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSpellAbility_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSpellAbility", 0);

	__asm call _GetSpellAbility;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSpellAbility", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSpellTargetLoc_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSpellTargetLoc", 0);

	__asm call _GetSpellTargetLoc;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSpellTargetLoc", retValue);

	return retValue;
}

real CJassInterface::Jass_GetSpellTargetX_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetSpellTargetX", 0);

	__asm call _GetSpellTargetX;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSpellTargetX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetSpellTargetY_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetSpellTargetY", 0);

	__asm call _GetSpellTargetY;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSpellTargetY", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSpellTargetDestructable_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSpellTargetDestructable", 0);

	__asm call _GetSpellTargetDestructable;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSpellTargetDestructable", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSpellTargetItem_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSpellTargetItem", 0);

	__asm call _GetSpellTargetItem;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSpellTargetItem", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSpellTargetUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSpellTargetUnit", 0);

	__asm call _GetSpellTargetUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSpellTargetUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetLevelingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetLevelingUnit", 0);

	__asm call _GetLevelingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetLevelingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetLearningUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetLearningUnit", 0);

	__asm call _GetLearningUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetLearningUnit", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetLearnedSkill_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetLearnedSkill", 0);

	__asm call _GetLearnedSkill;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetLearnedSkill", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetLearnedSkillLevel_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetLearnedSkillLevel", 0);

	__asm call _GetLearnedSkillLevel;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetLearnedSkillLevel", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetRevivableUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetRevivableUnit", 0);

	__asm call _GetRevivableUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetRevivableUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetRevivingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetRevivingUnit", 0);

	__asm call _GetRevivingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetRevivingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSummoningUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSummoningUnit", 0);

	__asm call _GetSummoningUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSummoningUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetSummonedUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetSummonedUnit", 0);

	__asm call _GetSummonedUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetSummonedUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTransportUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTransportUnit", 0);

	__asm call _GetTransportUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTransportUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetLoadedUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetLoadedUnit", 0);

	__asm call _GetLoadedUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetLoadedUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetManipulatingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetManipulatingUnit", 0);

	__asm call _GetManipulatingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetManipulatingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetManipulatedItem_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetManipulatedItem", 0);

	__asm call _GetManipulatedItem;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetManipulatedItem", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerAllianceChange_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterPlayerAllianceChange", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerAllianceChange;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("TriggerRegisterPlayerAllianceChange", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerChatEvent_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterPlayerChatEvent", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerChatEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("TriggerRegisterPlayerChatEvent", retValue);

	return retValue;
}

string CJassInterface::Jass_GetEventPlayerChatString_Hooked()
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetEventPlayerChatString", 0);

	__asm call _GetEventPlayerChatString;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEventPlayerChatString", retValue);

	return retValue;
}

string CJassInterface::Jass_GetEventPlayerChatStringMatched_Hooked()
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetEventPlayerChatStringMatched", 0);

	__asm call _GetEventPlayerChatStringMatched;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEventPlayerChatStringMatched", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterUnitStateEvent_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterUnitStateEvent", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterUnitStateEvent;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("TriggerRegisterUnitStateEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEventUnitState_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEventUnitState", 0);

	__asm call _GetEventUnitState;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEventUnitState", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterDeathEvent_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterDeathEvent", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterDeathEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("TriggerRegisterDeathEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterUnitEvent_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterUnitEvent", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("TriggerRegisterUnitEvent", retValue);

	return retValue;
}

real CJassInterface::Jass_GetEventDamage_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetEventDamage", 0);

	__asm call _GetEventDamage;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEventDamage", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEventDamageSource_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEventDamageSource", 0);

	__asm call _GetEventDamageSource;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEventDamageSource", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEventDetectingPlayer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEventDetectingPlayer", 0);

	__asm call _GetEventDetectingPlayer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEventDetectingPlayer", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEventTargetUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEventTargetUnit", 0);

	__asm call _GetEventTargetUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEventTargetUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterFilterUnitEvent_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterFilterUnitEvent", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterFilterUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("TriggerRegisterFilterUnitEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterUnitInRange_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterUnitInRange", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterUnitInRange;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("TriggerRegisterUnitInRange", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterEnterRegion_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterEnterRegion", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterEnterRegion;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("TriggerRegisterEnterRegion", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterLeaveRegion_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterLeaveRegion", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterLeaveRegion;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("TriggerRegisterLeaveRegion", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTriggeringRegion_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTriggeringRegion", 0);

	__asm call _GetTriggeringRegion;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTriggeringRegion", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEnteringUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEnteringUnit", 0);

	__asm call _GetEnteringUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEnteringUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetLeavingUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetLeavingUnit", 0);

	__asm call _GetLeavingUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetLeavingUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerAddCondition_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerAddCondition", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerAddCondition;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("TriggerAddCondition", retValue);

	return retValue;
}

nothing CJassInterface::Jass_TriggerRemoveCondition_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TriggerRemoveCondition", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRemoveCondition;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TriggerRemoveCondition", 0);

	return;
}

nothing CJassInterface::Jass_TriggerClearConditions_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("TriggerClearConditions", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TriggerClearConditions;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("TriggerClearConditions", 0);

	return;
}

handle CJassInterface::Jass_TriggerAddAction_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerAddAction", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerAddAction;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("TriggerAddAction", retValue);

	return retValue;
}

nothing CJassInterface::Jass_TriggerRemoveAction_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TriggerRemoveAction", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRemoveAction;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TriggerRemoveAction", 0);

	return;
}

nothing CJassInterface::Jass_TriggerClearActions_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("TriggerClearActions", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TriggerClearActions;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("TriggerClearActions", 0);

	return;
}

nothing CJassInterface::Jass_TriggerSleepAction_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("TriggerSleepAction", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TriggerSleepAction;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("TriggerSleepAction", 0);

	return;
}

nothing CJassInterface::Jass_TriggerWaitForSound_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TriggerWaitForSound", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerWaitForSound;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TriggerWaitForSound", 0);

	return;
}

nothing CJassInterface::Jass_TriggerExecute_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("TriggerExecute", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TriggerExecute;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("TriggerExecute", 0);

	return;
}

nothing CJassInterface::Jass_TriggerExecuteWait_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("TriggerExecuteWait", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TriggerExecuteWait;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("TriggerExecuteWait", 0);

	return;
}

jboolean CJassInterface::Jass_TriggerEvaluate_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("TriggerEvaluate", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _TriggerEvaluate;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("TriggerEvaluate", retValue);

	return retValue;
}

nothing CJassInterface::Jass_TriggerSyncStart_Hooked()
{
	auto params = OnNativeCalled_Pre("TriggerSyncStart", 0);

	__asm call _TriggerSyncStart;

	OnNativeCalled_Post_NoParam("TriggerSyncStart", 0);

	return;
}

nothing CJassInterface::Jass_TriggerSyncReady_Hooked()
{
	auto params = OnNativeCalled_Pre("TriggerSyncReady", 0);

	__asm call _TriggerSyncReady;

	OnNativeCalled_Post_NoParam("TriggerSyncReady", 0);

	return;
}

handle CJassInterface::Jass_GetTriggerWidget_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTriggerWidget", 0);

	__asm call _GetTriggerWidget;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTriggerWidget", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTriggerDestructable_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTriggerDestructable", 0);

	__asm call _GetTriggerDestructable;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTriggerDestructable", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTriggerUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTriggerUnit", 0);

	__asm call _GetTriggerUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTriggerUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTriggerPlayer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTriggerPlayer", 0);

	__asm call _GetTriggerPlayer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTriggerPlayer", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTriggeringTrigger_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTriggeringTrigger", 0);

	__asm call _GetTriggeringTrigger;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTriggeringTrigger", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTriggerEventId_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTriggerEventId", 0);

	__asm call _GetTriggerEventId;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTriggerEventId", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetTriggerEvalCount_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTriggerEvalCount", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetTriggerEvalCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetTriggerEvalCount", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetTriggerExecCount_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTriggerExecCount", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetTriggerExecCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetTriggerExecCount", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetFilterUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetFilterUnit", 0);

	__asm call _GetFilterUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetFilterUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEnumUnit_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEnumUnit", 0);

	__asm call _GetEnumUnit;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEnumUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEnumPlayer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEnumPlayer", 0);

	__asm call _GetEnumPlayer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEnumPlayer", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetFilterPlayer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetFilterPlayer", 0);

	__asm call _GetFilterPlayer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetFilterPlayer", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetFilterDestructable_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetFilterDestructable", 0);

	__asm call _GetFilterDestructable;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetFilterDestructable", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEnumDestructable_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEnumDestructable", 0);

	__asm call _GetEnumDestructable;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEnumDestructable", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetFilterItem_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetFilterItem", 0);

	__asm call _GetFilterItem;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetFilterItem", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetEnumItem_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetEnumItem", 0);

	__asm call _GetEnumItem;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetEnumItem", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateGroup_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateGroup", 0);

	__asm call _CreateGroup;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateGroup", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyGroup_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyGroup", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyGroup;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyGroup", 0);

	return;
}

nothing CJassInterface::Jass_GroupAddUnit_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("GroupAddUnit", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GroupAddUnit;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("GroupAddUnit", 0);

	return;
}

nothing CJassInterface::Jass_GroupRemoveUnit_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("GroupRemoveUnit", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GroupRemoveUnit;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("GroupRemoveUnit", 0);

	return;
}

nothing CJassInterface::Jass_GroupClear_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("GroupClear", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GroupClear;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("GroupClear", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsOfType_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsOfType", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsOfType;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsOfType", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsOfTypeCounted_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsOfTypeCounted", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsOfTypeCounted;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsOfTypeCounted", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRect_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsInRect", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRect;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsInRect", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRectCounted_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsInRectCounted", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRectCounted;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsInRectCounted", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsOfPlayer_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsOfPlayer", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsOfPlayer;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsOfPlayer", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRange_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsInRange", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRange;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsInRange", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRangeOfLoc_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsInRangeOfLoc", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRangeOfLoc;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsInRangeOfLoc", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRangeCounted_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsInRangeCounted", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRangeCounted;
	__asm add esp, 24;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsInRangeCounted", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRangeOfLocCounted_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsInRangeOfLocCounted", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRangeOfLocCounted;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsInRangeOfLocCounted", 0);

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsSelected_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("GroupEnumUnitsSelected", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsSelected;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("GroupEnumUnitsSelected", 0);

	return;
}

jboolean CJassInterface::Jass_GroupImmediateOrder_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GroupImmediateOrder", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GroupImmediateOrder;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GroupImmediateOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GroupImmediateOrderById_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GroupImmediateOrderById", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GroupImmediateOrderById;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GroupImmediateOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GroupPointOrder_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GroupPointOrder", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupPointOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("GroupPointOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GroupPointOrderLoc_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GroupPointOrderLoc", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupPointOrderLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GroupPointOrderLoc", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GroupPointOrderById_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GroupPointOrderById", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupPointOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("GroupPointOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GroupPointOrderByIdLoc_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GroupPointOrderByIdLoc", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupPointOrderByIdLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GroupPointOrderByIdLoc", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GroupTargetOrder_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GroupTargetOrder", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupTargetOrder;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GroupTargetOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GroupTargetOrderById_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GroupTargetOrderById", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupTargetOrderById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GroupTargetOrderById", retValue);

	return retValue;
}

nothing CJassInterface::Jass_ForGroup_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ForGroup", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ForGroup;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ForGroup", 0);

	return;
}

handle CJassInterface::Jass_FirstOfGroup_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("FirstOfGroup", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _FirstOfGroup;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("FirstOfGroup", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateForce_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateForce", 0);

	__asm call _CreateForce;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateForce", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyForce_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyForce", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyForce;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyForce", 0);

	return;
}

nothing CJassInterface::Jass_ForceAddPlayer_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ForceAddPlayer", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ForceAddPlayer;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ForceAddPlayer", 0);

	return;
}

nothing CJassInterface::Jass_ForceRemovePlayer_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ForceRemovePlayer", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ForceRemovePlayer;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ForceRemovePlayer", 0);

	return;
}

nothing CJassInterface::Jass_ForceClear_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("ForceClear", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ForceClear;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("ForceClear", 0);

	return;
}

nothing CJassInterface::Jass_ForceEnumPlayers_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ForceEnumPlayers", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ForceEnumPlayers;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ForceEnumPlayers", 0);

	return;
}

nothing CJassInterface::Jass_ForceEnumPlayersCounted_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("ForceEnumPlayersCounted", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ForceEnumPlayersCounted;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("ForceEnumPlayersCounted", 0);

	return;
}

nothing CJassInterface::Jass_ForceEnumAllies_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("ForceEnumAllies", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ForceEnumAllies;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("ForceEnumAllies", 0);

	return;
}

nothing CJassInterface::Jass_ForceEnumEnemies_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("ForceEnumEnemies", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ForceEnumEnemies;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("ForceEnumEnemies", 0);

	return;
}

nothing CJassInterface::Jass_ForForce_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ForForce", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ForForce;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ForForce", 0);

	return;
}

real CJassInterface::Jass_GetWidgetLife_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetWidgetLife", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetWidgetLife;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetWidgetLife", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetWidgetLife_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetWidgetLife", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetWidgetLife;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetWidgetLife", 0);

	return;
}

real CJassInterface::Jass_GetWidgetX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetWidgetX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetWidgetX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetWidgetX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetWidgetY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetWidgetY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetWidgetY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetWidgetY", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateDestructable_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateDestructable", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateDestructable;
	__asm mov retValue, eax;
	__asm add esp, 24;

	retValue = OnNativeCalled_Post("CreateDestructable", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateDestructableZ_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateDestructableZ", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateDestructableZ;
	__asm mov retValue, eax;
	__asm add esp, 28;

	retValue = OnNativeCalled_Post("CreateDestructableZ", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateDeadDestructable_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateDeadDestructable", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateDeadDestructable;
	__asm mov retValue, eax;
	__asm add esp, 24;

	retValue = OnNativeCalled_Post("CreateDeadDestructable", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateDeadDestructableZ_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateDeadDestructableZ", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateDeadDestructableZ;
	__asm mov retValue, eax;
	__asm add esp, 28;

	retValue = OnNativeCalled_Post("CreateDeadDestructableZ", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemoveDestructable_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveDestructable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveDestructable;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveDestructable", 0);

	return;
}

nothing CJassInterface::Jass_KillDestructable_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("KillDestructable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _KillDestructable;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("KillDestructable", 0);

	return;
}

nothing CJassInterface::Jass_SetDestructableInvulnerable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetDestructableInvulnerable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetDestructableInvulnerable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetDestructableInvulnerable", 0);

	return;
}

jboolean CJassInterface::Jass_IsDestructableInvulnerable_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsDestructableInvulnerable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsDestructableInvulnerable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsDestructableInvulnerable", retValue);

	return retValue;
}

nothing CJassInterface::Jass_EnumDestructablesInRect_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("EnumDestructablesInRect", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _EnumDestructablesInRect;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("EnumDestructablesInRect", 0);

	return;
}

integer CJassInterface::Jass_GetDestructableTypeId_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetDestructableTypeId", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetDestructableTypeId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetDestructableTypeId", retValue);

	return retValue;
}

real CJassInterface::Jass_GetDestructableX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetDestructableX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetDestructableX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetDestructableX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetDestructableY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetDestructableY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetDestructableY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetDestructableY", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetDestructableLife_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetDestructableLife", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetDestructableLife;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetDestructableLife", 0);

	return;
}

real CJassInterface::Jass_GetDestructableLife_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetDestructableLife", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetDestructableLife;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetDestructableLife", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetDestructableMaxLife_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetDestructableMaxLife", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetDestructableMaxLife;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetDestructableMaxLife", 0);

	return;
}

real CJassInterface::Jass_GetDestructableMaxLife_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetDestructableMaxLife", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetDestructableMaxLife;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetDestructableMaxLife", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestructableRestoreLife_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("DestructableRestoreLife", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DestructableRestoreLife;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("DestructableRestoreLife", 0);

	return;
}

nothing CJassInterface::Jass_QueueDestructableAnimation_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QueueDestructableAnimation", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QueueDestructableAnimation;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QueueDestructableAnimation", 0);

	return;
}

nothing CJassInterface::Jass_SetDestructableAnimation_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetDestructableAnimation", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetDestructableAnimation;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetDestructableAnimation", 0);

	return;
}

nothing CJassInterface::Jass_SetDestructableAnimationSpeed_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetDestructableAnimationSpeed", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetDestructableAnimationSpeed;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetDestructableAnimationSpeed", 0);

	return;
}

nothing CJassInterface::Jass_ShowDestructable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ShowDestructable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ShowDestructable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ShowDestructable", 0);

	return;
}

real CJassInterface::Jass_GetDestructableOccluderHeight_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetDestructableOccluderHeight", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetDestructableOccluderHeight;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetDestructableOccluderHeight", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetDestructableOccluderHeight_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetDestructableOccluderHeight", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetDestructableOccluderHeight;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetDestructableOccluderHeight", 0);

	return;
}

string CJassInterface::Jass_GetDestructableName_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetDestructableName", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetDestructableName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetDestructableName", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateUnit_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateUnit", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateUnit;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("CreateUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateUnitByName_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateUnitByName", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateUnitByName;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("CreateUnitByName", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateUnitAtLoc_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateUnitAtLoc", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateUnitAtLoc;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("CreateUnitAtLoc", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateUnitAtLocByName_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateUnitAtLocByName", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateUnitAtLocByName;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("CreateUnitAtLocByName", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateCorpse_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateCorpse", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateCorpse;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("CreateCorpse", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitState_Hooked(handle P1, handle P2)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitState", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetUnitState;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetUnitState", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitFoodUsed_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitFoodUsed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitFoodUsed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitFoodUsed", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitFoodMade_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitFoodMade", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitFoodMade;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitFoodMade", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetFoodMade_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetFoodMade", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetFoodMade;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetFoodMade", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetFoodUsed_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetFoodUsed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetFoodUsed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetFoodUsed", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetUnitUseFood_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitUseFood", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitUseFood;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitUseFood", 0);

	return;
}

real CJassInterface::Jass_GetUnitX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitY", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetUnitLoc_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetUnitLoc", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitLoc;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitLoc", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetUnitRallyPoint_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetUnitRallyPoint", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitRallyPoint;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitRallyPoint", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetUnitRallyUnit_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetUnitRallyUnit", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitRallyUnit;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitRallyUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetUnitRallyDestructable_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetUnitRallyDestructable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitRallyDestructable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitRallyDestructable", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitFacing_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitFacing", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitFacing;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitFacing", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitMoveSpeed_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitMoveSpeed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitMoveSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitMoveSpeed", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitDefaultMoveSpeed_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitDefaultMoveSpeed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitDefaultMoveSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitDefaultMoveSpeed", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitTypeId_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitTypeId", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitTypeId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitTypeId", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetUnitRace_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetUnitRace", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitRace;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitRace", retValue);

	return retValue;
}

string CJassInterface::Jass_GetUnitName_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetUnitName", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitName", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitPointValue_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitPointValue", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitPointValue;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitPointValue", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitPointValueByType_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitPointValueByType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitPointValueByType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitPointValueByType", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetUnitX_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitX", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitX;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitX", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitY_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitY", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitY;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitY", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitPosition_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetUnitPosition", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitPosition;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetUnitPosition", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitPositionLoc_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitPositionLoc", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitPositionLoc;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitPositionLoc", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitFacing_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitFacing", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitFacing;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitFacing", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitFacingTimed_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetUnitFacingTimed", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitFacingTimed;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetUnitFacingTimed", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitFlyHeight_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetUnitFlyHeight", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitFlyHeight;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetUnitFlyHeight", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitMoveSpeed_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitMoveSpeed", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitMoveSpeed;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitMoveSpeed", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitTurnSpeed_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitTurnSpeed", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitTurnSpeed;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitTurnSpeed", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitPropWindow_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitPropWindow", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitPropWindow;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitPropWindow", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitCreepGuard_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitCreepGuard", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitCreepGuard;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitCreepGuard", 0);

	return;
}

real CJassInterface::Jass_GetUnitAcquireRange_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitAcquireRange", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitAcquireRange;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitAcquireRange", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitTurnSpeed_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitTurnSpeed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitTurnSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitTurnSpeed", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitPropWindow_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitPropWindow", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitPropWindow;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitPropWindow", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitFlyHeight_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitFlyHeight", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitFlyHeight;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitFlyHeight", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitDefaultAcquireRange_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitDefaultAcquireRange", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitDefaultAcquireRange;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitDefaultAcquireRange", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitDefaultTurnSpeed_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitDefaultTurnSpeed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitDefaultTurnSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitDefaultTurnSpeed", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitDefaultPropWindow_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitDefaultPropWindow", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitDefaultPropWindow;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitDefaultPropWindow", retValue);

	return retValue;
}

real CJassInterface::Jass_GetUnitDefaultFlyHeight_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetUnitDefaultFlyHeight", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitDefaultFlyHeight;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitDefaultFlyHeight", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetUnitAcquireRange_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitAcquireRange", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitAcquireRange;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitAcquireRange", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitState_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetUnitState", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitState;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetUnitState", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitOwner_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetUnitOwner", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitOwner;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetUnitOwner", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitRescuable_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetUnitRescuable", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitRescuable;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetUnitRescuable", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitRescueRange_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitRescueRange", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitRescueRange;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitRescueRange", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitColor_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitColor", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitColor;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitColor", 0);

	return;
}

nothing CJassInterface::Jass_QueueUnitAnimation_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QueueUnitAnimation", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QueueUnitAnimation;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QueueUnitAnimation", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitAnimation_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitAnimation", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitAnimation;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitAnimation", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitAnimationWithRarity_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetUnitAnimationWithRarity", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitAnimationWithRarity;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetUnitAnimationWithRarity", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitAnimationByIndex_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitAnimationByIndex", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitAnimationByIndex;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitAnimationByIndex", 0);

	return;
}

nothing CJassInterface::Jass_AddUnitAnimationProperties_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("AddUnitAnimationProperties", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddUnitAnimationProperties;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("AddUnitAnimationProperties", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitScale_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetUnitScale", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitScale;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetUnitScale", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitTimeScale_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitTimeScale", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitTimeScale;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitTimeScale", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitBlendTime_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitBlendTime", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitBlendTime;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitBlendTime", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitVertexColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("SetUnitVertexColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitVertexColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("SetUnitVertexColor", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitLookAt_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	auto params = OnNativeCalled_Pre("SetUnitLookAt", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitLookAt;
	__asm add esp, 24;

	OnNativeCalled_Post_NoParam("SetUnitLookAt", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitPathing_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitPathing", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitPathing;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitPathing", 0);

	return;
}

nothing CJassInterface::Jass_ResetUnitLookAt_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("ResetUnitLookAt", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ResetUnitLookAt;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("ResetUnitLookAt", 0);

	return;
}

nothing CJassInterface::Jass_SetHeroStr_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetHeroStr", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroStr;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetHeroStr", 0);

	return;
}

nothing CJassInterface::Jass_SetHeroAgi_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetHeroAgi", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroAgi;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetHeroAgi", 0);

	return;
}

nothing CJassInterface::Jass_SetHeroInt_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetHeroInt", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroInt;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetHeroInt", 0);

	return;
}

integer CJassInterface::Jass_GetHeroStr_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetHeroStr", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetHeroStr;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetHeroStr", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetHeroAgi_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetHeroAgi", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetHeroAgi;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetHeroAgi", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetHeroInt_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetHeroInt", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetHeroInt;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetHeroInt", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetHeroSkillPoints_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetHeroSkillPoints", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetHeroSkillPoints;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetHeroSkillPoints", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitStripHeroLevel_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitStripHeroLevel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitStripHeroLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitStripHeroLevel", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitModifySkillPoints_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitModifySkillPoints", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitModifySkillPoints;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitModifySkillPoints", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetHeroXP_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetHeroXP", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetHeroXP;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetHeroXP", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetHeroXP_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetHeroXP", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroXP;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetHeroXP", 0);

	return;
}

nothing CJassInterface::Jass_AddHeroXP_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("AddHeroXP", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddHeroXP;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("AddHeroXP", 0);

	return;
}

nothing CJassInterface::Jass_SetHeroLevel_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetHeroLevel", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroLevel;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetHeroLevel", 0);

	return;
}

integer CJassInterface::Jass_GetHeroLevel_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetHeroLevel", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetHeroLevel;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetHeroLevel", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitLevel_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitLevel", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitLevel;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitLevel", retValue);

	return retValue;
}

string CJassInterface::Jass_GetHeroProperName_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetHeroProperName", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetHeroProperName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetHeroProperName", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SuspendHeroXP_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SuspendHeroXP", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SuspendHeroXP;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SuspendHeroXP", 0);

	return;
}

jboolean CJassInterface::Jass_IsSuspendedXP_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsSuspendedXP", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsSuspendedXP;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsSuspendedXP", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SelectHeroSkill_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SelectHeroSkill", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SelectHeroSkill;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SelectHeroSkill", 0);

	return;
}

integer CJassInterface::Jass_GetUnitAbilityLevel_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitAbilityLevel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetUnitAbilityLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetUnitAbilityLevel", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_ReviveHero_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("ReviveHero", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ReviveHero;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("ReviveHero", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_ReviveHeroLoc_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("ReviveHeroLoc", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ReviveHeroLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("ReviveHeroLoc", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetUnitExploded_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitExploded", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitExploded;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitExploded", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitInvulnerable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitInvulnerable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitInvulnerable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitInvulnerable", 0);

	return;
}

nothing CJassInterface::Jass_PauseUnit_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("PauseUnit", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _PauseUnit;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("PauseUnit", 0);

	return;
}

jboolean CJassInterface::Jass_IsUnitPaused_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitPaused", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsUnitPaused;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsUnitPaused", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitAddItem_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitAddItem", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddItem;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitAddItem", retValue);

	return retValue;
}

handle CJassInterface::Jass_UnitAddItemById_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("UnitAddItemById", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddItemById;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitAddItemById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitAddItemToSlotById_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitAddItemToSlotById", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitAddItemToSlotById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("UnitAddItemToSlotById", retValue);

	return retValue;
}

nothing CJassInterface::Jass_UnitRemoveItem_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("UnitRemoveItem", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveItem;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("UnitRemoveItem", 0);

	return;
}

handle CJassInterface::Jass_UnitRemoveItemFromSlot_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("UnitRemoveItemFromSlot", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveItemFromSlot;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitRemoveItemFromSlot", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitHasItem_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitHasItem", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitHasItem;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitHasItem", retValue);

	return retValue;
}

handle CJassInterface::Jass_UnitItemInSlot_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("UnitItemInSlot", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitItemInSlot;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitItemInSlot", retValue);

	return retValue;
}

integer CJassInterface::Jass_UnitInventorySize_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("UnitInventorySize", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitInventorySize;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("UnitInventorySize", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitDropItemPoint_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitDropItemPoint", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitDropItemPoint;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("UnitDropItemPoint", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitDropItemSlot_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitDropItemSlot", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitDropItemSlot;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("UnitDropItemSlot", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitDropItemTarget_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitDropItemTarget", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitDropItemTarget;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("UnitDropItemTarget", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitUseItem_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitUseItem", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitUseItem;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitUseItem", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitUseItemPoint_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitUseItemPoint", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitUseItemPoint;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("UnitUseItemPoint", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitUseItemTarget_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitUseItemTarget", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitUseItemTarget;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("UnitUseItemTarget", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetUnitCurrentOrder_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitCurrentOrder", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitCurrentOrder;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitCurrentOrder", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetResourceAmount_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetResourceAmount", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetResourceAmount;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetResourceAmount", 0);

	return;
}

nothing CJassInterface::Jass_AddResourceAmount_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("AddResourceAmount", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _AddResourceAmount;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("AddResourceAmount", 0);

	return;
}

integer CJassInterface::Jass_GetResourceAmount_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetResourceAmount", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetResourceAmount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetResourceAmount", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SelectUnit_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SelectUnit", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SelectUnit;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SelectUnit", 0);

	return;
}

nothing CJassInterface::Jass_ClearSelection_Hooked()
{
	auto params = OnNativeCalled_Pre("ClearSelection", 0);

	__asm call _ClearSelection;

	OnNativeCalled_Post_NoParam("ClearSelection", 0);

	return;
}

nothing CJassInterface::Jass_UnitAddIndicator_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("UnitAddIndicator", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitAddIndicator;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("UnitAddIndicator", 0);

	return;
}

nothing CJassInterface::Jass_AddIndicator_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("AddIndicator", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddIndicator;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("AddIndicator", 0);

	return;
}

nothing CJassInterface::Jass_KillUnit_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("KillUnit", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _KillUnit;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("KillUnit", 0);

	return;
}

nothing CJassInterface::Jass_RemoveUnit_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveUnit", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveUnit;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveUnit", 0);

	return;
}

nothing CJassInterface::Jass_ShowUnit_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ShowUnit", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ShowUnit;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ShowUnit", 0);

	return;
}

jboolean CJassInterface::Jass_IsUnitInForce_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitInForce", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInForce;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitInForce", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitInGroup_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitInGroup", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInGroup;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitInGroup", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitOwnedByPlayer_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitOwnedByPlayer", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitOwnedByPlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitOwnedByPlayer", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitAlly_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitAlly", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitAlly;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitAlly", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitEnemy_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitEnemy", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitEnemy;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitEnemy", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitVisible_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitVisible", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitVisible;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitVisible", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitDetected_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitDetected", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitDetected;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitDetected", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitInvisible_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitInvisible", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInvisible;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitInvisible", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitFogged_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitFogged", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitFogged;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitFogged", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitMasked_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitMasked", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitMasked;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitMasked", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitSelected_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitSelected", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitSelected;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitSelected", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitRace_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitRace", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitRace;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitRace", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitType_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitType", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitType", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnit_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnit", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnit;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnit", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitInRange_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitInRange", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInRange;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IsUnitInRange", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitInRangeXY_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitInRangeXY", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInRangeXY;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("IsUnitInRangeXY", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitInRangeLoc_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitInRangeLoc", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInRangeLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IsUnitInRangeLoc", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitHidden_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitHidden", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsUnitHidden;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsUnitHidden", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitIllusion_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitIllusion", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsUnitIllusion;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsUnitIllusion", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitInTransport_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitInTransport", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInTransport;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitInTransport", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitLoaded_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitLoaded", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsUnitLoaded;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsUnitLoaded", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsHeroUnitId_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsHeroUnitId", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsHeroUnitId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsHeroUnitId", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsUnitIdType_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsUnitIdType", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitIdType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsUnitIdType", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetOwningPlayer_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetOwningPlayer", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetOwningPlayer;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetOwningPlayer", retValue);

	return retValue;
}

nothing CJassInterface::Jass_UnitShareVision_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("UnitShareVision", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitShareVision;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("UnitShareVision", 0);

	return;
}

nothing CJassInterface::Jass_UnitSuspendDecay_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("UnitSuspendDecay", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitSuspendDecay;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("UnitSuspendDecay", 0);

	return;
}

jboolean CJassInterface::Jass_UnitAddType_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitAddType", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitAddType", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitRemoveType_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitRemoveType", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitRemoveType", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitAddAbility_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitAddAbility", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddAbility;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitAddAbility", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitRemoveAbility_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitRemoveAbility", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveAbility;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitRemoveAbility", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitMakeAbilityPermanent_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitMakeAbilityPermanent", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitMakeAbilityPermanent;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("UnitMakeAbilityPermanent", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitHasBuffsEx_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitHasBuffsEx", 8, P1, P2, P3, P4, P5, P6, P7, P8);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
	}

	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitHasBuffsEx;
	__asm mov retValue, eax;
	__asm add esp, 32;

	retValue = OnNativeCalled_Post("UnitHasBuffsEx", retValue);

	return retValue;
}

integer CJassInterface::Jass_UnitCountBuffsEx_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("UnitCountBuffsEx", 8, P1, P2, P3, P4, P5, P6, P7, P8);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
	}

	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitCountBuffsEx;
	__asm mov retValue, eax;
	__asm add esp, 32;

	retValue = OnNativeCalled_Post("UnitCountBuffsEx", retValue);

	return retValue;
}

nothing CJassInterface::Jass_UnitRemoveBuffs_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("UnitRemoveBuffs", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveBuffs;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("UnitRemoveBuffs", 0);

	return;
}

nothing CJassInterface::Jass_UnitRemoveBuffsEx_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8)
{
	auto params = OnNativeCalled_Pre("UnitRemoveBuffsEx", 8, P1, P2, P3, P4, P5, P6, P7, P8);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
	}

	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveBuffsEx;
	__asm add esp, 32;

	OnNativeCalled_Post_NoParam("UnitRemoveBuffsEx", 0);

	return;
}

nothing CJassInterface::Jass_UnitAddSleep_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("UnitAddSleep", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddSleep;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("UnitAddSleep", 0);

	return;
}

jboolean CJassInterface::Jass_UnitCanSleep_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitCanSleep", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitCanSleep;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("UnitCanSleep", retValue);

	return retValue;
}

nothing CJassInterface::Jass_UnitAddSleepPerm_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("UnitAddSleepPerm", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddSleepPerm;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("UnitAddSleepPerm", 0);

	return;
}

jboolean CJassInterface::Jass_UnitCanSleepPerm_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitCanSleepPerm", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitCanSleepPerm;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("UnitCanSleepPerm", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitIsSleeping_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitIsSleeping", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitIsSleeping;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("UnitIsSleeping", retValue);

	return retValue;
}

nothing CJassInterface::Jass_UnitWakeUp_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("UnitWakeUp", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitWakeUp;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("UnitWakeUp", 0);

	return;
}

nothing CJassInterface::Jass_UnitApplyTimedLife_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("UnitApplyTimedLife", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitApplyTimedLife;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("UnitApplyTimedLife", 0);

	return;
}

jboolean CJassInterface::Jass_UnitIgnoreAlarm_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitIgnoreAlarm", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitIgnoreAlarm;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("UnitIgnoreAlarm", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitIgnoreAlarmToggled_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitIgnoreAlarmToggled", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitIgnoreAlarmToggled;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("UnitIgnoreAlarmToggled", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitDamagePoint_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8, handle P9, handle P10, handle P11)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitDamagePoint", 11, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
		P9 = params[8];
		P10 = params[9];
		P11 = params[10];
	}

	__asm push P11;
	__asm push P10;
	__asm push P9;
	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitDamagePoint;
	__asm mov retValue, eax;
	__asm add esp, 44;

	retValue = OnNativeCalled_Post("UnitDamagePoint", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_UnitDamageTarget_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("UnitDamageTarget", 8, P1, P2, P3, P4, P5, P6, P7, P8);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
	}

	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitDamageTarget;
	__asm mov retValue, eax;
	__asm add esp, 32;

	retValue = OnNativeCalled_Post("UnitDamageTarget", retValue);

	return retValue;
}

integer CJassInterface::Jass_DecUnitAbilityLevel_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("DecUnitAbilityLevel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _DecUnitAbilityLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("DecUnitAbilityLevel", retValue);

	return retValue;
}

integer CJassInterface::Jass_IncUnitAbilityLevel_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("IncUnitAbilityLevel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IncUnitAbilityLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IncUnitAbilityLevel", retValue);

	return retValue;
}

integer CJassInterface::Jass_SetUnitAbilityLevel_Hooked(handle P1, handle P2, handle P3)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("SetUnitAbilityLevel", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitAbilityLevel;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("SetUnitAbilityLevel", retValue);

	return retValue;
}

nothing CJassInterface::Jass_UnitResetCooldown_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("UnitResetCooldown", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _UnitResetCooldown;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("UnitResetCooldown", 0);

	return;
}

nothing CJassInterface::Jass_UnitSetConstructionProgress_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("UnitSetConstructionProgress", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitSetConstructionProgress;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("UnitSetConstructionProgress", 0);

	return;
}

nothing CJassInterface::Jass_UnitSetUpgradeProgress_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("UnitSetUpgradeProgress", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitSetUpgradeProgress;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("UnitSetUpgradeProgress", 0);

	return;
}

nothing CJassInterface::Jass_UnitPauseTimedLife_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("UnitPauseTimedLife", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitPauseTimedLife;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("UnitPauseTimedLife", 0);

	return;
}

nothing CJassInterface::Jass_UnitSetUsesAltIcon_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("UnitSetUsesAltIcon", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitSetUsesAltIcon;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("UnitSetUsesAltIcon", 0);

	return;
}

jboolean CJassInterface::Jass_IssueImmediateOrderById_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueImmediateOrderById", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IssueImmediateOrderById;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IssueImmediateOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssuePointOrderById_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssuePointOrderById", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssuePointOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("IssuePointOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssuePointOrderByIdLoc_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssuePointOrderByIdLoc", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssuePointOrderByIdLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IssuePointOrderByIdLoc", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueTargetOrderById_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueTargetOrderById", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueTargetOrderById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IssueTargetOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueInstantPointOrderById_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueInstantPointOrderById", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueInstantPointOrderById;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("IssueInstantPointOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueInstantTargetOrderById_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueInstantTargetOrderById", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueInstantTargetOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("IssueInstantTargetOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueBuildOrderById_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueBuildOrderById", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueBuildOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("IssueBuildOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueNeutralImmediateOrderById_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueNeutralImmediateOrderById", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralImmediateOrderById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IssueNeutralImmediateOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueNeutralPointOrderById_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueNeutralPointOrderById", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralPointOrderById;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("IssueNeutralPointOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueNeutralTargetOrderById_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueNeutralTargetOrderById", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralTargetOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("IssueNeutralTargetOrderById", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueImmediateOrder_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueImmediateOrder", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IssueImmediateOrder;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IssueImmediateOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssuePointOrder_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssuePointOrder", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssuePointOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("IssuePointOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssuePointOrderLoc_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssuePointOrderLoc", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssuePointOrderLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IssuePointOrderLoc", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueTargetOrder_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueTargetOrder", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueTargetOrder;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IssueTargetOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueInstantPointOrder_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueInstantPointOrder", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueInstantPointOrder;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("IssueInstantPointOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueInstantTargetOrder_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueInstantTargetOrder", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueInstantTargetOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("IssueInstantTargetOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueBuildOrder_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueBuildOrder", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueBuildOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("IssueBuildOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueNeutralImmediateOrder_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueNeutralImmediateOrder", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralImmediateOrder;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IssueNeutralImmediateOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueNeutralPointOrder_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueNeutralPointOrder", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralPointOrder;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("IssueNeutralPointOrder", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IssueNeutralTargetOrder_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IssueNeutralTargetOrder", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralTargetOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("IssueNeutralTargetOrder", retValue);

	return retValue;
}

real CJassInterface::Jass_WaygateGetDestinationX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("WaygateGetDestinationX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _WaygateGetDestinationX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("WaygateGetDestinationX", retValue);

	return retValue;
}

real CJassInterface::Jass_WaygateGetDestinationY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("WaygateGetDestinationY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _WaygateGetDestinationY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("WaygateGetDestinationY", retValue);

	return retValue;
}

nothing CJassInterface::Jass_WaygateSetDestination_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("WaygateSetDestination", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _WaygateSetDestination;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("WaygateSetDestination", 0);

	return;
}

nothing CJassInterface::Jass_WaygateActivate_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("WaygateActivate", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _WaygateActivate;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("WaygateActivate", 0);

	return;
}

jboolean CJassInterface::Jass_WaygateIsActive_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("WaygateIsActive", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _WaygateIsActive;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("WaygateIsActive", retValue);

	return retValue;
}

nothing CJassInterface::Jass_AddItemToAllStock_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("AddItemToAllStock", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddItemToAllStock;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("AddItemToAllStock", 0);

	return;
}

nothing CJassInterface::Jass_AddItemToStock_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("AddItemToStock", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddItemToStock;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("AddItemToStock", 0);

	return;
}

nothing CJassInterface::Jass_AddUnitToAllStock_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("AddUnitToAllStock", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddUnitToAllStock;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("AddUnitToAllStock", 0);

	return;
}

nothing CJassInterface::Jass_AddUnitToStock_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("AddUnitToStock", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddUnitToStock;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("AddUnitToStock", 0);

	return;
}

nothing CJassInterface::Jass_RemoveItemFromAllStock_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveItemFromAllStock", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveItemFromAllStock;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveItemFromAllStock", 0);

	return;
}

nothing CJassInterface::Jass_RemoveItemFromStock_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("RemoveItemFromStock", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _RemoveItemFromStock;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("RemoveItemFromStock", 0);

	return;
}

nothing CJassInterface::Jass_RemoveUnitFromAllStock_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveUnitFromAllStock", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveUnitFromAllStock;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveUnitFromAllStock", 0);

	return;
}

nothing CJassInterface::Jass_RemoveUnitFromStock_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("RemoveUnitFromStock", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _RemoveUnitFromStock;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("RemoveUnitFromStock", 0);

	return;
}

nothing CJassInterface::Jass_SetAllItemTypeSlots_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetAllItemTypeSlots", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetAllItemTypeSlots;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetAllItemTypeSlots", 0);

	return;
}

nothing CJassInterface::Jass_SetAllUnitTypeSlots_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetAllUnitTypeSlots", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetAllUnitTypeSlots;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetAllUnitTypeSlots", 0);

	return;
}

nothing CJassInterface::Jass_SetItemTypeSlots_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetItemTypeSlots", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetItemTypeSlots;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetItemTypeSlots", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitTypeSlots_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitTypeSlots", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitTypeSlots;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitTypeSlots", 0);

	return;
}

integer CJassInterface::Jass_GetUnitUserData_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetUnitUserData", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetUnitUserData;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetUnitUserData", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetUnitUserData_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUnitUserData", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUnitUserData;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUnitUserData", 0);

	return;
}

handle CJassInterface::Jass_CreateItem_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateItem", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateItem;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("CreateItem", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemoveItem_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveItem", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveItem;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveItem", 0);

	return;
}

handle CJassInterface::Jass_GetItemPlayer_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetItemPlayer", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetItemPlayer;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetItemPlayer", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetItemTypeId_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetItemTypeId", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetItemTypeId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetItemTypeId", retValue);

	return retValue;
}

real CJassInterface::Jass_GetItemX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetItemX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetItemX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetItemX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetItemY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetItemY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetItemY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetItemY", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetItemPosition_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetItemPosition", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetItemPosition;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetItemPosition", 0);

	return;
}

nothing CJassInterface::Jass_SetItemDropOnDeath_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetItemDropOnDeath", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetItemDropOnDeath;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetItemDropOnDeath", 0);

	return;
}

nothing CJassInterface::Jass_SetItemDroppable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetItemDroppable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetItemDroppable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetItemDroppable", 0);

	return;
}

nothing CJassInterface::Jass_SetItemPawnable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetItemPawnable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetItemPawnable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetItemPawnable", 0);

	return;
}

nothing CJassInterface::Jass_SetItemPlayer_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetItemPlayer", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetItemPlayer;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetItemPlayer", 0);

	return;
}

nothing CJassInterface::Jass_SetItemInvulnerable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetItemInvulnerable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetItemInvulnerable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetItemInvulnerable", 0);

	return;
}

jboolean CJassInterface::Jass_IsItemInvulnerable_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsItemInvulnerable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsItemInvulnerable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsItemInvulnerable", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetItemLevel_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetItemLevel", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetItemLevel;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetItemLevel", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetItemType_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetItemType", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetItemType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetItemType", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetItemVisible_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetItemVisible", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetItemVisible;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetItemVisible", 0);

	return;
}

jboolean CJassInterface::Jass_IsItemVisible_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsItemVisible", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsItemVisible;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsItemVisible", retValue);

	return retValue;
}

nothing CJassInterface::Jass_EnumItemsInRect_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("EnumItemsInRect", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _EnumItemsInRect;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("EnumItemsInRect", 0);

	return;
}

jboolean CJassInterface::Jass_IsItemOwned_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsItemOwned", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsItemOwned;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsItemOwned", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsItemPowerup_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsItemPowerup", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsItemPowerup;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsItemPowerup", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsItemSellable_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsItemSellable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsItemSellable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsItemSellable", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsItemPawnable_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsItemPawnable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsItemPawnable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsItemPawnable", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsItemIdPowerup_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsItemIdPowerup", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsItemIdPowerup;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsItemIdPowerup", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsItemIdSellable_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsItemIdSellable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsItemIdSellable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsItemIdSellable", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsItemIdPawnable_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsItemIdPawnable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsItemIdPawnable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsItemIdPawnable", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetItemDropID_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetItemDropID", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetItemDropID;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetItemDropID", 0);

	return;
}

string CJassInterface::Jass_GetItemName_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetItemName", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetItemName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetItemName", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetItemCharges_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetItemCharges", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetItemCharges;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetItemCharges", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetItemCharges_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetItemCharges", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetItemCharges;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetItemCharges", 0);

	return;
}

integer CJassInterface::Jass_GetItemUserData_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetItemUserData", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetItemUserData;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetItemUserData", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetItemUserData_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetItemUserData", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetItemUserData;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetItemUserData", 0);

	return;
}

handle CJassInterface::Jass_Player_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("Player", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Player;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("Player", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetLocalPlayer_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetLocalPlayer", 0);

	__asm call _GetLocalPlayer;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetLocalPlayer", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsPlayerAlly_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsPlayerAlly", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsPlayerAlly;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsPlayerAlly", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsPlayerEnemy_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsPlayerEnemy", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsPlayerEnemy;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsPlayerEnemy", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsPlayerInForce_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsPlayerInForce", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsPlayerInForce;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsPlayerInForce", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsPlayerObserver_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsPlayerObserver", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsPlayerObserver;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsPlayerObserver", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetPlayerRace_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetPlayerRace", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerRace;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerRace", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetPlayerId_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerId", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerId", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerTechMaxAllowed_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetPlayerTechMaxAllowed", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerTechMaxAllowed;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetPlayerTechMaxAllowed", 0);

	return;
}

integer CJassInterface::Jass_GetPlayerTechMaxAllowed_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerTechMaxAllowed", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerTechMaxAllowed;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetPlayerTechMaxAllowed", retValue);

	return retValue;
}

nothing CJassInterface::Jass_AddPlayerTechResearched_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("AddPlayerTechResearched", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddPlayerTechResearched;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("AddPlayerTechResearched", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerTechResearched_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetPlayerTechResearched", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerTechResearched;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetPlayerTechResearched", 0);

	return;
}

jboolean CJassInterface::Jass_GetPlayerTechResearched_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GetPlayerTechResearched", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerTechResearched;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetPlayerTechResearched", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetPlayerTechCount_Hooked(handle P1, handle P2, handle P3)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerTechCount", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerTechCount;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetPlayerTechCount", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerAbilityAvailable_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetPlayerAbilityAvailable", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerAbilityAvailable;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetPlayerAbilityAvailable", 0);

	return;
}

integer CJassInterface::Jass_GetPlayerUnitCount_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerUnitCount", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerUnitCount;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetPlayerUnitCount", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetPlayerTypedUnitCount_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerTypedUnitCount", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerTypedUnitCount;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("GetPlayerTypedUnitCount", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetPlayerStructureCount_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerStructureCount", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerStructureCount;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetPlayerStructureCount", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsVisibleToPlayer_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsVisibleToPlayer", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IsVisibleToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IsVisibleToPlayer", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsLocationVisibleToPlayer_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsLocationVisibleToPlayer", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsLocationVisibleToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsLocationVisibleToPlayer", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsFoggedToPlayer_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsFoggedToPlayer", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IsFoggedToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IsFoggedToPlayer", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsLocationFoggedToPlayer_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsLocationFoggedToPlayer", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsLocationFoggedToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsLocationFoggedToPlayer", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsMaskedToPlayer_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsMaskedToPlayer", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IsMaskedToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IsMaskedToPlayer", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsLocationMaskedToPlayer_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsLocationMaskedToPlayer", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsLocationMaskedToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsLocationMaskedToPlayer", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerState_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetPlayerState", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerState;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetPlayerState", 0);

	return;
}

integer CJassInterface::Jass_GetPlayerState_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerState", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerState;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetPlayerState", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetPlayerScore_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetPlayerScore", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerScore;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetPlayerScore", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GetPlayerAlliance_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GetPlayerAlliance", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerAlliance;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetPlayerAlliance", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemovePlayer_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("RemovePlayer", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _RemovePlayer;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("RemovePlayer", 0);

	return;
}

nothing CJassInterface::Jass_CachePlayerHeroData_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("CachePlayerHeroData", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _CachePlayerHeroData;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("CachePlayerHeroData", 0);

	return;
}

real CJassInterface::Jass_GetPlayerHandicap_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetPlayerHandicap", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerHandicap;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerHandicap", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerHandicap_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerHandicap", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerHandicap;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerHandicap", 0);

	return;
}

real CJassInterface::Jass_GetPlayerHandicapXP_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetPlayerHandicapXP", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetPlayerHandicapXP;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetPlayerHandicapXP", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerHandicapXP_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerHandicapXP", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerHandicapXP;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerHandicapXP", 0);

	return;
}

nothing CJassInterface::Jass_SetPlayerUnitsOwner_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetPlayerUnitsOwner", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerUnitsOwner;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetPlayerUnitsOwner", 0);

	return;
}

nothing CJassInterface::Jass_CripplePlayer_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("CripplePlayer", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CripplePlayer;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("CripplePlayer", 0);

	return;
}

handle CJassInterface::Jass_VersionGet_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("VersionGet", 0);

	__asm call _VersionGet;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("VersionGet", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_VersionCompatible_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("VersionCompatible", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _VersionCompatible;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("VersionCompatible", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_VersionSupported_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("VersionSupported", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _VersionSupported;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("VersionSupported", retValue);

	return retValue;
}

nothing CJassInterface::Jass_EndGame_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("EndGame", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _EndGame;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("EndGame", 0);

	return;
}

nothing CJassInterface::Jass_ChangeLevel_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ChangeLevel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ChangeLevel;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ChangeLevel", 0);

	return;
}

nothing CJassInterface::Jass_RestartGame_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RestartGame", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RestartGame;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RestartGame", 0);

	return;
}

nothing CJassInterface::Jass_ReloadGame_Hooked()
{
	auto params = OnNativeCalled_Pre("ReloadGame", 0);

	__asm call _ReloadGame;

	OnNativeCalled_Post_NoParam("ReloadGame", 0);

	return;
}

nothing CJassInterface::Jass_LoadGame_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LoadGame", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LoadGame;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LoadGame", 0);

	return;
}

nothing CJassInterface::Jass_SaveGame_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SaveGame", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SaveGame;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SaveGame", 0);

	return;
}

jboolean CJassInterface::Jass_RenameSaveDirectory_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("RenameSaveDirectory", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _RenameSaveDirectory;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("RenameSaveDirectory", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_RemoveSaveDirectory_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("RemoveSaveDirectory", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveSaveDirectory;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("RemoveSaveDirectory", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_CopySaveGame_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("CopySaveGame", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _CopySaveGame;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("CopySaveGame", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveGameExists_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveGameExists", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SaveGameExists;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("SaveGameExists", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetFloatGameState_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetFloatGameState", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetFloatGameState;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetFloatGameState", 0);

	return;
}

real CJassInterface::Jass_GetFloatGameState_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetFloatGameState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetFloatGameState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetFloatGameState", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetIntegerGameState_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetIntegerGameState", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetIntegerGameState;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetIntegerGameState", 0);

	return;
}

integer CJassInterface::Jass_GetIntegerGameState_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetIntegerGameState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetIntegerGameState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetIntegerGameState", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SyncSelections_Hooked()
{
	auto params = OnNativeCalled_Pre("SyncSelections", 0);

	__asm call _SyncSelections;

	OnNativeCalled_Post_NoParam("SyncSelections", 0);

	return;
}

handle CJassInterface::Jass_DialogCreate_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("DialogCreate", 0);

	__asm call _DialogCreate;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("DialogCreate", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DialogDestroy_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DialogDestroy", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DialogDestroy;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DialogDestroy", 0);

	return;
}

nothing CJassInterface::Jass_DialogSetAsync_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DialogSetAsync", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DialogSetAsync;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DialogSetAsync", 0);

	return;
}

nothing CJassInterface::Jass_DialogClear_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DialogClear", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DialogClear;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DialogClear", 0);

	return;
}

nothing CJassInterface::Jass_DialogSetMessage_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("DialogSetMessage", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _DialogSetMessage;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("DialogSetMessage", 0);

	return;
}

handle CJassInterface::Jass_DialogAddButton_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("DialogAddButton", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DialogAddButton;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("DialogAddButton", retValue);

	return retValue;
}

handle CJassInterface::Jass_DialogAddQuitButton_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("DialogAddQuitButton", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DialogAddQuitButton;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("DialogAddQuitButton", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DialogDisplay_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("DialogDisplay", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DialogDisplay;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("DialogDisplay", 0);

	return;
}

nothing CJassInterface::Jass_SetMissionAvailable_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetMissionAvailable", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetMissionAvailable;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetMissionAvailable", 0);

	return;
}

nothing CJassInterface::Jass_SetCampaignAvailable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetCampaignAvailable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetCampaignAvailable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetCampaignAvailable", 0);

	return;
}

nothing CJassInterface::Jass_SetCampaignMenuRace_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCampaignMenuRace", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCampaignMenuRace;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCampaignMenuRace", 0);

	return;
}

nothing CJassInterface::Jass_SetCampaignMenuRaceEx_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCampaignMenuRaceEx", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCampaignMenuRaceEx;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCampaignMenuRaceEx", 0);

	return;
}

nothing CJassInterface::Jass_ForceCampaignSelectScreen_Hooked()
{
	auto params = OnNativeCalled_Pre("ForceCampaignSelectScreen", 0);

	__asm call _ForceCampaignSelectScreen;

	OnNativeCalled_Post_NoParam("ForceCampaignSelectScreen", 0);

	return;
}

nothing CJassInterface::Jass_SetOpCinematicAvailable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetOpCinematicAvailable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetOpCinematicAvailable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetOpCinematicAvailable", 0);

	return;
}

nothing CJassInterface::Jass_SetEdCinematicAvailable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetEdCinematicAvailable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetEdCinematicAvailable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetEdCinematicAvailable", 0);

	return;
}

nothing CJassInterface::Jass_SetTutorialCleared_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetTutorialCleared", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetTutorialCleared;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetTutorialCleared", 0);

	return;
}

handle CJassInterface::Jass_GetDefaultDifficulty_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetDefaultDifficulty", 0);

	__asm call _GetDefaultDifficulty;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetDefaultDifficulty", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetDefaultDifficulty_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetDefaultDifficulty", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetDefaultDifficulty;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetDefaultDifficulty", 0);

	return;
}

jboolean CJassInterface::Jass_ReloadGameCachesFromDisk_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("ReloadGameCachesFromDisk", 0);

	__asm call _ReloadGameCachesFromDisk;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("ReloadGameCachesFromDisk", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetCustomCampaignButtonVisible_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetCustomCampaignButtonVisible", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetCustomCampaignButtonVisible;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetCustomCampaignButtonVisible", 0);

	return;
}

jboolean CJassInterface::Jass_GetCustomCampaignButtonVisible_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GetCustomCampaignButtonVisible", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetCustomCampaignButtonVisible;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetCustomCampaignButtonVisible", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DoNotSaveReplay_Hooked()
{
	auto params = OnNativeCalled_Pre("DoNotSaveReplay", 0);

	__asm call _DoNotSaveReplay;

	OnNativeCalled_Post_NoParam("DoNotSaveReplay", 0);

	return;
}

handle CJassInterface::Jass_InitGameCache_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("InitGameCache", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _InitGameCache;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("InitGameCache", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveGameCache_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveGameCache", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SaveGameCache;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("SaveGameCache", retValue);

	return retValue;
}

nothing CJassInterface::Jass_StoreInteger_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("StoreInteger", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _StoreInteger;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("StoreInteger", 0);

	return;
}

nothing CJassInterface::Jass_StoreReal_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("StoreReal", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _StoreReal;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("StoreReal", 0);

	return;
}

nothing CJassInterface::Jass_StoreBoolean_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("StoreBoolean", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _StoreBoolean;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("StoreBoolean", 0);

	return;
}

jboolean CJassInterface::Jass_StoreUnit_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("StoreUnit", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _StoreUnit;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("StoreUnit", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_StoreString_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("StoreString", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _StoreString;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("StoreString", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SaveInteger_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SaveInteger", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveInteger;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SaveInteger", 0);

	return;
}

nothing CJassInterface::Jass_SaveReal_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SaveReal", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveReal;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SaveReal", 0);

	return;
}

nothing CJassInterface::Jass_SaveBoolean_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SaveBoolean", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveBoolean;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SaveBoolean", 0);

	return;
}

jboolean CJassInterface::Jass_SaveStr_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveStr", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveStr;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveStr", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SavePlayerHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SavePlayerHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SavePlayerHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SavePlayerHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveWidgetHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveWidgetHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveWidgetHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveWidgetHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveDestructableHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveDestructableHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveDestructableHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveDestructableHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveItemHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveItemHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveItemHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveUnitHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveUnitHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveUnitHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveUnitHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveAbilityHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveAbilityHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveAbilityHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveAbilityHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveTimerHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveTimerHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTimerHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveTimerHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveRegionHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveRegionHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveRegionHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveRegionHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveTriggerHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveTriggerHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTriggerHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveTriggerHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveTriggerConditionHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveTriggerConditionHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTriggerConditionHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveTriggerConditionHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveTriggerActionHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveTriggerActionHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTriggerActionHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveTriggerActionHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveTriggerEventHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveTriggerEventHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTriggerEventHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveTriggerEventHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveForceHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveForceHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveForceHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveForceHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveGroupHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveGroupHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveGroupHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveGroupHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveLocationHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveLocationHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveLocationHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveLocationHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveRectHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveRectHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveRectHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveRectHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveBooleanExprHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveBooleanExprHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveBooleanExprHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveBooleanExprHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveSoundHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveSoundHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveSoundHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveSoundHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveEffectHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveEffectHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveEffectHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveEffectHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveUnitPoolHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveUnitPoolHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveUnitPoolHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveUnitPoolHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveItemPoolHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveItemPoolHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveItemPoolHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveItemPoolHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveQuestHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveQuestHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveQuestHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveQuestHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveQuestItemHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveQuestItemHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveQuestItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveQuestItemHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveDefeatConditionHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveDefeatConditionHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveDefeatConditionHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveDefeatConditionHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveTimerDialogHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveTimerDialogHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTimerDialogHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveTimerDialogHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveLeaderboardHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveLeaderboardHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveLeaderboardHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveLeaderboardHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveMultiboardHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveMultiboardHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveMultiboardHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveMultiboardHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveMultiboardItemHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveMultiboardItemHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveMultiboardItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveMultiboardItemHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveTrackableHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveTrackableHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTrackableHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveTrackableHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveDialogHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveDialogHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveDialogHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveDialogHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveButtonHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveButtonHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveButtonHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveButtonHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveTextTagHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveTextTagHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTextTagHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveTextTagHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveLightningHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveLightningHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveLightningHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveLightningHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveImageHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveImageHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveImageHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveImageHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveUbersplatHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveUbersplatHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveUbersplatHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveUbersplatHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveFogStateHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveFogStateHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveFogStateHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveFogStateHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveFogModifierHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveFogModifierHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveFogModifierHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveFogModifierHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveAgentHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveAgentHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveAgentHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveAgentHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SaveHashtableHandle_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SaveHashtableHandle", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveHashtableHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("SaveHashtableHandle", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SyncStoredInteger_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SyncStoredInteger", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SyncStoredInteger;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SyncStoredInteger", 0);

	return;
}

nothing CJassInterface::Jass_SyncStoredReal_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SyncStoredReal", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SyncStoredReal;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SyncStoredReal", 0);

	return;
}

nothing CJassInterface::Jass_SyncStoredBoolean_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SyncStoredBoolean", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SyncStoredBoolean;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SyncStoredBoolean", 0);

	return;
}

nothing CJassInterface::Jass_SyncStoredUnit_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SyncStoredUnit", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SyncStoredUnit;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SyncStoredUnit", 0);

	return;
}

nothing CJassInterface::Jass_SyncStoredString_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SyncStoredString", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SyncStoredString;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SyncStoredString", 0);

	return;
}

integer CJassInterface::Jass_GetStoredInteger_Hooked(handle P1, handle P2, handle P3)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetStoredInteger", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetStoredInteger;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetStoredInteger", retValue);

	return retValue;
}

real CJassInterface::Jass_GetStoredReal_Hooked(handle P1, handle P2, handle P3)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetStoredReal", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetStoredReal;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetStoredReal", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GetStoredBoolean_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GetStoredBoolean", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetStoredBoolean;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetStoredBoolean", retValue);

	return retValue;
}

handle CJassInterface::Jass_RestoreUnit_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("RestoreUnit", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RestoreUnit;
	__asm mov retValue, eax;
	__asm add esp, 28;

	retValue = OnNativeCalled_Post("RestoreUnit", retValue);

	return retValue;
}

string CJassInterface::Jass_GetStoredString_Hooked(handle P1, handle P2, handle P3)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetStoredString", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetStoredString;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetStoredString", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveStoredInteger_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveStoredInteger", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveStoredInteger;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveStoredInteger", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveStoredReal_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveStoredReal", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveStoredReal;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveStoredReal", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveStoredBoolean_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveStoredBoolean", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveStoredBoolean;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveStoredBoolean", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveStoredUnit_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveStoredUnit", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveStoredUnit;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveStoredUnit", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveStoredString_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveStoredString", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveStoredString;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveStoredString", retValue);

	return retValue;
}

nothing CJassInterface::Jass_FlushGameCache_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("FlushGameCache", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _FlushGameCache;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("FlushGameCache", 0);

	return;
}

nothing CJassInterface::Jass_FlushStoredMission_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("FlushStoredMission", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _FlushStoredMission;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("FlushStoredMission", 0);

	return;
}

nothing CJassInterface::Jass_FlushStoredInteger_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("FlushStoredInteger", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _FlushStoredInteger;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("FlushStoredInteger", 0);

	return;
}

nothing CJassInterface::Jass_FlushStoredReal_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("FlushStoredReal", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _FlushStoredReal;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("FlushStoredReal", 0);

	return;
}

nothing CJassInterface::Jass_FlushStoredBoolean_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("FlushStoredBoolean", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _FlushStoredBoolean;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("FlushStoredBoolean", 0);

	return;
}

nothing CJassInterface::Jass_FlushStoredUnit_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("FlushStoredUnit", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _FlushStoredUnit;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("FlushStoredUnit", 0);

	return;
}

nothing CJassInterface::Jass_FlushStoredString_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("FlushStoredString", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _FlushStoredString;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("FlushStoredString", 0);

	return;
}

handle CJassInterface::Jass_InitHashtable_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("InitHashtable", 0);

	__asm call _InitHashtable;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("InitHashtable", retValue);

	return retValue;
}

integer CJassInterface::Jass_LoadInteger_Hooked(handle P1, handle P2, handle P3)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("LoadInteger", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadInteger;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadInteger", retValue);

	return retValue;
}

real CJassInterface::Jass_LoadReal_Hooked(handle P1, handle P2, handle P3)
{
	real retValue;

	auto params = OnNativeCalled_Pre("LoadReal", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadReal;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadReal", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_LoadBoolean_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("LoadBoolean", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadBoolean;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadBoolean", retValue);

	return retValue;
}

string CJassInterface::Jass_LoadStr_Hooked(handle P1, handle P2, handle P3)
{
	string retValue;

	auto params = OnNativeCalled_Pre("LoadStr", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadStr;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadStr", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadPlayerHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadPlayerHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadPlayerHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadPlayerHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadWidgetHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadWidgetHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadWidgetHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadWidgetHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadDestructableHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadDestructableHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadDestructableHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadDestructableHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadItemHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadItemHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadItemHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadUnitHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadUnitHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadUnitHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadUnitHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadAbilityHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadAbilityHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadAbilityHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadAbilityHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadTimerHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadTimerHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTimerHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadTimerHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadRegionHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadRegionHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadRegionHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadRegionHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadTriggerHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadTriggerHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTriggerHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadTriggerHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadTriggerConditionHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadTriggerConditionHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTriggerConditionHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadTriggerConditionHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadTriggerActionHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadTriggerActionHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTriggerActionHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadTriggerActionHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadTriggerEventHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadTriggerEventHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTriggerEventHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadTriggerEventHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadForceHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadForceHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadForceHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadForceHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadGroupHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadGroupHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadGroupHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadGroupHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadLocationHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadLocationHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadLocationHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadLocationHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadRectHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadRectHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadRectHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadRectHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadBooleanExprHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadBooleanExprHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadBooleanExprHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadBooleanExprHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadSoundHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadSoundHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadSoundHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadSoundHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadEffectHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadEffectHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadEffectHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadEffectHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadUnitPoolHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadUnitPoolHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadUnitPoolHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadUnitPoolHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadItemPoolHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadItemPoolHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadItemPoolHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadItemPoolHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadQuestHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadQuestHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadQuestHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadQuestHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadQuestItemHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadQuestItemHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadQuestItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadQuestItemHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadDefeatConditionHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadDefeatConditionHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadDefeatConditionHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadDefeatConditionHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadTimerDialogHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadTimerDialogHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTimerDialogHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadTimerDialogHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadLeaderboardHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadLeaderboardHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadLeaderboardHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadLeaderboardHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadMultiboardHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadMultiboardHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadMultiboardHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadMultiboardHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadMultiboardItemHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadMultiboardItemHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadMultiboardItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadMultiboardItemHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadTrackableHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadTrackableHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTrackableHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadTrackableHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadDialogHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadDialogHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadDialogHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadDialogHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadButtonHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadButtonHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadButtonHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadButtonHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadTextTagHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadTextTagHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTextTagHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadTextTagHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadLightningHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadLightningHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadLightningHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadLightningHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadImageHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadImageHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadImageHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadImageHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadUbersplatHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadUbersplatHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadUbersplatHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadUbersplatHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadFogStateHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadFogStateHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadFogStateHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadFogStateHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadFogModifierHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadFogModifierHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadFogModifierHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadFogModifierHandle", retValue);

	return retValue;
}

handle CJassInterface::Jass_LoadHashtableHandle_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("LoadHashtableHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadHashtableHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("LoadHashtableHandle", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveSavedInteger_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveSavedInteger", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedInteger;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveSavedInteger", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveSavedReal_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveSavedReal", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedReal;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveSavedReal", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveSavedBoolean_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveSavedBoolean", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedBoolean;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveSavedBoolean", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveSavedString_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveSavedString", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedString;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveSavedString", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_HaveSavedHandle_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("HaveSavedHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("HaveSavedHandle", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemoveSavedInteger_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("RemoveSavedInteger", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedInteger;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("RemoveSavedInteger", 0);

	return;
}

nothing CJassInterface::Jass_RemoveSavedReal_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("RemoveSavedReal", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedReal;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("RemoveSavedReal", 0);

	return;
}

nothing CJassInterface::Jass_RemoveSavedBoolean_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("RemoveSavedBoolean", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedBoolean;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("RemoveSavedBoolean", 0);

	return;
}

nothing CJassInterface::Jass_RemoveSavedString_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("RemoveSavedString", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedString;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("RemoveSavedString", 0);

	return;
}

nothing CJassInterface::Jass_RemoveSavedHandle_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("RemoveSavedHandle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedHandle;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("RemoveSavedHandle", 0);

	return;
}

nothing CJassInterface::Jass_FlushParentHashtable_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("FlushParentHashtable", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _FlushParentHashtable;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("FlushParentHashtable", 0);

	return;
}

nothing CJassInterface::Jass_FlushChildHashtable_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("FlushChildHashtable", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _FlushChildHashtable;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("FlushChildHashtable", 0);

	return;
}

integer CJassInterface::Jass_GetRandomInt_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetRandomInt", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetRandomInt;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetRandomInt", retValue);

	return retValue;
}

real CJassInterface::Jass_GetRandomReal_Hooked(handle P1, handle P2)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetRandomReal", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetRandomReal;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetRandomReal", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateUnitPool_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateUnitPool", 0);

	__asm call _CreateUnitPool;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateUnitPool", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyUnitPool_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyUnitPool", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyUnitPool;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyUnitPool", 0);

	return;
}

nothing CJassInterface::Jass_UnitPoolAddUnitType_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("UnitPoolAddUnitType", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitPoolAddUnitType;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("UnitPoolAddUnitType", 0);

	return;
}

nothing CJassInterface::Jass_UnitPoolRemoveUnitType_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("UnitPoolRemoveUnitType", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _UnitPoolRemoveUnitType;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("UnitPoolRemoveUnitType", 0);

	return;
}

handle CJassInterface::Jass_PlaceRandomUnit_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("PlaceRandomUnit", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _PlaceRandomUnit;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("PlaceRandomUnit", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateItemPool_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateItemPool", 0);

	__asm call _CreateItemPool;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateItemPool", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyItemPool_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyItemPool", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyItemPool;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyItemPool", 0);

	return;
}

nothing CJassInterface::Jass_ItemPoolAddItemType_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("ItemPoolAddItemType", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ItemPoolAddItemType;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("ItemPoolAddItemType", 0);

	return;
}

nothing CJassInterface::Jass_ItemPoolRemoveItemType_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ItemPoolRemoveItemType", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ItemPoolRemoveItemType;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ItemPoolRemoveItemType", 0);

	return;
}

handle CJassInterface::Jass_PlaceRandomItem_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("PlaceRandomItem", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _PlaceRandomItem;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("PlaceRandomItem", retValue);

	return retValue;
}

integer CJassInterface::Jass_ChooseRandomCreep_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("ChooseRandomCreep", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ChooseRandomCreep;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ChooseRandomCreep", retValue);

	return retValue;
}

integer CJassInterface::Jass_ChooseRandomNPBuilding_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("ChooseRandomNPBuilding", 0);

	__asm call _ChooseRandomNPBuilding;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("ChooseRandomNPBuilding", retValue);

	return retValue;
}

integer CJassInterface::Jass_ChooseRandomItem_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("ChooseRandomItem", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ChooseRandomItem;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("ChooseRandomItem", retValue);

	return retValue;
}

integer CJassInterface::Jass_ChooseRandomItemEx_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("ChooseRandomItemEx", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ChooseRandomItemEx;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("ChooseRandomItemEx", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetRandomSeed_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetRandomSeed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetRandomSeed;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetRandomSeed", 0);

	return;
}

nothing CJassInterface::Jass_DisplayTextToPlayer_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("DisplayTextToPlayer", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DisplayTextToPlayer;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("DisplayTextToPlayer", 0);

	return;
}

nothing CJassInterface::Jass_DisplayTimedTextToPlayer_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("DisplayTimedTextToPlayer", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DisplayTimedTextToPlayer;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("DisplayTimedTextToPlayer", 0);

	return;
}

nothing CJassInterface::Jass_DisplayTimedTextFromPlayer_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("DisplayTimedTextFromPlayer", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _DisplayTimedTextFromPlayer;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("DisplayTimedTextFromPlayer", 0);

	return;
}

nothing CJassInterface::Jass_ClearTextMessages_Hooked()
{
	auto params = OnNativeCalled_Pre("ClearTextMessages", 0);

	__asm call _ClearTextMessages;

	OnNativeCalled_Post_NoParam("ClearTextMessages", 0);

	return;
}

nothing CJassInterface::Jass_EnableUserControl_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("EnableUserControl", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _EnableUserControl;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("EnableUserControl", 0);

	return;
}

nothing CJassInterface::Jass_EnableUserUI_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("EnableUserUI", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _EnableUserUI;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("EnableUserUI", 0);

	return;
}

nothing CJassInterface::Jass_DisableRestartMission_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DisableRestartMission", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DisableRestartMission;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DisableRestartMission", 0);

	return;
}

nothing CJassInterface::Jass_ForceUIKey_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("ForceUIKey", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ForceUIKey;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("ForceUIKey", 0);

	return;
}

nothing CJassInterface::Jass_ForceUICancel_Hooked()
{
	auto params = OnNativeCalled_Pre("ForceUICancel", 0);

	__asm call _ForceUICancel;

	OnNativeCalled_Post_NoParam("ForceUICancel", 0);

	return;
}

nothing CJassInterface::Jass_DisplayLoadDialog_Hooked()
{
	auto params = OnNativeCalled_Pre("DisplayLoadDialog", 0);

	__asm call _DisplayLoadDialog;

	OnNativeCalled_Post_NoParam("DisplayLoadDialog", 0);

	return;
}

nothing CJassInterface::Jass_SetTerrainFog_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("SetTerrainFog", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTerrainFog;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("SetTerrainFog", 0);

	return;
}

nothing CJassInterface::Jass_SetUnitFog_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("SetUnitFog", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitFog;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("SetUnitFog", 0);

	return;
}

nothing CJassInterface::Jass_SetTerrainFogEx_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	auto params = OnNativeCalled_Pre("SetTerrainFogEx", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTerrainFogEx;
	__asm add esp, 28;

	OnNativeCalled_Post_NoParam("SetTerrainFogEx", 0);

	return;
}

nothing CJassInterface::Jass_ResetTerrainFog_Hooked()
{
	auto params = OnNativeCalled_Pre("ResetTerrainFog", 0);

	__asm call _ResetTerrainFog;

	OnNativeCalled_Post_NoParam("ResetTerrainFog", 0);

	return;
}

nothing CJassInterface::Jass_SetDayNightModels_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetDayNightModels", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetDayNightModels;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetDayNightModels", 0);

	return;
}

nothing CJassInterface::Jass_SetSkyModel_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetSkyModel", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetSkyModel;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetSkyModel", 0);

	return;
}

nothing CJassInterface::Jass_SuspendTimeOfDay_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SuspendTimeOfDay", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SuspendTimeOfDay;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SuspendTimeOfDay", 0);

	return;
}

nothing CJassInterface::Jass_SetTimeOfDayScale_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetTimeOfDayScale", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetTimeOfDayScale;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetTimeOfDayScale", 0);

	return;
}

real CJassInterface::Jass_GetTimeOfDayScale_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetTimeOfDayScale", 0);

	__asm call _GetTimeOfDayScale;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTimeOfDayScale", retValue);

	return retValue;
}

nothing CJassInterface::Jass_ShowInterface_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ShowInterface", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ShowInterface;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ShowInterface", 0);

	return;
}

nothing CJassInterface::Jass_PauseGame_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("PauseGame", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _PauseGame;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("PauseGame", 0);

	return;
}

nothing CJassInterface::Jass_PingMinimap_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("PingMinimap", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _PingMinimap;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("PingMinimap", 0);

	return;
}

nothing CJassInterface::Jass_PingMinimapEx_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	auto params = OnNativeCalled_Pre("PingMinimapEx", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _PingMinimapEx;
	__asm add esp, 28;

	OnNativeCalled_Post_NoParam("PingMinimapEx", 0);

	return;
}

nothing CJassInterface::Jass_SetIntroShotText_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetIntroShotText", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetIntroShotText;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetIntroShotText", 0);

	return;
}

nothing CJassInterface::Jass_SetIntroShotModel_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetIntroShotModel", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetIntroShotModel;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetIntroShotModel", 0);

	return;
}

nothing CJassInterface::Jass_EnableOcclusion_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("EnableOcclusion", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _EnableOcclusion;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("EnableOcclusion", 0);

	return;
}

nothing CJassInterface::Jass_EnableWorldFogBoundary_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("EnableWorldFogBoundary", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _EnableWorldFogBoundary;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("EnableWorldFogBoundary", 0);

	return;
}

nothing CJassInterface::Jass_PlayModelCinematic_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("PlayModelCinematic", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _PlayModelCinematic;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("PlayModelCinematic", 0);

	return;
}

nothing CJassInterface::Jass_PlayCinematic_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("PlayCinematic", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _PlayCinematic;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("PlayCinematic", 0);

	return;
}

nothing CJassInterface::Jass_SetAltMinimapIcon_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetAltMinimapIcon", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetAltMinimapIcon;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetAltMinimapIcon", 0);

	return;
}

handle CJassInterface::Jass_CreateTextTag_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateTextTag", 0);

	__asm call _CreateTextTag;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateTextTag", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyTextTag_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyTextTag", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyTextTag;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyTextTag", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagText_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetTextTagText", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagText;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetTextTagText", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagPos_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetTextTagPos", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagPos;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetTextTagPos", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagPosUnit_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetTextTagPosUnit", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagPosUnit;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetTextTagPosUnit", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("SetTextTagColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("SetTextTagColor", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagVelocity_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetTextTagVelocity", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagVelocity;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetTextTagVelocity", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagVisibility_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetTextTagVisibility", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagVisibility;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetTextTagVisibility", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagSuspended_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetTextTagSuspended", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagSuspended;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetTextTagSuspended", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagPermanent_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetTextTagPermanent", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagPermanent;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetTextTagPermanent", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagAge_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetTextTagAge", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagAge;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetTextTagAge", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagLifespan_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetTextTagLifespan", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagLifespan;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetTextTagLifespan", 0);

	return;
}

nothing CJassInterface::Jass_SetTextTagFadepoint_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetTextTagFadepoint", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagFadepoint;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetTextTagFadepoint", 0);

	return;
}

nothing CJassInterface::Jass_SetReservedLocalHeroButtons_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetReservedLocalHeroButtons", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetReservedLocalHeroButtons;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetReservedLocalHeroButtons", 0);

	return;
}

integer CJassInterface::Jass_GetAllyColorFilterState_Hooked()
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetAllyColorFilterState", 0);

	__asm call _GetAllyColorFilterState;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetAllyColorFilterState", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetAllyColorFilterState_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetAllyColorFilterState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetAllyColorFilterState;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetAllyColorFilterState", 0);

	return;
}

jboolean CJassInterface::Jass_GetCreepCampFilterState_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GetCreepCampFilterState", 0);

	__asm call _GetCreepCampFilterState;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCreepCampFilterState", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetCreepCampFilterState_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCreepCampFilterState", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCreepCampFilterState;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCreepCampFilterState", 0);

	return;
}

nothing CJassInterface::Jass_EnableMinimapFilterButtons_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("EnableMinimapFilterButtons", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _EnableMinimapFilterButtons;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("EnableMinimapFilterButtons", 0);

	return;
}

nothing CJassInterface::Jass_EnableDragSelect_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("EnableDragSelect", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _EnableDragSelect;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("EnableDragSelect", 0);

	return;
}

nothing CJassInterface::Jass_EnablePreSelect_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("EnablePreSelect", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _EnablePreSelect;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("EnablePreSelect", 0);

	return;
}

nothing CJassInterface::Jass_EnableSelect_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("EnableSelect", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _EnableSelect;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("EnableSelect", 0);

	return;
}

handle CJassInterface::Jass_CreateTrackable_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateTrackable", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateTrackable;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("CreateTrackable", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterTrackableHitEvent_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterTrackableHitEvent", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterTrackableHitEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("TriggerRegisterTrackableHitEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterTrackableTrackEvent_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TriggerRegisterTrackableTrackEvent", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterTrackableTrackEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("TriggerRegisterTrackableTrackEvent", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetTriggeringTrackable_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetTriggeringTrackable", 0);

	__asm call _GetTriggeringTrackable;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetTriggeringTrackable", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateQuest_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateQuest", 0);

	__asm call _CreateQuest;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateQuest", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyQuest_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyQuest", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyQuest;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyQuest", 0);

	return;
}

nothing CJassInterface::Jass_QuestSetTitle_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestSetTitle", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestSetTitle;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestSetTitle", 0);

	return;
}

nothing CJassInterface::Jass_QuestSetDescription_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestSetDescription", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestSetDescription;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestSetDescription", 0);

	return;
}

nothing CJassInterface::Jass_QuestSetIconPath_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestSetIconPath", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestSetIconPath;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestSetIconPath", 0);

	return;
}

nothing CJassInterface::Jass_QuestSetRequired_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestSetRequired", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestSetRequired;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestSetRequired", 0);

	return;
}

nothing CJassInterface::Jass_QuestSetCompleted_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestSetCompleted", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestSetCompleted;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestSetCompleted", 0);

	return;
}

nothing CJassInterface::Jass_QuestSetDiscovered_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestSetDiscovered", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestSetDiscovered;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestSetDiscovered", 0);

	return;
}

nothing CJassInterface::Jass_QuestSetFailed_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestSetFailed", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestSetFailed;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestSetFailed", 0);

	return;
}

nothing CJassInterface::Jass_QuestSetEnabled_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestSetEnabled", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestSetEnabled;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestSetEnabled", 0);

	return;
}

jboolean CJassInterface::Jass_IsQuestRequired_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsQuestRequired", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsQuestRequired;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsQuestRequired", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsQuestCompleted_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsQuestCompleted", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsQuestCompleted;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsQuestCompleted", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsQuestDiscovered_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsQuestDiscovered", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsQuestDiscovered;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsQuestDiscovered", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsQuestFailed_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsQuestFailed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsQuestFailed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsQuestFailed", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsQuestEnabled_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsQuestEnabled", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsQuestEnabled;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsQuestEnabled", retValue);

	return retValue;
}

handle CJassInterface::Jass_QuestCreateItem_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("QuestCreateItem", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _QuestCreateItem;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("QuestCreateItem", retValue);

	return retValue;
}

nothing CJassInterface::Jass_QuestItemSetDescription_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestItemSetDescription", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestItemSetDescription;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestItemSetDescription", 0);

	return;
}

nothing CJassInterface::Jass_QuestItemSetCompleted_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("QuestItemSetCompleted", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _QuestItemSetCompleted;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("QuestItemSetCompleted", 0);

	return;
}

jboolean CJassInterface::Jass_IsQuestItemCompleted_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsQuestItemCompleted", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsQuestItemCompleted;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsQuestItemCompleted", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateDefeatCondition_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateDefeatCondition", 0);

	__asm call _CreateDefeatCondition;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateDefeatCondition", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyDefeatCondition_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyDefeatCondition", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyDefeatCondition;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyDefeatCondition", 0);

	return;
}

nothing CJassInterface::Jass_DefeatConditionSetDescription_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("DefeatConditionSetDescription", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _DefeatConditionSetDescription;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("DefeatConditionSetDescription", 0);

	return;
}

nothing CJassInterface::Jass_FlashQuestDialogButton_Hooked()
{
	auto params = OnNativeCalled_Pre("FlashQuestDialogButton", 0);

	__asm call _FlashQuestDialogButton;

	OnNativeCalled_Post_NoParam("FlashQuestDialogButton", 0);

	return;
}

nothing CJassInterface::Jass_ForceQuestDialogUpdate_Hooked()
{
	auto params = OnNativeCalled_Pre("ForceQuestDialogUpdate", 0);

	__asm call _ForceQuestDialogUpdate;

	OnNativeCalled_Post_NoParam("ForceQuestDialogUpdate", 0);

	return;
}

handle CJassInterface::Jass_CreateTimerDialog_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateTimerDialog", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _CreateTimerDialog;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("CreateTimerDialog", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyTimerDialog_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyTimerDialog", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyTimerDialog;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyTimerDialog", 0);

	return;
}

nothing CJassInterface::Jass_TimerDialogSetTitle_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TimerDialogSetTitle", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TimerDialogSetTitle;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TimerDialogSetTitle", 0);

	return;
}

nothing CJassInterface::Jass_TimerDialogSetTitleColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("TimerDialogSetTitleColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TimerDialogSetTitleColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("TimerDialogSetTitleColor", 0);

	return;
}

nothing CJassInterface::Jass_TimerDialogSetTimeColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("TimerDialogSetTimeColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TimerDialogSetTimeColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("TimerDialogSetTimeColor", 0);

	return;
}

nothing CJassInterface::Jass_TimerDialogSetSpeed_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TimerDialogSetSpeed", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TimerDialogSetSpeed;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TimerDialogSetSpeed", 0);

	return;
}

nothing CJassInterface::Jass_TimerDialogDisplay_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TimerDialogDisplay", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TimerDialogDisplay;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TimerDialogDisplay", 0);

	return;
}

jboolean CJassInterface::Jass_IsTimerDialogDisplayed_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsTimerDialogDisplayed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsTimerDialogDisplayed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsTimerDialogDisplayed", retValue);

	return retValue;
}

nothing CJassInterface::Jass_TimerDialogSetRealTimeRemaining_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TimerDialogSetRealTimeRemaining", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TimerDialogSetRealTimeRemaining;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TimerDialogSetRealTimeRemaining", 0);

	return;
}

handle CJassInterface::Jass_CreateLeaderboard_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateLeaderboard", 0);

	__asm call _CreateLeaderboard;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateLeaderboard", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyLeaderboard_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyLeaderboard", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyLeaderboard;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyLeaderboard", 0);

	return;
}

integer CJassInterface::Jass_LeaderboardGetItemCount_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("LeaderboardGetItemCount", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _LeaderboardGetItemCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("LeaderboardGetItemCount", retValue);

	return retValue;
}

nothing CJassInterface::Jass_LeaderboardSetSizeByItemCount_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetSizeByItemCount", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetSizeByItemCount;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LeaderboardSetSizeByItemCount", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardAddItem_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("LeaderboardAddItem", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardAddItem;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("LeaderboardAddItem", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardRemoveItem_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LeaderboardRemoveItem", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardRemoveItem;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LeaderboardRemoveItem", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardRemovePlayerItem_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LeaderboardRemovePlayerItem", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardRemovePlayerItem;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LeaderboardRemovePlayerItem", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSortItemsByValue_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LeaderboardSortItemsByValue", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSortItemsByValue;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LeaderboardSortItemsByValue", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSortItemsByPlayer_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LeaderboardSortItemsByPlayer", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSortItemsByPlayer;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LeaderboardSortItemsByPlayer", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSortItemsByLabel_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LeaderboardSortItemsByLabel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSortItemsByLabel;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LeaderboardSortItemsByLabel", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardClear_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("LeaderboardClear", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _LeaderboardClear;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("LeaderboardClear", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardDisplay_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LeaderboardDisplay", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardDisplay;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LeaderboardDisplay", 0);

	return;
}

jboolean CJassInterface::Jass_IsLeaderboardDisplayed_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsLeaderboardDisplayed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsLeaderboardDisplayed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsLeaderboardDisplayed", retValue);

	return retValue;
}

string CJassInterface::Jass_LeaderboardGetLabelText_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("LeaderboardGetLabelText", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _LeaderboardGetLabelText;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("LeaderboardGetLabelText", retValue);

	return retValue;
}

nothing CJassInterface::Jass_PlayerSetLeaderboard_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("PlayerSetLeaderboard", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _PlayerSetLeaderboard;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("PlayerSetLeaderboard", 0);

	return;
}

handle CJassInterface::Jass_PlayerGetLeaderboard_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("PlayerGetLeaderboard", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _PlayerGetLeaderboard;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("PlayerGetLeaderboard", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_LeaderboardHasPlayerItem_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("LeaderboardHasPlayerItem", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardHasPlayerItem;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("LeaderboardHasPlayerItem", retValue);

	return retValue;
}

integer CJassInterface::Jass_LeaderboardGetPlayerIndex_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("LeaderboardGetPlayerIndex", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardGetPlayerIndex;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("LeaderboardGetPlayerIndex", retValue);

	return retValue;
}

nothing CJassInterface::Jass_LeaderboardSetLabel_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetLabel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetLabel;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("LeaderboardSetLabel", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSetLabelColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetLabelColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetLabelColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("LeaderboardSetLabelColor", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSetValueColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetValueColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetValueColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("LeaderboardSetValueColor", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSetStyle_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetStyle", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetStyle;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("LeaderboardSetStyle", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemValue_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetItemValue", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemValue;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("LeaderboardSetItemValue", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemLabel_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetItemLabel", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemLabel;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("LeaderboardSetItemLabel", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemStyle_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetItemStyle", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemStyle;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("LeaderboardSetItemStyle", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemLabelColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetItemLabelColor", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemLabelColor;
	__asm add esp, 24;

	OnNativeCalled_Post_NoParam("LeaderboardSetItemLabelColor", 0);

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemValueColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	auto params = OnNativeCalled_Pre("LeaderboardSetItemValueColor", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemValueColor;
	__asm add esp, 24;

	OnNativeCalled_Post_NoParam("LeaderboardSetItemValueColor", 0);

	return;
}

handle CJassInterface::Jass_CreateMultiboard_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateMultiboard", 0);

	__asm call _CreateMultiboard;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateMultiboard", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyMultiboard_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyMultiboard", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyMultiboard;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyMultiboard", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardDisplay_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardDisplay", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardDisplay;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardDisplay", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardMinimize_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardMinimize", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardMinimize;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardMinimize", 0);

	return;
}

jboolean CJassInterface::Jass_IsMultiboardDisplayed_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsMultiboardDisplayed", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsMultiboardDisplayed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsMultiboardDisplayed", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsMultiboardMinimized_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsMultiboardMinimized", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _IsMultiboardMinimized;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("IsMultiboardMinimized", retValue);

	return retValue;
}

nothing CJassInterface::Jass_MultiboardClear_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("MultiboardClear", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _MultiboardClear;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("MultiboardClear", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetTitleText_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardSetTitleText", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetTitleText;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardSetTitleText", 0);

	return;
}

string CJassInterface::Jass_MultiboardGetTitleText_Hooked(handle P1)
{
	string retValue;

	auto params = OnNativeCalled_Pre("MultiboardGetTitleText", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _MultiboardGetTitleText;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("MultiboardGetTitleText", retValue);

	return retValue;
}

nothing CJassInterface::Jass_MultiboardSetTitleTextColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("MultiboardSetTitleTextColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetTitleTextColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("MultiboardSetTitleTextColor", 0);

	return;
}

integer CJassInterface::Jass_MultiboardGetRowCount_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("MultiboardGetRowCount", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _MultiboardGetRowCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("MultiboardGetRowCount", retValue);

	return retValue;
}

integer CJassInterface::Jass_MultiboardGetColumnCount_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("MultiboardGetColumnCount", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _MultiboardGetColumnCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("MultiboardGetColumnCount", retValue);

	return retValue;
}

nothing CJassInterface::Jass_MultiboardSetColumnCount_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardSetColumnCount", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetColumnCount;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardSetColumnCount", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetRowCount_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardSetRowCount", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetRowCount;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardSetRowCount", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsStyle_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemsStyle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemsStyle;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("MultiboardSetItemsStyle", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsValueColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemsValueColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemsValueColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("MultiboardSetItemsValueColor", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsValue_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemsValue", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemsValue;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardSetItemsValue", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsWidth_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemsWidth", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemsWidth;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardSetItemsWidth", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsIcon_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemsIcon", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemsIcon;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardSetItemsIcon", 0);

	return;
}

handle CJassInterface::Jass_MultiboardGetItem_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("MultiboardGetItem", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardGetItem;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("MultiboardGetItem", retValue);

	return retValue;
}

nothing CJassInterface::Jass_MultiboardReleaseItem_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("MultiboardReleaseItem", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _MultiboardReleaseItem;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("MultiboardReleaseItem", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemStyle_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemStyle", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemStyle;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("MultiboardSetItemStyle", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemValue_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemValue", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemValue;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardSetItemValue", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemValueColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemValueColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemValueColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("MultiboardSetItemValueColor", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemWidth_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemWidth", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemWidth;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardSetItemWidth", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemIcon_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("MultiboardSetItemIcon", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemIcon;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("MultiboardSetItemIcon", 0);

	return;
}

nothing CJassInterface::Jass_MultiboardSuppressDisplay_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("MultiboardSuppressDisplay", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _MultiboardSuppressDisplay;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("MultiboardSuppressDisplay", 0);

	return;
}

nothing CJassInterface::Jass_SetCameraBounds_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8)
{
	auto params = OnNativeCalled_Pre("SetCameraBounds", 8, P1, P2, P3, P4, P5, P6, P7, P8);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
	}

	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCameraBounds;
	__asm add esp, 32;

	OnNativeCalled_Post_NoParam("SetCameraBounds", 0);

	return;
}

nothing CJassInterface::Jass_SetCameraPosition_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetCameraPosition", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetCameraPosition;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetCameraPosition", 0);

	return;
}

nothing CJassInterface::Jass_SetCameraQuickPosition_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetCameraQuickPosition", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetCameraQuickPosition;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetCameraQuickPosition", 0);

	return;
}

nothing CJassInterface::Jass_ResetToGameCamera_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("ResetToGameCamera", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ResetToGameCamera;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("ResetToGameCamera", 0);

	return;
}

nothing CJassInterface::Jass_StopCamera_Hooked()
{
	auto params = OnNativeCalled_Pre("StopCamera", 0);

	__asm call _StopCamera;

	OnNativeCalled_Post_NoParam("StopCamera", 0);

	return;
}

nothing CJassInterface::Jass_PanCameraTo_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("PanCameraTo", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _PanCameraTo;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("PanCameraTo", 0);

	return;
}

nothing CJassInterface::Jass_PanCameraToTimed_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("PanCameraToTimed", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _PanCameraToTimed;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("PanCameraToTimed", 0);

	return;
}

nothing CJassInterface::Jass_PanCameraToWithZ_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("PanCameraToWithZ", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _PanCameraToWithZ;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("PanCameraToWithZ", 0);

	return;
}

nothing CJassInterface::Jass_PanCameraToTimedWithZ_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("PanCameraToTimedWithZ", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _PanCameraToTimedWithZ;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("PanCameraToTimedWithZ", 0);

	return;
}

nothing CJassInterface::Jass_SetCinematicCamera_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCinematicCamera", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCinematicCamera;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCinematicCamera", 0);

	return;
}

nothing CJassInterface::Jass_SetCameraField_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetCameraField", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCameraField;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetCameraField", 0);

	return;
}

nothing CJassInterface::Jass_AdjustCameraField_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("AdjustCameraField", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AdjustCameraField;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("AdjustCameraField", 0);

	return;
}

nothing CJassInterface::Jass_SetCameraTargetController_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetCameraTargetController", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCameraTargetController;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetCameraTargetController", 0);

	return;
}

nothing CJassInterface::Jass_SetCameraOrientController_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetCameraOrientController", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCameraOrientController;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetCameraOrientController", 0);

	return;
}

nothing CJassInterface::Jass_SetCameraRotateMode_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetCameraRotateMode", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCameraRotateMode;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetCameraRotateMode", 0);

	return;
}

handle CJassInterface::Jass_CreateCameraSetup_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateCameraSetup", 0);

	__asm call _CreateCameraSetup;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("CreateCameraSetup", retValue);

	return retValue;
}

nothing CJassInterface::Jass_CameraSetupSetField_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("CameraSetupSetField", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CameraSetupSetField;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("CameraSetupSetField", 0);

	return;
}

real CJassInterface::Jass_CameraSetupGetField_Hooked(handle P1, handle P2)
{
	real retValue;

	auto params = OnNativeCalled_Pre("CameraSetupGetField", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _CameraSetupGetField;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("CameraSetupGetField", retValue);

	return retValue;
}

nothing CJassInterface::Jass_CameraSetupSetDestPosition_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("CameraSetupSetDestPosition", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CameraSetupSetDestPosition;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("CameraSetupSetDestPosition", 0);

	return;
}

handle CJassInterface::Jass_CameraSetupGetDestPositionLoc_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CameraSetupGetDestPositionLoc", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _CameraSetupGetDestPositionLoc;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("CameraSetupGetDestPositionLoc", retValue);

	return retValue;
}

real CJassInterface::Jass_CameraSetupGetDestPositionX_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("CameraSetupGetDestPositionX", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _CameraSetupGetDestPositionX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("CameraSetupGetDestPositionX", retValue);

	return retValue;
}

real CJassInterface::Jass_CameraSetupGetDestPositionY_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("CameraSetupGetDestPositionY", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _CameraSetupGetDestPositionY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("CameraSetupGetDestPositionY", retValue);

	return retValue;
}

nothing CJassInterface::Jass_CameraSetupApply_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("CameraSetupApply", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CameraSetupApply;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("CameraSetupApply", 0);

	return;
}

nothing CJassInterface::Jass_CameraSetupApplyWithZ_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("CameraSetupApplyWithZ", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _CameraSetupApplyWithZ;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("CameraSetupApplyWithZ", 0);

	return;
}

nothing CJassInterface::Jass_CameraSetupApplyForceDuration_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("CameraSetupApplyForceDuration", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CameraSetupApplyForceDuration;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("CameraSetupApplyForceDuration", 0);

	return;
}

nothing CJassInterface::Jass_CameraSetupApplyForceDurationWithZ_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("CameraSetupApplyForceDurationWithZ", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CameraSetupApplyForceDurationWithZ;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("CameraSetupApplyForceDurationWithZ", 0);

	return;
}

nothing CJassInterface::Jass_CameraSetTargetNoise_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("CameraSetTargetNoise", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _CameraSetTargetNoise;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("CameraSetTargetNoise", 0);

	return;
}

nothing CJassInterface::Jass_CameraSetSourceNoise_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("CameraSetSourceNoise", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _CameraSetSourceNoise;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("CameraSetSourceNoise", 0);

	return;
}

nothing CJassInterface::Jass_CameraSetTargetNoiseEx_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("CameraSetTargetNoiseEx", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CameraSetTargetNoiseEx;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("CameraSetTargetNoiseEx", 0);

	return;
}

nothing CJassInterface::Jass_CameraSetSourceNoiseEx_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("CameraSetSourceNoiseEx", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CameraSetSourceNoiseEx;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("CameraSetSourceNoiseEx", 0);

	return;
}

nothing CJassInterface::Jass_CameraSetSmoothingFactor_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("CameraSetSmoothingFactor", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _CameraSetSmoothingFactor;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("CameraSetSmoothingFactor", 0);

	return;
}

real CJassInterface::Jass_GetCameraMargin_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraMargin", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetCameraMargin;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetCameraMargin", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraBoundMinX_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraBoundMinX", 0);

	__asm call _GetCameraBoundMinX;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraBoundMinX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraBoundMinY_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraBoundMinY", 0);

	__asm call _GetCameraBoundMinY;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraBoundMinY", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraBoundMaxX_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraBoundMaxX", 0);

	__asm call _GetCameraBoundMaxX;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraBoundMaxX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraBoundMaxY_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraBoundMaxY", 0);

	__asm call _GetCameraBoundMaxY;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraBoundMaxY", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraField_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraField", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetCameraField;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetCameraField", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraTargetPositionX_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraTargetPositionX", 0);

	__asm call _GetCameraTargetPositionX;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraTargetPositionX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraTargetPositionY_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraTargetPositionY", 0);

	__asm call _GetCameraTargetPositionY;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraTargetPositionY", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraTargetPositionZ_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraTargetPositionZ", 0);

	__asm call _GetCameraTargetPositionZ;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraTargetPositionZ", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetCameraTargetPositionLoc_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetCameraTargetPositionLoc", 0);

	__asm call _GetCameraTargetPositionLoc;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraTargetPositionLoc", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraEyePositionX_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraEyePositionX", 0);

	__asm call _GetCameraEyePositionX;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraEyePositionX", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraEyePositionY_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraEyePositionY", 0);

	__asm call _GetCameraEyePositionY;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraEyePositionY", retValue);

	return retValue;
}

real CJassInterface::Jass_GetCameraEyePositionZ_Hooked()
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetCameraEyePositionZ", 0);

	__asm call _GetCameraEyePositionZ;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraEyePositionZ", retValue);

	return retValue;
}

handle CJassInterface::Jass_GetCameraEyePositionLoc_Hooked()
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetCameraEyePositionLoc", 0);

	__asm call _GetCameraEyePositionLoc;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("GetCameraEyePositionLoc", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetCineFilterTexture_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCineFilterTexture", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCineFilterTexture;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCineFilterTexture", 0);

	return;
}

nothing CJassInterface::Jass_SetCineFilterBlendMode_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCineFilterBlendMode", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCineFilterBlendMode;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCineFilterBlendMode", 0);

	return;
}

nothing CJassInterface::Jass_SetCineFilterTexMapFlags_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCineFilterTexMapFlags", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCineFilterTexMapFlags;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCineFilterTexMapFlags", 0);

	return;
}

nothing CJassInterface::Jass_SetCineFilterStartUV_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetCineFilterStartUV", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCineFilterStartUV;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetCineFilterStartUV", 0);

	return;
}

nothing CJassInterface::Jass_SetCineFilterEndUV_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetCineFilterEndUV", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCineFilterEndUV;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetCineFilterEndUV", 0);

	return;
}

nothing CJassInterface::Jass_SetCineFilterStartColor_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetCineFilterStartColor", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCineFilterStartColor;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetCineFilterStartColor", 0);

	return;
}

nothing CJassInterface::Jass_SetCineFilterEndColor_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetCineFilterEndColor", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCineFilterEndColor;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetCineFilterEndColor", 0);

	return;
}

nothing CJassInterface::Jass_SetCineFilterDuration_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetCineFilterDuration", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetCineFilterDuration;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetCineFilterDuration", 0);

	return;
}

nothing CJassInterface::Jass_DisplayCineFilter_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DisplayCineFilter", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DisplayCineFilter;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DisplayCineFilter", 0);

	return;
}

jboolean CJassInterface::Jass_IsCineFilterDisplayed_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsCineFilterDisplayed", 0);

	__asm call _IsCineFilterDisplayed;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("IsCineFilterDisplayed", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetCinematicScene_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	auto params = OnNativeCalled_Pre("SetCinematicScene", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCinematicScene;
	__asm add esp, 24;

	OnNativeCalled_Post_NoParam("SetCinematicScene", 0);

	return;
}

nothing CJassInterface::Jass_EndCinematicScene_Hooked()
{
	auto params = OnNativeCalled_Pre("EndCinematicScene", 0);

	__asm call _EndCinematicScene;

	OnNativeCalled_Post_NoParam("EndCinematicScene", 0);

	return;
}

nothing CJassInterface::Jass_ForceCinematicSubtitles_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("ForceCinematicSubtitles", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ForceCinematicSubtitles;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("ForceCinematicSubtitles", 0);

	return;
}

nothing CJassInterface::Jass_NewSoundEnvironment_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("NewSoundEnvironment", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _NewSoundEnvironment;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("NewSoundEnvironment", 0);

	return;
}

handle CJassInterface::Jass_CreateSound_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateSound", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateSound;
	__asm mov retValue, eax;
	__asm add esp, 28;

	retValue = OnNativeCalled_Post("CreateSound", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateSoundFilenameWithLabel_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateSoundFilenameWithLabel", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateSoundFilenameWithLabel;
	__asm mov retValue, eax;
	__asm add esp, 28;

	retValue = OnNativeCalled_Post("CreateSoundFilenameWithLabel", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateSoundFromLabel_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateSoundFromLabel", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateSoundFromLabel;
	__asm mov retValue, eax;
	__asm add esp, 24;

	retValue = OnNativeCalled_Post("CreateSoundFromLabel", retValue);

	return retValue;
}

handle CJassInterface::Jass_CreateMIDISound_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateMIDISound", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateMIDISound;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("CreateMIDISound", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetStackedSound_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetStackedSound", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetStackedSound;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetStackedSound", 0);

	return;
}

nothing CJassInterface::Jass_ClearStackedSound_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("ClearStackedSound", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ClearStackedSound;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("ClearStackedSound", 0);

	return;
}

nothing CJassInterface::Jass_SetStackedSoundRect_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetStackedSoundRect", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetStackedSoundRect;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetStackedSoundRect", 0);

	return;
}

nothing CJassInterface::Jass_ClearStackedSoundRect_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ClearStackedSoundRect", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ClearStackedSoundRect;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ClearStackedSoundRect", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundParamsFromLabel_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetSoundParamsFromLabel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetSoundParamsFromLabel;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetSoundParamsFromLabel", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundChannel_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetSoundChannel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetSoundChannel;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetSoundChannel", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundVolume_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetSoundVolume", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetSoundVolume;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetSoundVolume", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundPitch_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetSoundPitch", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetSoundPitch;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetSoundPitch", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundPlayPosition_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetSoundPlayPosition", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetSoundPlayPosition;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetSoundPlayPosition", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundDistances_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetSoundDistances", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetSoundDistances;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetSoundDistances", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundDistanceCutoff_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetSoundDistanceCutoff", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetSoundDistanceCutoff;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetSoundDistanceCutoff", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundConeAngles_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetSoundConeAngles", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetSoundConeAngles;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetSoundConeAngles", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundConeOrientation_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetSoundConeOrientation", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetSoundConeOrientation;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetSoundConeOrientation", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundPosition_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetSoundPosition", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetSoundPosition;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetSoundPosition", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundVelocity_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetSoundVelocity", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetSoundVelocity;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetSoundVelocity", 0);

	return;
}

nothing CJassInterface::Jass_AttachSoundToUnit_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("AttachSoundToUnit", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _AttachSoundToUnit;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("AttachSoundToUnit", 0);

	return;
}

nothing CJassInterface::Jass_StartSound_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("StartSound", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _StartSound;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("StartSound", 0);

	return;
}

nothing CJassInterface::Jass_StopSound_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("StopSound", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _StopSound;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("StopSound", 0);

	return;
}

nothing CJassInterface::Jass_KillSoundWhenDone_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("KillSoundWhenDone", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _KillSoundWhenDone;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("KillSoundWhenDone", 0);

	return;
}

nothing CJassInterface::Jass_SetMapMusic_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetMapMusic", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetMapMusic;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetMapMusic", 0);

	return;
}

nothing CJassInterface::Jass_ClearMapMusic_Hooked()
{
	auto params = OnNativeCalled_Pre("ClearMapMusic", 0);

	__asm call _ClearMapMusic;

	OnNativeCalled_Post_NoParam("ClearMapMusic", 0);

	return;
}

nothing CJassInterface::Jass_PlayMusic_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("PlayMusic", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _PlayMusic;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("PlayMusic", 0);

	return;
}

nothing CJassInterface::Jass_PlayMusicEx_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("PlayMusicEx", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _PlayMusicEx;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("PlayMusicEx", 0);

	return;
}

nothing CJassInterface::Jass_StopMusic_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("StopMusic", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _StopMusic;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("StopMusic", 0);

	return;
}

nothing CJassInterface::Jass_ResumeMusic_Hooked()
{
	auto params = OnNativeCalled_Pre("ResumeMusic", 0);

	__asm call _ResumeMusic;

	OnNativeCalled_Post_NoParam("ResumeMusic", 0);

	return;
}

nothing CJassInterface::Jass_PlayThematicMusic_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("PlayThematicMusic", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _PlayThematicMusic;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("PlayThematicMusic", 0);

	return;
}

nothing CJassInterface::Jass_PlayThematicMusicEx_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("PlayThematicMusicEx", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _PlayThematicMusicEx;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("PlayThematicMusicEx", 0);

	return;
}

nothing CJassInterface::Jass_EndThematicMusic_Hooked()
{
	auto params = OnNativeCalled_Pre("EndThematicMusic", 0);

	__asm call _EndThematicMusic;

	OnNativeCalled_Post_NoParam("EndThematicMusic", 0);

	return;
}

nothing CJassInterface::Jass_SetMusicVolume_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetMusicVolume", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetMusicVolume;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetMusicVolume", 0);

	return;
}

nothing CJassInterface::Jass_SetMusicPlayPosition_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetMusicPlayPosition", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetMusicPlayPosition;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetMusicPlayPosition", 0);

	return;
}

nothing CJassInterface::Jass_SetThematicMusicPlayPosition_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetThematicMusicPlayPosition", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetThematicMusicPlayPosition;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetThematicMusicPlayPosition", 0);

	return;
}

nothing CJassInterface::Jass_SetSoundDuration_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetSoundDuration", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetSoundDuration;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetSoundDuration", 0);

	return;
}

integer CJassInterface::Jass_GetSoundDuration_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetSoundDuration", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetSoundDuration;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetSoundDuration", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetSoundFileDuration_Hooked(handle P1)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetSoundFileDuration", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetSoundFileDuration;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetSoundFileDuration", retValue);

	return retValue;
}

nothing CJassInterface::Jass_VolumeGroupSetVolume_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("VolumeGroupSetVolume", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _VolumeGroupSetVolume;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("VolumeGroupSetVolume", 0);

	return;
}

nothing CJassInterface::Jass_VolumeGroupReset_Hooked()
{
	auto params = OnNativeCalled_Pre("VolumeGroupReset", 0);

	__asm call _VolumeGroupReset;

	OnNativeCalled_Post_NoParam("VolumeGroupReset", 0);

	return;
}

jboolean CJassInterface::Jass_GetSoundIsPlaying_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GetSoundIsPlaying", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetSoundIsPlaying;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetSoundIsPlaying", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_GetSoundIsLoading_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("GetSoundIsLoading", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetSoundIsLoading;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetSoundIsLoading", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RegisterStackedSound_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("RegisterStackedSound", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RegisterStackedSound;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("RegisterStackedSound", 0);

	return;
}

nothing CJassInterface::Jass_UnregisterStackedSound_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("UnregisterStackedSound", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnregisterStackedSound;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("UnregisterStackedSound", 0);

	return;
}

handle CJassInterface::Jass_AddWeatherEffect_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddWeatherEffect", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _AddWeatherEffect;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("AddWeatherEffect", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemoveWeatherEffect_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveWeatherEffect", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveWeatherEffect;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveWeatherEffect", 0);

	return;
}

nothing CJassInterface::Jass_EnableWeatherEffect_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("EnableWeatherEffect", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _EnableWeatherEffect;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("EnableWeatherEffect", 0);

	return;
}

handle CJassInterface::Jass_TerrainDeformCrater_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TerrainDeformCrater", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TerrainDeformCrater;
	__asm mov retValue, eax;
	__asm add esp, 24;

	retValue = OnNativeCalled_Post("TerrainDeformCrater", retValue);

	return retValue;
}

handle CJassInterface::Jass_TerrainDeformRipple_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8, handle P9, handle P10)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TerrainDeformRipple", 10, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
		P9 = params[8];
		P10 = params[9];
	}

	__asm push P10;
	__asm push P9;
	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TerrainDeformRipple;
	__asm mov retValue, eax;
	__asm add esp, 40;

	retValue = OnNativeCalled_Post("TerrainDeformRipple", retValue);

	return retValue;
}

handle CJassInterface::Jass_TerrainDeformWave_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8, handle P9, handle P10)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TerrainDeformWave", 10, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
		P9 = params[8];
		P10 = params[9];
	}

	__asm push P10;
	__asm push P9;
	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TerrainDeformWave;
	__asm mov retValue, eax;
	__asm add esp, 40;

	retValue = OnNativeCalled_Post("TerrainDeformWave", retValue);

	return retValue;
}

handle CJassInterface::Jass_TerrainDeformRandom_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("TerrainDeformRandom", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TerrainDeformRandom;
	__asm mov retValue, eax;
	__asm add esp, 28;

	retValue = OnNativeCalled_Post("TerrainDeformRandom", retValue);

	return retValue;
}

nothing CJassInterface::Jass_TerrainDeformStop_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("TerrainDeformStop", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _TerrainDeformStop;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("TerrainDeformStop", 0);

	return;
}

nothing CJassInterface::Jass_TerrainDeformStopAll_Hooked()
{
	auto params = OnNativeCalled_Pre("TerrainDeformStopAll", 0);

	__asm call _TerrainDeformStopAll;

	OnNativeCalled_Post_NoParam("TerrainDeformStopAll", 0);

	return;
}

nothing CJassInterface::Jass_DestroyEffect_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyEffect", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyEffect;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyEffect", 0);

	return;
}

handle CJassInterface::Jass_AddSpecialEffect_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddSpecialEffect", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpecialEffect;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("AddSpecialEffect", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddSpecialEffectLoc_Hooked(handle P1, handle P2)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddSpecialEffectLoc", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _AddSpecialEffectLoc;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("AddSpecialEffectLoc", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddSpecialEffectTarget_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddSpecialEffectTarget", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpecialEffectTarget;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("AddSpecialEffectTarget", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffect_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddSpellEffect", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpellEffect;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("AddSpellEffect", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectLoc_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddSpellEffectLoc", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpellEffectLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("AddSpellEffectLoc", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectById_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddSpellEffectById", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpellEffectById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("AddSpellEffectById", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectByIdLoc_Hooked(handle P1, handle P2, handle P3)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddSpellEffectByIdLoc", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpellEffectByIdLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("AddSpellEffectByIdLoc", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectTarget_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddSpellEffectTarget", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpellEffectTarget;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("AddSpellEffectTarget", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectTargetById_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddSpellEffectTargetById", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpellEffectTargetById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("AddSpellEffectTargetById", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddLightning_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddLightning", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddLightning;
	__asm mov retValue, eax;
	__asm add esp, 24;

	retValue = OnNativeCalled_Post("AddLightning", retValue);

	return retValue;
}

handle CJassInterface::Jass_AddLightningEx_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("AddLightningEx", 8, P1, P2, P3, P4, P5, P6, P7, P8);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
	}

	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddLightningEx;
	__asm mov retValue, eax;
	__asm add esp, 32;

	retValue = OnNativeCalled_Post("AddLightningEx", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_DestroyLightning_Hooked(handle P1)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("DestroyLightning", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyLightning;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("DestroyLightning", retValue);

	return retValue;
}

real CJassInterface::Jass_GetLightningColorA_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetLightningColorA", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetLightningColorA;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetLightningColorA", retValue);

	return retValue;
}

real CJassInterface::Jass_GetLightningColorR_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetLightningColorR", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetLightningColorR;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetLightningColorR", retValue);

	return retValue;
}

real CJassInterface::Jass_GetLightningColorG_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetLightningColorG", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetLightningColorG;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetLightningColorG", retValue);

	return retValue;
}

real CJassInterface::Jass_GetLightningColorB_Hooked(handle P1)
{
	real retValue;

	auto params = OnNativeCalled_Pre("GetLightningColorB", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetLightningColorB;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetLightningColorB", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_MoveLightning_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("MoveLightning", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MoveLightning;
	__asm mov retValue, eax;
	__asm add esp, 24;

	retValue = OnNativeCalled_Post("MoveLightning", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_MoveLightningEx_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("MoveLightningEx", 8, P1, P2, P3, P4, P5, P6, P7, P8);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
	}

	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MoveLightningEx;
	__asm mov retValue, eax;
	__asm add esp, 32;

	retValue = OnNativeCalled_Post("MoveLightningEx", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_SetLightningColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("SetLightningColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetLightningColor;
	__asm mov retValue, eax;
	__asm add esp, 20;

	retValue = OnNativeCalled_Post("SetLightningColor", retValue);

	return retValue;
}

string CJassInterface::Jass_GetAbilityEffect_Hooked(handle P1, handle P2, handle P3)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetAbilityEffect", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetAbilityEffect;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetAbilityEffect", retValue);

	return retValue;
}

string CJassInterface::Jass_GetAbilityEffectById_Hooked(handle P1, handle P2, handle P3)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetAbilityEffectById", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetAbilityEffectById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("GetAbilityEffectById", retValue);

	return retValue;
}

string CJassInterface::Jass_GetAbilitySound_Hooked(handle P1, handle P2)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetAbilitySound", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetAbilitySound;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetAbilitySound", retValue);

	return retValue;
}

string CJassInterface::Jass_GetAbilitySoundById_Hooked(handle P1, handle P2)
{
	string retValue;

	auto params = OnNativeCalled_Pre("GetAbilitySoundById", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetAbilitySoundById;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetAbilitySoundById", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetTerrainCliffLevel_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTerrainCliffLevel", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetTerrainCliffLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetTerrainCliffLevel", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetWaterBaseColor_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetWaterBaseColor", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetWaterBaseColor;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetWaterBaseColor", 0);

	return;
}

nothing CJassInterface::Jass_SetWaterDeforms_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("SetWaterDeforms", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _SetWaterDeforms;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("SetWaterDeforms", 0);

	return;
}

integer CJassInterface::Jass_GetTerrainType_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTerrainType", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetTerrainType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetTerrainType", retValue);

	return retValue;
}

integer CJassInterface::Jass_GetTerrainVariance_Hooked(handle P1, handle P2)
{
	integer retValue;

	auto params = OnNativeCalled_Pre("GetTerrainVariance", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _GetTerrainVariance;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("GetTerrainVariance", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetTerrainType_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6)
{
	auto params = OnNativeCalled_Pre("SetTerrainType", 6, P1, P2, P3, P4, P5, P6);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
	}

	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTerrainType;
	__asm add esp, 24;

	OnNativeCalled_Post_NoParam("SetTerrainType", 0);

	return;
}

jboolean CJassInterface::Jass_IsTerrainPathable_Hooked(handle P1, handle P2, handle P3)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsTerrainPathable", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IsTerrainPathable;
	__asm mov retValue, eax;
	__asm add esp, 12;

	retValue = OnNativeCalled_Post("IsTerrainPathable", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetTerrainPathable_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetTerrainPathable", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTerrainPathable;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetTerrainPathable", 0);

	return;
}

handle CJassInterface::Jass_CreateImage_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8, handle P9, handle P10, handle P11)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateImage", 11, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
		P9 = params[8];
		P10 = params[9];
		P11 = params[10];
	}

	__asm push P11;
	__asm push P10;
	__asm push P9;
	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateImage;
	__asm mov retValue, eax;
	__asm add esp, 44;

	retValue = OnNativeCalled_Post("CreateImage", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyImage_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyImage", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyImage;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyImage", 0);

	return;
}

nothing CJassInterface::Jass_ShowImage_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ShowImage", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ShowImage;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ShowImage", 0);

	return;
}

nothing CJassInterface::Jass_SetImageConstantHeight_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetImageConstantHeight", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetImageConstantHeight;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetImageConstantHeight", 0);

	return;
}

nothing CJassInterface::Jass_SetImagePosition_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetImagePosition", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetImagePosition;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetImagePosition", 0);

	return;
}

nothing CJassInterface::Jass_SetImageColor_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("SetImageColor", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetImageColor;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("SetImageColor", 0);

	return;
}

nothing CJassInterface::Jass_SetImageRender_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetImageRender", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetImageRender;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetImageRender", 0);

	return;
}

nothing CJassInterface::Jass_SetImageRenderAlways_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetImageRenderAlways", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetImageRenderAlways;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetImageRenderAlways", 0);

	return;
}

nothing CJassInterface::Jass_SetImageAboveWater_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetImageAboveWater", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetImageAboveWater;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetImageAboveWater", 0);

	return;
}

nothing CJassInterface::Jass_SetImageType_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetImageType", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetImageType;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetImageType", 0);

	return;
}

handle CJassInterface::Jass_CreateUbersplat_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7, handle P8, handle P9)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateUbersplat", 9, P1, P2, P3, P4, P5, P6, P7, P8, P9);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
		P8 = params[7];
		P9 = params[8];
	}

	__asm push P9;
	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateUbersplat;
	__asm mov retValue, eax;
	__asm add esp, 36;

	retValue = OnNativeCalled_Post("CreateUbersplat", retValue);

	return retValue;
}

nothing CJassInterface::Jass_DestroyUbersplat_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("DestroyUbersplat", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _DestroyUbersplat;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("DestroyUbersplat", 0);

	return;
}

nothing CJassInterface::Jass_ResetUbersplat_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("ResetUbersplat", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ResetUbersplat;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("ResetUbersplat", 0);

	return;
}

nothing CJassInterface::Jass_FinishUbersplat_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("FinishUbersplat", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _FinishUbersplat;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("FinishUbersplat", 0);

	return;
}

nothing CJassInterface::Jass_ShowUbersplat_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("ShowUbersplat", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _ShowUbersplat;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("ShowUbersplat", 0);

	return;
}

nothing CJassInterface::Jass_SetUbersplatRender_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUbersplatRender", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUbersplatRender;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUbersplatRender", 0);

	return;
}

nothing CJassInterface::Jass_SetUbersplatRenderAlways_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("SetUbersplatRenderAlways", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _SetUbersplatRenderAlways;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("SetUbersplatRenderAlways", 0);

	return;
}

nothing CJassInterface::Jass_SetBlight_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5)
{
	auto params = OnNativeCalled_Pre("SetBlight", 5, P1, P2, P3, P4, P5);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
	}

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetBlight;
	__asm add esp, 20;

	OnNativeCalled_Post_NoParam("SetBlight", 0);

	return;
}

nothing CJassInterface::Jass_SetBlightLoc_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetBlightLoc", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetBlightLoc;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetBlightLoc", 0);

	return;
}

nothing CJassInterface::Jass_SetBlightRect_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("SetBlightRect", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetBlightRect;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("SetBlightRect", 0);

	return;
}

nothing CJassInterface::Jass_SetBlightPoint_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetBlightPoint", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetBlightPoint;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetBlightPoint", 0);

	return;
}

handle CJassInterface::Jass_CreateBlightedGoldmine_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("CreateBlightedGoldmine", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateBlightedGoldmine;
	__asm mov retValue, eax;
	__asm add esp, 16;

	retValue = OnNativeCalled_Post("CreateBlightedGoldmine", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsPointBlighted_Hooked(handle P1, handle P2)
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsPointBlighted", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _IsPointBlighted;
	__asm mov retValue, eax;
	__asm add esp, 8;

	retValue = OnNativeCalled_Post("IsPointBlighted", retValue);

	return retValue;
}

nothing CJassInterface::Jass_SetDoodadAnimation_Hooked(handle P1, handle P2, handle P3, handle P4, handle P5, handle P6, handle P7)
{
	auto params = OnNativeCalled_Pre("SetDoodadAnimation", 7, P1, P2, P3, P4, P5, P6, P7);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
		P5 = params[4];
		P6 = params[5];
		P7 = params[6];
	}

	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetDoodadAnimation;
	__asm add esp, 28;

	OnNativeCalled_Post_NoParam("SetDoodadAnimation", 0);

	return;
}

nothing CJassInterface::Jass_SetDoodadAnimationRect_Hooked(handle P1, handle P2, handle P3, handle P4)
{
	auto params = OnNativeCalled_Pre("SetDoodadAnimationRect", 4, P1, P2, P3, P4);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
		P4 = params[3];
	}

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetDoodadAnimationRect;
	__asm add esp, 16;

	OnNativeCalled_Post_NoParam("SetDoodadAnimationRect", 0);

	return;
}

nothing CJassInterface::Jass_StartMeleeAI_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("StartMeleeAI", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _StartMeleeAI;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("StartMeleeAI", 0);

	return;
}

nothing CJassInterface::Jass_StartCampaignAI_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("StartCampaignAI", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _StartCampaignAI;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("StartCampaignAI", 0);

	return;
}

nothing CJassInterface::Jass_CommandAI_Hooked(handle P1, handle P2, handle P3)
{
	auto params = OnNativeCalled_Pre("CommandAI", 3, P1, P2, P3);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
		P3 = params[2];
	}

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CommandAI;
	__asm add esp, 12;

	OnNativeCalled_Post_NoParam("CommandAI", 0);

	return;
}

nothing CJassInterface::Jass_PauseCompAI_Hooked(handle P1, handle P2)
{
	auto params = OnNativeCalled_Pre("PauseCompAI", 2, P1, P2);

	if (!params.empty())
	{
		P1 = params[0];
		P2 = params[1];
	}

	__asm push P2;
	__asm push P1;
	__asm call _PauseCompAI;
	__asm add esp, 8;

	OnNativeCalled_Post_NoParam("PauseCompAI", 0);

	return;
}

handle CJassInterface::Jass_GetAIDifficulty_Hooked(handle P1)
{
	handle retValue;

	auto params = OnNativeCalled_Pre("GetAIDifficulty", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _GetAIDifficulty;
	__asm mov retValue, eax;
	__asm add esp, 4;

	retValue = OnNativeCalled_Post("GetAIDifficulty", retValue);

	return retValue;
}

nothing CJassInterface::Jass_RemoveGuardPosition_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveGuardPosition", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveGuardPosition;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveGuardPosition", 0);

	return;
}

nothing CJassInterface::Jass_RecycleGuardPosition_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RecycleGuardPosition", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RecycleGuardPosition;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RecycleGuardPosition", 0);

	return;
}

nothing CJassInterface::Jass_RemoveAllGuardPositions_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("RemoveAllGuardPositions", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _RemoveAllGuardPositions;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("RemoveAllGuardPositions", 0);

	return;
}

nothing CJassInterface::Jass_ExecuteFunc_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("ExecuteFunc", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _ExecuteFunc;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("ExecuteFunc", 0);

	return;
}

nothing CJassInterface::Jass_Cheat_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("Cheat", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Cheat;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("Cheat", 0);

	return;
}

jboolean CJassInterface::Jass_IsNoVictoryCheat_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsNoVictoryCheat", 0);

	__asm call _IsNoVictoryCheat;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("IsNoVictoryCheat", retValue);

	return retValue;
}

jboolean CJassInterface::Jass_IsNoDefeatCheat_Hooked()
{
	jboolean retValue;

	auto params = OnNativeCalled_Pre("IsNoDefeatCheat", 0);

	__asm call _IsNoDefeatCheat;
	__asm mov retValue, eax;

	retValue = OnNativeCalled_Post("IsNoDefeatCheat", retValue);

	return retValue;
}

nothing CJassInterface::Jass_Preload_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("Preload", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Preload;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("Preload", 0);

	return;
}

nothing CJassInterface::Jass_PreloadEnd_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("PreloadEnd", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _PreloadEnd;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("PreloadEnd", 0);

	return;
}

nothing CJassInterface::Jass_PreloadStart_Hooked()
{
	auto params = OnNativeCalled_Pre("PreloadStart", 0);

	__asm call _PreloadStart;

	OnNativeCalled_Post_NoParam("PreloadStart", 0);

	return;
}

nothing CJassInterface::Jass_PreloadRefresh_Hooked()
{
	auto params = OnNativeCalled_Pre("PreloadRefresh", 0);

	__asm call _PreloadRefresh;

	OnNativeCalled_Post_NoParam("PreloadRefresh", 0);

	return;
}

nothing CJassInterface::Jass_PreloadEndEx_Hooked()
{
	auto params = OnNativeCalled_Pre("PreloadEndEx", 0);

	__asm call _PreloadEndEx;

	OnNativeCalled_Post_NoParam("PreloadEndEx", 0);

	return;
}

nothing CJassInterface::Jass_PreloadGenStart_Hooked()
{
	auto params = OnNativeCalled_Pre("PreloadGenStart", 0);

	__asm call _PreloadGenStart;

	OnNativeCalled_Post_NoParam("PreloadGenStart", 0);

	return;
}

nothing CJassInterface::Jass_PreloadGenClear_Hooked()
{
	auto params = OnNativeCalled_Pre("PreloadGenClear", 0);

	__asm call _PreloadGenClear;

	OnNativeCalled_Post_NoParam("PreloadGenClear", 0);

	return;
}

nothing CJassInterface::Jass_PreloadGenEnd_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("PreloadGenEnd", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _PreloadGenEnd;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("PreloadGenEnd", 0);

	return;
}

nothing CJassInterface::Jass_Preloader_Hooked(handle P1)
{
	auto params = OnNativeCalled_Pre("Preloader", 1, P1);

	if (!params.empty())
	{
		P1 = params[0];
	}

	__asm push P1;
	__asm call _Preloader;
	__asm add esp, 4;

	OnNativeCalled_Post_NoParam("Preloader", 0);

	return;
}

#pragma endregion

/* Jass Binding */

nothing CJassInterface::Jass_DebugS(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _DebugS;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DebugFI(stringret P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _DebugFI;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_DebugUnitID(stringret P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _DebugUnitID;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_DisplayText(integer P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _DisplayText;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_DisplayTextI(integer P1, stringret P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _DisplayTextI;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_DisplayTextII(integer P1, stringret P2, integer P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P4;
	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _DisplayTextII;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_DisplayTextIII(integer P1, stringret P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _DisplayTextIII;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_SuicideUnit(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SuicideUnit;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SuicideUnitEx(integer P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SuicideUnitEx;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_Sleep(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P1;
	__asm push eax;
	__asm call _Sleep;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_StartThread(code P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _StartThread;
	__asm add esp, 4;

	return;
}

integer CJassInterface::Jass_GetAiPlayer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetAiPlayer;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_DoAiScriptDebug()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _DoAiScriptDebug;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetHeroId()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetHeroId;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetHeroLevelAI()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetHeroLevelAI;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_SetHeroLevels(code P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetHeroLevels;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetNewHeroes(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetNewHeroes;
	__asm add esp, 4;

	return;
}

integer CJassInterface::Jass_GetUnitCount(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetPlayerUnitTypeCount(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerUnitTypeCount;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_GetTownUnitCount(integer P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _GetTownUnitCount;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

integer CJassInterface::Jass_GetUnitCountDone(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitCountDone;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetUpgradeLevel(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUpgradeLevel;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetUnitGoldCost(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitGoldCost;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetUnitWoodCost(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitWoodCost;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetUnitBuildTime(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitBuildTime;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetUpgradeGoldCost(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUpgradeGoldCost;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetUpgradeWoodCost(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUpgradeWoodCost;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetEnemyPower()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetEnemyPower;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetMinesOwned()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetMinesOwned;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetGoldOwned()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetGoldOwned;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_TownWithMine()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _TownWithMine;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_TownHasMine(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _TownHasMine;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_TownHasHall(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _TownHasHall;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetNextExpansion()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetNextExpansion;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetExpansionPeon()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetExpansionPeon;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetEnemyExpansion()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEnemyExpansion;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_SetExpansion(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _SetExpansion;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_GetBuilding(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetBuilding;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetAllianceTarget(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetAllianceTarget;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_GetAllianceTarget()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetAllianceTarget;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_SetProduce(integer P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetProduce;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_MergeUnits(integer P1, integer P2, integer P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MergeUnits;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_ConvertUnits(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _ConvertUnits;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_SetUpgrade(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _SetUpgrade;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_Unsummon(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _Unsummon;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ClearHarvestAI()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ClearHarvestAI;

	return;
}

nothing CJassInterface::Jass_HarvestGold(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _HarvestGold;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_HarvestWood(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _HarvestWood;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_StopGathering()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _StopGathering;

	return;
}

nothing CJassInterface::Jass_AddGuardPost(integer P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _AddGuardPost;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_FillGuardPosts()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _FillGuardPosts;

	return;
}

nothing CJassInterface::Jass_ReturnGuardPosts()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ReturnGuardPosts;

	return;
}

nothing CJassInterface::Jass_CreateCaptains()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _CreateCaptains;

	return;
}

nothing CJassInterface::Jass_SetCaptainHome(integer P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetCaptainHome;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_ResetCaptainLocs()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ResetCaptainLocs;

	return;
}

nothing CJassInterface::Jass_ShiftTownSpot(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _ShiftTownSpot;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetCaptainChanges(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetCaptainChanges;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_TeleportCaptain(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _TeleportCaptain;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ClearCaptainTargets()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ClearCaptainTargets;

	return;
}

nothing CJassInterface::Jass_CaptainVsUnits(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _CaptainVsUnits;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_CaptainVsPlayer(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _CaptainVsPlayer;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_CaptainAttack(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _CaptainAttack;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_GroupTimedLife(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _GroupTimedLife;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_CaptainGoHome()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _CaptainGoHome;

	return;
}

jbooleanret CJassInterface::Jass_CaptainIsHome()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _CaptainIsHome;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_CaptainRetreating()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _CaptainRetreating;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_CaptainIsFull()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _CaptainIsFull;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_CaptainIsEmpty()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _CaptainIsEmpty;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_CaptainGroupSize()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _CaptainGroupSize;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_CaptainReadiness()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _CaptainReadiness;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_CaptainReadinessHP()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _CaptainReadinessHP;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_CaptainReadinessMa()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _CaptainReadinessMa;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_CaptainInCombat(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _CaptainInCombat;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_TownThreatened()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _TownThreatened;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_CaptainAtGoal()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _CaptainAtGoal;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_CreepsOnMap()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _CreepsOnMap;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_RemoveInjuries()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _RemoveInjuries;

	return;
}

nothing CJassInterface::Jass_RemoveSiege()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _RemoveSiege;

	return;
}

jbooleanret CJassInterface::Jass_IsTowered(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsTowered;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_DisablePathing()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _DisablePathing;

	return;
}

nothing CJassInterface::Jass_SetAmphibious()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _SetAmphibious;

	return;
}

nothing CJassInterface::Jass_InitAssault()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _InitAssault;

	return;
}

jbooleanret CJassInterface::Jass_AddAssault(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _AddAssault;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_AddDefenders(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _AddDefenders;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_GetCreepCamp(integer P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _GetCreepCamp;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_StartGetEnemyBase()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _StartGetEnemyBase;

	return;
}

jbooleanret CJassInterface::Jass_WaitGetEnemyBase()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _WaitGetEnemyBase;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetMegaTarget()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetMegaTarget;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetEnemyBase()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEnemyBase;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetExpansionFoe()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetExpansionFoe;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetExpansionX()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetExpansionX;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetExpansionY()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetExpansionY;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_SetStagePoint(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetStagePoint;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_AttackMoveKill(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _AttackMoveKill;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_AttackMoveXY(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _AttackMoveXY;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_LoadZepWave(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _LoadZepWave;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_SuicidePlayer(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SuicidePlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_SuicidePlayerUnits(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SuicidePlayerUnits;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitAlive(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _UnitAlive;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitInvis(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _UnitInvis;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_IgnoredUnits(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _IgnoredUnits;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_CommandsWaiting()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _CommandsWaiting;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetLastCommand()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetLastCommand;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetLastData()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetLastData;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_PopLastCommand()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _PopLastCommand;

	return;
}

nothing CJassInterface::Jass_SetCampaignAI()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _SetCampaignAI;

	return;
}

nothing CJassInterface::Jass_SetMeleeAI()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _SetMeleeAI;

	return;
}

nothing CJassInterface::Jass_SetTargetHeroes(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetTargetHeroes;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetHeroesFlee(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetHeroesFlee;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetHeroesBuyItems(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetHeroesBuyItems;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetIgnoreInjured(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetIgnoreInjured;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetPeonsRepair(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetPeonsRepair;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetRandomPaths(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetRandomPaths;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetDefendPlayer(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetDefendPlayer;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetHeroesTakeItems(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetHeroesTakeItems;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetUnitsFlee(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetUnitsFlee;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetGroupsFlee(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetGroupsFlee;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetSlowChopping(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetSlowChopping;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetSmartArtillery(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetSmartArtillery;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetWatchMegaTargets(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetWatchMegaTargets;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetReplacementCount(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetReplacementCount;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_PurchaseZeppelin()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _PurchaseZeppelin;

	return;
}

integer CJassInterface::Jass_MeleeDifficulty()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _MeleeDifficulty;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DebugBreak(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DebugBreak;
	__asm add esp, 4;

	return;
}

realret CJassInterface::Jass_Deg2Rad(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _Deg2Rad;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_Rad2Deg(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _Rad2Deg;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_Sin(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call __Sin;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_Cos(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _Cos;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_Tan(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _Tan;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_Asin(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _Asin;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_Acos(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _Acos;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_Atan(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _Atan;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_Atan2(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _Atan2;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue.fl;
}

realret CJassInterface::Jass_SquareRoot(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _SquareRoot;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_Pow(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _Pow;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue.fl;
}

realret CJassInterface::Jass_I2R(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _I2R;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

integer CJassInterface::Jass_R2I(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _R2I;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_I2S(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _I2S;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

stringret CJassInterface::Jass_R2S(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm lea eax, P1;
	__asm push eax;
	__asm call _R2S;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

stringret CJassInterface::Jass_R2SW(realret P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P3;
	__asm push P2;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _R2SW;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_S2I(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _S2I;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

realret CJassInterface::Jass_S2R(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _S2R;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

integer CJassInterface::Jass_GetHandleId(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetHandleId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_SubString(stringret P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P3;
	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SubString;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_StringLength(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _StringLength;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_StringCase(stringret P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;
	jboolean bP2 = P2;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push bP2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _StringCase;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_StringHash(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _StringHash;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_GetLocalizedString(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _GetLocalizedString;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_GetLocalizedHotkey(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _GetLocalizedHotkey;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertRace(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertRace;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertAllianceType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertAllianceType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertRacePref(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertRacePref;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertIGameState(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertIGameState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertFGameState(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertFGameState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerState(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertPlayerState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerScore(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertPlayerScore;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertStartLocPrio(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertStartLocPrio;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerGameResult(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertPlayerGameResult;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertUnitState(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertUnitState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertAIDifficulty(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertAIDifficulty;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertGameEvent(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertGameEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerEvent(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertPlayerEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerUnitEvent(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertPlayerUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertUnitEvent(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertWidgetEvent(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertWidgetEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertDialogEvent(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertDialogEvent;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertLimitOp(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertLimitOp;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertUnitType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertUnitType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertGameSpeed(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertGameSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertPlacement(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertPlacement;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertGameDifficulty(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertGameDifficulty;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertGameType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertGameType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertMapFlag(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertMapFlag;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertMapVisibility(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertMapVisibility;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertMapSetting(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertMapSetting;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertMapDensity(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertMapDensity;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertMapControl(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertMapControl;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerColor(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertPlayerColor;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertPlayerSlotState(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertPlayerSlotState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertVolumeGroup(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertVolumeGroup;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertCameraField(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertCameraField;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertBlendMode(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertBlendMode;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertRarityControl(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertRarityControl;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertTexMapFlags(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertTexMapFlags;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertFogState(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertFogState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertEffectType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertEffectType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertVersion(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertVersion;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertItemType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertItemType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertAttackType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertAttackType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertDamageType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertDamageType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertWeaponType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertWeaponType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertSoundType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertSoundType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_ConvertPathingType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _ConvertPathingType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetMapName(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetMapName;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetMapDescription(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetMapDescription;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetTeams(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetTeams;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetPlayers(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetPlayers;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetGameTypeSupported(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetGameTypeSupported;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetMapFlag(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetMapFlag;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetGameSpeed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetGameSpeed;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetGamePlacement(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetGamePlacement;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetGameDifficulty(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetGameDifficulty;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetResourceDensity(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetResourceDensity;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetCreatureDensity(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetCreatureDensity;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DefineStartLocation(integer P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _DefineStartLocation;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_DefineStartLocationLoc(integer P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _DefineStartLocationLoc;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetStartLocPrioCount(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetStartLocPrioCount;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetStartLocPrio(integer P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetStartLocPrio;
	__asm add esp, 16;

	return;
}

integer CJassInterface::Jass_GetStartLocPrioSlot(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetStartLocPrioSlot;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_GetStartLocPrio(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetStartLocPrio;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_GetTeams()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetTeams;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetPlayers()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetPlayers;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsGameTypeSupported(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsGameTypeSupported;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsMapFlagSet(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsMapFlagSet;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetGameTypeSelected()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetGameTypeSelected;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetGamePlacement()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetGamePlacement;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetGameSpeed()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetGameSpeed;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetGameDifficulty()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetGameDifficulty;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetResourceDensity()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetResourceDensity;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetCreatureDensity()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetCreatureDensity;
	__asm mov retValue, eax;

	return retValue;
}

realret CJassInterface::Jass_GetStartLocationX(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetStartLocationX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetStartLocationY(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetStartLocationY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

handle CJassInterface::Jass_GetStartLocationLoc(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetStartLocationLoc;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerTeam(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerTeam;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetPlayerStartLocation(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerStartLocation;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ForcePlayerStartLocation(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _ForcePlayerStartLocation;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetPlayerAlliance(handle P1, handle P2, handle P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP4 = P4;

	__asm push bP4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerAlliance;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetPlayerTaxRate(handle P1, handle P2, handle P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerTaxRate;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetPlayerRacePreference(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerRacePreference;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetPlayerRaceSelectable(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetPlayerRaceSelectable;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetPlayerController(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerController;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetPlayerColor(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerColor;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetPlayerOnScoreScreen(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetPlayerOnScoreScreen;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetPlayerName(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SetPlayerName;
	__asm add esp, 8;

	return;
}

integer CJassInterface::Jass_GetPlayerTeam(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetPlayerTeam;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_GetPlayerName(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _GetPlayerName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_GetPlayerStartLocation(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetPlayerStartLocation;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

realret CJassInterface::Jass_GetPlayerStartLocationX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetPlayerStartLocationX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetPlayerStartLocationY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetPlayerStartLocationY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

handle CJassInterface::Jass_GetPlayerColor(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetPlayerColor;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_GetPlayerSelectable(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _GetPlayerSelectable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetPlayerController(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetPlayerController;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetPlayerSlotState(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetPlayerSlotState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetPlayerTaxRate(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerTaxRate;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsPlayerRacePrefSet(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsPlayerRacePrefSet;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_Location(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _Location;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_RemoveLocation(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveLocation;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_MoveLocation(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _MoveLocation;
	__asm add esp, 12;

	return;
}

realret CJassInterface::Jass_GetLocationX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetLocationX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetLocationY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetLocationY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetLocationZ(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetLocationZ;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

handle CJassInterface::Jass_CreateTimer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateTimer;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyTimer(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyTimer;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_TimerStart(handle P1, realret P2, jbooleanret P3, code P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push P4;
	__asm push bP3;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _TimerStart;
	__asm add esp, 16;

	return;
}

realret CJassInterface::Jass_TimerGetTimeout(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _TimerGetTimeout;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_TimerGetElapsed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _TimerGetElapsed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_TimerGetRemaining(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _TimerGetRemaining;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_PauseTimer(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _PauseTimer;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ResumeTimer(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _ResumeTimer;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_GetExpiredTimer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetExpiredTimer;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_Condition(code P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _Condition;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_DestroyCondition(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyCondition;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_Filter(code P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _Filter;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_DestroyFilter(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyFilter;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DestroyBoolExpr(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyBoolExpr;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_And(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _And;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_Or(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _Or;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_Not(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _Not;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_CreateRegion()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateRegion;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_RemoveRegion(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveRegion;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_RegionAddRect(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _RegionAddRect;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_RegionClearRect(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _RegionClearRect;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_RegionAddCell(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _RegionAddCell;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_RegionAddCellAtLoc(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _RegionAddCellAtLoc;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_RegionClearCell(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _RegionClearCell;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_RegionClearCellAtLoc(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _RegionClearCellAtLoc;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsUnitInRegion(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInRegion;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsPointInRegion(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _IsPointInRegion;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsLocationInRegion(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsLocationInRegion;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_Rect(realret P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _Rect;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_RectFromLoc(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _RectFromLoc;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_RemoveRect(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveRect;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetRect(handle P1, realret P2, realret P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetRect;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_SetRectFromLoc(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetRectFromLoc;
	__asm add esp, 12;

	return;
}

realret CJassInterface::Jass_GetRectCenterX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetRectCenterX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetRectCenterY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetRectCenterY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_MoveRectTo(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _MoveRectTo;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_MoveRectToLoc(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _MoveRectToLoc;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetRectMinX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetRectMinX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetRectMinY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetRectMinY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetRectMaxX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetRectMaxX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetRectMaxY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetRectMaxY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

handle CJassInterface::Jass_GetWorldBounds()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetWorldBounds;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_SetFogStateRect(handle P1, handle P2, handle P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP4 = P4;

	__asm push bP4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetFogStateRect;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetFogStateRadius(handle P1, handle P2, realret P3, realret P4, realret P5, jbooleanret P6)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP6 = P6;

	__asm push bP6;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _SetFogStateRadius;
	__asm add esp, 24;

	return;
}

nothing CJassInterface::Jass_SetFogStateRadiusLoc(handle P1, handle P2, handle P3, realret P4, jbooleanret P5)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP5 = P5;

	__asm push bP5;
	__asm lea eax, P4;
	__asm push eax;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetFogStateRadiusLoc;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_FogMaskEnable(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _FogMaskEnable;
	__asm add esp, 4;

	return;
}

jbooleanret CJassInterface::Jass_IsFogMaskEnabled()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _IsFogMaskEnabled;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_FogEnable(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _FogEnable;
	__asm add esp, 4;

	return;
}

jbooleanret CJassInterface::Jass_IsFogEnabled()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _IsFogEnabled;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_CreateFogModifierRect(handle P1, handle P2, handle P3, jbooleanret P4, jbooleanret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP5 = P5;
	jboolean bP4 = P4;

	__asm push bP5;
	__asm push bP4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateFogModifierRect;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

handle CJassInterface::Jass_CreateFogModifierRadius(handle P1, handle P2, realret P3, realret P4, realret P5, jbooleanret P6, jbooleanret P7)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP7 = P7;
	jboolean bP6 = P6;

	__asm push bP7;
	__asm push bP6;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _CreateFogModifierRadius;
	__asm mov retValue, eax;
	__asm add esp, 28;

	return retValue;
}

handle CJassInterface::Jass_CreateFogModifierRadiusLoc(handle P1, handle P2, handle P3, realret P4, jbooleanret P5, jbooleanret P6)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP6 = P6;
	jboolean bP5 = P5;

	__asm push bP6;
	__asm push bP5;
	__asm lea eax, P4;
	__asm push eax;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateFogModifierRadiusLoc;
	__asm mov retValue, eax;
	__asm add esp, 24;

	return retValue;
}

nothing CJassInterface::Jass_DestroyFogModifier(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyFogModifier;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_FogModifierStart(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _FogModifierStart;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_FogModifierStop(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _FogModifierStop;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_CreateTrigger()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateTrigger;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyTrigger(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyTrigger;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ResetTrigger(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _ResetTrigger;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_EnableTrigger(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _EnableTrigger;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DisableTrigger(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DisableTrigger;
	__asm add esp, 4;

	return;
}

jbooleanret CJassInterface::Jass_IsTriggerEnabled(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsTriggerEnabled;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_TriggerWaitOnSleeps(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _TriggerWaitOnSleeps;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsTriggerWaitOnSleeps(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsTriggerWaitOnSleeps;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterVariableEvent(handle P1, stringret P2, handle P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P4;
	__asm push eax;
	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _TriggerRegisterVariableEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterTimerEvent(handle P1, realret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP3 = P3;

	__asm push bP3;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _TriggerRegisterTimerEvent;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterTimerExpireEvent(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterTimerExpireEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterGameStateEvent(handle P1, handle P2, handle P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterGameStateEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_GetEventGameState()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEventGameState;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterDialogEvent(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterDialogEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterDialogButtonEvent(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterDialogButtonEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_GetClickedButton()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetClickedButton;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetClickedDialog()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetClickedDialog;
	__asm mov retValue, eax;

	return retValue;
}

realret CJassInterface::Jass_GetTournamentFinishSoonTimeRemaining()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetTournamentFinishSoonTimeRemaining;
	__asm mov retValue, eax;

	return retValue.fl;
}

integer CJassInterface::Jass_GetTournamentFinishNowRule()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetTournamentFinishNowRule;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetTournamentFinishNowPlayer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTournamentFinishNowPlayer;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetTournamentScore(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetTournamentScore;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_GetSaveBasicFilename()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm call _GetSaveBasicFilename;
	__asm mov retValue, eax;

	return jStr2cStr(retValue);
}

handle CJassInterface::Jass_TriggerRegisterGameEvent(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterGameEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_GetWinningPlayer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetWinningPlayer;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerStateEvent(handle P1, handle P2, handle P3, handle P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P5;
	__asm push eax;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerStateEvent;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

handle CJassInterface::Jass_GetEventPlayerState()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEventPlayerState;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerEvent(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerEvent;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerUnitEvent(handle P1, handle P2, handle P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_GetAttacker()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetAttacker;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetRescuer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetRescuer;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetDyingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetDyingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetKillingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetKillingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetDecayingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetDecayingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetConstructingStructure()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetConstructingStructure;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetCancelledStructure()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetCancelledStructure;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetConstructedStructure()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetConstructedStructure;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetTrainedUnitType()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetTrainedUnitType;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetResearchingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetResearchingUnit;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetResearched()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetResearched;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetTrainedUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTrainedUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSellingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSellingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSoldUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSoldUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetBuyingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetBuyingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSoldItem()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSoldItem;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetChangingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetChangingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetChangingUnitPrevOwner()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetChangingUnitPrevOwner;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetDetectedUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetDetectedUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetOrderedUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetOrderedUnit;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_OrderId(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _OrderId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_OrderId2String(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _OrderId2String;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_AbilityId(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _AbilityId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_AbilityId2String(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _AbilityId2String;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_UnitId(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _UnitId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_UnitId2String(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _UnitId2String;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

stringret CJassInterface::Jass_GetObjectName(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _GetObjectName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_GetIssuedOrderId()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetIssuedOrderId;
	__asm mov retValue, eax;

	return retValue;
}

realret CJassInterface::Jass_GetOrderPointX()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetOrderPointX;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetOrderPointY()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetOrderPointY;
	__asm mov retValue, eax;

	return retValue.fl;
}

handle CJassInterface::Jass_GetOrderPointLoc()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetOrderPointLoc;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetOrderTarget()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetOrderTarget;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetOrderTargetDestructable()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetOrderTargetDestructable;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetOrderTargetItem()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetOrderTargetItem;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetOrderTargetUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetOrderTargetUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSpellAbilityUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSpellAbilityUnit;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetSpellAbilityId()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetSpellAbilityId;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSpellAbility()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSpellAbility;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSpellTargetLoc()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSpellTargetLoc;
	__asm mov retValue, eax;

	return retValue;
}

realret CJassInterface::Jass_GetSpellTargetX()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetSpellTargetX;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetSpellTargetY()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetSpellTargetY;
	__asm mov retValue, eax;

	return retValue.fl;
}

handle CJassInterface::Jass_GetSpellTargetDestructable()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSpellTargetDestructable;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSpellTargetItem()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSpellTargetItem;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSpellTargetUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSpellTargetUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetLevelingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetLevelingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetLearningUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetLearningUnit;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetLearnedSkill()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetLearnedSkill;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetLearnedSkillLevel()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetLearnedSkillLevel;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetRevivableUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetRevivableUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetRevivingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetRevivingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSummoningUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSummoningUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetSummonedUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetSummonedUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetTransportUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTransportUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetLoadedUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetLoadedUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetManipulatingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetManipulatingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetManipulatedItem()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetManipulatedItem;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerAllianceChange(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerAllianceChange;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterPlayerChatEvent(handle P1, handle P2, stringret P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP4 = P4;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);

	__asm push bP4;
	__asm lea eax, sP3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterPlayerChatEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

stringret CJassInterface::Jass_GetEventPlayerChatString()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm call _GetEventPlayerChatString;
	__asm mov retValue, eax;

	return jStr2cStr(retValue);
}

stringret CJassInterface::Jass_GetEventPlayerChatStringMatched()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm call _GetEventPlayerChatStringMatched;
	__asm mov retValue, eax;

	return jStr2cStr(retValue);
}

handle CJassInterface::Jass_TriggerRegisterUnitStateEvent(handle P1, handle P2, handle P3, handle P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P5;
	__asm push eax;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterUnitStateEvent;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

handle CJassInterface::Jass_GetEventUnitState()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEventUnitState;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterDeathEvent(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterDeathEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterUnitEvent(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

realret CJassInterface::Jass_GetEventDamage()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetEventDamage;
	__asm mov retValue, eax;

	return retValue.fl;
}

handle CJassInterface::Jass_GetEventDamageSource()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEventDamageSource;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetEventDetectingPlayer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEventDetectingPlayer;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetEventTargetUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEventTargetUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterFilterUnitEvent(handle P1, handle P2, handle P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterFilterUnitEvent;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterUnitInRange(handle P1, handle P2, realret P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P4;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterUnitInRange;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterEnterRegion(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterEnterRegion;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterLeaveRegion(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterLeaveRegion;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_GetTriggeringRegion()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTriggeringRegion;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetEnteringUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEnteringUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetLeavingUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetLeavingUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_TriggerAddCondition(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _TriggerAddCondition;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_TriggerRemoveCondition(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _TriggerRemoveCondition;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_TriggerClearConditions(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _TriggerClearConditions;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_TriggerAddAction(handle P1, code P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _TriggerAddAction;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_TriggerRemoveAction(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _TriggerRemoveAction;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_TriggerClearActions(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _TriggerClearActions;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_TriggerSleepAction(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P1;
	__asm push eax;
	__asm call _TriggerSleepAction;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_TriggerWaitForSound(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _TriggerWaitForSound;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_TriggerExecute(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _TriggerExecute;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_TriggerExecuteWait(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _TriggerExecuteWait;
	__asm add esp, 4;

	return;
}

jbooleanret CJassInterface::Jass_TriggerEvaluate(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _TriggerEvaluate;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_TriggerSyncStart()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _TriggerSyncStart;

	return;
}

nothing CJassInterface::Jass_TriggerSyncReady()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _TriggerSyncReady;

	return;
}

handle CJassInterface::Jass_GetTriggerWidget()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTriggerWidget;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetTriggerDestructable()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTriggerDestructable;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetTriggerUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTriggerUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetTriggerPlayer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTriggerPlayer;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetTriggeringTrigger()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTriggeringTrigger;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetTriggerEventId()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTriggerEventId;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_GetTriggerEvalCount(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetTriggerEvalCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetTriggerExecCount(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetTriggerExecCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetFilterUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetFilterUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetEnumUnit()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEnumUnit;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetEnumPlayer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEnumPlayer;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetFilterPlayer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetFilterPlayer;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetFilterDestructable()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetFilterDestructable;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetEnumDestructable()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEnumDestructable;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetFilterItem()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetFilterItem;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_GetEnumItem()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetEnumItem;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_CreateGroup()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateGroup;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyGroup(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyGroup;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_GroupAddUnit(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _GroupAddUnit;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_GroupRemoveUnit(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _GroupRemoveUnit;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_GroupClear(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _GroupClear;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsOfType(handle P1, stringret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GroupEnumUnitsOfType;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsOfTypeCounted(handle P1, stringret P2, handle P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P4;
	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GroupEnumUnitsOfTypeCounted;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRect(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRect;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRectCounted(handle P1, handle P2, handle P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRectCounted;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsOfPlayer(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsOfPlayer;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRange(handle P1, realret P2, realret P3, realret P4, handle P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _GroupEnumUnitsInRange;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRangeOfLoc(handle P1, handle P2, realret P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRangeOfLoc;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRangeCounted(handle P1, realret P2, realret P3, realret P4, handle P5, integer P6)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P6;
	__asm push P5;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _GroupEnumUnitsInRangeCounted;
	__asm add esp, 24;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsInRangeOfLocCounted(handle P1, handle P2, realret P3, handle P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsInRangeOfLocCounted;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_GroupEnumUnitsSelected(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupEnumUnitsSelected;
	__asm add esp, 12;

	return;
}

jbooleanret CJassInterface::Jass_GroupImmediateOrder(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GroupImmediateOrder;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_GroupImmediateOrderById(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GroupImmediateOrderById;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_GroupPointOrder(handle P1, stringret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GroupPointOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_GroupPointOrderLoc(handle P1, stringret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GroupPointOrderLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_GroupPointOrderById(handle P1, integer P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _GroupPointOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_GroupPointOrderByIdLoc(handle P1, integer P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupPointOrderByIdLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_GroupTargetOrder(handle P1, stringret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GroupTargetOrder;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_GroupTargetOrderById(handle P1, integer P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GroupTargetOrderById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_ForGroup(handle P1, code P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _ForGroup;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_FirstOfGroup(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _FirstOfGroup;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_CreateForce()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateForce;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyForce(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyForce;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ForceAddPlayer(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _ForceAddPlayer;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ForceRemovePlayer(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _ForceRemovePlayer;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ForceClear(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _ForceClear;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ForceEnumPlayers(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _ForceEnumPlayers;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ForceEnumPlayersCounted(handle P1, handle P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ForceEnumPlayersCounted;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_ForceEnumAllies(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ForceEnumAllies;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_ForceEnumEnemies(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _ForceEnumEnemies;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_ForForce(handle P1, code P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _ForForce;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetWidgetLife(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetWidgetLife;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_SetWidgetLife(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetWidgetLife;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetWidgetX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetWidgetX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetWidgetY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetWidgetY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

handle CJassInterface::Jass_CreateDestructable(integer P1, realret P2, realret P3, realret P4, realret P5, integer P6)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P6;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _CreateDestructable;
	__asm mov retValue, eax;
	__asm add esp, 24;

	return retValue;
}

handle CJassInterface::Jass_CreateDestructableZ(integer P1, realret P2, realret P3, realret P4, realret P5, realret P6, integer P7)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P7;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _CreateDestructableZ;
	__asm mov retValue, eax;
	__asm add esp, 28;

	return retValue;
}

handle CJassInterface::Jass_CreateDeadDestructable(integer P1, realret P2, realret P3, realret P4, realret P5, integer P6)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P6;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _CreateDeadDestructable;
	__asm mov retValue, eax;
	__asm add esp, 24;

	return retValue;
}

handle CJassInterface::Jass_CreateDeadDestructableZ(integer P1, realret P2, realret P3, realret P4, realret P5, realret P6, integer P7)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P7;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _CreateDeadDestructableZ;
	__asm mov retValue, eax;
	__asm add esp, 28;

	return retValue;
}

nothing CJassInterface::Jass_RemoveDestructable(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveDestructable;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_KillDestructable(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _KillDestructable;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetDestructableInvulnerable(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetDestructableInvulnerable;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsDestructableInvulnerable(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsDestructableInvulnerable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_EnumDestructablesInRect(handle P1, handle P2, code P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _EnumDestructablesInRect;
	__asm add esp, 12;

	return;
}

integer CJassInterface::Jass_GetDestructableTypeId(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetDestructableTypeId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

realret CJassInterface::Jass_GetDestructableX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetDestructableX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetDestructableY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetDestructableY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_SetDestructableLife(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetDestructableLife;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetDestructableLife(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetDestructableLife;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_SetDestructableMaxLife(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetDestructableMaxLife;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetDestructableMaxLife(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetDestructableMaxLife;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_DestructableRestoreLife(handle P1, realret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _DestructableRestoreLife;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_QueueDestructableAnimation(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _QueueDestructableAnimation;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetDestructableAnimation(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SetDestructableAnimation;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetDestructableAnimationSpeed(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetDestructableAnimationSpeed;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ShowDestructable(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _ShowDestructable;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetDestructableOccluderHeight(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetDestructableOccluderHeight;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_SetDestructableOccluderHeight(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetDestructableOccluderHeight;
	__asm add esp, 8;

	return;
}

stringret CJassInterface::Jass_GetDestructableName(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _GetDestructableName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

handle CJassInterface::Jass_CreateUnit(handle P1, integer P2, realret P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _CreateUnit;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

handle CJassInterface::Jass_CreateUnitByName(handle P1, stringret P2, realret P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _CreateUnitByName;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

handle CJassInterface::Jass_CreateUnitAtLoc(handle P1, integer P2, handle P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CreateUnitAtLoc;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_CreateUnitAtLocByName(handle P1, stringret P2, handle P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P4;
	__asm push eax;
	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _CreateUnitAtLocByName;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_CreateCorpse(handle P1, integer P2, realret P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _CreateCorpse;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

realret CJassInterface::Jass_GetUnitState(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetUnitState;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue.fl;
}

integer CJassInterface::Jass_GetUnitFoodUsed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitFoodUsed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetUnitFoodMade(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitFoodMade;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetFoodMade(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetFoodMade;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetFoodUsed(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetFoodUsed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetUnitUseFood(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetUnitUseFood;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetUnitX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

handle CJassInterface::Jass_GetUnitLoc(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetUnitLoc;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetUnitRallyPoint(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetUnitRallyPoint;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetUnitRallyUnit(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetUnitRallyUnit;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetUnitRallyDestructable(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetUnitRallyDestructable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

realret CJassInterface::Jass_GetUnitFacing(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitFacing;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitMoveSpeed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitMoveSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitDefaultMoveSpeed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitDefaultMoveSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

integer CJassInterface::Jass_GetUnitTypeId(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitTypeId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetUnitRace(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetUnitRace;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_GetUnitName(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _GetUnitName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_GetUnitPointValue(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitPointValue;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetUnitPointValueByType(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitPointValueByType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetUnitX(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitX;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitY(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitY;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitPosition(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitPosition;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetUnitPositionLoc(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetUnitPositionLoc;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitFacing(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitFacing;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitFacingTimed(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitFacingTimed;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetUnitFlyHeight(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitFlyHeight;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetUnitMoveSpeed(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitMoveSpeed;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitTurnSpeed(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitTurnSpeed;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitPropWindow(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitPropWindow;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitCreepGuard(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetUnitCreepGuard;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetUnitAcquireRange(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitAcquireRange;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitTurnSpeed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitTurnSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitPropWindow(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitPropWindow;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitFlyHeight(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitFlyHeight;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitDefaultAcquireRange(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitDefaultAcquireRange;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitDefaultTurnSpeed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitDefaultTurnSpeed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitDefaultPropWindow(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitDefaultPropWindow;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetUnitDefaultFlyHeight(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetUnitDefaultFlyHeight;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_SetUnitAcquireRange(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitAcquireRange;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitState(handle P1, handle P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitState;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetUnitOwner(handle P1, handle P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitOwner;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetUnitRescuable(handle P1, handle P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitRescuable;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetUnitRescueRange(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitRescueRange;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitColor(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetUnitColor;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_QueueUnitAnimation(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _QueueUnitAnimation;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitAnimation(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitAnimation;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitAnimationWithRarity(handle P1, stringret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitAnimationWithRarity;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetUnitAnimationByIndex(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetUnitAnimationByIndex;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_AddUnitAnimationProperties(handle P1, stringret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push bP3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _AddUnitAnimationProperties;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetUnitScale(handle P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitScale;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetUnitTimeScale(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitTimeScale;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitBlendTime(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitBlendTime;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitVertexColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitVertexColor;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_SetUnitLookAt(handle P1, stringret P2, handle P3, realret P4, realret P5, realret P6)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SetUnitLookAt;
	__asm add esp, 24;

	return;
}

nothing CJassInterface::Jass_SetUnitPathing(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetUnitPathing;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ResetUnitLookAt(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _ResetUnitLookAt;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetHeroStr(handle P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroStr;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetHeroAgi(handle P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroAgi;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetHeroInt(handle P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroInt;
	__asm add esp, 12;

	return;
}

integer CJassInterface::Jass_GetHeroStr(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _GetHeroStr;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_GetHeroAgi(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _GetHeroAgi;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_GetHeroInt(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _GetHeroInt;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_GetHeroSkillPoints(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetHeroSkillPoints;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitStripHeroLevel(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitStripHeroLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitModifySkillPoints(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitModifySkillPoints;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_GetHeroXP(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetHeroXP;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetHeroXP(handle P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroXP;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_AddHeroXP(handle P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _AddHeroXP;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetHeroLevel(handle P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetHeroLevel;
	__asm add esp, 12;

	return;
}

integer CJassInterface::Jass_GetHeroLevel(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetHeroLevel;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetUnitLevel(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitLevel;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_GetHeroProperName(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _GetHeroProperName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

nothing CJassInterface::Jass_SuspendHeroXP(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SuspendHeroXP;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsSuspendedXP(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsSuspendedXP;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SelectHeroSkill(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SelectHeroSkill;
	__asm add esp, 8;

	return;
}

integer CJassInterface::Jass_GetUnitAbilityLevel(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetUnitAbilityLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_ReviveHero(handle P1, realret P2, realret P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP4 = P4;

	__asm push bP4;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _ReviveHero;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_ReviveHeroLoc(handle P1, handle P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _ReviveHeroLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_SetUnitExploded(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetUnitExploded;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitInvulnerable(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetUnitInvulnerable;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_PauseUnit(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _PauseUnit;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsUnitPaused(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsUnitPaused;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitAddItem(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddItem;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_UnitAddItemById(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddItemById;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitAddItemToSlotById(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitAddItemToSlotById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_UnitRemoveItem(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveItem;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_UnitRemoveItemFromSlot(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveItemFromSlot;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitHasItem(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitHasItem;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_UnitItemInSlot(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitItemInSlot;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_UnitInventorySize(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _UnitInventorySize;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitDropItemPoint(handle P1, handle P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _UnitDropItemPoint;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitDropItemSlot(handle P1, handle P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitDropItemSlot;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitDropItemTarget(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitDropItemTarget;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitUseItem(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitUseItem;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitUseItemPoint(handle P1, handle P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _UnitUseItemPoint;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitUseItemTarget(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitUseItemTarget;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

integer CJassInterface::Jass_GetUnitCurrentOrder(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitCurrentOrder;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetResourceAmount(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetResourceAmount;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_AddResourceAmount(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _AddResourceAmount;
	__asm add esp, 8;

	return;
}

integer CJassInterface::Jass_GetResourceAmount(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetResourceAmount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SelectUnit(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SelectUnit;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ClearSelection()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ClearSelection;

	return;
}

nothing CJassInterface::Jass_UnitAddIndicator(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitAddIndicator;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_AddIndicator(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddIndicator;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_KillUnit(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _KillUnit;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_RemoveUnit(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveUnit;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ShowUnit(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _ShowUnit;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsUnitInForce(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInForce;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitInGroup(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInGroup;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitOwnedByPlayer(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitOwnedByPlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitAlly(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitAlly;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitEnemy(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitEnemy;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitVisible(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitVisible;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitDetected(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitDetected;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitInvisible(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInvisible;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitFogged(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitFogged;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitMasked(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitMasked;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitSelected(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitSelected;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitRace(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitRace;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitType(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnit(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnit;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitInRange(handle P1, handle P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInRange;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitInRangeXY(handle P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _IsUnitInRangeXY;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitInRangeLoc(handle P1, handle P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInRangeLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitHidden(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsUnitHidden;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitIllusion(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsUnitIllusion;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitInTransport(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitInTransport;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitLoaded(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsUnitLoaded;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsHeroUnitId(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsHeroUnitId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsUnitIdType(integer P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsUnitIdType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_GetOwningPlayer(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetOwningPlayer;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_UnitShareVision(handle P1, handle P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _UnitShareVision;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_UnitSuspendDecay(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _UnitSuspendDecay;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_UnitAddType(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitRemoveType(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitAddAbility(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitAddAbility;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitRemoveAbility(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _UnitRemoveAbility;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitMakeAbilityPermanent(handle P1, jbooleanret P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP2 = P2;

	__asm push P3;
	__asm push bP2;
	__asm push P1;
	__asm call _UnitMakeAbilityPermanent;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitHasBuffsEx(handle P1, jbooleanret P2, jbooleanret P3, jbooleanret P4, jbooleanret P5, jbooleanret P6, jbooleanret P7, jbooleanret P8)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP8 = P8;
	jboolean bP7 = P7;
	jboolean bP6 = P6;
	jboolean bP5 = P5;
	jboolean bP4 = P4;
	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP8;
	__asm push bP7;
	__asm push bP6;
	__asm push bP5;
	__asm push bP4;
	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _UnitHasBuffsEx;
	__asm mov retValue, eax;
	__asm add esp, 32;

	return retValue;
}

integer CJassInterface::Jass_UnitCountBuffsEx(handle P1, jbooleanret P2, jbooleanret P3, jbooleanret P4, jbooleanret P5, jbooleanret P6, jbooleanret P7, jbooleanret P8)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	jboolean bP8 = P8;
	jboolean bP7 = P7;
	jboolean bP6 = P6;
	jboolean bP5 = P5;
	jboolean bP4 = P4;
	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP8;
	__asm push bP7;
	__asm push bP6;
	__asm push bP5;
	__asm push bP4;
	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _UnitCountBuffsEx;
	__asm mov retValue, eax;
	__asm add esp, 32;

	return retValue;
}

nothing CJassInterface::Jass_UnitRemoveBuffs(handle P1, jbooleanret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _UnitRemoveBuffs;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_UnitRemoveBuffsEx(handle P1, jbooleanret P2, jbooleanret P3, jbooleanret P4, jbooleanret P5, jbooleanret P6, jbooleanret P7, jbooleanret P8)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP8 = P8;
	jboolean bP7 = P7;
	jboolean bP6 = P6;
	jboolean bP5 = P5;
	jboolean bP4 = P4;
	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP8;
	__asm push bP7;
	__asm push bP6;
	__asm push bP5;
	__asm push bP4;
	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _UnitRemoveBuffsEx;
	__asm add esp, 32;

	return;
}

nothing CJassInterface::Jass_UnitAddSleep(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _UnitAddSleep;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_UnitCanSleep(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _UnitCanSleep;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_UnitAddSleepPerm(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _UnitAddSleepPerm;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_UnitCanSleepPerm(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _UnitCanSleepPerm;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitIsSleeping(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _UnitIsSleeping;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_UnitWakeUp(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _UnitWakeUp;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_UnitApplyTimedLife(handle P1, integer P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _UnitApplyTimedLife;
	__asm add esp, 12;

	return;
}

jbooleanret CJassInterface::Jass_UnitIgnoreAlarm(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _UnitIgnoreAlarm;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitIgnoreAlarmToggled(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _UnitIgnoreAlarmToggled;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitDamagePoint(handle P1, realret P2, realret P3, realret P4, realret P5, realret P6, jbooleanret P7, jbooleanret P8, handle P9, handle P10, handle P11)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP8 = P8;
	jboolean bP7 = P7;

	__asm push P11;
	__asm push P10;
	__asm push P9;
	__asm push bP8;
	__asm push bP7;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _UnitDamagePoint;
	__asm mov retValue, eax;
	__asm add esp, 44;

	return retValue;
}

jbooleanret CJassInterface::Jass_UnitDamageTarget(handle P1, handle P2, realret P3, jbooleanret P4, jbooleanret P5, handle P6, handle P7, handle P8)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP5 = P5;
	jboolean bP4 = P4;

	__asm push P8;
	__asm push P7;
	__asm push P6;
	__asm push bP5;
	__asm push bP4;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _UnitDamageTarget;
	__asm mov retValue, eax;
	__asm add esp, 32;

	return retValue;
}

integer CJassInterface::Jass_DecUnitAbilityLevel(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _DecUnitAbilityLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_IncUnitAbilityLevel(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IncUnitAbilityLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_SetUnitAbilityLevel(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetUnitAbilityLevel;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_UnitResetCooldown(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _UnitResetCooldown;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_UnitSetConstructionProgress(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _UnitSetConstructionProgress;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_UnitSetUpgradeProgress(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _UnitSetUpgradeProgress;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_UnitPauseTimedLife(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _UnitPauseTimedLife;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_UnitSetUsesAltIcon(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _UnitSetUsesAltIcon;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IssueImmediateOrderById(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IssueImmediateOrderById;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssuePointOrderById(handle P1, integer P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _IssuePointOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssuePointOrderByIdLoc(handle P1, integer P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssuePointOrderByIdLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueTargetOrderById(handle P1, integer P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueTargetOrderById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueInstantPointOrderById(handle P1, integer P2, realret P3, realret P4, handle P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P5;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _IssueInstantPointOrderById;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueInstantTargetOrderById(handle P1, integer P2, handle P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueInstantTargetOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueBuildOrderById(handle P1, integer P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _IssueBuildOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueNeutralImmediateOrderById(handle P1, handle P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralImmediateOrderById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueNeutralPointOrderById(handle P1, handle P2, integer P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralPointOrderById;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueNeutralTargetOrderById(handle P1, handle P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralTargetOrderById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueImmediateOrder(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _IssueImmediateOrder;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssuePointOrder(handle P1, stringret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _IssuePointOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssuePointOrderLoc(handle P1, stringret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _IssuePointOrderLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueTargetOrder(handle P1, stringret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _IssueTargetOrder;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueInstantPointOrder(handle P1, stringret P2, realret P3, realret P4, handle P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P5;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _IssueInstantPointOrder;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueInstantTargetOrder(handle P1, stringret P2, handle P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P4;
	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _IssueInstantTargetOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueBuildOrder(handle P1, stringret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _IssueBuildOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueNeutralImmediateOrder(handle P1, handle P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);

	__asm lea eax, sP3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralImmediateOrder;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueNeutralPointOrder(handle P1, handle P2, stringret P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);

	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, sP3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralPointOrder;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

jbooleanret CJassInterface::Jass_IssueNeutralTargetOrder(handle P1, handle P2, stringret P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);

	__asm push P4;
	__asm lea eax, sP3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _IssueNeutralTargetOrder;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

realret CJassInterface::Jass_WaygateGetDestinationX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _WaygateGetDestinationX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_WaygateGetDestinationY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _WaygateGetDestinationY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_WaygateSetDestination(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _WaygateSetDestination;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_WaygateActivate(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _WaygateActivate;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_WaygateIsActive(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _WaygateIsActive;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_AddItemToAllStock(integer P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddItemToAllStock;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_AddItemToStock(handle P1, integer P2, integer P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddItemToStock;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_AddUnitToAllStock(integer P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddUnitToAllStock;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_AddUnitToStock(handle P1, integer P2, integer P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddUnitToStock;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_RemoveItemFromAllStock(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveItemFromAllStock;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_RemoveItemFromStock(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _RemoveItemFromStock;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_RemoveUnitFromAllStock(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveUnitFromAllStock;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_RemoveUnitFromStock(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _RemoveUnitFromStock;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetAllItemTypeSlots(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetAllItemTypeSlots;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetAllUnitTypeSlots(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetAllUnitTypeSlots;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetItemTypeSlots(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetItemTypeSlots;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUnitTypeSlots(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetUnitTypeSlots;
	__asm add esp, 8;

	return;
}

integer CJassInterface::Jass_GetUnitUserData(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetUnitUserData;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetUnitUserData(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetUnitUserData;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_CreateItem(integer P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _CreateItem;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_RemoveItem(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveItem;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_GetItemPlayer(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetItemPlayer;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetItemTypeId(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetItemTypeId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

realret CJassInterface::Jass_GetItemX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetItemX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetItemY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetItemY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_SetItemPosition(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetItemPosition;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetItemDropOnDeath(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetItemDropOnDeath;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetItemDroppable(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetItemDroppable;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetItemPawnable(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetItemPawnable;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetItemPlayer(handle P1, handle P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetItemPlayer;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetItemInvulnerable(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetItemInvulnerable;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsItemInvulnerable(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsItemInvulnerable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetItemLevel(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetItemLevel;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetItemType(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetItemType;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetItemVisible(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetItemVisible;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsItemVisible(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsItemVisible;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_EnumItemsInRect(handle P1, handle P2, code P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _EnumItemsInRect;
	__asm add esp, 12;

	return;
}

jbooleanret CJassInterface::Jass_IsItemOwned(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsItemOwned;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsItemPowerup(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsItemPowerup;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsItemSellable(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsItemSellable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsItemPawnable(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsItemPawnable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsItemIdPowerup(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsItemIdPowerup;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsItemIdSellable(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsItemIdSellable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsItemIdPawnable(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsItemIdPawnable;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetItemDropID(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetItemDropID;
	__asm add esp, 8;

	return;
}

stringret CJassInterface::Jass_GetItemName(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _GetItemName;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_GetItemCharges(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetItemCharges;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetItemCharges(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetItemCharges;
	__asm add esp, 8;

	return;
}

integer CJassInterface::Jass_GetItemUserData(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetItemUserData;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetItemUserData(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetItemUserData;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_Player(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _Player;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetLocalPlayer()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetLocalPlayer;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsPlayerAlly(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsPlayerAlly;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsPlayerEnemy(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsPlayerEnemy;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsPlayerInForce(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsPlayerInForce;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsPlayerObserver(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsPlayerObserver;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_GetPlayerRace(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetPlayerRace;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetPlayerId(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetPlayerId;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerTechMaxAllowed(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerTechMaxAllowed;
	__asm add esp, 12;

	return;
}

integer CJassInterface::Jass_GetPlayerTechMaxAllowed(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerTechMaxAllowed;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_AddPlayerTechResearched(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddPlayerTechResearched;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetPlayerTechResearched(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerTechResearched;
	__asm add esp, 12;

	return;
}

jbooleanret CJassInterface::Jass_GetPlayerTechResearched(handle P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerTechResearched;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

integer CJassInterface::Jass_GetPlayerTechCount(handle P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerTechCount;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerAbilityAvailable(handle P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerAbilityAvailable;
	__asm add esp, 12;

	return;
}

integer CJassInterface::Jass_GetPlayerUnitCount(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _GetPlayerUnitCount;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_GetPlayerTypedUnitCount(handle P1, stringret P2, jbooleanret P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	jboolean bP4 = P4;
	jboolean bP3 = P3;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push bP4;
	__asm push bP3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GetPlayerTypedUnitCount;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

integer CJassInterface::Jass_GetPlayerStructureCount(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _GetPlayerStructureCount;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsVisibleToPlayer(realret P1, realret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _IsVisibleToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsLocationVisibleToPlayer(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsLocationVisibleToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsFoggedToPlayer(realret P1, realret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _IsFoggedToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsLocationFoggedToPlayer(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsLocationFoggedToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsMaskedToPlayer(realret P1, realret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _IsMaskedToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsLocationMaskedToPlayer(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _IsLocationMaskedToPlayer;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_SetPlayerState(handle P1, handle P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerState;
	__asm add esp, 12;

	return;
}

integer CJassInterface::Jass_GetPlayerState(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerState;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_GetPlayerScore(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerScore;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_GetPlayerAlliance(handle P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetPlayerAlliance;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_RemovePlayer(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _RemovePlayer;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_CachePlayerHeroData(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _CachePlayerHeroData;
	__asm add esp, 4;

	return;
}

realret CJassInterface::Jass_GetPlayerHandicap(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetPlayerHandicap;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_SetPlayerHandicap(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetPlayerHandicap;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetPlayerHandicapXP(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetPlayerHandicapXP;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_SetPlayerHandicapXP(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetPlayerHandicapXP;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetPlayerUnitsOwner(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetPlayerUnitsOwner;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_CripplePlayer(handle P1, handle P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _CripplePlayer;
	__asm add esp, 12;

	return;
}

handle CJassInterface::Jass_VersionGet()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _VersionGet;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_VersionCompatible(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _VersionCompatible;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_VersionSupported(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _VersionSupported;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_EndGame(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _EndGame;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ChangeLevel(stringret P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push bP2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _ChangeLevel;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_RestartGame(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _RestartGame;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ReloadGame()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ReloadGame;

	return;
}

nothing CJassInterface::Jass_LoadGame(stringret P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push bP2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _LoadGame;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SaveGame(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SaveGame;
	__asm add esp, 4;

	return;
}

jbooleanret CJassInterface::Jass_RenameSaveDirectory(stringret P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP2;
	__asm push eax;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _RenameSaveDirectory;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_RemoveSaveDirectory(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _RemoveSaveDirectory;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_CopySaveGame(stringret P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP2;
	__asm push eax;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _CopySaveGame;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveGameExists(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SaveGameExists;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SetFloatGameState(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetFloatGameState;
	__asm add esp, 8;

	return;
}

realret CJassInterface::Jass_GetFloatGameState(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetFloatGameState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_SetIntegerGameState(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetIntegerGameState;
	__asm add esp, 8;

	return;
}

integer CJassInterface::Jass_GetIntegerGameState(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetIntegerGameState;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_SyncSelections()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _SyncSelections;

	return;
}

handle CJassInterface::Jass_DialogCreate()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _DialogCreate;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DialogDestroy(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DialogDestroy;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DialogSetAsync(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DialogSetAsync;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DialogClear(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DialogClear;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DialogSetMessage(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _DialogSetMessage;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_DialogAddButton(handle P1, stringret P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _DialogAddButton;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_DialogAddQuitButton(handle P1, jbooleanret P2, stringret P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	jboolean bP2 = P2;

	__asm push P4;
	__asm lea eax, sP3;
	__asm push eax;
	__asm push bP2;
	__asm push P1;
	__asm call _DialogAddQuitButton;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

nothing CJassInterface::Jass_DialogDisplay(handle P1, handle P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _DialogDisplay;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetMissionAvailable(integer P1, integer P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetMissionAvailable;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetCampaignAvailable(integer P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetCampaignAvailable;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetCampaignMenuRace(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetCampaignMenuRace;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetCampaignMenuRaceEx(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetCampaignMenuRaceEx;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ForceCampaignSelectScreen()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ForceCampaignSelectScreen;

	return;
}

nothing CJassInterface::Jass_SetOpCinematicAvailable(integer P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetOpCinematicAvailable;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetEdCinematicAvailable(integer P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetEdCinematicAvailable;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetTutorialCleared(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetTutorialCleared;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_GetDefaultDifficulty()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetDefaultDifficulty;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_SetDefaultDifficulty(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetDefaultDifficulty;
	__asm add esp, 4;

	return;
}

jbooleanret CJassInterface::Jass_ReloadGameCachesFromDisk()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _ReloadGameCachesFromDisk;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_SetCustomCampaignButtonVisible(integer P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetCustomCampaignButtonVisible;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_GetCustomCampaignButtonVisible(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _GetCustomCampaignButtonVisible;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_DoNotSaveReplay()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _DoNotSaveReplay;

	return;
}

handle CJassInterface::Jass_InitGameCache(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _InitGameCache;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveGameCache(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _SaveGameCache;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_StoreInteger(handle P1, stringret P2, stringret P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P4;
	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _StoreInteger;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_StoreReal(handle P1, stringret P2, stringret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _StoreReal;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_StoreBoolean(handle P1, stringret P2, stringret P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP4 = P4;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push bP4;
	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _StoreBoolean;
	__asm add esp, 16;

	return;
}

jbooleanret CJassInterface::Jass_StoreUnit(handle P1, stringret P2, stringret P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P4;
	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _StoreUnit;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_StoreString(handle P1, stringret P2, stringret P3, stringret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP4;
	This->cStr2jStr(P4, &sP4);
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP4;
	__asm push eax;
	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _StoreString;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

nothing CJassInterface::Jass_SaveInteger(handle P1, integer P2, integer P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveInteger;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SaveReal(handle P1, integer P2, integer P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveReal;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SaveBoolean(handle P1, integer P2, integer P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP4 = P4;

	__asm push bP4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveBoolean;
	__asm add esp, 16;

	return;
}

jbooleanret CJassInterface::Jass_SaveStr(handle P1, integer P2, integer P3, stringret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP4;
	This->cStr2jStr(P4, &sP4);

	__asm lea eax, sP4;
	__asm push eax;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveStr;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SavePlayerHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SavePlayerHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveWidgetHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveWidgetHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveDestructableHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveDestructableHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveItemHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveUnitHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveUnitHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveAbilityHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveAbilityHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveTimerHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTimerHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveRegionHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveRegionHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveTriggerHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTriggerHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveTriggerConditionHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTriggerConditionHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveTriggerActionHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTriggerActionHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveTriggerEventHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTriggerEventHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveForceHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveForceHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveGroupHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveGroupHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveLocationHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveLocationHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveRectHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveRectHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveBooleanExprHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveBooleanExprHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveSoundHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveSoundHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveEffectHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveEffectHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveUnitPoolHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveUnitPoolHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveItemPoolHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveItemPoolHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveQuestHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveQuestHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveQuestItemHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveQuestItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveDefeatConditionHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveDefeatConditionHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveTimerDialogHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTimerDialogHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveLeaderboardHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveLeaderboardHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveMultiboardHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveMultiboardHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveMultiboardItemHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveMultiboardItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveTrackableHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTrackableHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveDialogHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveDialogHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveButtonHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveButtonHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveTextTagHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveTextTagHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveLightningHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveLightningHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveImageHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveImageHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveUbersplatHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveUbersplatHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveFogStateHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveFogStateHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveFogModifierHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveFogModifierHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveAgentHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveAgentHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_SaveHashtableHandle(handle P1, integer P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SaveHashtableHandle;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

nothing CJassInterface::Jass_SyncStoredInteger(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SyncStoredInteger;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SyncStoredReal(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SyncStoredReal;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SyncStoredBoolean(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SyncStoredBoolean;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SyncStoredUnit(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SyncStoredUnit;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SyncStoredString(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SyncStoredString;
	__asm add esp, 12;

	return;
}

integer CJassInterface::Jass_GetStoredInteger(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GetStoredInteger;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

realret CJassInterface::Jass_GetStoredReal(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GetStoredReal;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue.fl;
}

jbooleanret CJassInterface::Jass_GetStoredBoolean(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GetStoredBoolean;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_RestoreUnit(handle P1, stringret P2, stringret P3, handle P4, realret P5, realret P6, realret P7)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P7;
	__asm push eax;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm push P4;
	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _RestoreUnit;
	__asm mov retValue, eax;
	__asm add esp, 28;

	return retValue;
}

stringret CJassInterface::Jass_GetStoredString(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _GetStoredString;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return jStr2cStr(retValue);
}

jbooleanret CJassInterface::Jass_HaveStoredInteger(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _HaveStoredInteger;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_HaveStoredReal(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _HaveStoredReal;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_HaveStoredBoolean(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _HaveStoredBoolean;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_HaveStoredUnit(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _HaveStoredUnit;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_HaveStoredString(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _HaveStoredString;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_FlushGameCache(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _FlushGameCache;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_FlushStoredMission(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _FlushStoredMission;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_FlushStoredInteger(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _FlushStoredInteger;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_FlushStoredReal(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _FlushStoredReal;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_FlushStoredBoolean(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _FlushStoredBoolean;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_FlushStoredUnit(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _FlushStoredUnit;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_FlushStoredString(handle P1, stringret P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _FlushStoredString;
	__asm add esp, 12;

	return;
}

handle CJassInterface::Jass_InitHashtable()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _InitHashtable;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_LoadInteger(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadInteger;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

realret CJassInterface::Jass_LoadReal(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadReal;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue.fl;
}

jbooleanret CJassInterface::Jass_LoadBoolean(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadBoolean;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

stringret CJassInterface::Jass_LoadStr(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadStr;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return jStr2cStr(retValue);
}

handle CJassInterface::Jass_LoadPlayerHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadPlayerHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadWidgetHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadWidgetHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadDestructableHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadDestructableHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadItemHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadUnitHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadUnitHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadAbilityHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadAbilityHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadTimerHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTimerHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadRegionHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadRegionHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadTriggerHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTriggerHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadTriggerConditionHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTriggerConditionHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadTriggerActionHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTriggerActionHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadTriggerEventHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTriggerEventHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadForceHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadForceHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadGroupHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadGroupHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadLocationHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadLocationHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadRectHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadRectHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadBooleanExprHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadBooleanExprHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadSoundHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadSoundHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadEffectHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadEffectHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadUnitPoolHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadUnitPoolHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadItemPoolHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadItemPoolHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadQuestHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadQuestHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadQuestItemHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadQuestItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadDefeatConditionHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadDefeatConditionHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadTimerDialogHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTimerDialogHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadLeaderboardHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadLeaderboardHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadMultiboardHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadMultiboardHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadMultiboardItemHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadMultiboardItemHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadTrackableHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTrackableHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadDialogHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadDialogHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadButtonHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadButtonHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadTextTagHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadTextTagHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadLightningHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadLightningHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadImageHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadImageHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadUbersplatHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadUbersplatHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadFogStateHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadFogStateHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadFogModifierHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadFogModifierHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_LoadHashtableHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LoadHashtableHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_HaveSavedInteger(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedInteger;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_HaveSavedReal(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedReal;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_HaveSavedBoolean(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedBoolean;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_HaveSavedString(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedString;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

jbooleanret CJassInterface::Jass_HaveSavedHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _HaveSavedHandle;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_RemoveSavedInteger(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedInteger;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_RemoveSavedReal(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedReal;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_RemoveSavedBoolean(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedBoolean;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_RemoveSavedString(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedString;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_RemoveSavedHandle(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _RemoveSavedHandle;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_FlushParentHashtable(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _FlushParentHashtable;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_FlushChildHashtable(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _FlushChildHashtable;
	__asm add esp, 8;

	return;
}

integer CJassInterface::Jass_GetRandomInt(integer P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetRandomInt;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

realret CJassInterface::Jass_GetRandomReal(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _GetRandomReal;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue.fl;
}

handle CJassInterface::Jass_CreateUnitPool()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateUnitPool;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyUnitPool(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyUnitPool;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_UnitPoolAddUnitType(handle P1, integer P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _UnitPoolAddUnitType;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_UnitPoolRemoveUnitType(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _UnitPoolRemoveUnitType;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_PlaceRandomUnit(handle P1, handle P2, realret P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _PlaceRandomUnit;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

handle CJassInterface::Jass_CreateItemPool()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateItemPool;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyItemPool(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyItemPool;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ItemPoolAddItemType(handle P1, integer P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _ItemPoolAddItemType;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_ItemPoolRemoveItemType(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _ItemPoolRemoveItemType;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_PlaceRandomItem(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _PlaceRandomItem;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

integer CJassInterface::Jass_ChooseRandomCreep(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _ChooseRandomCreep;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_ChooseRandomNPBuilding()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _ChooseRandomNPBuilding;
	__asm mov retValue, eax;

	return retValue;
}

integer CJassInterface::Jass_ChooseRandomItem(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _ChooseRandomItem;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_ChooseRandomItemEx(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _ChooseRandomItemEx;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_SetRandomSeed(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetRandomSeed;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DisplayTextToPlayer(handle P1, realret P2, realret P3, stringret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP4;
	This->cStr2jStr(P4, &sP4);

	__asm lea eax, sP4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _DisplayTextToPlayer;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_DisplayTimedTextToPlayer(handle P1, realret P2, realret P3, realret P4, stringret P5)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP5;
	This->cStr2jStr(P5, &sP5);

	__asm lea eax, sP5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _DisplayTimedTextToPlayer;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_DisplayTimedTextFromPlayer(handle P1, realret P2, realret P3, realret P4, stringret P5)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP5;
	This->cStr2jStr(P5, &sP5);

	__asm lea eax, sP5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _DisplayTimedTextFromPlayer;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_ClearTextMessages()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ClearTextMessages;

	return;
}

nothing CJassInterface::Jass_EnableUserControl(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _EnableUserControl;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_EnableUserUI(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _EnableUserUI;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DisableRestartMission(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _DisableRestartMission;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ForceUIKey(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _ForceUIKey;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ForceUICancel()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ForceUICancel;

	return;
}

nothing CJassInterface::Jass_DisplayLoadDialog()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _DisplayLoadDialog;

	return;
}

nothing CJassInterface::Jass_SetTerrainFog(realret P1, realret P2, realret P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetTerrainFog;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_SetUnitFog(realret P1, realret P2, realret P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetUnitFog;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_SetTerrainFogEx(integer P1, realret P2, realret P3, realret P4, realret P5, realret P6, realret P7)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P7;
	__asm push eax;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetTerrainFogEx;
	__asm add esp, 28;

	return;
}

nothing CJassInterface::Jass_ResetTerrainFog()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ResetTerrainFog;

	return;
}

nothing CJassInterface::Jass_SetDayNightModels(stringret P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP2;
	__asm push eax;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetDayNightModels;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetSkyModel(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetSkyModel;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SuspendTimeOfDay(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SuspendTimeOfDay;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetTimeOfDayScale(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetTimeOfDayScale;
	__asm add esp, 4;

	return;
}

realret CJassInterface::Jass_GetTimeOfDayScale()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetTimeOfDayScale;
	__asm mov retValue, eax;

	return retValue.fl;
}

nothing CJassInterface::Jass_ShowInterface(jbooleanret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm lea eax, P2;
	__asm push eax;
	__asm push bP1;
	__asm call _ShowInterface;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_PauseGame(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _PauseGame;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_PingMinimap(realret P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _PingMinimap;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_PingMinimapEx(realret P1, realret P2, realret P3, integer P4, integer P5, integer P6, jbooleanret P7)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP7 = P7;

	__asm push bP7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _PingMinimapEx;
	__asm add esp, 28;

	return;
}

nothing CJassInterface::Jass_SetIntroShotText(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetIntroShotText;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetIntroShotModel(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetIntroShotModel;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_EnableOcclusion(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _EnableOcclusion;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_EnableWorldFogBoundary(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _EnableWorldFogBoundary;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_PlayModelCinematic(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _PlayModelCinematic;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_PlayCinematic(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _PlayCinematic;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetAltMinimapIcon(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetAltMinimapIcon;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_CreateTextTag()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateTextTag;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyTextTag(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyTextTag;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetTextTagText(handle P1, stringret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SetTextTagText;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetTextTagPos(handle P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetTextTagPos;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetTextTagPosUnit(handle P1, handle P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagPosUnit;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetTextTagColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetTextTagColor;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_SetTextTagVelocity(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetTextTagVelocity;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetTextTagVisibility(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetTextTagVisibility;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetTextTagSuspended(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetTextTagSuspended;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetTextTagPermanent(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetTextTagPermanent;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetTextTagAge(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetTextTagAge;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetTextTagLifespan(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetTextTagLifespan;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetTextTagFadepoint(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetTextTagFadepoint;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetReservedLocalHeroButtons(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetReservedLocalHeroButtons;
	__asm add esp, 4;

	return;
}

integer CJassInterface::Jass_GetAllyColorFilterState()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm call _GetAllyColorFilterState;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_SetAllyColorFilterState(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetAllyColorFilterState;
	__asm add esp, 4;

	return;
}

jbooleanret CJassInterface::Jass_GetCreepCampFilterState()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _GetCreepCampFilterState;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_SetCreepCampFilterState(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetCreepCampFilterState;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_EnableMinimapFilterButtons(jbooleanret P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;
	jboolean bP1 = P1;

	__asm push bP2;
	__asm push bP1;
	__asm call _EnableMinimapFilterButtons;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_EnableDragSelect(jbooleanret P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;
	jboolean bP1 = P1;

	__asm push bP2;
	__asm push bP1;
	__asm call _EnableDragSelect;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_EnablePreSelect(jbooleanret P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;
	jboolean bP1 = P1;

	__asm push bP2;
	__asm push bP1;
	__asm call _EnablePreSelect;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_EnableSelect(jbooleanret P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;
	jboolean bP1 = P1;

	__asm push bP2;
	__asm push bP1;
	__asm call _EnableSelect;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_CreateTrackable(stringret P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _CreateTrackable;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterTrackableHitEvent(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterTrackableHitEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_TriggerRegisterTrackableTrackEvent(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _TriggerRegisterTrackableTrackEvent;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_GetTriggeringTrackable()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetTriggeringTrackable;
	__asm mov retValue, eax;

	return retValue;
}

handle CJassInterface::Jass_CreateQuest()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateQuest;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyQuest(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyQuest;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_QuestSetTitle(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _QuestSetTitle;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_QuestSetDescription(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _QuestSetDescription;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_QuestSetIconPath(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _QuestSetIconPath;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_QuestSetRequired(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _QuestSetRequired;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_QuestSetCompleted(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _QuestSetCompleted;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_QuestSetDiscovered(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _QuestSetDiscovered;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_QuestSetFailed(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _QuestSetFailed;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_QuestSetEnabled(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _QuestSetEnabled;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsQuestRequired(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsQuestRequired;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsQuestCompleted(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsQuestCompleted;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsQuestDiscovered(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsQuestDiscovered;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsQuestFailed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsQuestFailed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsQuestEnabled(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsQuestEnabled;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_QuestCreateItem(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _QuestCreateItem;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_QuestItemSetDescription(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _QuestItemSetDescription;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_QuestItemSetCompleted(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _QuestItemSetCompleted;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsQuestItemCompleted(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsQuestItemCompleted;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

handle CJassInterface::Jass_CreateDefeatCondition()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateDefeatCondition;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyDefeatCondition(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyDefeatCondition;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DefeatConditionSetDescription(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _DefeatConditionSetDescription;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_FlashQuestDialogButton()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _FlashQuestDialogButton;

	return;
}

nothing CJassInterface::Jass_ForceQuestDialogUpdate()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ForceQuestDialogUpdate;

	return;
}

handle CJassInterface::Jass_CreateTimerDialog(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _CreateTimerDialog;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_DestroyTimerDialog(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyTimerDialog;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_TimerDialogSetTitle(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _TimerDialogSetTitle;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_TimerDialogSetTitleColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TimerDialogSetTitleColor;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_TimerDialogSetTimeColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _TimerDialogSetTimeColor;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_TimerDialogSetSpeed(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _TimerDialogSetSpeed;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_TimerDialogDisplay(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _TimerDialogDisplay;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsTimerDialogDisplayed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsTimerDialogDisplayed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_TimerDialogSetRealTimeRemaining(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _TimerDialogSetRealTimeRemaining;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_CreateLeaderboard()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateLeaderboard;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyLeaderboard(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyLeaderboard;
	__asm add esp, 4;

	return;
}

integer CJassInterface::Jass_LeaderboardGetItemCount(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _LeaderboardGetItemCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_LeaderboardSetSizeByItemCount(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetSizeByItemCount;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_LeaderboardAddItem(handle P1, stringret P2, integer P3, handle P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm push P4;
	__asm push P3;
	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _LeaderboardAddItem;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_LeaderboardRemoveItem(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardRemoveItem;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_LeaderboardRemovePlayerItem(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardRemovePlayerItem;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_LeaderboardSortItemsByValue(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _LeaderboardSortItemsByValue;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_LeaderboardSortItemsByPlayer(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _LeaderboardSortItemsByPlayer;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_LeaderboardSortItemsByLabel(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _LeaderboardSortItemsByLabel;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_LeaderboardClear(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _LeaderboardClear;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_LeaderboardDisplay(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _LeaderboardDisplay;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsLeaderboardDisplayed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsLeaderboardDisplayed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

stringret CJassInterface::Jass_LeaderboardGetLabelText(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _LeaderboardGetLabelText;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

nothing CJassInterface::Jass_PlayerSetLeaderboard(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _PlayerSetLeaderboard;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_PlayerGetLeaderboard(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _PlayerGetLeaderboard;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_LeaderboardHasPlayerItem(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardHasPlayerItem;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_LeaderboardGetPlayerIndex(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardGetPlayerIndex;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_LeaderboardSetLabel(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _LeaderboardSetLabel;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_LeaderboardSetLabelColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetLabelColor;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_LeaderboardSetValueColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetValueColor;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_LeaderboardSetStyle(handle P1, jbooleanret P2, jbooleanret P3, jbooleanret P4, jbooleanret P5)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP5 = P5;
	jboolean bP4 = P4;
	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP5;
	__asm push bP4;
	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _LeaderboardSetStyle;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemValue(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemValue;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemLabel(handle P1, integer P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP3;
	This->cStr2jStr(P3, &sP3);

	__asm lea eax, sP3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemLabel;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemStyle(handle P1, integer P2, jbooleanret P3, jbooleanret P4, jbooleanret P5)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP5 = P5;
	jboolean bP4 = P4;
	jboolean bP3 = P3;

	__asm push bP5;
	__asm push bP4;
	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemStyle;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemLabelColor(handle P1, integer P2, integer P3, integer P4, integer P5, integer P6)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemLabelColor;
	__asm add esp, 24;

	return;
}

nothing CJassInterface::Jass_LeaderboardSetItemValueColor(handle P1, integer P2, integer P3, integer P4, integer P5, integer P6)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _LeaderboardSetItemValueColor;
	__asm add esp, 24;

	return;
}

handle CJassInterface::Jass_CreateMultiboard()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateMultiboard;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_DestroyMultiboard(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyMultiboard;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_MultiboardDisplay(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _MultiboardDisplay;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_MultiboardMinimize(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _MultiboardMinimize;
	__asm add esp, 8;

	return;
}

jbooleanret CJassInterface::Jass_IsMultiboardDisplayed(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsMultiboardDisplayed;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsMultiboardMinimized(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _IsMultiboardMinimized;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_MultiboardClear(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _MultiboardClear;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_MultiboardSetTitleText(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _MultiboardSetTitleText;
	__asm add esp, 8;

	return;
}

stringret CJassInterface::Jass_MultiboardGetTitleText(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P1;
	__asm call _MultiboardGetTitleText;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return jStr2cStr(retValue);
}

nothing CJassInterface::Jass_MultiboardSetTitleTextColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetTitleTextColor;
	__asm add esp, 20;

	return;
}

integer CJassInterface::Jass_MultiboardGetRowCount(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _MultiboardGetRowCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_MultiboardGetColumnCount(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _MultiboardGetColumnCount;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_MultiboardSetColumnCount(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetColumnCount;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_MultiboardSetRowCount(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetRowCount;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsStyle(handle P1, jbooleanret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _MultiboardSetItemsStyle;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsValueColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemsValueColor;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsValue(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _MultiboardSetItemsValue;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsWidth(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _MultiboardSetItemsWidth;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemsIcon(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _MultiboardSetItemsIcon;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_MultiboardGetItem(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardGetItem;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_MultiboardReleaseItem(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _MultiboardReleaseItem;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemStyle(handle P1, jbooleanret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _MultiboardSetItemStyle;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemValue(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _MultiboardSetItemValue;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemValueColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _MultiboardSetItemValueColor;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemWidth(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _MultiboardSetItemWidth;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_MultiboardSetItemIcon(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _MultiboardSetItemIcon;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_MultiboardSuppressDisplay(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _MultiboardSuppressDisplay;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetCameraBounds(realret P1, realret P2, realret P3, realret P4, realret P5, realret P6, realret P7, realret P8)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P8;
	__asm push eax;
	__asm lea eax, P7;
	__asm push eax;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetCameraBounds;
	__asm add esp, 32;

	return;
}

nothing CJassInterface::Jass_SetCameraPosition(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetCameraPosition;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetCameraQuickPosition(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetCameraQuickPosition;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ResetToGameCamera(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P1;
	__asm push eax;
	__asm call _ResetToGameCamera;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_StopCamera()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _StopCamera;

	return;
}

nothing CJassInterface::Jass_PanCameraTo(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _PanCameraTo;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_PanCameraToTimed(realret P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _PanCameraToTimed;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_PanCameraToWithZ(realret P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _PanCameraToWithZ;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_PanCameraToTimedWithZ(realret P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _PanCameraToTimedWithZ;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetCinematicCamera(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetCinematicCamera;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetCameraField(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetCameraField;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_AdjustCameraField(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _AdjustCameraField;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetCameraTargetController(handle P1, realret P2, realret P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP4 = P4;

	__asm push bP4;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetCameraTargetController;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetCameraOrientController(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetCameraOrientController;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetCameraRotateMode(realret P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetCameraRotateMode;
	__asm add esp, 16;

	return;
}

handle CJassInterface::Jass_CreateCameraSetup()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _CreateCameraSetup;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_CameraSetupSetField(handle P1, handle P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _CameraSetupSetField;
	__asm add esp, 16;

	return;
}

realret CJassInterface::Jass_CameraSetupGetField(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P2;
	__asm push P1;
	__asm call _CameraSetupGetField;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue.fl;
}

nothing CJassInterface::Jass_CameraSetupSetDestPosition(handle P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _CameraSetupSetDestPosition;
	__asm add esp, 16;

	return;
}

handle CJassInterface::Jass_CameraSetupGetDestPositionLoc(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _CameraSetupGetDestPositionLoc;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

realret CJassInterface::Jass_CameraSetupGetDestPositionX(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _CameraSetupGetDestPositionX;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_CameraSetupGetDestPositionY(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _CameraSetupGetDestPositionY;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

nothing CJassInterface::Jass_CameraSetupApply(handle P1, jbooleanret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _CameraSetupApply;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_CameraSetupApplyWithZ(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _CameraSetupApplyWithZ;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_CameraSetupApplyForceDuration(handle P1, jbooleanret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm lea eax, P3;
	__asm push eax;
	__asm push bP2;
	__asm push P1;
	__asm call _CameraSetupApplyForceDuration;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_CameraSetupApplyForceDurationWithZ(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _CameraSetupApplyForceDurationWithZ;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_CameraSetTargetNoise(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _CameraSetTargetNoise;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_CameraSetSourceNoise(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _CameraSetSourceNoise;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_CameraSetTargetNoiseEx(realret P1, realret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _CameraSetTargetNoiseEx;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_CameraSetSourceNoiseEx(realret P1, realret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _CameraSetSourceNoiseEx;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_CameraSetSmoothingFactor(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P1;
	__asm push eax;
	__asm call _CameraSetSmoothingFactor;
	__asm add esp, 4;

	return;
}

realret CJassInterface::Jass_GetCameraMargin(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetCameraMargin;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraBoundMinX()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraBoundMinX;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraBoundMinY()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraBoundMinY;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraBoundMaxX()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraBoundMaxX;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraBoundMaxY()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraBoundMaxY;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraField(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetCameraField;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraTargetPositionX()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraTargetPositionX;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraTargetPositionY()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraTargetPositionY;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraTargetPositionZ()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraTargetPositionZ;
	__asm mov retValue, eax;

	return retValue.fl;
}

handle CJassInterface::Jass_GetCameraTargetPositionLoc()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetCameraTargetPositionLoc;
	__asm mov retValue, eax;

	return retValue;
}

realret CJassInterface::Jass_GetCameraEyePositionX()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraEyePositionX;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraEyePositionY()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraEyePositionY;
	__asm mov retValue, eax;

	return retValue.fl;
}

realret CJassInterface::Jass_GetCameraEyePositionZ()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm call _GetCameraEyePositionZ;
	__asm mov retValue, eax;

	return retValue.fl;
}

handle CJassInterface::Jass_GetCameraEyePositionLoc()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm call _GetCameraEyePositionLoc;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_SetCineFilterTexture(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetCineFilterTexture;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetCineFilterBlendMode(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetCineFilterBlendMode;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetCineFilterTexMapFlags(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetCineFilterTexMapFlags;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetCineFilterStartUV(realret P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetCineFilterStartUV;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetCineFilterEndUV(realret P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetCineFilterEndUV;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetCineFilterStartColor(integer P1, integer P2, integer P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCineFilterStartColor;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetCineFilterEndColor(integer P1, integer P2, integer P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetCineFilterEndColor;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetCineFilterDuration(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetCineFilterDuration;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_DisplayCineFilter(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _DisplayCineFilter;
	__asm add esp, 4;

	return;
}

jbooleanret CJassInterface::Jass_IsCineFilterDisplayed()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _IsCineFilterDisplayed;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_SetCinematicScene(integer P1, handle P2, stringret P3, stringret P4, realret P5, realret P6)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP4;
	This->cStr2jStr(P4, &sP4);
	JassString sP3;
	This->cStr2jStr(P3, &sP3);

	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, sP4;
	__asm push eax;
	__asm lea eax, sP3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _SetCinematicScene;
	__asm add esp, 24;

	return;
}

nothing CJassInterface::Jass_EndCinematicScene()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _EndCinematicScene;

	return;
}

nothing CJassInterface::Jass_ForceCinematicSubtitles(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _ForceCinematicSubtitles;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_NewSoundEnvironment(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _NewSoundEnvironment;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_CreateSound(stringret P1, jbooleanret P2, jbooleanret P3, jbooleanret P4, integer P5, integer P6, stringret P7)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP7;
	This->cStr2jStr(P7, &sP7);
	jboolean bP4 = P4;
	jboolean bP3 = P3;
	jboolean bP2 = P2;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP7;
	__asm push eax;
	__asm push P6;
	__asm push P5;
	__asm push bP4;
	__asm push bP3;
	__asm push bP2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _CreateSound;
	__asm mov retValue, eax;
	__asm add esp, 28;

	return retValue;
}

handle CJassInterface::Jass_CreateSoundFilenameWithLabel(stringret P1, jbooleanret P2, jbooleanret P3, jbooleanret P4, integer P5, integer P6, stringret P7)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP7;
	This->cStr2jStr(P7, &sP7);
	jboolean bP4 = P4;
	jboolean bP3 = P3;
	jboolean bP2 = P2;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP7;
	__asm push eax;
	__asm push P6;
	__asm push P5;
	__asm push bP4;
	__asm push bP3;
	__asm push bP2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _CreateSoundFilenameWithLabel;
	__asm mov retValue, eax;
	__asm add esp, 28;

	return retValue;
}

handle CJassInterface::Jass_CreateSoundFromLabel(stringret P1, jbooleanret P2, jbooleanret P3, jbooleanret P4, integer P5, integer P6)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP4 = P4;
	jboolean bP3 = P3;
	jboolean bP2 = P2;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P6;
	__asm push P5;
	__asm push bP4;
	__asm push bP3;
	__asm push bP2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _CreateSoundFromLabel;
	__asm mov retValue, eax;
	__asm add esp, 24;

	return retValue;
}

handle CJassInterface::Jass_CreateMIDISound(stringret P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P3;
	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _CreateMIDISound;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_SetStackedSound(stringret P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetStackedSound;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_ClearStackedSound(stringret P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _ClearStackedSound;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetStackedSoundRect(stringret P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetStackedSoundRect;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_ClearStackedSoundRect(stringret P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _ClearStackedSoundRect;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetSoundParamsFromLabel(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _SetSoundParamsFromLabel;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetSoundChannel(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetSoundChannel;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetSoundVolume(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetSoundVolume;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetSoundPitch(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetSoundPitch;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetSoundPlayPosition(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetSoundPlayPosition;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetSoundDistances(handle P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetSoundDistances;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetSoundDistanceCutoff(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetSoundDistanceCutoff;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetSoundConeAngles(handle P1, realret P2, realret P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetSoundConeAngles;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetSoundConeOrientation(handle P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetSoundConeOrientation;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetSoundPosition(handle P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetSoundPosition;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetSoundVelocity(handle P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetSoundVelocity;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_AttachSoundToUnit(handle P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _AttachSoundToUnit;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_StartSound(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _StartSound;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_StopSound(handle P1, jbooleanret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _StopSound;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_KillSoundWhenDone(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _KillSoundWhenDone;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetMapMusic(stringret P1, jbooleanret P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P3;
	__asm push bP2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _SetMapMusic;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_ClearMapMusic()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ClearMapMusic;

	return;
}

nothing CJassInterface::Jass_PlayMusic(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _PlayMusic;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_PlayMusicEx(stringret P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P3;
	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _PlayMusicEx;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_StopMusic(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _StopMusic;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ResumeMusic()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _ResumeMusic;

	return;
}

nothing CJassInterface::Jass_PlayThematicMusic(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _PlayThematicMusic;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_PlayThematicMusicEx(stringret P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _PlayThematicMusicEx;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_EndThematicMusic()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _EndThematicMusic;

	return;
}

nothing CJassInterface::Jass_SetMusicVolume(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetMusicVolume;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetMusicPlayPosition(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetMusicPlayPosition;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetThematicMusicPlayPosition(integer P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _SetThematicMusicPlayPosition;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_SetSoundDuration(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetSoundDuration;
	__asm add esp, 8;

	return;
}

integer CJassInterface::Jass_GetSoundDuration(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm push P1;
	__asm call _GetSoundDuration;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

integer CJassInterface::Jass_GetSoundFileDuration(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _GetSoundFileDuration;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_VolumeGroupSetVolume(handle P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _VolumeGroupSetVolume;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_VolumeGroupReset()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _VolumeGroupReset;

	return;
}

jbooleanret CJassInterface::Jass_GetSoundIsPlaying(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _GetSoundIsPlaying;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

jbooleanret CJassInterface::Jass_GetSoundIsLoading(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _GetSoundIsLoading;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_RegisterStackedSound(handle P1, jbooleanret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push bP2;
	__asm push P1;
	__asm call _RegisterStackedSound;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_UnregisterStackedSound(handle P1, jbooleanret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push bP2;
	__asm push P1;
	__asm call _UnregisterStackedSound;
	__asm add esp, 16;

	return;
}

handle CJassInterface::Jass_AddWeatherEffect(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P2;
	__asm push P1;
	__asm call _AddWeatherEffect;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_RemoveWeatherEffect(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveWeatherEffect;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_EnableWeatherEffect(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _EnableWeatherEffect;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_TerrainDeformCrater(realret P1, realret P2, realret P3, realret P4, integer P5, jbooleanret P6)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP6 = P6;

	__asm push bP6;
	__asm push P5;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _TerrainDeformCrater;
	__asm mov retValue, eax;
	__asm add esp, 24;

	return retValue;
}

handle CJassInterface::Jass_TerrainDeformRipple(realret P1, realret P2, realret P3, realret P4, integer P5, integer P6, realret P7, realret P8, realret P9, jbooleanret P10)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP10 = P10;

	__asm push bP10;
	__asm lea eax, P9;
	__asm push eax;
	__asm lea eax, P8;
	__asm push eax;
	__asm lea eax, P7;
	__asm push eax;
	__asm push P6;
	__asm push P5;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _TerrainDeformRipple;
	__asm mov retValue, eax;
	__asm add esp, 40;

	return retValue;
}

handle CJassInterface::Jass_TerrainDeformWave(realret P1, realret P2, realret P3, realret P4, realret P5, realret P6, realret P7, realret P8, integer P9, integer P10)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P10;
	__asm push P9;
	__asm lea eax, P8;
	__asm push eax;
	__asm lea eax, P7;
	__asm push eax;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _TerrainDeformWave;
	__asm mov retValue, eax;
	__asm add esp, 40;

	return retValue;
}

handle CJassInterface::Jass_TerrainDeformRandom(realret P1, realret P2, realret P3, realret P4, realret P5, integer P6, integer P7)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P7;
	__asm push P6;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _TerrainDeformRandom;
	__asm mov retValue, eax;
	__asm add esp, 28;

	return retValue;
}

nothing CJassInterface::Jass_TerrainDeformStop(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _TerrainDeformStop;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_TerrainDeformStopAll()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _TerrainDeformStopAll;

	return;
}

nothing CJassInterface::Jass_DestroyEffect(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyEffect;
	__asm add esp, 4;

	return;
}

handle CJassInterface::Jass_AddSpecialEffect(stringret P1, realret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _AddSpecialEffect;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_AddSpecialEffectLoc(stringret P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _AddSpecialEffectLoc;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

handle CJassInterface::Jass_AddSpecialEffectTarget(stringret P1, handle P2, stringret P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP3;
	__asm push eax;
	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _AddSpecialEffectTarget;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffect(stringret P1, handle P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _AddSpellEffect;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectLoc(stringret P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P3;
	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _AddSpellEffectLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectById(integer P1, handle P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpellEffectById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectByIdLoc(integer P1, handle P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpellEffectByIdLoc;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectTarget(stringret P1, handle P2, handle P3, stringret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP4;
	This->cStr2jStr(P4, &sP4);
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP4;
	__asm push eax;
	__asm push P3;
	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _AddSpellEffectTarget;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_AddSpellEffectTargetById(integer P1, handle P2, handle P3, stringret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP4;
	This->cStr2jStr(P4, &sP4);

	__asm lea eax, sP4;
	__asm push eax;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _AddSpellEffectTargetById;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

handle CJassInterface::Jass_AddLightning(stringret P1, jbooleanret P2, realret P3, realret P4, realret P5, realret P6)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP2 = P2;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push bP2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _AddLightning;
	__asm mov retValue, eax;
	__asm add esp, 24;

	return retValue;
}

handle CJassInterface::Jass_AddLightningEx(stringret P1, jbooleanret P2, realret P3, realret P4, realret P5, realret P6, realret P7, realret P8)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP2 = P2;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, P8;
	__asm push eax;
	__asm lea eax, P7;
	__asm push eax;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push bP2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _AddLightningEx;
	__asm mov retValue, eax;
	__asm add esp, 32;

	return retValue;
}

jbooleanret CJassInterface::Jass_DestroyLightning(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P1;
	__asm call _DestroyLightning;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

realret CJassInterface::Jass_GetLightningColorA(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetLightningColorA;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetLightningColorR(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetLightningColorR;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetLightningColorG(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetLightningColorG;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

realret CJassInterface::Jass_GetLightningColorB(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	DWFP retValue;

	__asm push P1;
	__asm call _GetLightningColorB;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue.fl;
}

jbooleanret CJassInterface::Jass_MoveLightning(handle P1, jbooleanret P2, realret P3, realret P4, realret P5, realret P6)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP2 = P2;

	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push bP2;
	__asm push P1;
	__asm call _MoveLightning;
	__asm mov retValue, eax;
	__asm add esp, 24;

	return retValue;
}

jbooleanret CJassInterface::Jass_MoveLightningEx(handle P1, jbooleanret P2, realret P3, realret P4, realret P5, realret P6, realret P7, realret P8)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;
	jboolean bP2 = P2;

	__asm lea eax, P8;
	__asm push eax;
	__asm lea eax, P7;
	__asm push eax;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm push bP2;
	__asm push P1;
	__asm call _MoveLightningEx;
	__asm mov retValue, eax;
	__asm add esp, 32;

	return retValue;
}

jbooleanret CJassInterface::Jass_SetLightningColor(handle P1, realret P2, realret P3, realret P4, realret P5)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetLightningColor;
	__asm mov retValue, eax;
	__asm add esp, 20;

	return retValue;
}

stringret CJassInterface::Jass_GetAbilityEffect(stringret P1, handle P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P3;
	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _GetAbilityEffect;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return jStr2cStr(retValue);
}

stringret CJassInterface::Jass_GetAbilityEffectById(integer P1, handle P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _GetAbilityEffectById;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return jStr2cStr(retValue);
}

stringret CJassInterface::Jass_GetAbilitySound(stringret P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P2;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _GetAbilitySound;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return jStr2cStr(retValue);
}

stringret CJassInterface::Jass_GetAbilitySoundById(integer P1, handle P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	string retValue;

	__asm push P2;
	__asm push P1;
	__asm call _GetAbilitySoundById;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return jStr2cStr(retValue);
}

integer CJassInterface::Jass_GetTerrainCliffLevel(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _GetTerrainCliffLevel;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_SetWaterBaseColor(integer P1, integer P2, integer P3, integer P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetWaterBaseColor;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetWaterDeforms(jbooleanret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP1 = P1;

	__asm push bP1;
	__asm call _SetWaterDeforms;
	__asm add esp, 4;

	return;
}

integer CJassInterface::Jass_GetTerrainType(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _GetTerrainType;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

integer CJassInterface::Jass_GetTerrainVariance(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	integer retValue;

	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _GetTerrainVariance;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_SetTerrainType(realret P1, realret P2, integer P3, integer P4, integer P5, integer P6)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetTerrainType;
	__asm add esp, 24;

	return;
}

jbooleanret CJassInterface::Jass_IsTerrainPathable(realret P1, realret P2, handle P3)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm push P3;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _IsTerrainPathable;
	__asm mov retValue, eax;
	__asm add esp, 12;

	return retValue;
}

nothing CJassInterface::Jass_SetTerrainPathable(realret P1, realret P2, handle P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP4 = P4;

	__asm push bP4;
	__asm push P3;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetTerrainPathable;
	__asm add esp, 16;

	return;
}

handle CJassInterface::Jass_CreateImage(stringret P1, realret P2, realret P3, realret P4, realret P5, realret P6, realret P7, realret P8, realret P9, realret P10, integer P11)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm push P11;
	__asm lea eax, P10;
	__asm push eax;
	__asm lea eax, P9;
	__asm push eax;
	__asm lea eax, P8;
	__asm push eax;
	__asm lea eax, P7;
	__asm push eax;
	__asm lea eax, P6;
	__asm push eax;
	__asm lea eax, P5;
	__asm push eax;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, sP1;
	__asm push eax;
	__asm call _CreateImage;
	__asm mov retValue, eax;
	__asm add esp, 44;

	return retValue;
}

nothing CJassInterface::Jass_DestroyImage(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyImage;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ShowImage(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _ShowImage;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetImageConstantHeight(handle P1, jbooleanret P2, realret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm lea eax, P3;
	__asm push eax;
	__asm push bP2;
	__asm push P1;
	__asm call _SetImageConstantHeight;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetImagePosition(handle P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetImagePosition;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetImageColor(handle P1, integer P2, integer P3, integer P4, integer P5)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P5;
	__asm push P4;
	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _SetImageColor;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_SetImageRender(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetImageRender;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetImageRenderAlways(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetImageRenderAlways;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetImageAboveWater(handle P1, jbooleanret P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;
	jboolean bP2 = P2;

	__asm push bP3;
	__asm push bP2;
	__asm push P1;
	__asm call _SetImageAboveWater;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetImageType(handle P1, integer P2)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P2;
	__asm push P1;
	__asm call _SetImageType;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_CreateUbersplat(realret P1, realret P2, stringret P3, integer P4, integer P5, integer P6, integer P7, jbooleanret P8, jbooleanret P9)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;
	jboolean bP9 = P9;
	jboolean bP8 = P8;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);

	__asm push bP9;
	__asm push bP8;
	__asm push P7;
	__asm push P6;
	__asm push P5;
	__asm push P4;
	__asm lea eax, sP3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _CreateUbersplat;
	__asm mov retValue, eax;
	__asm add esp, 36;

	return retValue;
}

nothing CJassInterface::Jass_DestroyUbersplat(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _DestroyUbersplat;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ResetUbersplat(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _ResetUbersplat;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_FinishUbersplat(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _FinishUbersplat;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ShowUbersplat(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _ShowUbersplat;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUbersplatRender(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetUbersplatRender;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetUbersplatRenderAlways(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _SetUbersplatRenderAlways;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_SetBlight(handle P1, realret P2, realret P3, realret P4, jbooleanret P5)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP5 = P5;

	__asm push bP5;
	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetBlight;
	__asm add esp, 20;

	return;
}

nothing CJassInterface::Jass_SetBlightLoc(handle P1, handle P2, realret P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP4 = P4;

	__asm push bP4;
	__asm lea eax, P3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _SetBlightLoc;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_SetBlightRect(handle P1, handle P2, jbooleanret P3)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP3 = P3;

	__asm push bP3;
	__asm push P2;
	__asm push P1;
	__asm call _SetBlightRect;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_SetBlightPoint(handle P1, realret P2, realret P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP4 = P4;

	__asm push bP4;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _SetBlightPoint;
	__asm add esp, 16;

	return;
}

handle CJassInterface::Jass_CreateBlightedGoldmine(handle P1, realret P2, realret P3, realret P4)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm lea eax, P4;
	__asm push eax;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm push P1;
	__asm call _CreateBlightedGoldmine;
	__asm mov retValue, eax;
	__asm add esp, 16;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsPointBlighted(realret P1, realret P2)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _IsPointBlighted;
	__asm mov retValue, eax;
	__asm add esp, 8;

	return retValue;
}

nothing CJassInterface::Jass_SetDoodadAnimation(realret P1, realret P2, realret P3, integer P4, jbooleanret P5, stringret P6, jbooleanret P7)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP7 = P7;
	JassString sP6;
	This->cStr2jStr(P6, &sP6);
	jboolean bP5 = P5;

	__asm push bP7;
	__asm lea eax, sP6;
	__asm push eax;
	__asm push bP5;
	__asm push P4;
	__asm lea eax, P3;
	__asm push eax;
	__asm lea eax, P2;
	__asm push eax;
	__asm lea eax, P1;
	__asm push eax;
	__asm call _SetDoodadAnimation;
	__asm add esp, 28;

	return;
}

nothing CJassInterface::Jass_SetDoodadAnimationRect(handle P1, integer P2, stringret P3, jbooleanret P4)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP4 = P4;
	JassString sP3;
	This->cStr2jStr(P3, &sP3);

	__asm push bP4;
	__asm lea eax, sP3;
	__asm push eax;
	__asm push P2;
	__asm push P1;
	__asm call _SetDoodadAnimationRect;
	__asm add esp, 16;

	return;
}

nothing CJassInterface::Jass_StartMeleeAI(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _StartMeleeAI;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_StartCampaignAI(handle P1, stringret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP2;
	This->cStr2jStr(P2, &sP2);

	__asm lea eax, sP2;
	__asm push eax;
	__asm push P1;
	__asm call _StartCampaignAI;
	__asm add esp, 8;

	return;
}

nothing CJassInterface::Jass_CommandAI(handle P1, integer P2, integer P3)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P3;
	__asm push P2;
	__asm push P1;
	__asm call _CommandAI;
	__asm add esp, 12;

	return;
}

nothing CJassInterface::Jass_PauseCompAI(handle P1, jbooleanret P2)
{
	if (!InGameOrLoadingscreen(false))
		return;

	jboolean bP2 = P2;

	__asm push bP2;
	__asm push P1;
	__asm call _PauseCompAI;
	__asm add esp, 8;

	return;
}

handle CJassInterface::Jass_GetAIDifficulty(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	handle retValue;

	__asm push P1;
	__asm call _GetAIDifficulty;
	__asm mov retValue, eax;
	__asm add esp, 4;

	return retValue;
}

nothing CJassInterface::Jass_RemoveGuardPosition(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveGuardPosition;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_RecycleGuardPosition(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RecycleGuardPosition;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_RemoveAllGuardPositions(handle P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm push P1;
	__asm call _RemoveAllGuardPositions;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_ExecuteFunc(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _ExecuteFunc;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_Cheat(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _Cheat;
	__asm add esp, 4;

	return;
}

jbooleanret CJassInterface::Jass_IsNoVictoryCheat()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _IsNoVictoryCheat;
	__asm mov retValue, eax;

	return retValue;
}

jbooleanret CJassInterface::Jass_IsNoDefeatCheat()
{
	if (!InGameOrLoadingscreen(false))
		return 0;

	jboolean retValue;

	__asm call _IsNoDefeatCheat;
	__asm mov retValue, eax;

	return retValue;
}

nothing CJassInterface::Jass_Preload(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _Preload;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_PreloadEnd(realret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm lea eax, P1;
	__asm push eax;
	__asm call _PreloadEnd;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_PreloadStart()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _PreloadStart;

	return;
}

nothing CJassInterface::Jass_PreloadRefresh()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _PreloadRefresh;

	return;
}

nothing CJassInterface::Jass_PreloadEndEx()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _PreloadEndEx;

	return;
}

nothing CJassInterface::Jass_PreloadGenStart()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _PreloadGenStart;

	return;
}

nothing CJassInterface::Jass_PreloadGenClear()
{
	if (!InGameOrLoadingscreen(false))
		return;


	__asm call _PreloadGenClear;

	return;
}

nothing CJassInterface::Jass_PreloadGenEnd(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _PreloadGenEnd;
	__asm add esp, 4;

	return;
}

nothing CJassInterface::Jass_Preloader(stringret P1)
{
	if (!InGameOrLoadingscreen(false))
		return;

	JassString sP1;
	This->cStr2jStr(P1, &sP1);

	__asm lea eax, sP1;
	__asm push eax;
	__asm call _Preloader;
	__asm add esp, 4;

	return;
}