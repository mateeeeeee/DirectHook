# DirectHook
DirectHook is a library designed for intercepting and modifying DirectX API function calls.

Supported APIs: D3D9, D3D10, D3D11, D3D12, DirectDraw 7.

## TODO
 - Consider adding support for non-DirectX graphics APIs such as OpenGL and Vulkan

## Samples
For each supported API, the Samples folder includes a basic DLL that hooks into several API functions, as well as an application whose calls are intercepted by this DLL.
The samples also demonstrate how to use DirectHook to implement an ImGui hook for supported APIs.

To test them, you can use either provided DLLInjector project and pass as command line arguments the name of the target process and path to dll:
```
DLLInjector.exe D3D11App.exe D3D11Hook.dll
```
Or if you want to test it quickly, you can add `LoadLibrary(L"D3D11Hook.dll")` to the application source code.

Each of the supported APIs provides two utility headers for easier use, one for **hook indices** and the other one for **API typedefs/aliases**.

Indices are provided as enum members, while typedefs are provided as using aliases. 

### D3D11 Example

In case of D3D11, hook indices look like this:
```cpp
namespace directhook::d3d11
{
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
	};
}
```
And using aliases:
```cpp
namespace directhook::d3d11
{
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
	//...
}
```
If you want to write a simple DLL hooking `Present` call, you can use `d3d11::SwapChain_Present` for index when calling `Hook` function and `d3d11::PFN_DXGISwapChain_Present` for declaring function pointer variable. You can check the D3D11Hook sample project to see it being used for ImGui hooking.
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
		Hook(d3d11::SwapChain_Present, dxgiPresent, MyPresent);
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
1. Add DirectHook folder to your DLL project
2. Either link to MinHook libraries or add MinHook source code in your project
3. Define a graphics API macro (`DH_USE_*`) telling for which API you are building your DLL
	- In Visual Studio: Project -> Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions 
	- In CMake: `target_compile_definitions(MyDLL PRIVATE DH_USE_*)`
	- Or simply add the define you need at top of directhook.h

