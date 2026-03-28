#include <dxgi.h>
#include <d3d12.h>
#include "d3d12hook.h"
#include "com_utils.h"

using PFN_CreateDXGIFactory = HRESULT(STDMETHODCALLTYPE*)(REFIID, void**);
using PFN_CreateD3D12Device = HRESULT(STDMETHODCALLTYPE*)(IUnknown*, D3D_FEATURE_LEVEL, REFIID, void**);

template <typename T, typename BaseT>
static BOOL TryQIAddEntries(PDH_METHOD_TABLE pTable, BaseT* pBase, UINT cEntries, UINT cMaxEntries)
{
	T* p = nullptr;
	if (FAILED(pBase->QueryInterface(IID_PPV_ARGS(&p)))) 
	{
		return FALSE;
	}
	DH_MethodTableAddEntries(pTable, p, cEntries, cMaxEntries);
	SafeRelease(p);
	return TRUE;
}

#define DH_TRY(Type, Entries, Max) \
	do { if (TryQIAddEntries<Type>(pTable, pBase, Entries, Max)) return; } while (0)

static void AddDeviceEntries(PDH_METHOD_TABLE pTable, ID3D12Device* pBase)
{
#if defined(__ID3D12Device14_INTERFACE_DEFINED__)
	DH_TRY(ID3D12Device14, D3D12_DEVICE14_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
#endif
#if defined(__ID3D12Device13_INTERFACE_DEFINED__)
	DH_TRY(ID3D12Device13, D3D12_DEVICE13_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
#endif
#if defined(__ID3D12Device12_INTERFACE_DEFINED__)
	DH_TRY(ID3D12Device12, D3D12_DEVICE12_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
#endif
#if defined(__ID3D12Device11_INTERFACE_DEFINED__)
	DH_TRY(ID3D12Device11, D3D12_DEVICE11_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
#endif
#if defined(__ID3D12Device10_INTERFACE_DEFINED__)
	DH_TRY(ID3D12Device10, D3D12_DEVICE10_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
#endif
#if defined(__ID3D12Device9_INTERFACE_DEFINED__)
	DH_TRY(ID3D12Device9, D3D12_DEVICE9_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
#endif
	DH_TRY(ID3D12Device8, D3D12_DEVICE8_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
	DH_TRY(ID3D12Device7, D3D12_DEVICE7_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
	DH_TRY(ID3D12Device6, D3D12_DEVICE6_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
	DH_TRY(ID3D12Device5, D3D12_DEVICE5_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
	DH_TRY(ID3D12Device4, D3D12_DEVICE4_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
	DH_TRY(ID3D12Device3, D3D12_DEVICE3_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
	DH_TRY(ID3D12Device2, D3D12_DEVICE2_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
	DH_TRY(ID3D12Device1, D3D12_DEVICE1_ENTRIES, D3D12_MAX_DEVICE_ENTRIES);
	DH_MethodTableAddEntries(pTable, pBase, D3D12_DEVICE_ENTRIES);
}

static void AddCommandListEntries(PDH_METHOD_TABLE pTable, ID3D12GraphicsCommandList* pBase)
{
#if defined(__ID3D12GraphicsCommandList10_INTERFACE_DEFINED__)
	DH_TRY(ID3D12GraphicsCommandList10, D3D12_LIST10_ENTRIES, D3D12_MAX_LIST_ENTRIES);
#endif
#if defined(__ID3D12GraphicsCommandList9_INTERFACE_DEFINED__)
	DH_TRY(ID3D12GraphicsCommandList9, D3D12_LIST9_ENTRIES, D3D12_MAX_LIST_ENTRIES);
#endif
#if defined(__ID3D12GraphicsCommandList8_INTERFACE_DEFINED__)
	DH_TRY(ID3D12GraphicsCommandList8, D3D12_LIST8_ENTRIES, D3D12_MAX_LIST_ENTRIES);
#endif
#if defined(__ID3D12GraphicsCommandList7_INTERFACE_DEFINED__)
	DH_TRY(ID3D12GraphicsCommandList7, D3D12_LIST7_ENTRIES, D3D12_MAX_LIST_ENTRIES);
#endif
#if defined(__ID3D12GraphicsCommandList6_INTERFACE_DEFINED__)
	DH_TRY(ID3D12GraphicsCommandList6, D3D12_LIST6_ENTRIES, D3D12_MAX_LIST_ENTRIES);
#endif
	DH_TRY(ID3D12GraphicsCommandList5, D3D12_LIST5_ENTRIES, D3D12_MAX_LIST_ENTRIES);
	DH_TRY(ID3D12GraphicsCommandList4, D3D12_LIST4_ENTRIES, D3D12_MAX_LIST_ENTRIES);
	DH_TRY(ID3D12GraphicsCommandList3, D3D12_LIST3_ENTRIES, D3D12_MAX_LIST_ENTRIES);
	DH_TRY(ID3D12GraphicsCommandList2, D3D12_LIST2_ENTRIES, D3D12_MAX_LIST_ENTRIES);
	DH_TRY(ID3D12GraphicsCommandList1, D3D12_LIST1_ENTRIES, D3D12_MAX_LIST_ENTRIES);
	DH_MethodTableAddEntries(pTable, pBase, D3D12_LIST_ENTRIES);
}

static void AddSwapChainEntries(PDH_METHOD_TABLE pTable, IDXGISwapChain* pBase)
{
	DH_TRY(IDXGISwapChain4, D3D12_SWAPCHAIN4_ENTRIES, D3D12_MAX_SWAPCHAIN_ENTRIES);
	DH_TRY(IDXGISwapChain3, D3D12_SWAPCHAIN3_ENTRIES, D3D12_MAX_SWAPCHAIN_ENTRIES);
	DH_TRY(IDXGISwapChain2, D3D12_SWAPCHAIN2_ENTRIES, D3D12_MAX_SWAPCHAIN_ENTRIES);
	DH_TRY(IDXGISwapChain1, D3D12_SWAPCHAIN1_ENTRIES, D3D12_MAX_SWAPCHAIN_ENTRIES);
	DH_MethodTableAddEntries(pTable, pBase, D3D12_SWAPCHAIN_ENTRIES, D3D12_MAX_SWAPCHAIN_ENTRIES);
}

static void AddResourceEntries(PDH_METHOD_TABLE pTable, ID3D12Resource* pBase)
{
	DH_TRY(ID3D12Resource2, D3D12_RESOURCE2_ENTRIES, D3D12_MAX_RESOURCE_ENTRIES);
	DH_TRY(ID3D12Resource1, D3D12_RESOURCE1_ENTRIES, D3D12_MAX_RESOURCE_ENTRIES);
	DH_MethodTableAddEntries(pTable, pBase, D3D12_RESOURCE_ENTRIES, D3D12_MAX_RESOURCE_ENTRIES);
}

static void AddFenceEntries(PDH_METHOD_TABLE pTable, ID3D12Fence* pBase)
{
	DH_TRY(ID3D12Fence1, D3D12_FENCE1_ENTRIES, D3D12_MAX_FENCE_ENTRIES);
	DH_MethodTableAddEntries(pTable, pBase, D3D12_FENCE_ENTRIES, D3D12_MAX_FENCE_ENTRIES);
}

DH_STATUS WINAPI DH_D3D12_Initialize(PDH_METHOD_TABLE pTable)
{
	WNDCLASSEX windowClass{};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.hInstance = GetModuleHandle(nullptr);
	windowClass.lpszClassName = L"DirectHook_D3D12";

	::RegisterClassEx(&windowClass);
	HWND hWnd = ::CreateWindow(windowClass.lpszClassName, L"Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, windowClass.hInstance, nullptr);

	IDXGIFactory* pFactory = nullptr;
	IDXGIAdapter* pAdapter = nullptr;
	ID3D12Device* pDevice = nullptr;
	ID3D12CommandQueue* pQueue = nullptr;
	ID3D12CommandAllocator* pAllocator = nullptr;
	ID3D12GraphicsCommandList* pList = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D12Resource* pResource = nullptr;
	ID3D12Fence* pFence = nullptr;
	DH_STATUS status = DH_STATUS_ERROR_GFX_API_INIT_FAILED;

	HMODULE hLibDXGI = ::GetModuleHandle(L"dxgi.dll");
	HMODULE hLibD3D12 = ::GetModuleHandle(L"d3d12.dll");
	if (hLibDXGI == nullptr || hLibD3D12 == nullptr)
	{
		goto cleanup;
	}

	{
		PFN_CreateDXGIFactory pfnCreateDXGIFactory = (PFN_CreateDXGIFactory)::GetProcAddress(hLibDXGI, "CreateDXGIFactory");
		if (pfnCreateDXGIFactory == nullptr)
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

		PFN_CreateD3D12Device pfnD3D12CreateDevice = (PFN_CreateD3D12Device)::GetProcAddress(hLibD3D12, "D3D12CreateDevice");
		if (pfnD3D12CreateDevice == nullptr)
		{
			goto cleanup;
		}

		if (FAILED(pfnD3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&pDevice))))
		{
			goto cleanup;
		}

		D3D12_COMMAND_QUEUE_DESC queueDesc{};
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Priority = 0;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 0;

		if (FAILED(pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&pQueue))))
		{
			goto cleanup;
		}

		if (FAILED(pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&pAllocator))))
		{
			goto cleanup;
		}

		if (FAILED(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, pAllocator, nullptr, IID_PPV_ARGS(&pList))))
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
		swapChainDesc.BufferCount = 2;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		if (FAILED(pFactory->CreateSwapChain(pQueue, &swapChainDesc, &pSwapChain)))
		{
			goto cleanup;
		}

		D3D12_HEAP_PROPERTIES heapProps{};
		heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
		D3D12_RESOURCE_DESC desc{};
		desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Width = 1024;
		desc.Height = 1;
		desc.DepthOrArraySize = 1;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;
		desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.Alignment = 0;
		desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		if (FAILED(pDevice->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&pResource))))
		{
			goto cleanup;
		}

		if (FAILED(pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pFence))))
		{
			goto cleanup;
		}

		AddDeviceEntries(pTable, pDevice);
		DH_MethodTableAddEntries(pTable, pQueue, D3D12_QUEUE_ENTRIES);
		DH_MethodTableAddEntries(pTable, pAllocator, D3D12_ALLOCATOR_ENTRIES);
		AddCommandListEntries(pTable, pList);
		AddSwapChainEntries(pTable, pSwapChain);
		AddResourceEntries(pTable, pResource);
		AddFenceEntries(pTable, pFence);

		status = DH_STATUS_SUCCESS;
	}

cleanup:
	SafeRelease(pFence);
	SafeRelease(pResource);
	SafeRelease(pSwapChain);
	SafeRelease(pList);
	SafeRelease(pAllocator);
	SafeRelease(pQueue);
	SafeRelease(pDevice);
	SafeRelease(pAdapter);
	SafeRelease(pFactory);
	::DestroyWindow(hWnd);
	::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
	return status;
}
