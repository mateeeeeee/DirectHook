#define DIRECTDRAW_VERSION 0x0700
#include <ddraw.h>
#include "ddrawhook.h"

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

#define WINDOW_CLASS_NAME L"DirectHook_DDraw"
#define WINDOW_TITLE_NAME L"DirectHook_DDraw"

DH_STATUS WINAPI DH_DDRAW_Initialize(PDH_METHOD_TABLE pTable)
{
	WNDCLASS wc{};
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = WINDOW_CLASS_NAME;

	if (!RegisterClass(&wc))
	{
		return DH_STATUS_ERROR_GFX_API_INIT_FAILED;
	}

	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		WINDOW_TITLE_NAME,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, NULL, NULL, wc.hInstance, NULL);

	if (hwnd == nullptr)
	{
		UnregisterClass(WINDOW_CLASS_NAME, wc.hInstance);
		return DH_STATUS_ERROR_GFX_API_INIT_FAILED;
	}

	IDirectDraw7* pInstance = NULL;
	IDirectDrawSurface7* pSurface = NULL;
	IDirectDrawClipper* pClipper = NULL;
	DH_STATUS status = DH_STATUS_ERROR_GFX_API_INIT_FAILED;

	if (DirectDrawCreateEx(NULL, (LPVOID*)&pInstance, IID_IDirectDraw7, NULL) != DD_OK)
	{
		goto cleanup;
	}
	pInstance->SetCooperativeLevel(hwnd, DDSCL_NORMAL);

	{
		DDSURFACEDESC2 desc;
		ZeroMemory(&desc, sizeof(DDSURFACEDESC2));
		desc.dwSize = sizeof(DDSURFACEDESC2);
		desc.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
		desc.dwWidth = 100;
		desc.dwHeight = 100;
		desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

		if (pInstance->CreateSurface(&desc, &pSurface, NULL) != DD_OK)
		{
			goto cleanup;
		}

		if (pInstance->CreateClipper(0, &pClipper, NULL) != DD_OK)
		{
			goto cleanup;
		}

		DH_MethodTableAddEntries(pTable, pInstance, DDRAW_DEVICE_ENTRIES);
		DH_MethodTableAddEntries(pTable, pSurface, DDRAW_SURFACE_ENTRIES);
		DH_MethodTableAddEntries(pTable, pClipper, DDRAW_CLIPPER_ENTRIES);

		status = DH_STATUS_SUCCESS;
	}

cleanup:
	if (pClipper) pClipper->Release();
	if (pSurface) pSurface->Release();
	if (pInstance) pInstance->Release();
	DestroyWindow(hwnd);
	UnregisterClass(WINDOW_CLASS_NAME, wc.hInstance);
	return status;
}
