#pragma once
#include <windef.h>

#define D3D12_ENTRY_COUNT(Class) (D3D12_##Class##_LastEntry - D3D12_##Class##_FirstEntry + 1)
#define D3D12_ENTRY_COUNT_(Class, x)	(D3D12_##Class##x##_LastEntry - D3D12_##Class##_FirstEntry + 1)

enum
{
	D3D12_Device_FirstEntry,
	D3D12_Device_QueryInterface = D3D12_Device_FirstEntry,
	D3D12_Device_AddRef,
	D3D12_Device_Release,
	D3D12_Device_GetPrivateData,
	D3D12_Device_SetPrivateData,
	D3D12_Device_SetPrivateDataInterface,
	D3D12_Device_SetName,
	D3D12_Device_GetNodeCount,
	D3D12_Device_CreateCommandQueue,
	D3D12_Device_CreateCommandAllocator,
	D3D12_Device_CreateGraphicsPipelineState,
	D3D12_Device_CreateComputePipelineState,
	D3D12_Device_CreateCommandList,
	D3D12_Device_CheckFeatureSupport,
	D3D12_Device_CreateDescriptorHeap,
	D3D12_Device_GetDescriptorHandleIncrementSize,
	D3D12_Device_CreateRootSignature,
	D3D12_Device_CreateConstantBufferView,
	D3D12_Device_CreateShaderResourceView,
	D3D12_Device_CreateUnorderedAccessView,
	D3D12_Device_CreateRenderTargetView,
	D3D12_Device_CreateDepthStencilView,
	D3D12_Device_CreateSampler,
	D3D12_Device_CopyDescriptors,
	D3D12_Device_CopyDescriptorsSimple,
	D3D12_Device_GetResourceAllocationInfo,
	D3D12_Device_GetCustomHeapProperties,
	D3D12_Device_CreateCommittedResource,
	D3D12_Device_CreateHeap,
	D3D12_Device_CreatePlacedResource,
	D3D12_Device_CreateReservedResource,
	D3D12_Device_CreateSharedHandle,
	D3D12_Device_OpenSharedHandle,
	D3D12_Device_OpenSharedHandleByName,
	D3D12_Device_MakeResident,
	D3D12_Device_Evict,
	D3D12_Device_CreateFence,
	D3D12_Device_GetDeviceRemovedReason,
	D3D12_Device_GetCopyableFootprints,
	D3D12_Device_CreateQueryHeap,
	D3D12_Device_SetStablePowerState,
	D3D12_Device_CreateCommandSignature,
	D3D12_Device_GetResourceTiling,
	D3D12_Device_GetAdapterLuid,
	D3D12_Device_LastEntry = D3D12_Device_GetAdapterLuid,

	D3D12_Device1_CreatePipelineLibrary,
	D3D12_Device1_SetEventOnMultipleFenceCompletion,
	D3D12_Device1_SetResidencyPriority,
	D3D12_Device1_LastEntry = D3D12_Device1_SetResidencyPriority,

	D3D12_Device2_CreatePipelineState,
	D3D12_Device2_LastEntry = D3D12_Device2_CreatePipelineState,

	D3D12_Device3_OpenExistingHeapFromAddress,
	D3D12_Device3_OpenExistingHeapFromFileMapping,
	D3D12_Device3_EnqueueMakeResident,
	D3D12_Device3_LastEntry = D3D12_Device3_EnqueueMakeResident,

	D3D12_Device4_CreateCommandList1,
	D3D12_Device4_CreateProtectedResourceSession,
	D3D12_Device4_CreateCommittedResource1,
	D3D12_Device4_CreateHeap1,
	D3D12_Device4_CreateReservedResource1,
	D3D12_Device4_GetResourceAllocationInfo1,
	D3D12_Device4_LastEntry = D3D12_Device4_GetResourceAllocationInfo1,

