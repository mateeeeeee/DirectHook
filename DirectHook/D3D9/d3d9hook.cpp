#include <dxgi.h>
#include <d3d9.h>
#include "d3d9hook.h"
#include "../method_table.h"

namespace directhook::d3d9
{
	DHStatus Initialize(MethodTable& methodTable)
	{
		WNDCLASSEXA windowClass;
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
		windowClass.lpszClassName = "DirectHook";
		windowClass.hIconSm = nullptr;

		::RegisterClassExA(&windowClass);
		HWND window = ::CreateWindowA(windowClass.lpszClassName, "Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, windowClass.hInstance, nullptr);

		HMODULE libD3D9 = ::GetModuleHandleA("d3d9.dll");
		if (libD3D9 == nullptr)
		{
			::DestroyWindow(window);
			::UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
			return DHStatus::Error_APIInitFailed;
		}

		void* Direct3DCreate9;
		if ((Direct3DCreate9 = ::GetProcAddress(libD3D9, "Direct3DCreate9")) == NULL)
		{
			::DestroyWindow(window);
			::UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
			return DHStatus::Error_APIInitFailed;
		}

		LPDIRECT3D9 direct3D9;
		if ((direct3D9 = ((LPDIRECT3D9(__stdcall*)(uint32_t))(Direct3DCreate9))(D3D_SDK_VERSION)) == NULL)
		{
			::DestroyWindow(window);
			::UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
			return DHStatus::Error_APIInitFailed;
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
			::UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
			return DHStatus::Error_APIInitFailed;
		}
		methodTable.AddVTableEntries(device, DEVICE_ENTRIES);
		return DHStatus::Success;
	}

}

