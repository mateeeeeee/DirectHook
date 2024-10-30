#include "directhook.h"

using namespace directhook;

static d3d11::PFN_D3D11DeviceContext_Draw d3d11Draw = nullptr;
static d3d11::PFN_DXGISwapChain_Present   DxgiPresent = nullptr;

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
	return DxgiPresent(SwapChain, SyncInterval, Flags);
}

int D3D11HookThread()
{
	if (Status dh = Initialize(); dh == Status::Success)
	{
		SaveOriginal(d3d11::Context_Draw, d3d11Draw);
		Hook(d3d11::Context_Draw, d3d11Draw, MyDraw);

		SaveOriginal(d3d11::SwapChain_Present, DxgiPresent);
		Hook(d3d11::SwapChain_Present, DxgiPresent, MyPresent);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)D3D11HookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}


