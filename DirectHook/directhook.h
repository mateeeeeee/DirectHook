#pragma once
#include <windows.h>

#if DH_USE_DDRAW
#include "DDraw/ddrawhook_aliases.h"
#include "DDraw/ddrawhook_indices.h"
#endif

#if DH_USE_D3D9
#include "D3D9/d3d9hook_aliases.h"
#include "D3D9/d3d9hook_indices.h"
#endif

#if DH_USE_D3D10
#include "D3D10/d3d10hook_aliases.h"
#include "D3D10/d3d10hook_indices.h"
#endif

#if DH_USE_D3D11
#include "D3D11/d3d11hook_aliases.h"
#include "D3D11/d3d11hook_indices.h"
#endif

#if DH_USE_D3D12
#include "D3D12/d3d12hook_aliases.h"
#include "D3D12/d3d12hook_indices.h"
#endif

typedef enum DH_STATUS
{
	DH_STATUS_SUCCESS = 0,
	DH_STATUS_ERROR_MIN_HOOK_INIT_FAILED,
	DH_STATUS_ERROR_GFX_API_INIT_FAILED,
	DH_STATUS_ERROR_DH_ALREADY_INITIALIZED,
	DH_STATUS_ERROR_MIN_HOOK_FAILED,
	DH_STATUS_ERROR_MIN_HOOK_ENABLE_FAILED,
	DH_STATUS_ERROR_NO_GFX_API,
} DH_STATUS;

#ifdef __cplusplus
extern "C" {
#endif

DH_STATUS WINAPI DH_Initialize(VOID);
VOID      WINAPI DH_Shutdown(VOID);

DH_STATUS WINAPI DH_Hook(UINT uIndex, LPVOID* lpOriginal, LPVOID lpFunction);
DH_STATUS WINAPI DH_Unhook(UINT uIndex);
LPVOID    WINAPI DH_GetOriginal(UINT uIndex);

DH_STATUS WINAPI DH_HookFunction(LPVOID lpTarget, LPVOID* lpOriginal, LPVOID lpFunction);
DH_STATUS WINAPI DH_UnhookFunction(LPVOID lpTarget);

#ifdef __cplusplus
} // extern "C"

template<typename FuncT>
inline DH_STATUS DH_Hook(UINT uIndex, FuncT*& lpOriginal, FuncT& lpFunction)
{
	return DH_Hook(uIndex, (LPVOID*)&lpOriginal, (LPVOID)lpFunction);
}

template<typename FuncT>
inline VOID DH_SaveOriginal(UINT uIndex, FuncT& F)
{
	F = (FuncT)DH_GetOriginal(uIndex);
}

template<typename FuncT>
inline DH_STATUS DH_HookFunction(FuncT* lpTarget, FuncT*& lpOriginal, FuncT& lpFunction)
{
	return DH_HookFunction((LPVOID)lpTarget, (LPVOID*)&lpOriginal, (LPVOID)lpFunction);
}

#endif
