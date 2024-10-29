# DirectHook
DirectHook is a library designed for intercepting and modifying Direct3D API function calls.

Supported APIs: D3D9, D3D10, D3D11, D3D12, DirectDraw 7.


## Example
For each supported API, the Samples folder includes a simple DLL that hooks a few of the API functions, along with an application whose calls are intercepted by the DLL.

Also each of the supported APIs provides two utility headers for easier use, one for **hook indices** and the other one for **API typedefs/aliases**.  

Indices are provided as enum members, while typedefs are provided as using aliases.
### D3D11

In case of D3D11, indices look like this:
```cpp
enum 
{
    SwapChain_FirstEntry = 0,
    SwapChain_QueryInterface = SwapChain_FirstEntry,
    SwapChain_AddRef,
    SwapChain_Release,
    SwapChain_SetPrivateData,
    SwapChain_SetPrivateDataInterface,
    SwapChain_GetPrivateData,
    SwapChain_GetParent,
    SwapChain_GetDevice,
    SwapChain_Present
    //...
```
And typedefs:
```cpp
using PFN_DXGISwapChain_QueryInterface = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFIID, void**);
using PFN_DXGISwapChain_AddRef = ULONG(STDMETHODCALLTYPE*)(IDXGISwapChain*);
using PFN_DXGISwapChain_Release = ULONG(STDMETHODCALLTYPE*)(IDXGISwapChain*);
using PFN_DXGISwapChain_SetPrivateData = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFGUID, UINT, const void*);
using PFN_DXGISwapChain_SetPrivateDataInterface = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFGUID, const IUnknown*);
using PFN_DXGISwapChain_GetPrivateData = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFGUID, UINT*, void*);
using PFN_DXGISwapChain_GetParent = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFIID, void**);
using PFN_DXGISwapChain_GetDevice = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFIID, void**);
using PFN_DXGISwapChain_Present = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
using PFN_DXGISwapChain_GetBuffer = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, REFIID, void**);
```
If you want to write a simple DLL hooking `Present` call, you would use `d3d11::SwapChain_Present` and `d3d11::PFN_DXGISwapChain_Present` for declaring function pointer variables:
```cpp
#include "directhook.h"

using namespace directhook;

static d3d11::PFN_DXGISwapChain_Present   dxgiPresent = nullptr;

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

int D3D11HookThread()
{
	if (Status dh = Initialize(); dh == Status::Success)
	{
		GetOriginal(d3d11::SwapChain_Present, dxgiPresent);
		Hook(d3d11::SwapChain_Present, dxgiPresent, &MyPresent);
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
```

## Usage
When writing a DLL, you first add the DirectHook folder to your project and link to MinHook libraries. Second, you need to specify which graphics API are you building your DLL for. 


