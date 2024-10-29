#include <dxgi.h>
#include <d3d10.h>
#include "d3d10hook.h"
#include "../method_table.h"

namespace directhook::d3d10
{
	using PFN_CreateDXGIFactory = HRESULT(STDMETHODCALLTYPE*)(REFIID, void**);

	using PFN_D3D10CreateDeviceAndSwapChain = HRESULT(*)(
		IDXGIAdapter*,
		D3D10_DRIVER_TYPE,
		HMODULE,
		UINT,
		UINT,
		DXGI_SWAP_CHAIN_DESC*,
		IDXGISwapChain** ,
		ID3D10Device**
	);

	Status Initialize(MethodTable& methodTable)
	{
		WNDCLASSEX windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = DefWindowProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(nullptr);
		windowClass.hIcon = nullptr;
		windowClass.hCursor = nullptr;
		windowClass.hbrBackground = nullptr;
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = L"DirectHook";
		windowClass.hIconSm = nullptr;

		::RegisterClassEx(&windowClass);
		HWND window = ::CreateWindow(windowClass.lpszClassName, L"Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, windowClass.hInstance, nullptr);

		HMODULE libDXGI  = ::GetModuleHandle(L"dxgi.dll");
		HMODULE libD3D10 = ::GetModuleHandle(L"d3d10.dll");
		if (!libDXGI || !libD3D10)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		PFN_CreateDXGIFactory CreateDXGIFactory = (PFN_CreateDXGIFactory)::GetProcAddress(libDXGI, "CreateDXGIFactory");
		if (!CreateDXGIFactory)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		IDXGIFactory* factory = nullptr;
		if (CreateDXGIFactory(IID_PPV_ARGS(&factory)) != S_OK)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		IDXGIAdapter* adapter = nullptr;
		if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		PFN_D3D10CreateDeviceAndSwapChain D3D10CreateDeviceAndSwapChain = (PFN_D3D10CreateDeviceAndSwapChain)::GetProcAddress(libD3D10, "D3D10CreateDeviceAndSwapChain");
		if (!D3D10CreateDeviceAndSwapChain)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		DXGI_RATIONAL refreshRate{};
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		DXGI_MODE_DESC bufferDesc{};
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC sampleDesc{};
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc{};
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = window;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGISwapChain* swapChain;
		ID3D10Device* device;

		if (D3D10CreateDeviceAndSwapChain(adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &swapChainDesc, &swapChain, &device) != S_OK)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		methodTable.AddEntries(swapChain, 18);
		methodTable.AddEntries(device, 98);

		swapChain->Release();
		swapChain = nullptr;

		device->Release();
		device = nullptr;

		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

		return Status::Success;
	}

}