	D3D12_Device5_CreateLifetimeTracker,
	D3D12_Device5_RemoveDevice,
	D3D12_Device5_EnumerateMetaCommands,
	D3D12_Device5_EnumerateMetaCommandParameters,
	D3D12_Device5_CreateMetaCommand,
	D3D12_Device5_CreateStateObject,
	D3D12_Device5_GetRaytracingAccelerationStructurePrebuildInfo,
	D3D12_Device5_CheckDriverMatchingIdentifier,
	D3D12_Device5_LastEntry = D3D12_Device5_CheckDriverMatchingIdentifier,

	D3D12_Device6_SetBackgroundProcessingMode,
	D3D12_Device6_LastEntry = D3D12_Device6_SetBackgroundProcessingMode,

	D3D12_Device7_AddToStateObject,
	D3D12_Device7_CreateProtectedResourceSession1,
	D3D12_Device7_LastEntry = D3D12_Device7_CreateProtectedResourceSession1,

	D3D12_Device8_GetResourceAllocationInfo2,
	D3D12_Device8_CreateCommittedResource2,
	D3D12_Device8_CreatePlacedResource1,
	D3D12_Device8_CreateSamplerFeedbackUnorderedAccessView,
	D3D12_Device8_GetCopyableFootprints1,
	D3D12_Device8_LastEntry = D3D12_Device8_GetCopyableFootprints1,

	D3D12_Device9_CreateShaderCacheSession,
	D3D12_Device9_ShaderCacheControl,
	D3D12_Device9_CreateCommandQueue1,
	D3D12_Device9_LastEntry = D3D12_Device9_CreateCommandQueue1,

	D3D12_Device10_CreateCommittedResource3,
	D3D12_Device10_CreatePlacedResource2,
	D3D12_Device10_CreateReservedResource2,
	D3D12_Device10_LastEntry = D3D12_Device10_CreateReservedResource2,

	D3D12_Device11_CreateSampler2,
	D3D12_Device11_LastEntry = D3D12_Device11_CreateSampler2,

	D3D12_Device12_GetResourceAllocationInfo3,
	D3D12_Device12_LastEntry = D3D12_Device12_GetResourceAllocationInfo3,

	D3D12_Device13_OpenExistingHeapFromAddress1,
	D3D12_Device13_LastEntry = D3D12_Device13_OpenExistingHeapFromAddress1,

	D3D12_Device14_CreateRootSignatureFromSubobjectInLibrary,
	D3D12_Device14_LastEntry = D3D12_Device14_CreateRootSignatureFromSubobjectInLibrary,

	D3D12_Queue_FirstEntry,
	D3D12_Queue_QueryInterface = D3D12_Queue_FirstEntry,
	D3D12_Queue_AddRef,
	D3D12_Queue_Release,
	D3D12_Queue_GetPrivateData,
	D3D12_Queue_SetPrivateData,
	D3D12_Queue_SetPrivateDataInterface,
	D3D12_Queue_SetName,
	D3D12_Queue_GetDevice,
	D3D12_Queue_UpdateTileMappings,
	D3D12_Queue_CopyTileMappings,
	D3D12_Queue_ExecuteCommandLists,
	D3D12_Queue_SetMarker,
	D3D12_Queue_BeginEvent,
	D3D12_Queue_EndEvent,
	D3D12_Queue_Signal,
	D3D12_Queue_Wait,
	D3D12_Queue_GetTimestampFrequency,
	D3D12_Queue_GetClockCalibration,
	D3D12_Queue_GetDesc,
	D3D12_Queue_LastEntry = D3D12_Queue_GetDesc,

	D3D12_Allocator_FirstEntry,
	D3D12_Allocator_QueryInterface = D3D12_Allocator_FirstEntry,
	D3D12_Allocator_AddRef,
	D3D12_Allocator_Release,
	D3D12_Allocator_GetPrivateData,
	D3D12_Allocator_SetPrivateData,
	D3D12_Allocator_SetPrivateDataInterface,
	D3D12_Allocator_SetName,
	D3D12_Allocator_GetDevice,
	D3D12_Allocator_Reset,
	D3D12_Allocator_LastEntry = D3D12_Allocator_Reset,

