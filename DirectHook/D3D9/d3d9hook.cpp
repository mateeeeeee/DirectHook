#include <d3d9.h>
#include "d3d9hook.h"

using PFN_Direct3DCreate9 = IDirect3D9*(WINAPI*)(UINT);

DH_STATUS WINAPI DH_D3D9_Initialize(PDH_METHOD_TABLE pTable)
{
	WNDCLASSEX windowClass{};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.hInstance = GetModuleHandle(nullptr);
	windowClass.lpszClassName = L"DirectHook_D3D9";

	::RegisterClassEx(&windowClass);
	HWND hWnd = ::CreateWindow(windowClass.lpszClassName, L"Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, windowClass.hInstance, nullptr);
	if (hWnd == nullptr)
	{
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return DH_STATUS_ERROR_GFX_API_INIT_FAILED;
	}

	LPDIRECT3D9 pDirect3D9 = nullptr;
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	DH_STATUS status = DH_STATUS_ERROR_GFX_API_INIT_FAILED;

	HMODULE hLibD3D9 = ::GetModuleHandle(L"d3d9.dll");
	if (hLibD3D9 == nullptr)
	{
		goto cleanup;
	}

	{
		PFN_Direct3DCreate9 pfnDirect3DCreate9 = (PFN_Direct3DCreate9)::GetProcAddress(hLibD3D9, "Direct3DCreate9");
		if (pfnDirect3DCreate9 == nullptr)
		{
			goto cleanup;
		}

		pDirect3D9 = pfnDirect3DCreate9(D3D_SDK_VERSION);
		if (pDirect3D9 == nullptr)
		{
			goto cleanup;
		}

		D3DPRESENT_PARAMETERS params{};
		params.BackBufferFormat = D3DFMT_UNKNOWN;
		params.MultiSampleType = D3DMULTISAMPLE_NONE;
		params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		params.hDeviceWindow = hWnd;
		params.Windowed = 1;
		params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;

		if (FAILED(pDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &pDevice)))
		{
			goto cleanup;
		}

		DH_MethodTableAddEntries(pTable, pDevice, D3D9_DEVICE_ENTRIES);
		status = DH_STATUS_SUCCESS;
	}

cleanup:
	if (pDevice) pDevice->Release();
	if (pDirect3D9) pDirect3D9->Release();
	::DestroyWindow(hWnd);
	::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
	return status;
}
