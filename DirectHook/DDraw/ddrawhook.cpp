#define DIRECTDRAW_VERSION 0x0700
#include <ddraw.h>
#include "ddrawhook.h"
#include "../method_table.h"

#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dxguid.lib")

namespace directhook::ddraw
{
	#define WINDOW_CLASS_NAME L"DirectDraw"
	#define WINDOW_TITLE_NAME L"DirectDraw"

	Status Initialize(MethodTable& methodTable)
	{
		WNDCLASS wc{};
		wc.lpfnWndProc = DefWindowProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszClassName = WINDOW_CLASS_NAME;

		if (!RegisterClass(&wc)) { return Status::Error_GfxApiInitFailed; }

		HWND hwnd = CreateWindow(
			wc.lpszClassName,
			WINDOW_TITLE_NAME,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, NULL, NULL, wc.hInstance, NULL);

		if (hwnd == nullptr) 
		{ 
			UnregisterClass(WINDOW_CLASS_NAME, wc.hInstance); return Status::Error_GfxApiInitFailed; 
		}

		IDirectDraw7* Instance = NULL;
		if (DirectDrawCreateEx(NULL, (void**)&Instance, IID_IDirectDraw7, NULL) != DD_OK)
		{
			DestroyWindow(hwnd);
			UnregisterClass(WINDOW_CLASS_NAME, wc.hInstance);
			return Status::Error_GfxApiInitFailed;
		}
		Instance->SetCooperativeLevel(hwnd, DDSCL_NORMAL);

		IDirectDrawSurface7* Main = NULL;
		DDSURFACEDESC2 desc;
		ZeroMemory(&desc, sizeof(DDSURFACEDESC2));
		desc.dwSize = sizeof(DDSURFACEDESC2);
		desc.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
		desc.dwWidth = 100;
		desc.dwHeight = 100;
		desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

		if (HRESULT hr = Instance->CreateSurface(&desc, &Main, NULL); hr != DD_OK)
		{
			Instance->Release();
			DestroyWindow(hwnd);
			UnregisterClass(WINDOW_CLASS_NAME, wc.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		IDirectDrawClipper* Clipper = NULL;
		if (Instance->CreateClipper(0, &Clipper, NULL) != DD_OK)
		{
			Instance->Release();
			Main->Release();
			DestroyWindow(hwnd);
			UnregisterClass(WINDOW_CLASS_NAME, wc.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		methodTable.AddEntries(Instance, DEVICE_ENTRIES);
		methodTable.AddEntries(Main, SURFACE_ENTRIES);
		methodTable.AddEntries(Clipper, CLIPPER_ENTRIES);

		return Status::Success;
	}

}

