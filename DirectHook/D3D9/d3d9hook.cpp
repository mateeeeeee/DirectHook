#include <dxgi.h>
#include <d3d9.h>
#include "d3d9hook.h"
#include "../method_table.h"

namespace directhook::d3d9
{
	using PFN_Direct3DCreate9 = IDirect3D9*(*)(UINT);

	Status Initialize(MethodTable& methodTable)
	{
		WNDCLASSEX windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = DefWindowProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(nullptr);
		windowClass.hIcon = nullptr;
		windowClass.hCursor = nullptr;
		windowClass.hbrBackground = nullptr;
		windowClass.lpszMenuName = nullptr;
		windowClass.lpszClassName = L"DirectHook";
		windowClass.hIconSm = nullptr;

		::RegisterClassEx(&windowClass);
		HWND window = ::CreateWindow(windowClass.lpszClassName, L"Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, windowClass.hInstance, nullptr);

		HMODULE libD3D9 = ::GetModuleHandle(L"d3d9.dll");
		if (libD3D9 == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		PFN_Direct3DCreate9 Direct3DCreate9 = (PFN_Direct3DCreate9)::GetProcAddress(libD3D9, "Direct3DCreate9");
		if (Direct3DCreate9 == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		LPDIRECT3D9 direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
		if (direct3D9 == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}

		D3DPRESENT_PARAMETERS params;
		params.BackBufferWidth = 0;
		params.BackBufferHeight = 0;
		params.BackBufferFormat = D3DFMT_UNKNOWN;
		params.BackBufferCount = 0;
		params.MultiSampleType = D3DMULTISAMPLE_NONE;
		params.MultiSampleQuality = NULL;
		params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		params.hDeviceWindow = window;
		params.Windowed = 1;
		params.EnableAutoDepthStencil = 0;
		params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
		params.Flags = NULL;
		params.FullScreen_RefreshRateInHz = 0;
		params.PresentationInterval = 0;

		LPDIRECT3DDEVICE9 device = nullptr;
		if (direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, window, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &device) < 0)
		{
			direct3D9->Release();
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::Error_GfxApiInitFailed;
		}
		methodTable.AddEntries(device, DEVICE_ENTRIES);

		device->Release();
		device = nullptr;

		direct3D9->Release();
		direct3D9 = nullptr;

		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);

		return Status::Success;
	}

}

