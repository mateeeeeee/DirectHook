#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>

namespace directhook::d3d12
{
	using PFN_D3D12Device_QueryInterface = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, REFIID, void**);
	using PFN_D3D12Device_AddRef = ULONG(*)(ID3D12Device*);
	using PFN_D3D12Device_Release = ULONG(*)(ID3D12Device*);
	using PFN_D3D12Device_GetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, REFGUID, UINT*, void*);
	using PFN_D3D12Device_SetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, REFGUID, UINT, const void*);
	using PFN_D3D12Device_SetPrivateDataInterface = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, REFGUID, const IUnknown*);
	using PFN_D3D12Device_SetName = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, LPCWSTR);
	using PFN_D3D12Device_GetNodeCount = UINT(STDMETHODCALLTYPE*)(ID3D12Device*);
	using PFN_D3D12Device_CreateCommandQueue = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_COMMAND_QUEUE_DESC*, REFIID, void**);
	using PFN_D3D12Device_CreateCommandAllocator = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, D3D12_COMMAND_LIST_TYPE, REFIID, void**);
	using PFN_D3D12Device_CreateGraphicsPipelineState = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_GRAPHICS_PIPELINE_STATE_DESC*, REFIID, void**);
	using PFN_D3D12Device_CreateComputePipelineState = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_COMPUTE_PIPELINE_STATE_DESC*, REFIID, void**);
	using PFN_D3D12Device_CreateCommandList = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, UINT, D3D12_COMMAND_LIST_TYPE, ID3D12CommandAllocator*, ID3D12PipelineState*, REFIID, void**);
	using PFN_D3D12Device_CheckFeatureSupport = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, D3D12_FEATURE, void*, UINT);
	using PFN_D3D12Device_CreateDescriptorHeap = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_DESCRIPTOR_HEAP_DESC*, REFIID, void**);
	using PFN_D3D12Device_GetDescriptorHandleIncrementSize = UINT(*)(ID3D12Device*, D3D12_DESCRIPTOR_HEAP_TYPE);
	using PFN_D3D12Device_CreateRootSignature = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, UINT, const void*, SIZE_T, REFIID, void**);
	using PFN_D3D12Device_CreateConstantBufferView = void(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_CONSTANT_BUFFER_VIEW_DESC*, D3D12_CPU_DESCRIPTOR_HANDLE);
	using PFN_D3D12Device_CreateShaderResourceView = void(STDMETHODCALLTYPE*)(ID3D12Device*, ID3D12Resource*, const D3D12_SHADER_RESOURCE_VIEW_DESC*, D3D12_CPU_DESCRIPTOR_HANDLE);
	using PFN_D3D12Device_CreateUnorderedAccessView = void(STDMETHODCALLTYPE*)(ID3D12Device*, ID3D12Resource*, ID3D12Resource*, const D3D12_UNORDERED_ACCESS_VIEW_DESC*, D3D12_CPU_DESCRIPTOR_HANDLE);
	using PFN_D3D12Device_CreateRenderTargetView = void(STDMETHODCALLTYPE*)(ID3D12Device*, ID3D12Resource*, const D3D12_RENDER_TARGET_VIEW_DESC*, D3D12_CPU_DESCRIPTOR_HANDLE);
	using PFN_D3D12Device_CreateDepthStencilView = void(STDMETHODCALLTYPE*)(ID3D12Device*, ID3D12Resource*, const D3D12_DEPTH_STENCIL_VIEW_DESC*, D3D12_CPU_DESCRIPTOR_HANDLE);
	using PFN_D3D12Device_CreateSampler = void(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_SAMPLER_DESC*, D3D12_CPU_DESCRIPTOR_HANDLE);
	using PFN_D3D12Device_CopyDescriptors = void(STDMETHODCALLTYPE*)(ID3D12Device*, UINT, const D3D12_CPU_DESCRIPTOR_HANDLE*, UINT, const D3D12_CPU_DESCRIPTOR_HANDLE*, UINT, D3D12_DESCRIPTOR_HEAP_TYPE);
	using PFN_D3D12Device_CopyDescriptorsSimple = void(STDMETHODCALLTYPE*)(ID3D12Device*, UINT, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_CPU_DESCRIPTOR_HANDLE, D3D12_DESCRIPTOR_HEAP_TYPE);
	using PFN_D3D12Device_GetResourceAllocationInfo = D3D12_RESOURCE_ALLOCATION_INFO(STDMETHODCALLTYPE*)(ID3D12Device*, UINT, const D3D12_RESOURCE_DESC*);
	using PFN_D3D12Device_GetCustomHeapProperties = D3D12_HEAP_PROPERTIES(STDMETHODCALLTYPE*)(ID3D12Device*, UINT, D3D12_HEAP_TYPE);
	using PFN_D3D12Device_CreateCommittedResource = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_HEAP_PROPERTIES*, D3D12_HEAP_FLAGS, const D3D12_RESOURCE_DESC*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*, REFIID, void**);
	using PFN_D3D12Device_CreateHeap = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_HEAP_DESC*, REFIID, void**);
	using PFN_D3D12Device_CreatePlacedResource = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, ID3D12Heap*, UINT64, const D3D12_RESOURCE_DESC*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*, REFIID, void**);
	using PFN_D3D12Device_CreateReservedResource = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_RESOURCE_DESC*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*, REFIID, void**);
	using PFN_D3D12Device_CreateSharedHandle = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, ID3D12Resource*, const SECURITY_ATTRIBUTES*, LPCWSTR, HANDLE*);
	using PFN_D3D12Device_OpenSharedHandle = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, HANDLE, REFIID, void**);
	using PFN_D3D12Device_OpenSharedHandleByName = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, LPCWSTR, DWORD, REFIID, void**);
	using PFN_D3D12Device_MakeResident = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, UINT, ID3D12Resource* const*);
	using PFN_D3D12Device_Evict = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, UINT, ID3D12Resource* const*);
	using PFN_D3D12Device_CreateFence = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, UINT64, D3D12_FENCE_FLAGS, REFIID, void**);
	using PFN_D3D12Device_GetDeviceRemovedReason = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*);
	using PFN_D3D12Device_GetCopyableFootprints = void(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_RESOURCE_DESC*, UINT, UINT, D3D12_PLACED_SUBRESOURCE_FOOTPRINT*, UINT*, UINT64*);
	using PFN_D3D12Device_CreateQueryHeap = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_QUERY_HEAP_DESC*, REFIID, void**);
	using PFN_D3D12Device_SetStablePowerState = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, BOOL);
	using PFN_D3D12Device_CreateCommandSignature = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device*, const D3D12_COMMAND_SIGNATURE_DESC*, REFIID, void**);
	using PFN_D3D12Device_GetResourceTiling = void(STDMETHODCALLTYPE*)(ID3D12Device*, ID3D12Resource*, UINT*, UINT*, D3D12_SUBRESOURCE_TILING*, UINT*);
	using PFN_D3D12Device_GetAdapterLuid = LUID(*)(ID3D12Device*);

	using PFN_ID3D12Device1_CreatePipelineLibrary = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device1*, const void*, SIZE_T, REFIID, void**);
	using PFN_ID3D12Device1_SetEventOnMultipleFenceCompletion = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device1*, UINT, const HANDLE*, D3D12_FENCE_FLAGS, HANDLE);
	using PFN_ID3D12Device1_SetResidencyPriority = void (STDMETHODCALLTYPE*)(ID3D12Device1*, UINT, ID3D12Resource* const*, D3D12_RESIDENCY_PRIORITY*);

	using PFN_ID3D12Device2_CreatePipelineState = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device2*, const D3D12_PIPELINE_STATE_STREAM_DESC*, REFIID, void**);

	using PFN_ID3D12Device3_OpenExistingHeapFromFileMapping = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device3*, HANDLE, REFIID, void**);
	using PFN_ID3D12Device3_OpenExistingHeapFromAddress = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device3*, void*, REFIID, void**);
	using PFN_ID3D12Device3_EnqueueMakeResident = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device3*, UINT, ID3D12Resource* const*, UINT*);

	using PFN_ID3D12Device4_CreateCommandList1 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device4*, UINT, D3D12_COMMAND_LIST_TYPE, D3D12_COMMAND_LIST_FLAGS, REFIID, void**);
	using PFN_ID3D12Device4_CreateProtectedResourceSession = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device4*, const D3D12_PROTECTED_RESOURCE_SESSION_DESC*, REFIID, void**);
	using PFN_ID3D12Device4_CreateCommittedResource1 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device4*, const D3D12_HEAP_PROPERTIES*, D3D12_HEAP_FLAGS, const D3D12_RESOURCE_DESC*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*, ID3D12ProtectedResourceSession*, REFIID, void**);
	using PFN_ID3D12Device4_CreateHeap1 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device4*, const D3D12_HEAP_DESC*, ID3D12ProtectedResourceSession*, REFIID, void**);
	using PFN_ID3D12Device4_CreateReservedResource1 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device4*, const D3D12_RESOURCE_DESC*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*, ID3D12ProtectedResourceSession*, REFIID, void**);
	using PFN_ID3D12Device4_GetResourceAllocationInfo1 = void (STDMETHODCALLTYPE*)(ID3D12Device4*, UINT, UINT, const D3D12_RESOURCE_DESC*, const D3D12_RESOURCE_ALLOCATION_INFO*);

	using PFN_ID3D12Device5_CreateLifetimeTracker = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device5*, ID3D12LifetimeOwner*, REFIID, void**);
	using PFN_ID3D12Device5_RemoveDevice = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device5*);
	using PFN_ID3D12Device5_EnumerateMetaCommands = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device5*, UINT*, D3D12_META_COMMAND_DESC*);
	using PFN_ID3D12Device5_EnumerateMetaCommandParameters = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device5*, REFGUID, D3D12_META_COMMAND_PARAMETER_STAGE, UINT*, UINT*, D3D12_META_COMMAND_PARAMETER_DESC*);
	using PFN_ID3D12Device5_CreateMetaCommand = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device5*, REFGUID, UINT, const void*, SIZE_T, REFIID, void**);
	using PFN_ID3D12Device5_CreateStateObject = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device5*, const D3D12_STATE_OBJECT_DESC*, REFIID, void**);
	using PFN_ID3D12Device5_GetRaytracingAccelerationStructurePrebuildInfo = void (STDMETHODCALLTYPE*)(ID3D12Device5*, const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_INPUTS*, D3D12_RAYTRACING_ACCELERATION_STRUCTURE_PREBUILD_INFO*);
	using PFN_ID3D12Device5_CheckDriverMatchingIdentifier = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device5*, D3D12_SERIALIZED_DATA_TYPE, const D3D12_SERIALIZED_DATA_DRIVER_MATCHING_IDENTIFIER*);

	using PFN_ID3D12Device6_SetBackgroundProcessingMode = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device6*, D3D12_BACKGROUND_PROCESSING_MODE, D3D12_MEASUREMENTS_ACTION, HANDLE, BOOL*);

	using PFN_ID3D12Device7_AddToStateObject = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device7*, D3D12_BACKGROUND_PROCESSING_MODE, D3D12_MEASUREMENTS_ACTION, HANDLE, BOOL*);
	using PFN_ID3D12Device7_CreateProtectedResourceSession1 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device7*, D3D12_BACKGROUND_PROCESSING_MODE, D3D12_MEASUREMENTS_ACTION, HANDLE, BOOL*);

	using PFN_ID3D12Device8_GetResourceAllocationInfo2 = D3D12_RESOURCE_ALLOCATION_INFO(STDMETHODCALLTYPE*)(ID3D12Device8*, UINT, UINT, const D3D12_RESOURCE_DESC1*, D3D12_RESOURCE_ALLOCATION_INFO1*);
	using PFN_ID3D12Device8_CreateCommittedResource2 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device8*, const D3D12_HEAP_PROPERTIES*, D3D12_HEAP_FLAGS, const D3D12_RESOURCE_DESC1*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*, ID3D12ProtectedResourceSession*, REFIID, void**);
	using PFN_ID3D12Device8_CreatePlacedResource1 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device8*, ID3D12Heap*, UINT64, const D3D12_RESOURCE_DESC1*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*, REFIID, void**);
	using PFN_ID3D12Device8_CreateSamplerFeedbackUnorderedAccessView = void(STDMETHODCALLTYPE*)(ID3D12Device8*, ID3D12Resource*, ID3D12Resource*, D3D12_CPU_DESCRIPTOR_HANDLE);
	using PFN_ID3D12Device8_GetCopyableFootprints1 = void(STDMETHODCALLTYPE*)(ID3D12Device8*, const D3D12_RESOURCE_DESC1*, UINT, UINT, UINT64, D3D12_PLACED_SUBRESOURCE_FOOTPRINT*, UINT*, UINT64*, UINT64*);

