#include <dxgi.h>
#include <d3d10.h>
#include "d3d10hook.h"
#include "com_utils.h"

using PFN_CreateDXGIFactory = HRESULT(WINAPI*)(REFIID, void**);

using PFN_D3D10CreateDeviceAndSwapChain = HRESULT(WINAPI*)(
	IDXGIAdapter*,
	D3D10_DRIVER_TYPE,
	HMODULE,
	UINT,
	UINT,
	DXGI_SWAP_CHAIN_DESC*,
	IDXGISwapChain**,
	ID3D10Device**
);

DH_STATUS WINAPI DH_D3D10_Initialize(PDH_METHOD_TABLE pTable)
{
	WNDCLASSEX windowClass{};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.hInstance = GetModuleHandle(nullptr);
	windowClass.lpszClassName = L"DirectHook_D3D10";

	::RegisterClassEx(&windowClass);
	HWND hWnd = ::CreateWindow(windowClass.lpszClassName, L"Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, windowClass.hInstance, nullptr);

	IDXGIFactory* pFactory = nullptr;
	IDXGIAdapter* pAdapter = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D10Device* pDevice = nullptr;
	DH_STATUS status = DH_STATUS_ERROR_GFX_API_INIT_FAILED;

	HMODULE hLibDXGI  = ::GetModuleHandle(L"dxgi.dll");
	HMODULE hLibD3D10 = ::GetModuleHandle(L"d3d10.dll");
	if (!hLibDXGI || !hLibD3D10)
	{
		goto cleanup;
	}

	{
		PFN_CreateDXGIFactory pfnCreateDXGIFactory = (PFN_CreateDXGIFactory)::GetProcAddress(hLibDXGI, "CreateDXGIFactory");
		if (!pfnCreateDXGIFactory)
		{
			goto cleanup;
		}

		if (FAILED(pfnCreateDXGIFactory(IID_PPV_ARGS(&pFactory))))
		{
			goto cleanup;
		}

		if (FAILED(pFactory->EnumAdapters(0, &pAdapter)))
		{
			goto cleanup;
		}

		PFN_D3D10CreateDeviceAndSwapChain pfnD3D10CreateDeviceAndSwapChain = (PFN_D3D10CreateDeviceAndSwapChain)::GetProcAddress(hLibD3D10, "D3D10CreateDeviceAndSwapChain");
		if (!pfnD3D10CreateDeviceAndSwapChain)
		{
			goto cleanup;
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
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		if (FAILED(pfnD3D10CreateDeviceAndSwapChain(pAdapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice)))
		{
			goto cleanup;
		}

		DH_MethodTableAddEntries(pTable, pSwapChain, D3D10_SWAPCHAIN_ENTRIES);
		DH_MethodTableAddEntries(pTable, pDevice, D3D10_DEVICE_ENTRIES);

		status = DH_STATUS_SUCCESS;
	}

cleanup:
	SafeRelease(pDevice);
	SafeRelease(pSwapChain);
	SafeRelease(pAdapter);
	SafeRelease(pFactory);
	::DestroyWindow(hWnd);
	::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
	return status;
}
