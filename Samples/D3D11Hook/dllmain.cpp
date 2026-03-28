#include "directhook.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

static PFN_D3D11_DeviceContext_Draw    g_pfnD3D11Draw = nullptr;
static PFN_D3D11_DXGISwapChain_Present g_pfnDxgiPresent = nullptr;
static WNDPROC g_pfnWin32WndProc = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam) > 0)
	{
		return 1L;
	}
	return ::CallWindowProcA(g_pfnWin32WndProc, hwnd, uMsg, wParam, lParam);
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

		ID3D11Device* pDevice = nullptr;
		if (FAILED(pSwapChain->GetDevice(IID_PPV_ARGS(&pDevice))))
		{
			InterlockedExchange(&initStatus, 0);
			return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
		}
		ID3D11DeviceContext* pContext = nullptr;
		pDevice->GetImmediateContext(&pContext);

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(swapchainDesc.OutputWindow);
		ImGui_ImplDX11_Init(pDevice, pContext);

		pContext->Release();
		pDevice->Release();
		InterlockedExchange(&initStatus, 2);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return g_pfnDxgiPresent(pSwapChain, SyncInterval, Flags);
}

static void STDMETHODCALLTYPE MyDraw(ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation)
{
	static BOOL bCalled = FALSE;
	if (!bCalled)
	{
		MessageBoxA(0, "Called MyDraw!", "DirectHook", MB_OK);
		bCalled = TRUE;
	}
	g_pfnD3D11Draw(pContext, VertexCount, StartVertexLocation);
}

INT D3D11HookThread()
{
	if (DH_Initialize() == DH_STATUS_SUCCESS)
	{
		DH_Hook(D3D11_Context_Draw, g_pfnD3D11Draw, MyDraw);
		DH_Hook(D3D11_SwapChain_Present, g_pfnDxgiPresent, MyPresent);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)D3D11HookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}