	D3D12_List_FirstEntry,
	D3D12_List_QueryInterface = D3D12_List_FirstEntry,
	D3D12_List_AddRef,
	D3D12_List_Release,
	D3D12_List_GetPrivateData,
	D3D12_List_SetPrivateData,
	D3D12_List_SetPrivateDataInterface,
	D3D12_List_SetName,
	D3D12_List_GetDevice,
	D3D12_List_GetType,
	D3D12_List_Close,
	D3D12_List_Reset,
	D3D12_List_ClearState,
	D3D12_List_DrawInstanced,
	D3D12_List_DrawIndexedInstanced,
	D3D12_List_Dispatch,
	D3D12_List_CopyBufferRegion,
	D3D12_List_CopyTextureRegion,
	D3D12_List_CopyResource,
	D3D12_List_CopyTiles,
	D3D12_List_ResolveSubresource,
	D3D12_List_IASetPrimitiveTopology,
	D3D12_List_RSSetViewports,
	D3D12_List_RSSetScissorRects,
	D3D12_List_OMSetBlendFactor,
	D3D12_List_OMSetStencilRef,
	D3D12_List_SetPipelineState,
	D3D12_List_ResourceBarrier,
	D3D12_List_ExecuteBundle,
	D3D12_List_SetDescriptorHeaps,
	D3D12_List_SetComputeRootSignature,
	D3D12_List_SetGraphicsRootSignature,
	D3D12_List_SetComputeRootDescriptorTable,
	D3D12_List_SetGraphicsRootDescriptorTable,
	D3D12_List_SetComputeRoot32BitConstant,
	D3D12_List_SetGraphicsRoot32BitConstant,
	D3D12_List_SetComputeRoot32BitConstants,
	D3D12_List_SetGraphicsRoot32BitConstants,
	D3D12_List_SetComputeRootConstantBufferView,
	D3D12_List_SetGraphicsRootConstantBufferView,
	D3D12_List_SetComputeRootShaderResourceView,
	D3D12_List_SetGraphicsRootShaderResourceView,
	D3D12_List_SetComputeRootUnorderedAccessView,
	D3D12_List_SetGraphicsRootUnorderedAccessView,
	D3D12_List_IASetIndexBuffer,
	D3D12_List_IASetVertexBuffers,
	D3D12_List_SOSetTargets,
	D3D12_List_OMSetRenderTargets,
	D3D12_List_ClearDepthStencilView,
	D3D12_List_ClearRenderTargetView,
	D3D12_List_ClearUnorderedAccessViewUint,
	D3D12_List_ClearUnorderedAccessViewFloat,
	D3D12_List_DiscardResource,
	D3D12_List_BeginQuery,
	D3D12_List_EndQuery,
	D3D12_List_ResolveQueryData,
	D3D12_List_SetPredication,
	D3D12_List_SetMarker,
	D3D12_List_BeginEvent,
	D3D12_List_EndEvent,
	D3D12_List_ExecuteIndirect,
	D3D12_List_LastEntry = D3D12_List_ExecuteIndirect,

	D3D12_List1_AtomicCopyBufferUINT,
	D3D12_List1_AtomicCopyBufferUINT64,
	D3D12_List1_OMSetDepthBounds,
	D3D12_List1_SetSamplePositions,
	D3D12_List1_ResolveSubresourceRegion,
	D3D12_List1_SetViewInstanceMask,
	D3D12_List1_LastEntry = D3D12_List1_SetViewInstanceMask,

	D3D12_List2_WriteBufferImmediate,
	D3D12_List2_LastEntry = D3D12_List2_WriteBufferImmediate,

	D3D12_List3_SetProtectedResourceSession,
	D3D12_List3_LastEntry = D3D12_List3_SetProtectedResourceSession,

