#include "directhook.h"
#include "ImGui/imgui_impl_dx10.h"
#include "ImGui/imgui_impl_win32.h"

using namespace directhook;

static d3d10::PFN_D3D10Device_Draw		  D3D10Draw = nullptr;
static d3d10::PFN_DXGISwapChain_Present   DxgiPresent = nullptr;
static WNDPROC Win32WndProc = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam) > 0)
	{
		return 1L;
	}
	return ::CallWindowProcA(Win32WndProc, hwnd, uMsg, wParam, lParam);
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

		ID3D10Device* device = nullptr;
		if (FAILED(SwapChain->GetDevice(IID_PPV_ARGS(&device))))
		{
			return DxgiPresent(SwapChain, SyncInterval, Flags);
		}
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(swapchainDesc.OutputWindow);
		ImGui_ImplDX10_Init(device);

		initialized = TRUE;
	}

	ImGui_ImplDX10_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX10_RenderDrawData(ImGui::GetDrawData());

	return DxgiPresent(SwapChain, SyncInterval, Flags);
}
static void STDMETHODCALLTYPE MyDraw(ID3D10Device* Device, UINT VertexCount, UINT StartVertexLocation)
{
	static BOOL called = FALSE;
	if (!called)
	{
		MessageBoxA(0, "Called MyDraw!", "DirectHook", MB_OK);
		called = TRUE;
	}
	D3D10Draw(Device, VertexCount, StartVertexLocation);
}

INT D3D10HookThread()
{
	if (DH_Status dh = DH_Initialize(); dh == DH_Status::Success)
	{
		Hook(d3d10::Device_Draw, D3D10Draw, MyDraw);
		Hook(d3d10::SwapChain_Present, DxgiPresent, MyPresent);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)D3D10HookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}







