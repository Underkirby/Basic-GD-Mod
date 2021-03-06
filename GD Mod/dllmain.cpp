#include "pch.h"
#include "PauseLayer.h"

DWORD WINAPI thread(void* hModule)
{
	if (MH_Initialize() != MH_OK)
	{
		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
	}
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x1E4620), PauseLayer::hook, reinterpret_cast<void**>(&PauseLayer::init));
	MH_EnableHook(MH_ALL_HOOKS);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0x1000, thread, hModule, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}