	D3D12_List4_BeginRenderPass,
	D3D12_List4_EndRenderPass,
	D3D12_List4_InitializeMetaCommand,
	D3D12_List4_ExecuteMetaCommand,
	D3D12_List4_BuildRaytracingAccelerationStructure,
	D3D12_List4_EmitRaytracingAccelerationStructurePostbuildInfo,
	D3D12_List4_CopyRaytracingAccelerationStructure,
	D3D12_List4_SetPipelineState1,
	D3D12_List4_DispatchRays,
	D3D12_List4_LastEntry = D3D12_List4_DispatchRays,

	D3D12_List5_RSSetShadingRate,
	D3D12_List5_RSSetShadingRateImage,
	D3D12_List5_LastEntry = D3D12_List5_RSSetShadingRateImage,

	D3D12_List6_DispatchMesh,
	D3D12_List6_LastEntry = D3D12_List6_DispatchMesh,

	D3D12_List7_Barrier,
	D3D12_List7_LastEntry = D3D12_List7_Barrier,

	D3D12_List8_OMSetFrontAndBackStencilRef,
	D3D12_List8_LastEntry = D3D12_List8_OMSetFrontAndBackStencilRef,

	D3D12_List9_RSSetDepthBias,
	D3D12_List9_IASetIndexBufferStripCutValue,
	D3D12_List9_LastEntry = D3D12_List9_IASetIndexBufferStripCutValue,

	D3D12_List10_SetProgram,
	D3D12_List10_DispatchGraph,
	D3D12_List10_LastEntry = D3D12_List10_DispatchGraph,

	D3D12_SwapChain_FirstEntry,
	D3D12_SwapChain_QueryInterface = D3D12_SwapChain_FirstEntry,
	D3D12_SwapChain_AddRef,
	D3D12_SwapChain_Release,
	D3D12_SwapChain_SetPrivateData,
	D3D12_SwapChain_SetPrivateDataInterface,
	D3D12_SwapChain_GetPrivateData,
	D3D12_SwapChain_GetParent,
	D3D12_SwapChain_GetDevice,
	D3D12_SwapChain_Present,
	D3D12_SwapChain_GetBuffer,
	D3D12_SwapChain_SetFullscreenState,
	D3D12_SwapChain_GetFullscreenState,
	D3D12_SwapChain_GetDesc,
	D3D12_SwapChain_ResizeBuffers,
	D3D12_SwapChain_ResizeTarget,
	D3D12_SwapChain_GetContainingOutput,
	D3D12_SwapChain_GetFrameStatistics,
	D3D12_SwapChain_GetLastPresentCount,
	D3D12_SwapChain_LastEntry = D3D12_SwapChain_GetLastPresentCount,

	D3D12_SwapChain1_GetDesc1,
	D3D12_SwapChain1_GetFullscreenDesc,
	D3D12_SwapChain1_GetHwnd,
	D3D12_SwapChain1_GetCoreWindow,
	D3D12_SwapChain1_Present1,
	D3D12_SwapChain1_IsTemporaryMonoSupported,
	D3D12_SwapChain1_GetRestrictToOutput,
	D3D12_SwapChain1_SetBackgroundColor,
	D3D12_SwapChain1_GetBackgroundColor,
	D3D12_SwapChain1_SetRotation,
	D3D12_SwapChain1_GetRotation,
	D3D12_SwapChain1_LastEntry = D3D12_SwapChain1_GetRotation,

	D3D12_SwapChain2_SetSourceSize,
	D3D12_SwapChain2_GetSourceSize,
	D3D12_SwapChain2_SetMaximumFrameLatency,
	D3D12_SwapChain2_GetMaximumFrameLatency,
	D3D12_SwapChain2_GetFrameLatencyWaitableObject,
	D3D12_SwapChain2_SetMatrixTransform,
	D3D12_SwapChain2_GetMatrixTransform,
	D3D12_SwapChain2_LastEntry = D3D12_SwapChain2_GetMatrixTransform,

