#pragma once

#define ENTRY_COUNT(Class) (Class##_LastEntry - Class##_FirstEntry + 1)
#define ENTRY_COUNT_(Class, x)	(Class##x##_LastEntry - Class##_FirstEntry + 1)

namespace directhook::d3d12
{
	enum
	{
		Device_FirstEntry,
		Device_QueryInterface = Device_FirstEntry,
		Device_AddRef,
		Device_Release,
		Device_GetPrivateData,
		Device_SetPrivateData,
		Device_SetPrivateDataInterface,
		Device_SetName,
		Device_GetNodeCount,
		Device_CreateCommandQueue,
		Device_CreateCommandAllocator,
		Device_CreateGraphicsPipelineState,
		Device_CreateComputePipelineState,
		Device_CreateCommandList,
		Device_CheckFeatureSupport,
		Device_CreateDescriptorHeap,
		Device_GetDescriptorHandleIncrementSize,
		Device_CreateRootSignature,
		Device_CreateConstantBufferView,
		Device_CreateShaderResourceView,
		Device_CreateUnorderedAccessView,
		Device_CreateRenderTargetView,
		Device_CreateDepthStencilView,
		Device_CreateSampler,
		Device_CopyDescriptors,
		Device_CopyDescriptorsSimple,
		Device_GetResourceAllocationInfo,
		Device_GetCustomHeapProperties,
		Device_CreateCommittedResource,
		Device_CreateHeap,
		Device_CreatePlacedResource,
		Device_CreateReservedResource,
		Device_CreateSharedHandle,
		Device_OpenSharedHandle,
		Device_OpenSharedHandleByName,
		Device_MakeResident,
		Device_Evict,
		Device_CreateFence,
		Device_GetDeviceRemovedReason,
		Device_GetCopyableFootprints,
		Device_CreateQueryHeap,
		Device_SetStablePowerState,
		Device_CreateCommandSignature,
		Device_GetResourceTiling,
		Device_GetAdapterLuid,
		Device_LastEntry = Device_GetAdapterLuid,

		Device1_CreatePipelineLibrary,
		Device1_SetEventOnMultipleFenceCompletion,
		Device1_SetResidencyPriority,
		Device1_LastEntry = Device1_SetResidencyPriority,

		Device2_CreatePipelineState,
		Device2_LastEntry = Device2_CreatePipelineState,

		Device3_OpenExistingHeapFromFileMapping,
		Device3_OpenExistingHeapFromAddress,
		Device3_EnqueueMakeResident,
		Device3_LastEntry = Device3_EnqueueMakeResident,

		Device4_CreateCommandList1,
		Device4_CreateProtectedResourceSession,
		Device4_CreateCommittedResource1,
		Device4_CreateHeap1,
		Device4_CreateReservedResource1,
		Device4_GetResourceAllocationInfo1,
		Device4_LastEntry = Device4_GetResourceAllocationInfo1,

		Device5_CreateLifetimeTracker,
		Device5_RemoveDevice,
		Device5_EnumerateMetaCommands,
		Device5_EnumerateMetaCommandParameters,
		Device5_CreateMetaCommand,
		Device5_CreateStateObject,
		Device5_GetRaytracingAccelerationStructurePrebuildInfo,
		Device5_CheckDriverMatchingIdentifier,
		Device5_LastEntry = Device5_CheckDriverMatchingIdentifier,

		Device6_SetBackgroundProcessingMode,
		Device6_LastEntry = Device6_SetBackgroundProcessingMode,

		Device7_AddToStateObject,
		Device7_CreateProtectedResourceSession1,
		Device7_LastEntry = Device7_CreateProtectedResourceSession1,

		Device8_GetResourceAllocationInfo2,
		Device8_CreateCommittedResource2,
		Device8_CreatePlacedResource1,
		Device8_CreateSamplerFeedbackUnorderedAccessView,
		Device8_GetCopyableFootprints1,
		Device8_LastEntry = Device8_GetCopyableFootprints1,

		Device9_CreateShaderCacheSession,
		Device9_ShaderCacheControl,
		Device9_CreateCommandQueue1,
		Device9_LastEntry = Device9_CreateCommandQueue1,

		Device10_CreateCommittedResource3,
		Device10_CreatePlacedResource2,
		Device10_CreateReservedResource2,
		Device10_LastEntry = Device10_CreateReservedResource2,

