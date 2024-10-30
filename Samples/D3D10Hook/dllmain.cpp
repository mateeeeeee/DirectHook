#include "directhook.h"

using namespace directhook;

static d3d10::PFN_D3D10Device_Draw		  d3d10Draw = nullptr;
static d3d10::PFN_DXGISwapChain_Present   DxgiPresent = nullptr;

void STDMETHODCALLTYPE MyDraw(ID3D10Device* Device, UINT VertexCount, UINT StartVertexLocation)
{
	static bool called = false;
	if (!called)
	{
		MessageBoxA(0, "Called MyDraw!", "DirectHook", MB_OK);
		called = true;
	}
	d3d10Draw(Device, VertexCount, StartVertexLocation);
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

int D3D10HookThread()
{
	if (Status dh = Initialize(); dh == Status::Success)
	{
		SaveOriginal(d3d10::Device_Draw, d3d10Draw);
		Hook(d3d10::Device_Draw, d3d10Draw, MyDraw);

		SaveOriginal(d3d10::SwapChain_Present, DxgiPresent);
		Hook(d3d10::SwapChain_Present, DxgiPresent, MyPresent);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)D3D10HookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}