#if defined(__ID3D12Device9_INTERFACE_DEFINED__)
	using PFN_ID3D12Device9_CreateShaderCacheSession = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device9*, const D3D12_SHADER_CACHE_SESSION_DESC*, REFIID, void**);
	using PFN_ID3D12Device9_ShaderCacheControl = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device9*, D3D12_SHADER_CACHE_KIND_FLAGS, D3D12_SHADER_CACHE_CONTROL_FLAGS);
	using PFN_ID3D12Device9_CreateCommandQueue1 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device9*, const D3D12_COMMAND_QUEUE_DESC*, REFIID, REFIID, void**);
#endif

#if defined(__ID3D12Device10_INTERFACE_DEFINED__)
	using PFN_ID3D12Device10_CreateCommittedResource3 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device10*, const D3D12_HEAP_PROPERTIES*, D3D12_HEAP_FLAGS, const D3D12_RESOURCE_DESC1*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*, ID3D12ProtectedResourceSession*, REFIID, void**);
	using PFN_ID3D12Device10_CreatePlacedResource2 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device10*, ID3D12Heap*, UINT64, const D3D12_RESOURCE_DESC1*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*, ID3D12ProtectedResourceSession*, REFIID, void**);
	using PFN_ID3D12Device10_CreateReservedResource2 = HRESULT(STDMETHODCALLTYPE*)(ID3D12Device10*, const D3D12_RESOURCE_DESC1*, D3D12_RESOURCE_STATES, const D3D12_CLEAR_VALUE*,ID3D12ProtectedResourceSession*, REFIID, void**);
