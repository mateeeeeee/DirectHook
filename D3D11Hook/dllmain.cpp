#include <d3d11_1.h>
#include "directhook.h"

using PFN_D3D11Draw = void(STDMETHODCALLTYPE*)(ID3D11DeviceContext*, UINT, UINT);
using PFN_DXGIPresent = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);

static PFN_D3D11Draw d3d11Draw = nullptr;
static PFN_DXGIPresent dxgiPresent = nullptr;

using namespace directhook;


void STDMETHODCALLTYPE MyDraw(
	ID3D11DeviceContext* DeviceContext,
	UINT VertexCount, UINT StartVertexLocation)
{
	static bool called = false;
	if (!called)
	{
		MessageBoxA(0, "Called MyDraw!", "DirectHook", MB_OK);
		called = true;
	}
	d3d11Draw(DeviceContext, VertexCount, StartVertexLocation);
}

HRESULT STDMETHODCALLTYPE MyPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)
{
	static bool called = false;
	if (!called)
	{
		MessageBoxA(0, "Called MyPresent!", "DirectHook", MB_OK);
		called = true;
	}
	return dxgiPresent(SwapChain, SyncInterval, Flags);
}

int d3d11hookThread()
{
	if (DHStatus dh = Initialize(); dh == DHStatus::Success)
	{
		d3d11Draw = GetOriginalT<PFN_D3D11Draw>(74);
		Hook(74, (void**)&d3d11Draw, MyDraw);

		dxgiPresent = GetOriginalT<PFN_DXGIPresent>(8);
		Hook(8, (void**)&dxgiPresent, MyPresent);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)d3d11hookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}


