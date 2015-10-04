#pragma once

namespace Utils
{

//	-------------------------------------
//	|			API Wrapper				|
//	-------------------------------------

	void Sleep(DWORD dwMilliSeconds);

//	-------------------------------------
//	|			Logging Stuff			|
//	-------------------------------------

	void Msg(LPCSTR msg);
	void Warning(LPCSTR msg);
	void Error(LPCSTR msg);

	typedef void(*MsgSignature)(LPCSTR msg);
	template<MsgSignature T>
	int LogWrapper(lua_State *L) {
		lua_gettop(L);
		T(lua_tostring(L, 1));
		return 0;
	}
}