#pragma once

#define ENTRY_COUNT(Class) (Class##_LastEntry - Class##_FirstEntry + 1)

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
		SwapChain_LastEntry = SwapChain_GetLastPresentCount
	};

	static constexpr int DEVICE_ENTRIES = ENTRY_COUNT(Device);
	static constexpr int QUEUE_ENTRIES  = ENTRY_COUNT(Queue);
	static constexpr int ALLOCATOR_ENTRIES  = ENTRY_COUNT(Allocator);
	static constexpr int LIST_ENTRIES  = ENTRY_COUNT(List);
	static constexpr int SWAPCHAIN_ENTRIES  = ENTRY_COUNT(SwapChain);
}