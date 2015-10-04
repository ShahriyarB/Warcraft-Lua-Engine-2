// Detours.cpp

#include "stdafx.h"
#include "Detours.h"

namespace Detours
{
	bool PlantDetourJMP(BYTE* source, const BYTE* destination, const int length)
	{
		BYTE* jump = (BYTE*)malloc(length + 5);

		if (jump == NULL)
			return false;

		DWORD oldProtection;
		BOOL bRet = VirtualProtect(source, length, PAGE_EXECUTE_READWRITE, &oldProtection);

		if (bRet == FALSE)
			return false;

		memcpy(jump, source, length);

		jump[length] = 0xE9;
		*(DWORD*)(jump + length) = (DWORD)((source + length) - (jump + length)) - 5;

		source[0] = 0xE9;
		*(DWORD*)(source + 1) = (DWORD)(destination - source) - 5;

		for (int i = 5; i < length; i++)
			source[i] = 0x90;

		VirtualProtect(source, length, oldProtection, &oldProtection);

		return true;
	}
}