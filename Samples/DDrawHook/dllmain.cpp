#include "directhook.h"

using namespace directhook;

static ddraw::PFN_DDrawDevice_CreateSurface		ddrawCreateSurface = nullptr;
static ddraw::PFN_DDrawSurface_Blt				ddrawBlt = nullptr;

HRESULT STDMETHODCALLTYPE MyCreateSurface(IDirectDraw7* Instance, LPDDSURFACEDESC2 unnamedParam1, LPDIRECTDRAWSURFACE7* unnamedParam2, IUnknown* unnamedParam3)
{
	static bool called = false;
	if (!called)
	{
		MessageBoxA(0, "Called MyCreateSurface!", "DirectHook", MB_OK);
		called = true;
	}
	return ddrawCreateSurface(Instance, unnamedParam1, unnamedParam2, unnamedParam3);
}

HRESULT STDMETHODCALLTYPE MyBlt(
	IDirectDrawSurface7* Surface, LPCRECT unnamedParam1, IDirectDrawSurface7* unnamedParam2, LPCRECT unnamedParam3,
	DWORD unnamedParam4, LPDDBLTFX unnamedParam5
)
{
	static bool called = false;
	if (!called)
	{
		MessageBoxA(0, "Called MyBlt!", "DirectHook", MB_OK);
		called = true;
	}
	return ddrawBlt(Surface, unnamedParam1, unnamedParam2, unnamedParam3, unnamedParam4, unnamedParam5);
}

int DDrawHookThread()
{
	if (Status dh = Initialize(); dh == Status::Success)
	{
		SaveOriginal(ddraw::Device_CreateSurface, ddrawCreateSurface);
		Hook(ddraw::Device_CreateSurface, ddrawCreateSurface, MyCreateSurface);

		SaveOriginal(ddraw::Surface_Blt, ddrawBlt);
		Hook(ddraw::Surface_Blt, ddrawBlt, MyBlt);
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