		Queue_FirstEntry,
		Queue_QueryInterface = Queue_FirstEntry,
		Queue_AddRef,
		Queue_Release,
		Queue_GetPrivateData,
		Queue_SetPrivateData,
		Queue_SetPrivateDataInterface,
		Queue_SetName,
		Queue_GetDevice,
		Queue_UpdateTileMappings,
		Queue_CopyTileMappings,
		Queue_ExecuteCommandLists,
		Queue_SetMarker,
		Queue_BeginEvent,
		Queue_EndEvent,
		Queue_Signal,
		Queue_Wait,
		Queue_GetTimestampFrequency,
		Queue_GetClockCalibration,
		Queue_GetDesc,
		Queue_LastEntry = Queue_GetDesc,

		Allocator_FirstEntry,
		Allocator_QueryInterface = Allocator_FirstEntry,
		Allocator_AddRef,
		Allocator_Release,
		Allocator_GetPrivateData,
		Allocator_SetPrivateData,
		Allocator_SetPrivateDataInterface,
		Allocator_SetName,
		Allocator_GetDevice,
		Allocator_Reset,
		Allocator_LastEntry = Allocator_Reset,

		List_FirstEntry,
		List_QueryInterface = List_FirstEntry,
		List_AddRef,
		List_Release,
		List_GetPrivateData,
		List_SetPrivateData,
		List_SetPrivateDataInterface,
		List_SetName,
		List_GetDevice,
		List_GetType,
		List_Close,
		List_Reset,
		List_ClearState,
		List_DrawInstanced,
		List_DrawIndexedInstanced,
		List_Dispatch,
		List_CopyBufferRegion,
		List_CopyTextureRegion,
		List_CopyResource,
		List_CopyTiles,
		List_ResolveSubresource,
		List_IASetPrimitiveTopology,
		List_RSSetViewports,
		List_RSSetScissorRects,
		List_OMSetBlendFactor,
		List_OMSetStencilRef,
		List_SetPipelineState,
		List_ResourceBarrier,
		List_ExecuteBundle,
		List_SetDescriptorHeaps,
		List_SetComputeRootSignature,
		List_SetGraphicsRootSignature,
		List_SetComputeRootDescriptorTable,
		List_SetGraphicsRootDescriptorTable,
		List_SetComputeRoot32BitConstant,
		List_SetGraphicsRoot32BitConstant,
		List_SetComputeRoot32BitConstants,
		List_SetGraphicsRoot32BitConstants,
		List_SetComputeRootConstantBufferView,
		List_SetGraphicsRootConstantBufferView,
		List_SetComputeRootShaderResourceView,
		List_SetGraphicsRootShaderResourceView,
		List_SetComputeRootUnorderedAccessView,
		List_SetGraphicsRootUnorderedAccessView,
		List_IASetIndexBuffer,
		List_IASetVertexBuffers,
		List_SOSetTargets,
		List_OMSetRenderTargets,
		List_ClearDepthStencilView,
		List_ClearRenderTargetView,
		List_ClearUnorderedAccessViewUint,
		List_ClearUnorderedAccessViewFloat,
		List_DiscardResource,
		List_BeginQuery,
		List_EndQuery,
		List_ResolveQueryData,
		List_SetPredication,
		List_SetMarker,
		List_BeginEvent,
		List_EndEvent,
		List_ExecuteIndirect,
		List_LastEntry = List_ExecuteIndirect,

		List1_AtomicCopyBufferUINT,
		List1_AtomicCopyBufferUINT64,
		List1_OMSetDepthBounds,
		List1_SetSamplePositions,
		List1_ResolveSubresourceRegion,
		List1_SetViewInstanceMask,
		List1_LastEntry = List1_SetViewInstanceMask,

		List2_WriteBufferImmediate,
		List2_LastEntry = List2_WriteBufferImmediate,

		List3_SetProtectedResourceSession,
		List3_LastEntry = List3_SetProtectedResourceSession,

		List4_BeginRenderPass,
		List4_EndRenderPass,
		List4_InitializeMetaCommand,
		List4_ExecuteMetaCommand,
		List4_BuildRaytracingAccelerationStructure,
		List4_EmitRaytracingAccelerationStructurePostbuildInfo,
		List4_CopyRaytracingAccelerationStructure,
		List4_SetPipelineState1,
		List4_DispatchRays,
		List4_LastEntry = List4_DispatchRays,

		List5_RSSetShadingRate,
		List5_RSSetShadingRateImage,
		List5_LastEntry = List5_RSSetShadingRateImage,

		List6_DispatchMesh,
		List6_LastEntry = List6_DispatchMesh,

		List7_Barrier,
		List7_LastEntry = List7_Barrier,

