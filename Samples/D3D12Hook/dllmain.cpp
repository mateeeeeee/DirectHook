#include <windows.h>
#include <VersionHelpers.h>
#include <vector>
#include "directhook.h"
#include "ImGui/imgui_impl_dx12.h"
#include "ImGui/imgui_impl_win32.h"

#pragma comment(lib, "dxgi.lib")

struct ImGuiD3D12Context
{
	ID3D12DescriptorHeap* FontDescriptorHeap = nullptr;
	ID3D12DescriptorHeap* RTVDescriptorHeap = nullptr;
	ID3D12CommandQueue* CommandQueue = nullptr;
	ID3D12GraphicsCommandList* CommandList = nullptr;
	std::vector<ID3D12CommandAllocator*> CommandAllocators;
	std::vector<ID3D12Resource*> BackBuffers;
	std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> BackBufferDescriptors;
	UINT BufferIndex;
	UINT BufferCount;
};

static PFN_D3D12_CommandList_DrawInstanced     g_pfnD3D12Draw = nullptr;
static PFN_D3D12_DXGISwapChain_Present  g_pfnDxgiPresent = nullptr;
static WNDPROC g_pfnWin32WndProc = nullptr;
static ImGuiD3D12Context g_Context;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam) > 0)
	{
		return 1L;
	}
	return ::CallWindowProcA(g_pfnWin32WndProc, hwnd, uMsg, wParam, lParam);
}

