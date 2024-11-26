#include <dxgi1_4.h>
#include <d3d11_4.h>
#include "d3d11hook.h"
#include "../method_table.h"

namespace directhook::d3d11
{
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

	template<typename ComT>
	void SafeRelease(ComT* ptr)
	{
		if (ptr) ptr->Release();
		ptr = nullptr;
	}

	DH_Status Initialize(MethodTable& methodTable)
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

		HMODULE libD3D11 = ::GetModuleHandle(L"d3d11.dll");
		if (libD3D11 == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return DH_Status::Error_GfxApiInitFailed;
		}

		PFN_D3D11CreateDeviceAndSwapChain D3D11CreateDeviceAndSwapChain = (PFN_D3D11CreateDeviceAndSwapChain)::GetProcAddress(libD3D11, "D3D11CreateDeviceAndSwapChain");
		if (D3D11CreateDeviceAndSwapChain == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return DH_Status::Error_GfxApiInitFailed;
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

		IDXGISwapChain* swapChain = nullptr;
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* deviceContext = nullptr;
		if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, nullptr, &deviceContext) < 0)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return DH_Status::Error_GfxApiInitFailed;
		}

        IDXGISwapChain3* swapChain3 = nullptr;
		IDXGISwapChain2* swapChain2 = nullptr;
		IDXGISwapChain1* swapChain1 = nullptr;
		if (SUCCEEDED(swapChain->QueryInterface(IID_PPV_ARGS(&swapChain3))))
		{
			methodTable.AddEntries(swapChain3, SWAPCHAIN3_ENTRIES, MAX_SWAPCHAIN_ENTRIES);
			SafeRelease(swapChain3);
		}
		else if (SUCCEEDED(swapChain->QueryInterface(IID_PPV_ARGS(&swapChain2))))
		{
			methodTable.AddEntries(swapChain2, SWAPCHAIN2_ENTRIES, MAX_SWAPCHAIN_ENTRIES);
			SafeRelease(swapChain2);
		}
		else if (SUCCEEDED(swapChain->QueryInterface(IID_PPV_ARGS(&swapChain1))))
		{
			methodTable.AddEntries(swapChain1, SWAPCHAIN1_ENTRIES, MAX_SWAPCHAIN_ENTRIES);
			SafeRelease(swapChain1);
		}
		else
		{
			methodTable.AddEntries(swapChain, SWAPCHAIN_ENTRIES, MAX_SWAPCHAIN_ENTRIES);
		}

		ID3D11Device* device1 = nullptr;
		ID3D11Device* device2 = nullptr;
		ID3D11Device* device3 = nullptr;
		ID3D11Device* device4 = nullptr;
		ID3D11Device* device5 = nullptr;
		if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&device5))))
		{
			methodTable.AddEntries(device5, DEVICE5_ENTRIES, MAX_DEVICE_ENTRIES);
			SafeRelease(device5);
		}
		else if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&device4))))
		{
			methodTable.AddEntries(device4, DEVICE4_ENTRIES, MAX_DEVICE_ENTRIES);
			SafeRelease(device4);

		}
		else if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&device3))))
		{
			methodTable.AddEntries(device3, DEVICE3_ENTRIES, MAX_DEVICE_ENTRIES);
			SafeRelease(device3);

		}
		else if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&device2))))
		{
			methodTable.AddEntries(device2, DEVICE2_ENTRIES, MAX_DEVICE_ENTRIES);
			SafeRelease(device2);
		}
		else if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&device1))))
		{
			methodTable.AddEntries(device1, DEVICE1_ENTRIES, MAX_DEVICE_ENTRIES);
			SafeRelease(device1);
		}
		else
		{
			methodTable.AddEntries(device, DEVICE_ENTRIES, MAX_DEVICE_ENTRIES);
		}

		ID3D11DeviceContext1* deviceContext1 = nullptr;
		ID3D11DeviceContext2* deviceContext2 = nullptr;
		ID3D11DeviceContext3* deviceContext3 = nullptr;
		ID3D11DeviceContext4* deviceContext4 = nullptr;
		if (SUCCEEDED(deviceContext->QueryInterface(IID_PPV_ARGS(&deviceContext4))))
		{
			methodTable.AddEntries(deviceContext4, CONTEXT4_ENTRIES, MAX_CONTEXT_ENTRIES);
			SafeRelease(deviceContext4);
		}
		else if (SUCCEEDED(deviceContext->QueryInterface(IID_PPV_ARGS(&deviceContext3))))
		{
			methodTable.AddEntries(deviceContext3, CONTEXT3_ENTRIES, MAX_CONTEXT_ENTRIES);
			SafeRelease(deviceContext3);
		}
		else if (SUCCEEDED(deviceContext->QueryInterface(IID_PPV_ARGS(&deviceContext2))))
		{
			methodTable.AddEntries(deviceContext2, CONTEXT2_ENTRIES, MAX_CONTEXT_ENTRIES);
			SafeRelease(deviceContext2);
		}
		else if (SUCCEEDED(deviceContext->QueryInterface(IID_PPV_ARGS(&deviceContext1))))
		{
			methodTable.AddEntries(deviceContext1, CONTEXT1_ENTRIES, MAX_CONTEXT_ENTRIES);
			SafeRelease(deviceContext1);
		}
		else
		{
			methodTable.AddEntries(deviceContext, CONTEXT_ENTRIES, MAX_CONTEXT_ENTRIES);
		}

		SafeRelease(swapChain);
		SafeRelease(device);
		SafeRelease(deviceContext);

		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

		return DH_Status::Success;
	}

}

