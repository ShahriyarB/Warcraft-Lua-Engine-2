// LuaEngine.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "LuaEngine.h"
#include "LuaScript.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLuaEngineApp

BEGIN_MESSAGE_MAP(CLuaEngineApp, CWinApp)
END_MESSAGE_MAP()

bool bShutDown;
bool bPluginState[256] = { false };

// CLuaEngineApp construction

CLuaEngineApp::CLuaEngineApp() :
	index(-1)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CLuaEngineApp object

CLuaEngineApp theApp;

int setLuaPath(lua_State* L, const char* path)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
	std::string cur_path = lua_tostring(L, -1); // grab path string from top of stack
	cur_path.append(";"); // do your path magic here
	cur_path.append(path);
	lua_pop(L, 1); // get rid of the string on the stack we just pushed on line 5
	lua_pushstring(L, cur_path.c_str()); // push the new one
	lua_setfield(L, -2, "path"); // set the field "path" in table at -2 with value at top of stack
	lua_pop(L, 1); // get rid of package table from top of stack
	return 0; // all done!
}

int setLuaCPath(lua_State* L, const char* path)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "cpath"); // get field "path" from table at top of stack (-1)
	std::string cur_path = lua_tostring(L, -1); // grab path string from top of stack
	cur_path.append(";"); // do your path magic here
	cur_path.append(path);
	lua_pop(L, 1); // get rid of the string on the stack we just pushed on line 5
	lua_pushstring(L, cur_path.c_str()); // push the new one
	lua_setfield(L, -2, "cpath"); // set the field "path" in table at -2 with value at top of stack
	lua_pop(L, 1); // get rid of package table from top of stack
	return 0; // all done!
}

DWORD WINAPI CLuaEngineApp::LoadScript(LPVOID lpParam)
{
	if (!lpParam)
		return 1;

	ThreadParam* param = static_cast<ThreadParam*>(lpParam);

	CString* Path = param->script;

	lua_State* L = luaL_newstate();

	theApp.m_Memory.push_back(MemoryManager(L, true));

	luaL_openlibs(L);
	setLuaPath(L, "Plugins/Libraries/?.lua;?.lua");
	setLuaCPath(L, "Plugins/Libraries/?.dll;?.dll");

	CLuaScript* Script = new (std::nothrow) CLuaScript(L, &param->pThis->m_GameInterface, &param->pThis->m_JassInterface);

	if (luaL_loadfile(L, CStringA(Path->GetString())) != 0)
		MessageBoxA(NULL, lua_tostring(L, -1), "Lua Script Error", MB_OK | MB_ICONERROR);
	
	try
	{
		luabridge::LuaException::pcall(L);
		luabridge::LuaRef init_function =
			luabridge::getGlobal(L, "Initialize");
		init_function(Script);
	}
	catch (luabridge::LuaException const& e) {
		MessageBoxA(NULL, e.what(), "Lua Script Error", MB_OK | MB_ICONERROR);
	}
	catch (...) {
		MessageBoxA(NULL, "Default lua exception", "Lua Script Error", MB_OK | MB_ICONERROR);
	}

	int32 iPreviousState = 0;
	int32 iCurrentState = 0;

	while (!bShutDown && !Script->bShutdown)
	{
		iCurrentState = param->pThis->m_GameInterface.GetGameStateValue();

		if (iCurrentState != iPreviousState)
			Script->HandleGameStateChange(iPreviousState, iCurrentState);

		iPreviousState = iCurrentState;

		Script->OnGameTick();

		Sleep(100);
	}

	Script->OnPluginUnload();

	param->pThis->m_GameInterface.RemoveScript(Script);

	bPluginState[param->index] = true;

	return ERROR_SUCCESS;
}


void CLuaEngineApp::GetScripts(CString root, CStringArray &ret)
{
	CFileFind ff;
	BOOL bFind = ff.FindFile(root);

	while (bFind) {
		bFind = ff.FindNextFile();
		if (!ff.IsDots() && !ff.IsDirectory())
			ret.Add(ff.GetFilePath());
	}

	ff.Close();
}

// CLuaEngineApp initialization

BOOL CLuaEngineApp::InitInstance()
{
	CWinApp::InitInstance();

//	if (!AfxSocketInit())
//	{
//		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
//		return FALSE;
//	}

	bShutDown = false;

	m_GameInterface.Init(&m_JassInterface);
	m_JassInterface.Init(&m_GameInterface);

	int32 nScripts = 0;
	CStringArray Result;

	GetScripts(_T("Plugins\\*.lua"), Result);
	nScripts = Result.GetSize();

	if (nScripts <= 0)
		return FALSE;

	for (int32 i = 0; i < nScripts; i++)
	{
		CString *Temp = new CString(Result[i]);
		ThreadParam *params = new ThreadParam(this, Temp, ++index);
		m_Memory.push_back(MemoryManager(Temp, false));
		m_Memory.push_back(MemoryManager(params, false));
		HANDLE hThread = ::CreateThread(NULL, 0, LoadScript, params, 0, NULL);
		CloseHandle(hThread);
	}

	return TRUE;
}


int CLuaEngineApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class

#ifdef DEBUG
	uint32 nMemoriesFreed = 0;
	CHAR szOut[128];
#endif

	bShutDown = true;

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	if (index >= 0)
	{
		for (int i = 0; i <= index; i++)
		{
			check:
			if (bPluginState[i] == false){
				Sleep(100);
				goto check;
			}	
		}
	}

	Sleep(500);

	for (auto &memory : m_Memory)
	{
		if (memory.Address != NULL)
		{
			try
			{
				if (memory.bLua)
					lua_close((lua_State*)memory.Address);
				else
					delete memory.Address;
			}
			catch (...){}
#ifdef DEBUG
			nMemoriesFreed++;
#endif
		}
	}

#ifdef DEBUG
	sprintf_s(szOut, "CLuaEngineApp::ExitInstance ==> nMemoriesFreed ==> %i", nMemoriesFreed);
	OutputDebugStringA(szOut);
#endif

	return CWinApp::ExitInstance();
}
