#include <vector>
#include "MinHook.h"

#include "directhook.h"
#include "method_table.h"

#if DH_USE_D3D9
#include "D3D9/d3d9hook.h"
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

	DHStatus Initialize()
	{
#if DH_USE_D3D9
		DHStatus status = d3d9::Initialize(gMethodTable);
		if (status != DHStatus::Success)
		{
			return status;
		}
#elif DH_USE_D3D11
		DHStatus status = d3d11::Initialize(gMethodTable);
		if (status != DHStatus::Success)
		{
			return status;
		}
#elif DH_USE_D3D12
		DHStatus status = d3d12::Initialize(gMethodTable);
		if (status != DHStatus::Success)
		{
			return status;
		}
#endif
		
		MH_STATUS mhStatus = MH_Initialize();
		if (mhStatus != MH_OK)
		{
			return DHStatus::Error_MHInitFailed;
		}
		gInitialized = true;
		return DHStatus::Success;
	}

	void Shutdown()
	{
		if (gInitialized)
		{
			MH_DisableHook(MH_ALL_HOOKS);
		}
	}

	DHStatus Hook(uint16 index, void** original, void* function)
	{
		DH_ASSERT(original != nullptr && function != nullptr);

		if (gInitialized)
		{
			void* target = gMethodTable[index];
			if (MH_CreateHook(target, function, original) != MH_OK)
			{
				return DHStatus::Error_MHHookingFailed;
			}
			if (MH_EnableHook(target) != MH_OK)
			{
				return DHStatus::Error_MHEnableHookFailed;
			}
			return DHStatus::Success;
		}
		return DHStatus::Error_NoAPI;
	}

	DHStatus Unhook(uint16 index)
	{
		if (gInitialized)
		{
			MH_STATUS mhStatus = MH_DisableHook(gMethodTable[index]);
			if (mhStatus != MH_OK)
			{
				return DHStatus::Error_MHHookingFailed;
			}
			return DHStatus::Success;
		}
		return DHStatus::Error_NoAPI;
	}

	void* GetOriginal(uint16 index)
	{
		return gMethodTable[index];
	}

}