	D3D12_SwapChain3_GetCurrentBackBufferIndex,
	D3D12_SwapChain3_CheckColorSpaceSupport,
	D3D12_SwapChain3_SetColorSpace1,
	D3D12_SwapChain3_ResizeBuffers1,
	D3D12_SwapChain3_LastEntry = D3D12_SwapChain3_ResizeBuffers1,

	D3D12_SwapChain4_SetHDRMetaData,
	D3D12_SwapChain4_LastEntry = D3D12_SwapChain4_SetHDRMetaData,

	D3D12_Resource_FirstEntry,
	D3D12_Resource_QueryInterface = D3D12_Resource_FirstEntry,
	D3D12_Resource_AddRef,
	D3D12_Resource_Release,
	D3D12_Resource_GetPrivateData,
	D3D12_Resource_SetPrivateData,
	D3D12_Resource_SetPrivateDataInterface,
	D3D12_Resource_SetName,
	D3D12_Resource_GetDevice,
	D3D12_Resource_Map,
	D3D12_Resource_Unmap,
	D3D12_Resource_GetDesc,
	D3D12_Resource_GetGPUVirtualAddress,
	D3D12_Resource_WriteToSubresource,
	D3D12_Resource_ReadFromSubresource,
	D3D12_Resource_GetHeapProperties,
	D3D12_Resource_LastEntry = D3D12_Resource_GetHeapProperties,

	D3D12_Resource1_GetProtectedResourceSession,
	D3D12_Resource1_LastEntry = D3D12_Resource1_GetProtectedResourceSession,

	D3D12_Resource2_GetDesc1,
	D3D12_Resource2_LastEntry = D3D12_Resource2_GetDesc1,

	D3D12_Fence_FirstEntry,
	D3D12_Fence_QueryInterface = D3D12_Fence_FirstEntry,
	D3D12_Fence_AddRef,
	D3D12_Fence_Release,
	D3D12_Fence_GetPrivateData,
	D3D12_Fence_SetPrivateData,
	D3D12_Fence_SetPrivateDataInterface,
	D3D12_Fence_SetName,
	D3D12_Fence_GetDevice,
	D3D12_Fence_GetCompletedValue,
	D3D12_Fence_SetEventOnCompletion,
	D3D12_Fence_Signal,
	D3D12_Fence_LastEntry = D3D12_Fence_Signal,

	D3D12_Fence1_GetCreationFlags,
	D3D12_Fence1_LastEntry = D3D12_Fence1_GetCreationFlags,
};

static const UINT D3D12_DEVICE_ENTRIES = D3D12_ENTRY_COUNT(Device);
static const UINT D3D12_DEVICE1_ENTRIES = D3D12_ENTRY_COUNT_(Device, 1);
static const UINT D3D12_DEVICE2_ENTRIES = D3D12_ENTRY_COUNT_(Device, 2);
static const UINT D3D12_DEVICE3_ENTRIES = D3D12_ENTRY_COUNT_(Device, 3);
static const UINT D3D12_DEVICE4_ENTRIES = D3D12_ENTRY_COUNT_(Device, 4);
static const UINT D3D12_DEVICE5_ENTRIES = D3D12_ENTRY_COUNT_(Device, 5);
static const UINT D3D12_DEVICE6_ENTRIES = D3D12_ENTRY_COUNT_(Device, 6);
static const UINT D3D12_DEVICE7_ENTRIES = D3D12_ENTRY_COUNT_(Device, 7);
static const UINT D3D12_DEVICE8_ENTRIES = D3D12_ENTRY_COUNT_(Device, 8);
static const UINT D3D12_DEVICE9_ENTRIES = D3D12_ENTRY_COUNT_(Device, 9);
static const UINT D3D12_DEVICE10_ENTRIES = D3D12_ENTRY_COUNT_(Device, 10);
static const UINT D3D12_DEVICE11_ENTRIES = D3D12_ENTRY_COUNT_(Device, 11);
static const UINT D3D12_DEVICE12_ENTRIES = D3D12_ENTRY_COUNT_(Device, 12);
static const UINT D3D12_DEVICE13_ENTRIES = D3D12_ENTRY_COUNT_(Device, 13);
static const UINT D3D12_DEVICE14_ENTRIES = D3D12_ENTRY_COUNT_(Device, 14);
static const UINT D3D12_MAX_DEVICE_ENTRIES = D3D12_DEVICE14_ENTRIES;