		SwapChain_FirstEntry,
		SwapChain_QueryInterface = SwapChain_FirstEntry,
		SwapChain_AddRef,
		SwapChain_Release,
		SwapChain_SetPrivateData,
		SwapChain_SetPrivateDataInterface,
		SwapChain_GetPrivateData,
		SwapChain_GetParent,
		SwapChain_GetDevice,
		SwapChain_Present,
		SwapChain_GetBuffer,
		SwapChain_SetFullscreenState,
		SwapChain_GetFullscreenState,
		SwapChain_GetDesc,
		SwapChain_ResizeBuffers,
		SwapChain_ResizeTarget,
		SwapChain_GetContainingOutput,
		SwapChain_GetFrameStatistics,
		SwapChain_GetLastPresentCount,
		SwapChain_LastEntry = SwapChain_GetLastPresentCount,

        SwapChain1_GetBackgroundColor,
        SwapChain1_GetCoreWindow,
        SwapChain1_GetDesc1,
        SwapChain1_GetFullscreenDesc,
        SwapChain1_GetHwnd,
        SwapChain1_GetRestrictToOutput,
        SwapChain1_GetRotation,
        SwapChain1_IsTemporaryMonoSupported,
        SwapChain1_Present1,
        SwapChain1_SetBackgroundColor,
        SwapChain1_SetRotation,
        SwapChain1_LastEntry = SwapChain1_SetRotation,

        SwapChain2_GetFrameLatencyWaitableObject,
        SwapChain2_GetMatrixTransform,
        SwapChain2_GetMaximumFrameLatency,
        SwapChain2_GetSourceSize,
        SwapChain2_SetMatrixTransform,
        SwapChain2_SetMaximumFrameLatency,
        SwapChain2_SetSourceSize,
        SwapChain2_LastEntry = SwapChain2_SetSourceSize,

        SwapChain3_CheckColorSpaceSupport,
        SwapChain3_GetCurrentBackBufferIndex,
        SwapChain3_ResizeBuffers1,
        SwapChain3_SetColorSpace1,
        SwapChain3_LastEntry = SwapChain3_SetColorSpace1,
	};

	static constexpr int DEVICE_ENTRIES = ENTRY_COUNT(Device);
	static constexpr int DEVICE1_ENTRIES = ENTRY_COUNT_(Device, 1);
	static constexpr int DEVICE2_ENTRIES = ENTRY_COUNT_(Device, 2);
	static constexpr int DEVICE3_ENTRIES = ENTRY_COUNT_(Device, 3);
	static constexpr int DEVICE4_ENTRIES = ENTRY_COUNT_(Device, 4);
	static constexpr int DEVICE5_ENTRIES = ENTRY_COUNT_(Device, 5);
	static constexpr int DEVICE6_ENTRIES = ENTRY_COUNT_(Device, 6);
	static constexpr int DEVICE7_ENTRIES = ENTRY_COUNT_(Device, 7);
	static constexpr int DEVICE8_ENTRIES = ENTRY_COUNT_(Device, 8);
	static constexpr int DEVICE9_ENTRIES = ENTRY_COUNT_(Device, 9);
	static constexpr int DEVICE10_ENTRIES = ENTRY_COUNT_(Device, 10);
	static constexpr int MAX_DEVICE_ENTRIES = DEVICE10_ENTRIES;

	static constexpr int QUEUE_ENTRIES  = ENTRY_COUNT(Queue);
	static constexpr int ALLOCATOR_ENTRIES  = ENTRY_COUNT(Allocator);

	static constexpr int LIST_ENTRIES  = ENTRY_COUNT(List);
	static constexpr int LIST1_ENTRIES = ENTRY_COUNT_(List, 1);
	static constexpr int LIST2_ENTRIES = ENTRY_COUNT_(List, 2);
	static constexpr int LIST3_ENTRIES = ENTRY_COUNT_(List, 3);
	static constexpr int LIST4_ENTRIES = ENTRY_COUNT_(List, 4);
	static constexpr int LIST5_ENTRIES = ENTRY_COUNT_(List, 5);
	static constexpr int LIST6_ENTRIES = ENTRY_COUNT_(List, 6);
	static constexpr int LIST7_ENTRIES = ENTRY_COUNT_(List, 7);
	static constexpr int MAX_LIST_ENTRIES = LIST7_ENTRIES;

	static constexpr int SWAPCHAIN_ENTRIES  = ENTRY_COUNT(SwapChain);
    static constexpr int SWAPCHAIN1_ENTRIES = ENTRY_COUNT_(SwapChain, 1);
    static constexpr int SWAPCHAIN2_ENTRIES = ENTRY_COUNT_(SwapChain, 2);
    static constexpr int SWAPCHAIN3_ENTRIES = ENTRY_COUNT_(SwapChain, 3);
    static constexpr int MAX_SWAPCHAIN_ENTRIES = SWAPCHAIN3_ENTRIES;
}