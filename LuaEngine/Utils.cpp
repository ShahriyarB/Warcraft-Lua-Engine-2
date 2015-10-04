#include "stdafx.h"
#include "Utils.h"

namespace Utils
{
//	-------------------------------------
//	|			API Wrapper				|
//	-------------------------------------

	void Sleep(DWORD dwMilliSeconds)
	{
		if (dwMilliSeconds <= 0)
			return;

		return ::Sleep(dwMilliSeconds);
	}

	void Msg(LPCSTR msg)
	{
		MessageBoxA(NULL, msg, "Lua Script", MB_OK | MB_ICONINFORMATION);
	}

	void Warning(LPCSTR msg)
	{
		MessageBoxA(NULL, msg, "Lua Script", MB_OK | MB_ICONEXCLAMATION);
	}

	void Error(LPCSTR msg)
	{
		MessageBoxA(NULL, msg, "Lua Script", MB_OK | MB_ICONERROR);
	}
}