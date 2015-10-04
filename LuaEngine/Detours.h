// Detours.h

#pragma once

namespace Detours
{
	template <typename T>
	inline MH_STATUS MH_CreateHookEx(LPVOID pTarget, LPVOID pDetour, T** ppOriginal)
	{
		static MH_STATUS status;

		if ((status = MH_CreateHook(pTarget, pDetour, reinterpret_cast<void**>(ppOriginal))) != MH_OK)
			return status;

		if ((status = MH_EnableHook(pTarget)) != MH_OK)
			return status;

		return MH_OK;
	}

	bool PlantDetourJMP(BYTE* source, const BYTE* destination, const int length);
}