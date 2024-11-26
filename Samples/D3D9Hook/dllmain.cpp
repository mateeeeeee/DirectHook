#include "directhook.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

using namespace directhook;

static d3d9::PFN_D3D9Device_DrawPrimitive	D3D9DrawPrimitive = nullptr;
static d3d9::PFN_D3D9Device_Present			D3D9Present = nullptr;
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

static HRESULT STDMETHODCALLTYPE MyPresent(IDirect3DDevice9* Device, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	static BOOL initialized = FALSE;
	if (!initialized)
	{
		D3DDEVICE_CREATION_PARAMETERS creationParams;
		Device->GetCreationParameters(&creationParams);

		Win32WndProc = (WNDPROC)::SetWindowLongPtr(creationParams.hFocusWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(MyWindowProc));

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(creationParams.hFocusWindow);
		ImGui_ImplDX9_Init(Device);

		initialized = TRUE;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return D3D9Present(Device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
static HRESULT STDMETHODCALLTYPE MyDrawPrimitive(IDirect3DDevice9* Device, D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	static BOOL called = FALSE;
	if (!called)
	{
		MessageBoxA(0, "Called MyDrawPrimitive!", "DirectHook", MB_OK);
		called = TRUE;
	}
	return D3D9DrawPrimitive(Device, PrimitiveType, StartVertex, PrimitiveCount);
}

INT D3D9HookThread()
{
	if (DH_Status dh = DH_Initialize(); dh == DH_Status::Success)
	{
		Hook(d3d9::Device_DrawPrimitive, D3D9DrawPrimitive, MyDrawPrimitive);
		Hook(d3d9::Device_Present, D3D9Present, MyPresent);
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


