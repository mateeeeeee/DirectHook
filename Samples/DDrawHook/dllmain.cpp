#include "directhook.h"

static PFN_DDRAW_Device_CreateSurface	g_pfnDDrawCreateSurface = nullptr;
static PFN_DDRAW_Surface_Blt			g_pfnDDrawBlt = nullptr;

static HRESULT STDMETHODCALLTYPE MyCreateSurface(IDirectDraw7* pInstance, LPDDSURFACEDESC2 unnamedParam1, LPDIRECTDRAWSURFACE7* unnamedParam2, IUnknown* unnamedParam3)
{
	static BOOL bCalled = FALSE;
	if (!bCalled)
	{
		MessageBoxA(0, "Called MyCreateSurface!", "DirectHook", MB_OK);
		bCalled = TRUE;
	}
	return g_pfnDDrawCreateSurface(pInstance, unnamedParam1, unnamedParam2, unnamedParam3);
}

static HRESULT STDMETHODCALLTYPE MyBlt(IDirectDrawSurface7* pSurface, LPCRECT unnamedParam1, IDirectDrawSurface7* unnamedParam2, LPCRECT unnamedParam3, DWORD unnamedParam4, LPDDBLTFX unnamedParam5)
{
	static BOOL bCalled = FALSE;
	if (!bCalled)
	{
		MessageBoxA(0, "Called MyBlt!", "DirectHook", MB_OK);
		bCalled = TRUE;
	}
	return g_pfnDDrawBlt(pSurface, unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4, unnamedParam5);
}

INT DDrawHookThread()
{
	if (DH_Initialize() == DH_STATUS_SUCCESS)
	{
		DH_Hook(DDRAW_Device_CreateSurface, g_pfnDDrawCreateSurface, MyCreateSurface);
		DH_Hook(DDRAW_Surface_Blt, g_pfnDDrawBlt, MyBlt);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DDrawHookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}
