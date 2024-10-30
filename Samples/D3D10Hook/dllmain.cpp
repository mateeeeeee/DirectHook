#include "directhook.h"
#include "ImGui/imgui_impl_dx10.h"
#include "ImGui/imgui_impl_win32.h"

using namespace directhook;

static d3d10::PFN_D3D10Device_Draw		  d3d10Draw = nullptr;
static d3d10::PFN_DXGISwapChain_Present   DxgiPresent = nullptr;
static WNDPROC Win32WndProc = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MyWindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam) > 0)
	{
		return 1L;
	}
	return ::CallWindowProcA(Win32WndProc, hwnd, uMsg, wParam, lParam);
}

HRESULT STDMETHODCALLTYPE MyPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)
{
	static bool initialized = false;
	if (!initialized)
	{
		ImGui::CreateContext();

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

		ImGui_ImplWin32_Init(swapchainDesc.OutputWindow);
		ImGui_ImplDX10_Init(device);

		initialized = true;
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

void STDMETHODCALLTYPE MyDraw(ID3D10Device* Device, UINT VertexCount, UINT StartVertexLocation)
{
	static bool called = false;
	if (!called)
	{
		MessageBoxA(0, "Called MyDraw!", "DirectHook", MB_OK);
		called = true;
	}
	d3d10Draw(Device, VertexCount, StartVertexLocation);
}

int D3D10HookThread()
{
	if (Status dh = Initialize(); dh == Status::Success)
	{
		Hook(d3d10::Device_Draw, d3d10Draw, MyDraw);
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