static BOOL GetCommandQueueOffset(UINT& offset)
{
	OSVERSIONINFOEXW osInfo{};
	osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
	typedef LONG(WINAPI* RtlGetVersionPtr)(OSVERSIONINFOEXW*);
	HMODULE hMod = GetModuleHandleW(L"ntdll.dll");
	if (hMod)
	{
		RtlGetVersionPtr rtlGetVersion = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");
		if (rtlGetVersion != nullptr)
		{
			if (rtlGetVersion(&osInfo) == 0)
			{
				if (osInfo.dwBuildNumber >= 26200)
				{
					offset = 0x140;
				}
				else if (osInfo.dwBuildNumber >= 26100)
				{
					offset = 0x138;
				}
				else if (osInfo.dwBuildNumber >= 21996)
				{
					offset = 0x168;
				}
				else
				{
					offset = 0x118;
				}
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
	}
	return FALSE;
}

static HRESULT STDMETHODCALLTYPE MyPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	static LONG initStatus = 0;
	LONG prev = InterlockedCompareExchange(&initStatus, 1, 0);
	if (prev == 1)
	{
		return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
	}
	if (prev == 0)
	{
		DXGI_SWAP_CHAIN_DESC swapchainDesc{};
		if (FAILED(pSwapChain->GetDesc(&swapchainDesc)))
		{
			InterlockedExchange(&initStatus, 0);
			return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
		}
		g_pfnWin32WndProc = (WNDPROC)::SetWindowLongPtr(swapchainDesc.OutputWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(MyWindowProc));

		ID3D12Device* pDevice = nullptr;
		if (FAILED(pSwapChain->GetDevice(IID_PPV_ARGS(&pDevice))))
		{
			InterlockedExchange(&initStatus, 0);
			return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
		}

		if (!g_Context.CommandQueue)
		{
			UINT queueOffset;
			if (GetCommandQueueOffset(queueOffset))
			{
				g_Context.CommandQueue = *reinterpret_cast<ID3D12CommandQueue**>((uintptr_t)pSwapChain + queueOffset);
			}
		}

		D3D12_DESCRIPTOR_HEAP_DESC fontHeapDesc{};
		fontHeapDesc.NumDescriptors = 1;
		fontHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		fontHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		fontHeapDesc.NodeMask = 0;
		if (FAILED(pDevice->CreateDescriptorHeap(&fontHeapDesc, IID_PPV_ARGS(&g_Context.FontDescriptorHeap))))
		{
			pDevice->Release();
			InterlockedExchange(&initStatus, 0);
			return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
		}

		IDXGISwapChain3* pSwapChain3 = nullptr;
		if (FAILED(pSwapChain->QueryInterface(&pSwapChain3)))
		{
			pDevice->Release();
			InterlockedExchange(&initStatus, 0);
			return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
		}

		g_Context.BufferIndex = pSwapChain3->GetCurrentBackBufferIndex();
		g_Context.BufferCount = swapchainDesc.BufferCount;
		pSwapChain3->Release();

		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.NumDescriptors = g_Context.BufferCount;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		if (FAILED(pDevice->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&g_Context.RTVDescriptorHeap))))
		{
			pDevice->Release();
			InterlockedExchange(&initStatus, 0);
			return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
		}

		g_Context.BackBuffers.resize(g_Context.BufferCount);
		g_Context.BackBufferDescriptors.resize(g_Context.BufferCount);
		UINT rtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_Context.RTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		for (UINT i = 0; i < g_Context.BufferCount; i++)
		{
			g_Context.BackBufferDescriptors[i] = rtvHandle;
			pSwapChain->GetBuffer(i, IID_PPV_ARGS(&g_Context.BackBuffers[i]));
			pDevice->CreateRenderTargetView(g_Context.BackBuffers[i], nullptr, rtvHandle);
			rtvHandle.ptr += rtvDescriptorSize;
		}

		g_Context.CommandAllocators.resize(g_Context.BufferCount);
		BOOL bAllocatorsOk = TRUE;
		for (UINT i = 0; i < g_Context.BufferCount; ++i)
		{
			if (FAILED(pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_Context.CommandAllocators[i]))))
			{
				bAllocatorsOk = FALSE;
				break;
			}
		}
		if (!bAllocatorsOk)
		{
			pDevice->Release();
			InterlockedExchange(&initStatus, 0);
			return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
		}

		if (FAILED(pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_Context.CommandAllocators[0], nullptr, IID_PPV_ARGS(&g_Context.CommandList))))
		{
			pDevice->Release();
			InterlockedExchange(&initStatus, 0);
			return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
		}

		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = g_Context.FontDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = g_Context.FontDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(swapchainDesc.OutputWindow);
		ImGui_ImplDX12_InitInfo init_info;
		init_info.Device = pDevice;
		init_info.NumFramesInFlight = swapchainDesc.BufferCount;
		init_info.RTVFormat = swapchainDesc.BufferDesc.Format;
		init_info.SrvDescriptorHeap = g_Context.FontDescriptorHeap;
		init_info.LegacySingleSrvCpuDescriptor = cpuHandle;
		init_info.LegacySingleSrvGpuDescriptor = gpuHandle;
		init_info.CommandQueue = g_Context.CommandQueue;
		ImGui_ImplDX12_Init(&init_info);

		pDevice->Release();
		InterlockedExchange(&initStatus, 2);
	}

	if (!g_Context.CommandQueue)
	{
		return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::Render();

	D3D12_RESOURCE_BARRIER Barrier;
	Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	Barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	Barrier.Transition.pResource = g_Context.BackBuffers[g_Context.BufferIndex];
	Barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	g_Context.CommandList->ResourceBarrier(1, &Barrier);
	g_Context.CommandList->OMSetRenderTargets(1, &g_Context.BackBufferDescriptors[g_Context.BufferIndex], FALSE, nullptr);

	g_Context.CommandList->SetDescriptorHeaps(1, &g_Context.FontDescriptorHeap);
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), g_Context.CommandList);

	Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	g_Context.CommandList->ResourceBarrier(1, &Barrier);

	g_Context.CommandList->Close();
	g_Context.CommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&g_Context.CommandList));
	g_Context.CommandAllocators[g_Context.BufferIndex]->Reset();
	g_Context.CommandList->Reset(g_Context.CommandAllocators[g_Context.BufferIndex], nullptr);

	g_Context.BufferIndex = (g_Context.BufferIndex + 1) % g_Context.BufferCount;
	return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
}

static void STDMETHODCALLTYPE MyDraw(ID3D12GraphicsCommandList* pCmdList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
	static BOOL bCalled = FALSE;
	if (!bCalled)
	{
		MessageBoxA(0, "Called MyDraw!", "DirectHook", MB_OK);
		bCalled = TRUE;
	}
	g_pfnD3D12Draw(pCmdList, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

INT D3D12HookThread()
{
	if (DH_Initialize() == DH_STATUS_SUCCESS)
	{
		DH_Hook(D3D12_SwapChain_Present, g_pfnDxgiPresent, MyPresent);
		DH_Hook(D3D12_List_DrawInstanced, g_pfnD3D12Draw, MyDraw);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)D3D12HookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}
