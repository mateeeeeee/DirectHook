#include "directhook.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

static PFN_D3D9_Device_DrawPrimitive g_pfnD3D9DrawPrimitive = nullptr;
static PFN_D3D9_Device_Present       g_pfnD3D9Present = nullptr;
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

static HRESULT STDMETHODCALLTYPE MyPresent(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	static LONG initStatus = 0;
	LONG prev = InterlockedCompareExchange(&initStatus, 1, 0);
	if (prev == 1)
	{
		return g_pfnD3D9Present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	}
	if (prev == 0)
	{
		D3DDEVICE_CREATION_PARAMETERS creationParams;
		pDevice->GetCreationParameters(&creationParams);

		g_pfnWin32WndProc = (WNDPROC)::SetWindowLongPtr(creationParams.hFocusWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(MyWindowProc));

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(creationParams.hFocusWindow);
		ImGui_ImplDX9_Init(pDevice);

		InterlockedExchange(&initStatus, 2);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return g_pfnD3D9Present(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

static HRESULT STDMETHODCALLTYPE MyDrawPrimitive(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	static BOOL bCalled = FALSE;
	if (!bCalled)
	{
		MessageBoxA(0, "Called MyDrawPrimitive!", "DirectHook", MB_OK);
		bCalled = TRUE;
	}
	return g_pfnD3D9DrawPrimitive(pDevice, PrimitiveType, StartVertex, PrimitiveCount);
}

INT D3D9HookThread()
{
	if (DH_Initialize() == DH_STATUS_SUCCESS)
	{
		DH_Hook(D3D9_Device_DrawPrimitive, g_pfnD3D9DrawPrimitive, MyDrawPrimitive);
		DH_Hook(D3D9_Device_Present, g_pfnD3D9Present, MyPresent);
	}
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID)
{
	DisableThreadLibraryCalls(hInstance);
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)D3D9HookThread, NULL, 0, NULL);
		break;
	}
	return TRUE;
}
