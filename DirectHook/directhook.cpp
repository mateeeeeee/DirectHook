#include "MinHook/include/MinHook.h"
#include <cassert>

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

static BOOL g_bInitialized = FALSE;
static BOOL g_bOwnsMinHook = FALSE;
static DH_METHOD_TABLE g_MethodTable;

extern "C" {

DH_STATUS WINAPI DH_Initialize(VOID)
{
	if (g_bInitialized)
	{
		return DH_STATUS_ERROR_DH_ALREADY_INITIALIZED;
	}
	DH_MethodTableInit(&g_MethodTable);
	DH_STATUS status = DH_STATUS_ERROR_NO_GFX_API;
#if DH_USE_D3D9
	status = DH_D3D9_Initialize(&g_MethodTable);
#elif DH_USE_D3D10
	status = DH_D3D10_Initialize(&g_MethodTable);
#elif DH_USE_D3D11
	status = DH_D3D11_Initialize(&g_MethodTable);
#elif DH_USE_D3D12
	status = DH_D3D12_Initialize(&g_MethodTable);
#elif DH_USE_DDRAW
	status = DH_DDRAW_Initialize(&g_MethodTable);
#endif
	if (status != DH_STATUS_SUCCESS)
	{
		DH_MethodTableFree(&g_MethodTable);
		return status;
	}

	MH_STATUS mhStatus = MH_Initialize();
	if (mhStatus == MH_OK)
	{
		g_bOwnsMinHook = TRUE;
	}
	else if (mhStatus != MH_ERROR_ALREADY_INITIALIZED)
	{
		DH_MethodTableFree(&g_MethodTable);
		return DH_STATUS_ERROR_MIN_HOOK_INIT_FAILED;
	}

	g_bInitialized = TRUE;
	return DH_STATUS_SUCCESS;
}

VOID WINAPI DH_Shutdown(VOID)
{
	if (!g_bInitialized)
	{
		return;
	}

	MH_DisableHook(MH_ALL_HOOKS);
	for (UINT i = 0; i < g_MethodTable.cMethods; ++i)
	{
		LPVOID lpTarget = g_MethodTable.lpMethods[i];
		if (lpTarget != nullptr)
		{
			MH_RemoveHook(lpTarget);
		}
	}

	if (g_bOwnsMinHook)
	{
		MH_Uninitialize();
		g_bOwnsMinHook = FALSE;
	}

	DH_MethodTableFree(&g_MethodTable);
	g_bInitialized = FALSE;
}

DH_STATUS WINAPI DH_Hook(UINT uIndex, LPVOID* lpOriginal, LPVOID lpFunction)
{
	assert(lpOriginal != nullptr && lpFunction != nullptr);

	if (!g_bInitialized)
	{
		return DH_STATUS_ERROR_NO_GFX_API;
	}
	if (!DH_MethodTableIsValidIndex(&g_MethodTable, uIndex))
	{
		return DH_STATUS_ERROR_MIN_HOOK_FAILED;
	}

	LPVOID lpTarget = DH_MethodTableGet(&g_MethodTable, uIndex);
	if (MH_CreateHook(lpTarget, lpFunction, lpOriginal) != MH_OK)
	{
		return DH_STATUS_ERROR_MIN_HOOK_FAILED;
	}
	if (MH_EnableHook(lpTarget) != MH_OK)
	{
		return DH_STATUS_ERROR_MIN_HOOK_ENABLE_FAILED;
	}
	return DH_STATUS_SUCCESS;
}

DH_STATUS WINAPI DH_Unhook(UINT uIndex)
{
	if (!g_bInitialized)
	{
		return DH_STATUS_ERROR_NO_GFX_API;
	}
	if (!DH_MethodTableIsValidIndex(&g_MethodTable, uIndex))
	{
		return DH_STATUS_ERROR_MIN_HOOK_FAILED;
	}

	if (MH_DisableHook(DH_MethodTableGet(&g_MethodTable, uIndex)) != MH_OK)
	{
		return DH_STATUS_ERROR_MIN_HOOK_FAILED;
	}
	return DH_STATUS_SUCCESS;
}

LPVOID WINAPI DH_GetOriginal(UINT uIndex)
{
	if (!DH_MethodTableIsValidIndex(&g_MethodTable, uIndex))
	{
		return nullptr;
	}
	return DH_MethodTableGet(&g_MethodTable, uIndex);
}

DH_STATUS WINAPI DH_HookFunction(LPVOID lpTarget, LPVOID* lpOriginal, LPVOID lpFunction)
{
	assert(lpTarget != nullptr && lpOriginal != nullptr && lpFunction != nullptr);

	if (!g_bInitialized)
	{
		return DH_STATUS_ERROR_NO_GFX_API;
	}
	if (MH_CreateHook(lpTarget, lpFunction, lpOriginal) != MH_OK)
	{
		return DH_STATUS_ERROR_MIN_HOOK_FAILED;
	}
	if (MH_EnableHook(lpTarget) != MH_OK)
	{
		return DH_STATUS_ERROR_MIN_HOOK_ENABLE_FAILED;
	}
	return DH_STATUS_SUCCESS;
}

DH_STATUS WINAPI DH_UnhookFunction(LPVOID lpTarget)
{
	if (!g_bInitialized)
	{
		return DH_STATUS_ERROR_NO_GFX_API;
	}
	if (MH_DisableHook(lpTarget) != MH_OK)
	{
		return DH_STATUS_ERROR_MIN_HOOK_FAILED;
	}
	MH_RemoveHook(lpTarget);
	return DH_STATUS_SUCCESS;
}

} // extern "C"
