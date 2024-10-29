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

		HMODULE libD3D11 = ::GetModuleHandle(L"d3d11.dll");
		if (libD3D11 == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		PFN_D3D11CreateDeviceAndSwapChain D3D11CreateDeviceAndSwapChain = (PFN_D3D11CreateDeviceAndSwapChain)::GetProcAddress(libD3D11, "D3D11CreateDeviceAndSwapChain");
		if (D3D11CreateDeviceAndSwapChain == nullptr)
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

		IDXGISwapChain* swapChain = nullptr;
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* deviceContext = nullptr;
		if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, nullptr, &deviceContext) < 0)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

        IDXGISwapChain3* swapChain3 = nullptr;
        swapChain->QueryInterface(IID_PPV_ARGS(&swapChain3));
        IDXGISwapChain2* swapChain2 = nullptr;
        swapChain->QueryInterface(IID_PPV_ARGS(&swapChain2));
		IDXGISwapChain1* swapChain1 = nullptr;
        swapChain->QueryInterface(IID_PPV_ARGS(&swapChain1));

		if (swapChain3)
		{
            methodTable.AddEntries(swapChain3, SWAPCHAIN3_ENTRIES);
		}
        else if (swapChain2)
        {
            methodTable.AddEntries(swapChain2, SWAPCHAIN2_ENTRIES);
        }
		else if (swapChain1)
        {
            methodTable.AddEntries(swapChain1, SWAPCHAIN1_ENTRIES);
        }
		else
		{
            methodTable.AddEntries(swapChain, SWAPCHAIN_ENTRIES);
		}

        methodTable.AddEntries(device, DEVICE_ENTRIES);
        methodTable.AddEntries(deviceContext, CONTEXT_ENTRIES);

		SafeRelease(swapChain);
		SafeRelease(swapChain1);
		SafeRelease(swapChain2);
		SafeRelease(swapChain3);
		SafeRelease(device);
		SafeRelease(deviceContext);

		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

		return Status::Success;
	}

}

