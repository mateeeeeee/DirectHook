#include "directhook.h"

//steps for creating a hook:
//add minhook path to additional library directories
//link with minhook.x64.lib or minhook.x86.lib
//add directhook files to dll project
//add include directories for minhook and directhook
//add define for API (E.G. DH_USE_D3D12)

using namespace directhook;

static d3d12::PFN_D3D12CommandList_DrawInstanced d3d12Draw = nullptr;
static d3d12::PFN_IDXGISwapChain_Present dxgiPresent = nullptr;

void STDMETHODCALLTYPE MyDraw(ID3D12CommandList* CmdList, UINT VertexCountPerInstance,
	UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
	static bool called = false;
	if (!called)
	{
		MessageBoxA(0, "Called MyDraw!", "DirectHook", MB_OK);
		called = true;
	}
	d3d12Draw(CmdList, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
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

int D3D12HookThread()
{
	if (Status dh = Initialize(); dh == Status::Success)
	{
		SaveOriginal(d3d12::List_DrawInstanced, d3d12Draw);
		Hook(d3d12::List_DrawInstanced, d3d12Draw, MyDraw);

		SaveOriginal(d3d12::SwapChain_Present, dxgiPresent);
		Hook(d3d12::SwapChain_Present, dxgiPresent, MyPresent);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)D3D12HookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}


