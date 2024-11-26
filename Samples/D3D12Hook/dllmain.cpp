#include <windows.h>
#include <VersionHelpers.h>
#include <vector>
#include "directhook.h"
#include "ImGui/imgui_impl_dx12.h"
#include "ImGui/imgui_impl_win32.h"

using namespace directhook;

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

static d3d12::PFN_D3D12CommandList_DrawInstanced D3D12Draw = nullptr;
static d3d12::PFN_IDXGISwapChain_Present DxgiPresent = nullptr;
static WNDPROC Win32WndProc = nullptr;
static ImGuiD3D12Context Context;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam) > 0)
	{
		return 1L;
	}
	return ::CallWindowProcA(Win32WndProc, hwnd, uMsg, wParam, lParam);
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
				if (osInfo.dwBuildNumber >= 26100) offset = 0x138;
				else if (osInfo.dwBuildNumber >= 21996) offset = 0x168;
				else offset = 0x118;
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
static HRESULT STDMETHODCALLTYPE MyPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)
{
	static BOOL initialized = FALSE;
	if (!initialized)
	{
		DXGI_SWAP_CHAIN_DESC swapchainDesc{};
		if (FAILED(SwapChain->GetDesc(&swapchainDesc)))
		{
			return DxgiPresent(SwapChain, SyncInterval, Flags);
		}
		Win32WndProc = (WNDPROC)::SetWindowLongPtr(swapchainDesc.OutputWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(MyWindowProc));

		ID3D12Device* device = nullptr;
		if (FAILED(SwapChain->GetDevice(IID_PPV_ARGS(&device))))
		{
			return DxgiPresent(SwapChain, SyncInterval, Flags);
		}

        if (!Context.CommandQueue)
        {
			UINT queueOffset;
            if (GetCommandQueueOffset(queueOffset))
            {
				Context.CommandQueue = *reinterpret_cast<ID3D12CommandQueue**>((uintptr_t)SwapChain + queueOffset);
            }
        }

		D3D12_DESCRIPTOR_HEAP_DESC fontHeapDesc{};
		fontHeapDesc.NumDescriptors = 1;
		fontHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; 
		fontHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; 
		fontHeapDesc.NodeMask = 0; 
		if (FAILED(device->CreateDescriptorHeap(&fontHeapDesc, IID_PPV_ARGS(&Context.FontDescriptorHeap))))
		{
			return DxgiPresent(SwapChain, SyncInterval, Flags);
		}

		IDXGISwapChain3* SwapChain3 = nullptr;
		if (FAILED(SwapChain->QueryInterface(&SwapChain3)))
		{
			return DxgiPresent(SwapChain, SyncInterval, Flags);
		}

		Context.BufferIndex = SwapChain3->GetCurrentBackBufferIndex();
		Context.BufferCount = swapchainDesc.BufferCount;

		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.NumDescriptors = Context.BufferCount;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		if (device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&Context.RTVDescriptorHeap)) != S_OK)
		{
			return DxgiPresent(SwapChain, SyncInterval, Flags);
		}

		Context.BackBuffers.resize(Context.BufferCount);
		Context.BackBufferDescriptors.resize(Context.BufferCount);
		UINT rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = Context.RTVDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		for (UINT i = 0; i < Context.BufferCount; i++)
		{
			Context.BackBufferDescriptors[i] = rtvHandle;
			SwapChain->GetBuffer(i, IID_PPV_ARGS(&Context.BackBuffers[i]));
			device->CreateRenderTargetView(Context.BackBuffers[i], nullptr, rtvHandle);
			rtvHandle.ptr += rtvDescriptorSize;
		}
		
		Context.CommandAllocators.resize(Context.BufferCount);
		for (UINT i = 0; i < Context.BufferCount; ++i)
		{
			if (FAILED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&Context.CommandAllocators[i]))))
			{
				return DxgiPresent(SwapChain, SyncInterval, Flags);
			}
		}

		if (FAILED(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, Context.CommandAllocators[0], nullptr, IID_PPV_ARGS(&Context.CommandList))))
		{
			return DxgiPresent(SwapChain, SyncInterval, Flags);
		}

		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = Context.FontDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = Context.FontDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(swapchainDesc.OutputWindow);
		ImGui_ImplDX12_Init(device, swapchainDesc.BufferCount, swapchainDesc.BufferDesc.Format, Context.FontDescriptorHeap, cpuHandle, gpuHandle);

		initialized = TRUE;
	}
	if (!Context.CommandQueue)
	{
		return DxgiPresent(SwapChain, SyncInterval, Flags);
	}
	
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::Render();

	D3D12_RESOURCE_BARRIER Barrier;
	Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	Barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	Barrier.Transition.pResource = Context.BackBuffers[Context.BufferIndex];
	Barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	Context.CommandList->OMSetRenderTargets(1, &Context.BackBufferDescriptors[Context.BufferIndex], FALSE, nullptr);

	Context.CommandList->SetDescriptorHeaps(1, &Context.FontDescriptorHeap);
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), Context.CommandList);

	Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	Context.CommandList->ResourceBarrier(1, &Barrier);

	Context.CommandList->Close();
	Context.CommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&Context.CommandList));
	Context.CommandAllocators[Context.BufferIndex]->Reset();
	Context.CommandList->Reset(Context.CommandAllocators[Context.BufferIndex], nullptr);

	Context.BufferIndex = (Context.BufferIndex + 1) % Context.BufferCount;
	return DxgiPresent(SwapChain, SyncInterval, Flags);
}
static void STDMETHODCALLTYPE MyDraw(ID3D12GraphicsCommandList* CmdList, UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation)
{
	static BOOL called = FALSE;
	if (!called)
	{
		MessageBoxA(0, "Called MyDraw!", "DirectHook", MB_OK);
		called = TRUE;
	}
	D3D12Draw(CmdList, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

INT D3D12HookThread()
{
	if (DH_Status dh = DH_Initialize(); dh == DH_Status::Success)
	{
		Hook(d3d12::SwapChain_Present, DxgiPresent, MyPresent);
		Hook(d3d12::List_DrawInstanced, D3D12Draw, MyDraw);
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


