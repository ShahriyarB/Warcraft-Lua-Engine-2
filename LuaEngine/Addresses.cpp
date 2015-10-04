#include "stdafx.h"
#include "Addresses.h"

DWORD GameBase = 0;
DWORD StormBase = 0;

DWORD GetGameBase()
{
	if (!GameBase)
		return (GameBase = (DWORD)GetModuleHandle(_T("Game.dll")));

	return GameBase;
}

DWORD GetStormBase()
{
	if (!StormBase)
		return (StormBase = (DWORD)GetModuleHandle(_T("Storm.dll")));

	return StormBase;
}