#endif

	using PFN_D3D12CommandQueue_QueryInterface = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, REFIID, void**);
	using PFN_D3D12CommandQueue_AddRef = ULONG(STDMETHODCALLTYPE*)(ID3D12CommandQueue*);
	using PFN_D3D12CommandQueue_Release = ULONG(STDMETHODCALLTYPE*)(ID3D12CommandQueue*);
	using PFN_D3D12CommandQueue_GetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, REFGUID, UINT*, void*);
	using PFN_D3D12CommandQueue_SetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, REFGUID, UINT, const void*);
	using PFN_D3D12CommandQueue_SetPrivateDataInterface = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, REFGUID, const IUnknown*);
	using PFN_D3D12CommandQueue_SetName = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, LPCWSTR);
	using PFN_D3D12CommandQueue_GetDevice = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, REFIID, void**);
	using PFN_D3D12CommandQueue_UpdateTileMappings = void(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, ID3D12Resource*, UINT, const D3D12_TILED_RESOURCE_COORDINATE*, UINT, const D3D12_TILE_REGION_SIZE*, ID3D12Heap*, UINT, const D3D12_TILE_MAPPING_FLAGS*);
	using PFN_D3D12CommandQueue_CopyTileMappings = void(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, ID3D12Resource*, const D3D12_TILED_RESOURCE_COORDINATE*, ID3D12Resource*, const D3D12_TILED_RESOURCE_COORDINATE*, const D3D12_TILE_REGION_SIZE*, D3D12_TILE_MAPPING_FLAGS);
	using PFN_D3D12CommandQueue_ExecuteCommandLists = void(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, UINT, ID3D12CommandList* const*);
	using PFN_D3D12CommandQueue_SetMarker = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, UINT, const void*);
	using PFN_D3D12CommandQueue_BeginEvent = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, UINT, const void*);
	using PFN_D3D12CommandQueue_EndEvent = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*);
	using PFN_D3D12CommandQueue_Signal = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, ID3D12Fence*, UINT64);
	using PFN_D3D12CommandQueue_Wait = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, ID3D12Fence*, UINT64);
	using PFN_D3D12CommandQueue_GetTimestampFrequency = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, UINT64*);
	using PFN_D3D12CommandQueue_GetClockCalibration = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandQueue*, UINT64*, UINT64*);
	using PFN_D3D12CommandQueue_GetDesc = D3D12_COMMAND_QUEUE_DESC(STDMETHODCALLTYPE*)(ID3D12CommandQueue*);

	using PFN_D3D12CommandAllocator_QueryInterface = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandAllocator*, REFIID, void**);
	using PFN_D3D12CommandAllocator_AddRef = ULONG(*)(ID3D12CommandAllocator*);
	using PFN_D3D12CommandAllocator_Release = ULONG(*)(ID3D12CommandAllocator*);
	using PFN_D3D12CommandAllocator_GetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandAllocator*, REFGUID, UINT*, void*);
	using PFN_D3D12CommandAllocator_SetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandAllocator*, REFGUID, UINT, const void*);
	using PFN_D3D12CommandAllocator_SetPrivateDataInterface = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandAllocator*, REFGUID, const IUnknown*);
	using PFN_D3D12CommandAllocator_SetName = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandAllocator*, LPCWSTR);
	using PFN_D3D12CommandAllocator_GetDevice = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandAllocator*, REFIID, void**);
	using PFN_D3D12CommandAllocator_Reset = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandAllocator*);

	using PFN_D3D12CommandList_QueryInterface = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandList*, REFIID, void**);
	using PFN_D3D12CommandList_AddRef = ULONG(STDMETHODCALLTYPE*)(ID3D12CommandList*);
	using PFN_D3D12CommandList_Release = ULONG(STDMETHODCALLTYPE*)(ID3D12CommandList*);
	using PFN_D3D12CommandList_GetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandList*, REFGUID, UINT*, void*);
	using PFN_D3D12CommandList_SetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandList*, REFGUID, UINT, const void*);
	using PFN_D3D12CommandList_SetPrivateDataInterface = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandList*, REFGUID, const IUnknown*);
	using PFN_D3D12CommandList_SetName = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandList*, LPCWSTR);
	using PFN_D3D12CommandList_GetDevice = HRESULT(STDMETHODCALLTYPE*)(ID3D12CommandList*, REFIID, void**);
	using PFN_D3D12CommandList_GetType = D3D12_COMMAND_LIST_TYPE(STDMETHODCALLTYPE*)(ID3D12CommandList*);
	using PFN_D3D12CommandList_Close = HRESULT(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*);
	using PFN_D3D12CommandList_Reset = HRESULT(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12CommandAllocator*, ID3D12PipelineState*);
	using PFN_D3D12CommandList_ClearState = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*);
	using PFN_D3D12CommandList_DrawInstanced = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, UINT, UINT, UINT);
	using PFN_D3D12CommandList_DrawIndexedInstanced = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, UINT, UINT, INT, UINT);
	using PFN_D3D12CommandList_Dispatch = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, UINT, UINT);
	using PFN_D3D12CommandList_CopyBufferRegion = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12Resource*, UINT, ID3D12Resource*, UINT, UINT);
	using PFN_D3D12CommandList_CopyTextureRegion = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, const D3D12_TEXTURE_COPY_LOCATION*, UINT, UINT, UINT, const D3D12_TEXTURE_COPY_LOCATION*, const D3D12_BOX*);
	using PFN_D3D12CommandList_CopyResource = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12Resource*, ID3D12Resource*);
	using PFN_D3D12CommandList_CopyTiles = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12Resource*, UINT, const D3D12_TILED_RESOURCE_COORDINATE*, const D3D12_TILE_REGION_SIZE*, ID3D12Resource*, UINT, D3D12_TILE_COPY_FLAGS);
	using PFN_D3D12CommandList_ResolveSubresource = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12Resource*, UINT, ID3D12Resource*, UINT, DXGI_FORMAT);
	using PFN_D3D12CommandList_IASetPrimitiveTopology = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, D3D12_PRIMITIVE_TOPOLOGY);
	using PFN_D3D12CommandList_RSSetViewports = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, const D3D12_VIEWPORT*);
	using PFN_D3D12CommandList_RSSetScissorRects = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, const D3D12_RECT*);
	using PFN_D3D12CommandList_OMSetBlendFactor = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, const FLOAT*);
	using PFN_D3D12CommandList_OMSetStencilRef = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT);
	using PFN_D3D12CommandList_SetPipelineState = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12PipelineState*);
	using PFN_D3D12CommandList_ResourceBarrier = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, const D3D12_RESOURCE_BARRIER*);
	using PFN_D3D12CommandList_ExecuteBundle = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12GraphicsCommandList*);
	using PFN_D3D12CommandList_SetDescriptorHeaps = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, ID3D12DescriptorHeap**);
	using PFN_D3D12CommandList_SetComputeRootSignature = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12RootSignature*);
	using PFN_D3D12CommandList_SetGraphicsRootSignature = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12RootSignature*);
	using PFN_D3D12CommandList_SetComputeRootDescriptorTable = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, D3D12_GPU_DESCRIPTOR_HANDLE);
	using PFN_D3D12CommandList_SetGraphicsRootDescriptorTable = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, D3D12_GPU_DESCRIPTOR_HANDLE);
	using PFN_D3D12CommandList_SetComputeRoot32BitConstant = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, UINT, UINT);
	using PFN_D3D12CommandList_SetGraphicsRoot32BitConstant = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, UINT, UINT);
	using PFN_D3D12CommandList_SetComputeRoot32BitConstants = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, UINT, const void*, UINT);
	using PFN_D3D12CommandList_SetGraphicsRoot32BitConstants = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, UINT, const void*, UINT);
	using PFN_D3D12CommandList_SetComputeRootConstantBufferView = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, D3D12_GPU_VIRTUAL_ADDRESS);
	using PFN_D3D12CommandList_SetGraphicsRootConstantBufferView = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, D3D12_GPU_VIRTUAL_ADDRESS);
	using PFN_D3D12CommandList_SetComputeRootShaderResourceView = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, D3D12_GPU_VIRTUAL_ADDRESS);
	using PFN_D3D12CommandList_SetGraphicsRootShaderResourceView = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, D3D12_GPU_VIRTUAL_ADDRESS);
	using PFN_D3D12CommandList_SetComputeRootUnorderedAccessView = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, D3D12_GPU_VIRTUAL_ADDRESS);
	using PFN_D3D12CommandList_SetGraphicsRootUnorderedAccessView = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, D3D12_GPU_VIRTUAL_ADDRESS);
	using PFN_D3D12CommandList_IASetIndexBuffer = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, const D3D12_INDEX_BUFFER_VIEW*);
	using PFN_D3D12CommandList_IASetVertexBuffers = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, UINT, const D3D12_VERTEX_BUFFER_VIEW*);
	using PFN_D3D12CommandList_SOSetTargets = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, UINT, const D3D12_STREAM_OUTPUT_BUFFER_VIEW*);
	using PFN_D3D12CommandList_OMSetRenderTargets = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, const D3D12_CPU_DESCRIPTOR_HANDLE*, BOOL, const D3D12_CPU_DESCRIPTOR_HANDLE*);
	using PFN_D3D12CommandList_ClearDepthStencilView = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, D3D12_CPU_DESCRIPTOR_HANDLE, UINT, FLOAT, UINT, UINT, const UINT*, UINT, const D3D12_RECT*);
	using PFN_D3D12CommandList_ClearRenderTargetView = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, D3D12_CPU_DESCRIPTOR_HANDLE, const FLOAT*, UINT, const D3D12_RECT*);
	using PFN_D3D12CommandList_ClearUnorderedAccessViewUint = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, D3D12_CPU_DESCRIPTOR_HANDLE, ID3D12Resource*, const UINT*, UINT, const D3D12_RECT*);
	using PFN_D3D12CommandList_ClearUnorderedAccessViewFloat = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, D3D12_CPU_DESCRIPTOR_HANDLE, ID3D12Resource*, const FLOAT*, UINT, const D3D12_RECT*);
	using PFN_D3D12CommandList_DiscardResource = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12Resource*, const D3D12_DISCARD_REGION*);
	using PFN_D3D12CommandList_BeginQuery = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12QueryHeap*, D3D12_QUERY_TYPE, UINT);
	using PFN_D3D12CommandList_EndQuery = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12QueryHeap*, D3D12_QUERY_TYPE, UINT);
	using PFN_D3D12CommandList_ResolveQueryData = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12QueryHeap*, D3D12_QUERY_TYPE, UINT, UINT, ID3D12Resource*, UINT, UINT);
	using PFN_D3D12CommandList_SetPredication = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12Resource*, UINT, D3D12_PREDICATION_OP);
	using PFN_D3D12CommandList_SetMarker = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, const void*);
	using PFN_D3D12CommandList_BeginEvent = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, UINT, const void*);
	using PFN_D3D12CommandList_EndEvent = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*);
	using PFN_D3D12CommandList_ExecuteIndirect = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList*, ID3D12CommandSignature*, UINT, ID3D12Resource*, UINT, ID3D12Resource*, UINT, void*);

	using PFN_D3D12CommandList1_AtomicCopyBufferUINT = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList1*, ID3D12Resource*, UINT64, ID3D12Resource*, UINT64, UINT, ID3D12Resource* const*, const D3D12_SUBRESOURCE_RANGE_UINT64*);
	using PFN_D3D12CommandList1_AtomicCopyBufferUINT64 = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList1*, ID3D12Resource*, UINT64, ID3D12Resource*, UINT64, UINT, ID3D12Resource* const*, const D3D12_SUBRESOURCE_RANGE_UINT64*);
	using PFN_D3D12CommandList1_OMSetDepthBounds = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList1*, FLOAT, FLOAT);
	using PFN_D3D12CommandList1_SetSamplePositions = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList1*, UINT, UINT, D3D12_SAMPLE_POSITION*);
	using PFN_D3D12CommandList1_ResolveSubresourceRegion = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList1*, ID3D12Resource*, UINT, UINT, UINT, ID3D12Resource*, UINT, D3D12_RECT*, DXGI_FORMAT, D3D12_RESOLVE_MODE);
	using PFN_D3D12CommandList1_SetViewInstanceMask = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList1*, UINT);

	using PFN_D3D12CommandList2_WriteBufferImmediate = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList2*, UINT, const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER*, const D3D12_WRITEBUFFERIMMEDIATE_MODE*);

	using PFN_D3D12CommandList3_SetProtectedResourceSession = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList3*, ID3D12ProtectedResourceSession*);

	using PFN_ID3D12GraphicsCommandList4_BeginRenderPass = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList4*, UINT, const D3D12_RENDER_PASS_RENDER_TARGET_DESC*, const D3D12_RENDER_PASS_DEPTH_STENCIL_DESC*, D3D12_RENDER_PASS_FLAGS);
	using PFN_ID3D12GraphicsCommandList4_EndRenderPass = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList4*);
	using PFN_ID3D12GraphicsCommandList4_InitializeMetaCommand = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList4*, ID3D12MetaCommand*, const void*, SIZE_T);
	using PFN_ID3D12GraphicsCommandList4_ExecuteMetaCommand = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList4*, ID3D12MetaCommand*, const void*, SIZE_T);
	using PFN_ID3D12GraphicsCommandList4_BuildRaytracingAccelerationStructure = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList4*, const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC*, UINT, const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC*);
	using PFN_ID3D12GraphicsCommandList4_EmitRaytracingAccelerationStructurePostbuildInfo = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList4*, const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC*, UINT, const D3D12_GPU_VIRTUAL_ADDRESS*);
	using PFN_ID3D12GraphicsCommandList4_CopyRaytracingAccelerationStructure = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList4*, D3D12_GPU_VIRTUAL_ADDRESS, D3D12_GPU_VIRTUAL_ADDRESS, D3D12_RAYTRACING_ACCELERATION_STRUCTURE_COPY_MODE);
	using PFN_ID3D12GraphicsCommandList4_SetPipelineState1 = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList4*, ID3D12StateObject*);
	using PFN_ID3D12GraphicsCommandList4_DispatchRays = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList4*, const D3D12_DISPATCH_RAYS_DESC*);

	using PFN_ID3D12GraphicsCommandList5_RSSetShadingRate = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList5*, D3D12_SHADING_RATE, const D3D12_SHADING_RATE_COMBINER*);
	using PFN_ID3D12GraphicsCommandList5_RSSetShadingRateImage = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList5*, ID3D12Resource*);

