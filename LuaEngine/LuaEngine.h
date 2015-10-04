// LuaEngine.h : main header file for the LuaEngine DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <queue>
#include <vector>
#include "GameInterface.h"
#include "JassInterface.h"

// CLuaEngineApp
// See LuaEngine.cpp for the implementation of this class
//

extern bool bShutDown;
extern bool bPluginState[256];

class CLuaEngineApp;

struct MemoryManager
{
	LPVOID Address;
	bool bLua;

	MemoryManager(LPVOID address, bool lua) :
		Address(address), bLua(lua) {}
};

struct ThreadParam
{
	CLuaEngineApp* pThis;
	CString* script;
	int index;

	ThreadParam(CLuaEngineApp* _this, CString* _script, int _index) :
		pThis(_this), script(_script), index(_index) {}
};

class CLuaEngineApp : public CWinApp
{
public:
	CLuaEngineApp();

public:
	static DWORD WINAPI LoadScript(LPVOID lpParam);
	void GetScripts(CString root, CStringArray &ret);

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

	CGameInterface m_GameInterface;
	CJassInterface m_JassInterface;
private:
	std::vector <MemoryManager> m_Memory;
	int index;
};
