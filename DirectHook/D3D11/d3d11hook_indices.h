#pragma once

#define ENTRY_COUNT(Class) (Class##_LastEntry - Class##_FirstEntry + 1)

namespace directhook::d3d11
{
	enum 
	{
		SwapChain_FirstEntry = 0,
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
		Device_FirstEntry,
		Device_QueryInterface = Device_FirstEntry,
		Device_AddRef,
		Device_Release,
		Device_CreateBuffer,
		Device_CreateTexture1D,
		Device_CreateTexture2D,
		Device_CreateTexture3D,
		Device_CreateShaderResourceView,
		Device_CreateUnorderedAccessView,
		Device_CreateRenderTargetView,
		Device_CreateDepthStencilView,
		Device_CreateInputLayout,
		Device_CreateVertexShader,
		Device_CreateGeometryShader,
		Device_CreateGeometryShaderWithStreamOutput,
		Device_CreatePixelShader,
		Device_CreateHullShader,
		Device_CreateDomainShader,
		Device_CreateComputeShader,
		Device_CreateClassLinkage,
		Device_CreateBlendState,
		Device_CreateDepthStencilState,
		Device_CreateRasterizerState,
		Device_CreateSamplerState,
		Device_CreateQuery,
		Device_CreatePredicate,
		Device_CreateCounter,
		Device_CreateDeferredContext,
		Device_OpenSharedResource,
		Device_CheckFormatSupport,
		Device_CheckMultisampleQualityLevels,
		Device_CheckCounterInfo,
		Device_CheckCounter,
		Device_CheckFeatureSupport,
		Device_GetPrivateData,
		Device_SetPrivateData,
		Device_SetPrivateDataInterface,
		Device_GetFeatureLevel,
		Device_GetCreationFlags,
		Device_GetDeviceRemovedReason,
		Device_GetImmediateContext,
		Device_SetExceptionMode,
		Device_GetExceptionMode,
		Device_LastEntry = Device_GetExceptionMode,
		Context_FirstEntry,
		Context_QueryInterface = Context_FirstEntry,
		Context_AddRef,
		Context_Release,
		Context_GetDevice,
		Context_GetPrivateData,
		Context_SetPrivateData,
		Context_SetPrivateDataInterface,
		Context_VSSetConstantBuffers,
		Context_PSSetShaderResources,
		Context_PSSetShader,
		Context_PSSetSamplers,
		Context_VSSetShader,
		Context_DrawIndexed,
		Context_Draw,
		Context_Map,
		Context_Unmap,
		Context_PSSetConstantBuffers,
		Context_IASetInputLayout,
		Context_IASetVertexBuffers,
		Context_IASetIndexBuffer,
		Context_DrawIndexedInstanced,
		Context_DrawInstanced,
		Context_GSSetConstantBuffers,
		Context_GSSetShader,
		Context_IASetPrimitiveTopology,
		Context_VSSetShaderResources,
		Context_VSSetSamplers,
		Context_Begin,
		Context_End,
		Context_GetData,
		Context_SetPredication,
		Context_GSSetShaderResources,
		Context_GSSetSamplers,
		Context_OMSetRenderTargets,
		Context_OMSetRenderTargetsAndUnorderedAccessViews,
		Context_OMSetBlendState,
		Context_OMSetDepthStencilState,
		Context_SOSetTargets,
		Context_DrawAuto,
		Context_DrawIndexedInstancedIndirect,
		Context_DrawInstancedIndirect,
		Context_Dispatch,
		Context_DispatchIndirect,
		Context_RSSetState,
		Context_RSSetViewports,
		Context_RSSetScissorRects,
		Context_CopySubresourceRegion,
		Context_CopyResource,
		Context_UpdateSubresource,
		Context_CopyStructureCount,
		Context_ClearRenderTargetView,
		Context_ClearUnorderedAccessViewUint,
		Context_ClearUnorderedAccessViewFloat,
		Context_ClearDepthStencilView,
		Context_GenerateMips,
		Context_SetResourceMinLOD,
		Context_GetResourceMinLOD,
		Context_ResolveSubresource,
		Context_ExecuteCommandList,
		Context_HSSetShaderResources,
		Context_HSSetShader,
		Context_HSSetSamplers,
		Context_HSSetConstantBuffers,
		Context_DSSetShaderResources,
		Context_DSSetShader,
		Context_DSSetSamplers,
		Context_DSSetConstantBuffers,
		Context_CSSetShaderResources,
		Context_CSSetUnorderedAccessViews,
		Context_CSSetShader,
		Context_CSSetSamplers,
		Context_CSSetConstantBuffers,
		Context_VSGetConstantBuffers,
		Context_PSGetShaderResources,
		Context_PSGetShader,
		Context_PSGetSamplers,
		Context_VSGetShader,
		Context_PSGetConstantBuffers,
		Context_IAGetInputLayout,
		Context_IAGetVertexBuffers,
		Context_IAGetIndexBuffer,
		Context_GSGetConstantBuffers,
		Context_GSGetShader,
		Context_IAGetPrimitiveTopology,
		Context_VSGetShaderResources,
		Context_VSGetSamplers,
		Context_GetPredication,
		Context_GSGetShaderResources,
		Context_GSGetSamplers,
		Context_OMGetRenderTargets,
		Context_OMGetRenderTargetsAndUnorderedAccessViews,
		Context_OMGetBlendState,
		Context_OMGetDepthStencilState,
		Context_SOGetTargets,
		Context_RSGetState,
		Context_RSGetViewports,
		Context_RSGetScissorRects,
		Context_HSGetShaderResources,
		Context_HSGetShader,
		Context_HSGetSamplers,
		Context_HSGetConstantBuffers,
		Context_DSGetShaderResources,
		Context_DSGetShader,
		Context_DSGetSamplers,
		Context_DSGetConstantBuffers,
		Context_CSGetShaderResources,
		Context_CSGetUnorderedAccessViews,
		Context_CSGetShader,
		Context_CSGetSamplers,
		Context_CSGetConstantBuffers,
		Context_ClearState,
		Context_Flush,
		Context_GetType,
		Context_GetContextFlags,
		Context_FinishCommandList,
		Context_CopySubresourceRegion1,
		Context_UpdateSubresource1,
		Context_DiscardResource,
		Context_DiscardView,
		Context_VSSetConstantBuffers1,
		Context_HSSetConstantBuffers1,
		Context_DSSetConstantBuffers1,
		Context_GSSetConstantBuffers1,
		Context_PSSetConstantBuffers1,
		Context_CSSetConstantBuffers1,
		Context_VSGetConstantBuffers1,
		Context_HSGetConstantBuffers1,
		Context_DSGetConstantBuffers1,
		Context_GSGetConstantBuffers1,
		Context_PSGetConstantBuffers1,
		Context_CSGetConstantBuffers1,
		Context_SwapDeviceContextState,
		Context_ClearView,
		Context_DiscardView1,
		Context_UpdateTileMappings,
		Context_CopyTileMappings,
		Context_CopyTiles,
		Context_UpdateTiles,
		Context_ResizeTilePool,
		Context_TiledResourceBarrier,
		Context_IsAnnotationEnabled,
		Context_SetMarkerInt,
		Context_BeginEventInt,
		Context_EndEvent,
		Context_LastEntry = Context_EndEvent
	};

	static constexpr int SWAPCHAIN_ENTRIES = ENTRY_COUNT(SwapChain);
	static constexpr int DEVICE_ENTRIES = ENTRY_COUNT(Device);
	static constexpr int CONTEXT_ENTRIES = ENTRY_COUNT(Context);
}