#if defined(__ID3D12GraphicsCommandList6_INTERFACE_DEFINED__)
	using PFN_ID3D12GraphicsCommandList6_DispatchMesh = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList6*, UINT, UINT, UINT);
#endif

#if defined(__ID3D12GraphicsCommandList7_INTERFACE_DEFINED__)
	using PFN_ID3D12GraphicsCommandList7_Barrier = void(STDMETHODCALLTYPE*)(ID3D12GraphicsCommandList7*, UINT, const D3D12_BARRIER_GROUP*);
#endif

	using PFN_IDXGISwapChain_QueryInterface = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFIID, void**);
	using PFN_IDXGISwapChain_AddRef = ULONG(STDMETHODCALLTYPE*)(IDXGISwapChain*);
	using PFN_IDXGISwapChain_Release = ULONG(STDMETHODCALLTYPE*)(IDXGISwapChain*);
	using PFN_IDXGISwapChain_SetPrivateData = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFGUID, UINT, const void*);
	using PFN_IDXGISwapChain_SetPrivateDataInterface = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFGUID, const IUnknown*);
	using PFN_IDXGISwapChain_GetPrivateData = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFGUID, UINT*, void*);
	using PFN_IDXGISwapChain_GetParent = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFIID, void**);
	using PFN_IDXGISwapChain_GetDevice = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFIID, void**);
	using PFN_IDXGISwapChain_Present = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
	using PFN_IDXGISwapChain_GetBuffer = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, REFIID, void**);
	using PFN_IDXGISwapChain_SetFullscreenState = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, BOOL, IDXGIOutput*);
	using PFN_IDXGISwapChain_GetFullscreenState = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, BOOL*, IDXGIOutput**);
	using PFN_IDXGISwapChain_GetDesc = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, DXGI_SWAP_CHAIN_DESC*);
	using PFN_IDXGISwapChain_ResizeBuffers = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT, DXGI_FORMAT, UINT);
	using PFN_IDXGISwapChain_ResizeTarget = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, const DXGI_MODE_DESC*);
	using PFN_IDXGISwapChain_GetContainingOutput = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, IDXGIOutput**);
	using PFN_IDXGISwapChain_GetFrameStatistics = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, DXGI_FRAME_STATISTICS*);
	using PFN_IDXGISwapChain_GetLastPresentCount = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT*);

    using PFN_DXGISwapChain1_GetBackgroundColor = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, DXGI_RGBA*);
    using PFN_DXGISwapChain1_GetCoreWindow = HWND(STDMETHODCALLTYPE*)(IDXGISwapChain1*);
    using PFN_DXGISwapChain1_GetDesc1 = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, DXGI_SWAP_CHAIN_DESC1*);
    using PFN_DXGISwapChain1_GetFullscreenDesc = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, DXGI_SWAP_CHAIN_FULLSCREEN_DESC*);
    using PFN_DXGISwapChain1_GetHwnd = HWND(STDMETHODCALLTYPE*)(IDXGISwapChain1*);
    using PFN_DXGISwapChain1_GetRestrictToOutput = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, IDXGIOutput**);
    using PFN_DXGISwapChain1_GetRotation = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, DXGI_MODE_ROTATION*);
    using PFN_DXGISwapChain1_IsTemporaryMonoSupported = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, BOOL*);
    using PFN_DXGISwapChain1_Present1 = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, UINT, const DXGI_PRESENT_PARAMETERS*);
    using PFN_DXGISwapChain1_SetBackgroundColor = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, const DXGI_RGBA*);
    using PFN_DXGISwapChain1_SetRotation = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, DXGI_MODE_ROTATION*);

    using PFN_DXGISwapChain2_GetFrameLatencyWaitableObject = HANDLE(STDMETHODCALLTYPE*)(IDXGISwapChain2*);
    using PFN_DXGISwapChain2_GetMatrixTransform = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain2*, DXGI_MATRIX_3X2_F*);
    using PFN_DXGISwapChain2_GetMaximumFrameLatency = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain2*, UINT*);
    using PFN_DXGISwapChain2_GetSourceSize = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain2*, UINT*, UINT*);
    using PFN_DXGISwapChain2_SetMatrixTransform = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain2*, const DXGI_MATRIX_3X2_F*);
    using PFN_DXGISwapChain2_SetMaximumFrameLatency = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain2*, UINT);
    using PFN_DXGISwapChain2_SetSourceSize = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain2*, UINT, UINT);

    using PFN_DXGISwapChain3_CheckColorSpaceSupport = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain3*, DXGI_COLOR_SPACE_TYPE, UINT*);
    using PFN_DXGISwapChain3_GetCurrentBackBufferIndex = UINT(STDMETHODCALLTYPE*)(IDXGISwapChain3*);
    using PFN_DXGISwapChain3_ResizeBuffers1 = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain3*, UINT, UINT, UINT, DXGI_FORMAT, UINT, const UINT*, IUnknown* const*);
    using PFN_DXGISwapChain3_SetColorSpace1 = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain3*, DXGI_COLOR_SPACE_TYPE);
}