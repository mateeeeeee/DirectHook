#include <dxgi1_4.h>
#include <d3d11_4.h>
#include "d3d11hook.h"
#include "com_utils.h"

using PFN_D3D11CreateDeviceAndSwapChain = HRESULT(STDMETHODCALLTYPE*)(
	IDXGIAdapter*,
	D3D_DRIVER_TYPE,
	HMODULE,
	UINT,
	const D3D_FEATURE_LEVEL*,
	UINT,
	UINT,
	const DXGI_SWAP_CHAIN_DESC*,
	IDXGISwapChain**,
	ID3D11Device**,
	D3D_FEATURE_LEVEL*,
	ID3D11DeviceContext**);

DH_STATUS WINAPI DH_D3D11_Initialize(PDH_METHOD_TABLE pTable)
{
	WNDCLASSEX windowClass{};
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
	windowClass.lpszClassName = L"DirectHook_D3D11";
	windowClass.hIconSm = nullptr;

	::RegisterClassEx(&windowClass);
	HWND hWnd = ::CreateWindow(windowClass.lpszClassName, L"Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, windowClass.hInstance, nullptr);

	HMODULE hLibD3D11 = ::GetModuleHandle(L"d3d11.dll");
	if (hLibD3D11 == nullptr)
	{
		::DestroyWindow(hWnd);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return DH_STATUS_ERROR_GFX_API_INIT_FAILED;
	}

	PFN_D3D11CreateDeviceAndSwapChain pfnD3D11CreateDeviceAndSwapChain = (PFN_D3D11CreateDeviceAndSwapChain)::GetProcAddress(hLibD3D11, "D3D11CreateDeviceAndSwapChain");
	if (pfnD3D11CreateDeviceAndSwapChain == nullptr)
	{
		::DestroyWindow(hWnd);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return DH_STATUS_ERROR_GFX_API_INIT_FAILED;
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

	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	if (pfnD3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, nullptr, &pContext) < 0)
	{
		::DestroyWindow(hWnd);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return DH_STATUS_ERROR_GFX_API_INIT_FAILED;
	}

	IDXGISwapChain4* pSwapChain4 = nullptr;
	IDXGISwapChain3* pSwapChain3 = nullptr;
	IDXGISwapChain2* pSwapChain2 = nullptr;
	IDXGISwapChain1* pSwapChain1 = nullptr;
	if (SUCCEEDED(pSwapChain->QueryInterface(IID_PPV_ARGS(&pSwapChain4))))
	{
		DH_MethodTableAddEntries(pTable, pSwapChain4, D3D11_SWAPCHAIN4_ENTRIES, D3D11_MAX_SWAPCHAIN_ENTRIES);
		SafeRelease(pSwapChain4);
	}
	else if (SUCCEEDED(pSwapChain->QueryInterface(IID_PPV_ARGS(&pSwapChain3))))
	{
		DH_MethodTableAddEntries(pTable, pSwapChain3, D3D11_SWAPCHAIN3_ENTRIES, D3D11_MAX_SWAPCHAIN_ENTRIES);
		SafeRelease(pSwapChain3);
	}
	else if (SUCCEEDED(pSwapChain->QueryInterface(IID_PPV_ARGS(&pSwapChain2))))
	{
		DH_MethodTableAddEntries(pTable, pSwapChain2, D3D11_SWAPCHAIN2_ENTRIES, D3D11_MAX_SWAPCHAIN_ENTRIES);
		SafeRelease(pSwapChain2);
	}
	else if (SUCCEEDED(pSwapChain->QueryInterface(IID_PPV_ARGS(&pSwapChain1))))
	{
		DH_MethodTableAddEntries(pTable, pSwapChain1, D3D11_SWAPCHAIN1_ENTRIES, D3D11_MAX_SWAPCHAIN_ENTRIES);
		SafeRelease(pSwapChain1);
	}
	else
	{
		DH_MethodTableAddEntries(pTable, pSwapChain, D3D11_SWAPCHAIN_ENTRIES, D3D11_MAX_SWAPCHAIN_ENTRIES);
	}

	ID3D11Device1* pDevice1 = nullptr;
	ID3D11Device2* pDevice2 = nullptr;
	ID3D11Device3* pDevice3 = nullptr;
	ID3D11Device4* pDevice4 = nullptr;
	ID3D11Device5* pDevice5 = nullptr;
	if (SUCCEEDED(pDevice->QueryInterface(IID_PPV_ARGS(&pDevice5))))
	{
		DH_MethodTableAddEntries(pTable, pDevice5, D3D11_DEVICE5_ENTRIES, D3D11_MAX_DEVICE_ENTRIES);
		SafeRelease(pDevice5);
	}
	else if (SUCCEEDED(pDevice->QueryInterface(IID_PPV_ARGS(&pDevice4))))
	{
		DH_MethodTableAddEntries(pTable, pDevice4, D3D11_DEVICE4_ENTRIES, D3D11_MAX_DEVICE_ENTRIES);
		SafeRelease(pDevice4);
	}
	else if (SUCCEEDED(pDevice->QueryInterface(IID_PPV_ARGS(&pDevice3))))
	{
		DH_MethodTableAddEntries(pTable, pDevice3, D3D11_DEVICE3_ENTRIES, D3D11_MAX_DEVICE_ENTRIES);
		SafeRelease(pDevice3);
	}
	else if (SUCCEEDED(pDevice->QueryInterface(IID_PPV_ARGS(&pDevice2))))
	{
		DH_MethodTableAddEntries(pTable, pDevice2, D3D11_DEVICE2_ENTRIES, D3D11_MAX_DEVICE_ENTRIES);
		SafeRelease(pDevice2);
	}
	else if (SUCCEEDED(pDevice->QueryInterface(IID_PPV_ARGS(&pDevice1))))
	{
		DH_MethodTableAddEntries(pTable, pDevice1, D3D11_DEVICE1_ENTRIES, D3D11_MAX_DEVICE_ENTRIES);
		SafeRelease(pDevice1);
	}
	else
	{
		DH_MethodTableAddEntries(pTable, pDevice, D3D11_DEVICE_ENTRIES, D3D11_MAX_DEVICE_ENTRIES);
	}

	ID3D11DeviceContext1* pContext1 = nullptr;
	ID3D11DeviceContext2* pContext2 = nullptr;
	ID3D11DeviceContext3* pContext3 = nullptr;
	ID3D11DeviceContext4* pContext4 = nullptr;
	if (SUCCEEDED(pContext->QueryInterface(IID_PPV_ARGS(&pContext4))))
	{
		DH_MethodTableAddEntries(pTable, pContext4, D3D11_CONTEXT4_ENTRIES, D3D11_MAX_CONTEXT_ENTRIES);
		SafeRelease(pContext4);
	}
	else if (SUCCEEDED(pContext->QueryInterface(IID_PPV_ARGS(&pContext3))))
	{
		DH_MethodTableAddEntries(pTable, pContext3, D3D11_CONTEXT3_ENTRIES, D3D11_MAX_CONTEXT_ENTRIES);
		SafeRelease(pContext3);
	}
	else if (SUCCEEDED(pContext->QueryInterface(IID_PPV_ARGS(&pContext2))))
	{
		DH_MethodTableAddEntries(pTable, pContext2, D3D11_CONTEXT2_ENTRIES, D3D11_MAX_CONTEXT_ENTRIES);
		SafeRelease(pContext2);
	}
	else if (SUCCEEDED(pContext->QueryInterface(IID_PPV_ARGS(&pContext1))))
	{
		DH_MethodTableAddEntries(pTable, pContext1, D3D11_CONTEXT1_ENTRIES, D3D11_MAX_CONTEXT_ENTRIES);
		SafeRelease(pContext1);
	}
	else
	{
		DH_MethodTableAddEntries(pTable, pContext, D3D11_CONTEXT_ENTRIES, D3D11_MAX_CONTEXT_ENTRIES);
	}

	SafeRelease(pSwapChain);
	SafeRelease(pDevice);
	SafeRelease(pContext);

	::DestroyWindow(hWnd);
	::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

	return DH_STATUS_SUCCESS;
}
