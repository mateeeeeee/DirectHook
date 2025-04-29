#include <vector>
#include "MinHook/include/MinHook.h"

#include "directhook.h"
#include "method_table.h"

#if DH_USE_DDRAW
#include "DDraw/ddrawhook.h"
#endif
#if DH_USE_D3D9
#include "D3D9/d3d9hook.h"
#endif
#if DH_USE_D3D10
#include "D3D10/d3d10hook.h"
#endif
#if DH_USE_D3D11
#include "D3D11/d3d11hook.h"
#endif
#if DH_USE_D3D12
#include "D3D12/d3d12hook.h"
#endif

namespace directhook
{
	namespace
	{
		bool gInitialized = false;
		MethodTable gMethodTable;
	}

	DH_Status DH_Initialize()
	{
		DH_Status status = DH_Status::Error_NoGfxApi;
#if DH_USE_D3D9
		status = d3d9::Initialize(gMethodTable);
		if (status != DH_Status::Success)
		{
			return status;
		}
#elif DH_USE_D3D10
		status = d3d10::Initialize(gMethodTable);
		if (status != DH_Status::Success)
		{
			return status;
		}
#elif DH_USE_D3D11
		status = d3d11::Initialize(gMethodTable);
		if (status != DH_Status::Success)
		{
			return status;
		}
#elif DH_USE_D3D12
		status = d3d12::Initialize(gMethodTable);
		if (status != DH_Status::Success)
		{
			return status;
		}
#elif DH_USE_DDRAW
		status = ddraw::Initialize(gMethodTable);
		if (status != DH_Status::Success)
		{
			return status;
		}
#endif
		if (status == DH_Status::Error_NoGfxApi)
		{
			return status;
		}
		
		MH_STATUS mhStatus = MH_Initialize();
		if (mhStatus != MH_OK)
		{
			return DH_Status::Error_MinHookInitFailed;
		}
		gInitialized = true;
		return DH_Status::Success;
	}

	void DH_Shutdown()
	{
		if (gInitialized)
		{
			MH_DisableHook(MH_ALL_HOOKS);
		}
	}

	DH_Status Hook(unsigned int index, void** original, void* function)
	{
		DH_ASSERT(original != nullptr && function != nullptr);

		if (gInitialized)
		{
			void* target = gMethodTable[index];
			if (MH_CreateHook(target, function, original) != MH_OK)
			{
				return DH_Status::Error_MinHookFailed;
			}
			if (MH_EnableHook(target) != MH_OK)
			{
				return DH_Status::Error_MinHookEnableFailed;
			}
			return DH_Status::Success;
		}
		return DH_Status::Error_NoGfxApi;
	}

	DH_Status Unhook(unsigned int index)
	{
		if (gInitialized)
		{
			MH_STATUS mhStatus = MH_DisableHook(gMethodTable[index]);
			if (mhStatus != MH_OK)
			{
				return DH_Status::Error_MinHookFailed;
			}
			return DH_Status::Success;
		}
		return DH_Status::Error_NoGfxApi;
	}

	void* GetOriginal(unsigned int index)
	{
		return gMethodTable[index];
	}

}