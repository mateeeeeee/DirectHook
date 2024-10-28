#pragma once
#include <cstdint>
#include <cassert>

#define DH_ASSERT(cond) assert(cond)
#define DH_ASSERT_MSG(cond, msg) assert(cond && msg)

#ifndef DH_USE_DDRAW
#define DH_USE_DDRAW  0
#endif

#ifndef DH_USE_D3D7
#define DH_USE_D3D7  0
#endif

#ifndef DH_USE_D3D8
#define DH_USE_D3D8  0
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

namespace directhook
{
	using uint8		= std::uint8_t;
	using uint16	= std::uint16_t;
	using uint32	= std::uint32_t;
	using uint64	= std::uint64_t;
	using int8		= std::int8_t;
	using int16		= std::int16_t;
	using int32		= std::int32_t;
	using int64		= std::int64_t;
#ifdef _X86_
	using address_t = uint32;
#else
	using address_t = uint64;
#endif

	enum class DHStatus : uint8
	{
		Success,
		Error_MHInitFailed,
		Error_APIInitFailed,
		Error_AlreadyInitialized,
		Error_MHHookingFailed,
		Error_MHEnableHookFailed,
		Error_NoAPI,
	};

	DHStatus Initialize();
	void Shutdown();

	DHStatus Hook(uint16 index, void** original, void* function);
	DHStatus Unhook(uint16 index);
	void* GetOriginal(uint16 index);


	template<typename PFN>
	DHStatus HookT(uint16 index, PFN original, void* function)
	{
		return Hook(index, (void**)&original, function);
	}

	template<typename PFN>
	PFN GetOriginalT(uint16 index)
	{
		return (PFN)GetOriginal(index);
	}
}
