
#include "directhook.h"

using namespace directhook;

static d3d9::PFN_D3D9Device_DrawPrimitive	d3d9DrawPrimitive = nullptr;
static d3d9::PFN_D3D9Device_Present			d3d9Present = nullptr;

HRESULT STDMETHODCALLTYPE MyDrawPrimitive(IDirect3DDevice9* Device, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	static bool called = false;
	if (!called)
	{
		MessageBoxA(0, "Called MyDrawPrimitive!", "DirectHook", MB_OK);
		called = true;
	}
	return d3d9DrawPrimitive(Device, PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT STDMETHODCALLTYPE MyPresent(
	IDirect3DDevice9* Device,
	const RECT* pSourceRect,
	const RECT* pDestRect,
	HWND          hDestWindowOverride,
	const RGNDATA* pDirtyRegion
)
{
	static bool called = false;
	if (!called)
	{
		MessageBoxA(0, "Called MyPresent!", "DirectHook", MB_OK);
		called = true;
	}
	return d3d9Present(Device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

int D3D9HookThread()
{
	if (Status dh = Initialize(); dh == Status::Success)
	{
		SaveOriginal(d3d9::Device_DrawPrimitive, d3d9DrawPrimitive);
		Hook(d3d9::Device_DrawPrimitive, d3d9DrawPrimitive, MyDrawPrimitive);

		SaveOriginal(d3d9::Device_Present, d3d9Present);
		Hook(d3d9::Device_Present, d3d9Present, MyPresent);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)D3D9HookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}