static const UINT D3D12_QUEUE_ENTRIES  = D3D12_ENTRY_COUNT(Queue);
static const UINT D3D12_ALLOCATOR_ENTRIES  = D3D12_ENTRY_COUNT(Allocator);

static const UINT D3D12_LIST_ENTRIES  = D3D12_ENTRY_COUNT(List);
static const UINT D3D12_LIST1_ENTRIES = D3D12_ENTRY_COUNT_(List, 1);
static const UINT D3D12_LIST2_ENTRIES = D3D12_ENTRY_COUNT_(List, 2);
static const UINT D3D12_LIST3_ENTRIES = D3D12_ENTRY_COUNT_(List, 3);
static const UINT D3D12_LIST4_ENTRIES = D3D12_ENTRY_COUNT_(List, 4);
static const UINT D3D12_LIST5_ENTRIES = D3D12_ENTRY_COUNT_(List, 5);
static const UINT D3D12_LIST6_ENTRIES = D3D12_ENTRY_COUNT_(List, 6);
static const UINT D3D12_LIST7_ENTRIES = D3D12_ENTRY_COUNT_(List, 7);
static const UINT D3D12_LIST8_ENTRIES = D3D12_ENTRY_COUNT_(List, 8);
static const UINT D3D12_LIST9_ENTRIES = D3D12_ENTRY_COUNT_(List, 9);
static const UINT D3D12_LIST10_ENTRIES = D3D12_ENTRY_COUNT_(List, 10);
static const UINT D3D12_MAX_LIST_ENTRIES = D3D12_LIST10_ENTRIES;

static const UINT D3D12_SWAPCHAIN_ENTRIES  = D3D12_ENTRY_COUNT(SwapChain);
    static const UINT D3D12_SWAPCHAIN1_ENTRIES = D3D12_ENTRY_COUNT_(SwapChain, 1);
    static const UINT D3D12_SWAPCHAIN2_ENTRIES = D3D12_ENTRY_COUNT_(SwapChain, 2);
    static const UINT D3D12_SWAPCHAIN3_ENTRIES = D3D12_ENTRY_COUNT_(SwapChain, 3);
    static const UINT D3D12_SWAPCHAIN4_ENTRIES = D3D12_ENTRY_COUNT_(SwapChain, 4);
    static const UINT D3D12_MAX_SWAPCHAIN_ENTRIES = D3D12_SWAPCHAIN4_ENTRIES;

static const UINT D3D12_RESOURCE_ENTRIES  = D3D12_ENTRY_COUNT(Resource);
static const UINT D3D12_RESOURCE1_ENTRIES = D3D12_ENTRY_COUNT_(Resource, 1);
static const UINT D3D12_RESOURCE2_ENTRIES = D3D12_ENTRY_COUNT_(Resource, 2);
static const UINT D3D12_MAX_RESOURCE_ENTRIES = D3D12_RESOURCE2_ENTRIES;

static const UINT D3D12_FENCE_ENTRIES = D3D12_ENTRY_COUNT(Fence);
static const UINT D3D12_FENCE1_ENTRIES = D3D12_ENTRY_COUNT_(Fence, 1);
static const UINT D3D12_MAX_FENCE_ENTRIES = D3D12_FENCE1_ENTRIES;
