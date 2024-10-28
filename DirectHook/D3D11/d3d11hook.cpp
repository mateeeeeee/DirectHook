#include <dxgi.h>
#include <d3d11_1.h>
#include "d3d11hook.h"
#include "../method_table.h"

namespace directhook::d3d11
{
	using PFN_D3D11CreateDeviceAndSwapChain = HRESULT(__stdcall*)(
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

	DHStatus Initialize(MethodTable& methodTable)
	{
		WNDCLASSEXA windowClass;
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
		windowClass.lpszClassName = "DirectHook";
		windowClass.hIconSm = nullptr;

		::RegisterClassExA(&windowClass);
		HWND window = ::CreateWindowA(windowClass.lpszClassName, "Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, windowClass.hInstance, nullptr);

		HMODULE libD3D11 = ::GetModuleHandleA("d3d11.dll");
		if (libD3D11 == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
			return DHStatus::Error_APIInitFailed;
		}

		PFN_D3D11CreateDeviceAndSwapChain D3D11CreateDeviceAndSwapChain = (PFN_D3D11CreateDeviceAndSwapChain)::GetProcAddress(libD3D11, "D3D11CreateDeviceAndSwapChain");
		if (D3D11CreateDeviceAndSwapChain == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
			return DHStatus::Error_APIInitFailed;
		}

		DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;
		DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
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
		if ((D3D11CreateDeviceAndSwapChain)(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, nullptr, &deviceContext) < 0)
		{
			::DestroyWindow(window);
			::UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
			return DHStatus::Error_APIInitFailed;
		}

		methodTable.AddVTableEntries(swapChain, SWAPCHAIN_ENTRIES);
		methodTable.AddVTableEntries(device, DEVICE_ENTRIES);
		methodTable.AddVTableEntries(deviceContext, CONTEXT_ENTRIES);

		swapChain->Release();
		device->Release();
		deviceContext->Release();

		return DHStatus::Success;
	}

}

