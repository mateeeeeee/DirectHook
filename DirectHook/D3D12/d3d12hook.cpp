#include <dxgi.h>
#include <d3d12.h>
#include "d3d12hook.h"
#include "../method_table.h"

namespace directhook::d3d12
{

	using PFN_CreateDXGIFactory = HRESULT(STDMETHODCALLTYPE*)(REFIID, void**);
	using PFN_CreateD3D12Device = HRESULT(STDMETHODCALLTYPE*)(IUnknown*, D3D_FEATURE_LEVEL, REFIID, void**);

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

		HMODULE libDXGI = ::GetModuleHandle(L"dxgi.dll");
		HMODULE libD3D12 = ::GetModuleHandle(L"d3d12.dll");
		if (libDXGI == nullptr || libD3D12 == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		PFN_CreateDXGIFactory CreateDXGIFactory = (PFN_CreateDXGIFactory)::GetProcAddress(libDXGI, "CreateDXGIFactory");
		if (CreateDXGIFactory == nullptr)
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

		PFN_CreateD3D12Device D3D12CreateDevice = (PFN_CreateD3D12Device)::GetProcAddress(libD3D12, "D3D12CreateDevice");
		if (D3D12CreateDevice == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		ID3D12Device* device = nullptr;
		if (D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)) != S_OK)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		D3D12_COMMAND_QUEUE_DESC queueDesc{};
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Priority = 0;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 0;

		ID3D12CommandQueue* commandQueue = nullptr;
		if (device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue)) != S_OK)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		ID3D12CommandAllocator* commandAllocator = nullptr;
		if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)) < 0)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		ID3D12GraphicsCommandList* commandList = nullptr;
		if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr, IID_PPV_ARGS(&commandList)) < 0)
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
		swapChainDesc.BufferCount = 2;
		swapChainDesc.OutputWindow = window;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGISwapChain* swapChain = nullptr;
		if (factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain) < 0)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		methodTable.AddEntries(device, DEVICE_ENTRIES);
		methodTable.AddEntries(commandQueue, QUEUE_ENTRIES);
		methodTable.AddEntries(commandAllocator, ALLOCATOR_ENTRIES);
		methodTable.AddEntries(commandList, LIST_ENTRIES);
		methodTable.AddEntries(swapChain, SWAPCHAIN_ENTRIES);

		device->Release();
		device = nullptr;

		commandQueue->Release();
		commandQueue = nullptr;

		commandAllocator->Release();
		commandAllocator = nullptr;

		commandList->Release();
		commandList = nullptr;

		swapChain->Release();
		swapChain = nullptr;

		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

		return Status::Success;
	}

}

