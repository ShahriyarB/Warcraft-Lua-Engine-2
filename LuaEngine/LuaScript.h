#pragma once

#include "GameInterface.h"
#include "JassInterface.h"
#include <LuaBridge.h>
#include <map>
#include <list>
#include "SafeQueue.h"

using namespace luabridge;

typedef std::pair<std::string, std::string> TStrStrPair;

class CLuaScript
{
public:
	CLuaScript(lua_State *L, CGameInterface* gameInterface, CJassInterface* jassInterface);
	~CLuaScript();

	void HandleGameStateChange(int32 prevState, int32 newState);
	bool RegisterGameEvent(int32 nEvent, LPCSTR funcName);
	bool RegisterNativeHook(LPCSTR native, LPCSTR funcName_pre, LPCSTR funcName_post);
	bool RegisterChatEvent(LPCSTR chat, LPCSTR funcName);

// --------------------------
// |		Events			|
// --------------------------
	void OnGameFinished(void);
	void OnEnterLobby(void);
	void OnEnterLoading(void);
	void OnGameStarted(void);
	void OnGameResumed(void);
	void OnGamePaused(void);
	void OnGameTick(void);
	void OnUnitCreate(unit hUnit);
	void OnPluginUnload(void);
	bool OnChatEvent(LPCSTR chat);
	// --------------------------
	// |	  Plugin Info		|
	// --------------------------
	void SetPluginName(LPCSTR strName);
	void SetPluginVersion(LPCSTR strVersion);
	void SetPluginAuthor(LPCSTR strAuthor);
	void SetPluginDescription(LPCSTR strDescription);
	LPCSTR GetPluginName();
	LPCSTR GetPluginVersion();
	LPCSTR GetPluginAuthor();
	LPCSTR GetPluginDescription();
	void Unload(void);

	/* Native Hooks */

	std::vector<handle> OnNativeCalled_Pre(std::string name, int paramCount, handle p1 = 0, handle p2 = 0, handle p3 = 0, handle p4 = 0, handle p5 = 0, handle p6 = 0, handle p7 = 0, handle p8 = 0, handle p9 = 0, handle p10 = 0, handle p11 = 0)
	{
		std::vector < handle > ret;

		if (m_nativehooks_pre[name].empty())
			return ret;

		LuaRef Ref = luabridge::getGlobal(m_LuaState, m_nativehooks_pre[name].c_str());
		LuaRef lua_ret = luabridge::newTable(m_LuaState);

		try
		{
			switch (paramCount)
			{
			case 0:
				lua_ret = Ref();
				return ret;
			case 1:
				lua_ret = Ref(p1);
				break;
			case 2:
				lua_ret = Ref(p1, p2);
				break;
			case 3:
				lua_ret = Ref(p1, p2, p3);
				break;
			case 4:
				lua_ret = Ref(p1, p2, p3, p4);
				break;
			case 5:
				lua_ret = Ref(p1, p2, p3, p4, p5);
				break;
			case 6:
				lua_ret = Ref(p1, p2, p3, p4, p5, p6);
				break;
			case 7:
				lua_ret = Ref(p1, p2, p3, p4, p5, p6, p7);
				break;
			case 8:
				lua_ret = Ref(p1, p2, p3, p4, p5, p6, p7, p8);
				break;
			case 9:
				lua_ret = Ref(p1, p2, p3, p4, p5, p6, p7, p8, p9);
				break;
			case 10:
				lua_ret = Ref(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
				break;
			case 11:
				lua_ret = Ref(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
				break;
			default:
				MessageBoxA(NULL, "Invalid paramCount passed to 'OnNativeCalled_Pre' !", "Error", MB_OK | MB_ICONERROR);
				return ret;
			}

			if (lua_ret.isNil())
				return ret;

			if (lua_ret.isTable())
			{
				for (int i = 0; i < paramCount; i++)
					ret.push_back(lua_ret[i+1].cast<handle>());
			}
		}
		catch (LuaException const &ex) { MessageBoxA(NULL, ex.what(), "Lua Script Error", MB_OK | MB_ICONINFORMATION); return ret; }

		return ret;
	}

	void OnNativeCalled_Post(std::string name)
	{
		if (m_nativehooks_post[name].empty())
			return;

		LuaRef Ref = luabridge::getGlobal(m_LuaState, m_nativehooks_post[name].c_str());
		LuaRef lua_ret = luabridge::newTable(m_LuaState);

		try
		{
			lua_ret = Ref();

			if (lua_ret.isNil())
				return;
		}
		catch (LuaException const &ex) { MessageBoxA(NULL, ex.what(), "Lua Script Error", MB_OK | MB_ICONINFORMATION); }
	}

	template <class TYPE>
	TYPE OnNativeCalled_Post(std::string name, TYPE p1)
	{
		if (m_nativehooks_post[name].empty())
			return p1;

		LuaRef Ref = luabridge::getGlobal(m_LuaState, m_nativehooks_post[name].c_str());
		LuaRef lua_ret = luabridge::newTable(m_LuaState);

		try
		{
			lua_ret = Ref(p1);

			if (lua_ret.isNil())
				return p1;
		}
		catch (LuaException const &ex) { MessageBoxA(NULL, ex.what(), "Lua Script Error", MB_OK | MB_ICONINFORMATION); return p1; }
		
		return lua_ret.cast<TYPE>();
	}

	lua_State *m_LuaState;
	BOOL bShutdown;
private:
	DWORD TlsValue, TlsIndex;
	CGameInterface* pGameInterface;
	CJassInterface* pJassInterface;

	std::map<int32, std::string> m_events;
	std::map<std::string, std::string> m_chatevents;
	std::map<std::string, std::string> m_nativehooks_pre;
	std::map<std::string, std::string> m_nativehooks_post;
	std::vector<std::string> m_chateventslist;
	std::string strPluginName;
	std::string strPluginVersion;
	std::string strPluginAuthor;
	std::string strPluginDesc;

	DWORD GetW3TlsForIndex(DWORD index);
	void addToState(void);
	void GetTlsValue(void);
};

