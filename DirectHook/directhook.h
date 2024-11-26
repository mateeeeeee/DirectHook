#pragma once
#include <cstdint>
#include <cassert>

#define DH_ASSERT(cond) assert(cond)
#define DH_ASSERT_MSG(cond, msg) assert(cond && msg)

#ifndef DH_USE_DDRAW
#define DH_USE_DDRAW  0
#endif

#ifndef DH_USE_D3D9
#define DH_USE_D3D9  0
#endif

#ifndef DH_USE_D3D10
#define DH_USE_D3D10  0
#endif

#ifndef DH_USE_D3D11
#define DH_USE_D3D11  0
#endif

#ifndef DH_USE_D3D12
#define DH_USE_D3D12  0
#endif

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

namespace directhook
{
	using Uint8		= std::uint8_t;
	using Uint16	= std::uint16_t;
	using Uint32	= std::uint32_t;
	using Uint64	= std::uint64_t;
	using Int8		= std::int8_t;
	using Int16		= std::int16_t;
	using Int32		= std::int32_t;
	using Int64		= std::int64_t;

	enum class DH_Status : Uint8
	{
		Success,
		Error_MinHookInitFailed,
		Error_GfxApiInitFailed,
		Error_DHAlreadyInitialized,
		Error_MinHookFailed,
		Error_MinHookEnableFailed,
		Error_NoGfxApi,
	};

	DH_Status	DH_Initialize();
	void	DH_Shutdown();

	DH_Status Hook(Uint16 index, void** original, void* function);
	DH_Status Unhook(Uint16 index);
	void* GetOriginal(Uint16 index);

	template<typename FuncT>
	DH_Status Hook(Uint16 index, FuncT*& original, FuncT& function)
	{
		return Hook(index, (void**)&original, (void*)function);
	}

	template<typename FuncT>
	void SaveOriginal(Uint16 index, FuncT& F)
	{
		F = (FuncT)GetOriginal(index);
	}
}
