// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "Resource.h"
#include "RunWithParametersExt_i.h"
#include "dllmain.h"

CRunWithParametersExtModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
