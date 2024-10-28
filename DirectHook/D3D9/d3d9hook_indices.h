#pragma once

namespace directhook::d3d9
{
	enum 
	{
		Device_QueryInterface,
		Device_AddRef,
		Device_Release,
		Device_TestCooperativeLevel,
		Device_GetAvailableTextureMem,
		Device_EvictManagedResources,
		Device_GetDirect3D,
		Device_GetDeviceCaps,
		Device_GetDisplayMode,
		Device_GetCreationParameters,
		Device_SetCursorProperties,
		Device_SetCursorPosition,
		Device_ShowCursor,
		Device_CreateAdditionalSwapChain,
		Device_GetSwapChain,
		Device_GetNumberOfSwapChains,
		Device_Reset,
		Device_Present,
		Device_GetBackBuffer,
		Device_GetRasterStatus,
		Device_SetDialogBoxMode,
		Device_SetGammaRamp,
		Device_GetGammaRamp,
		Device_CreateTexture,
		Device_CreateVolumeTexture,
		Device_CreateCubeTexture,
		Device_CreateVertexBuffer,
		Device_CreateIndexBuffer,
		Device_CreateRenderTarget,
		Device_CreateDepthStencilSurface,
		Device_UpdateSurface,
		Device_UpdateTexture,
		Device_GetRenderTargetData,
		Device_GetFrontBufferData,
		Device_StretchRect,
		Device_ColorFill,
		Device_CreateOffscreenPlainSurface,
		Device_SetRenderTarget,
		Device_GetRenderTarget,
		Device_SetDepthStencilSurface,
		Device_GetDepthStencilSurface,
		Device_BeginScene,
		Device_EndScene,
		Device_Clear,
		Device_SetTransform,
		Device_GetTransform,
		Device_MultiplyTransform,
		Device_SetViewport,
		Device_GetViewport,
		Device_SetMaterial,
		Device_GetMaterial,
		Device_SetLight,
		Device_GetLight,
		Device_LightEnable,
		Device_GetLightEnable,
		Device_SetClipPlane,
		Device_GetClipPlane,
		Device_SetRenderState,
		Device_GetRenderState,
		Device_CreateStateBlock,
		Device_BeginStateBlock,
		Device_EndStateBlock,
		Device_SetClipStatus,
		Device_GetClipStatus,
		Device_GetTexture,
		Device_SetTexture,
		Device_GetTextureStageState,
		Device_SetTextureStageState,
		Device_GetSamplerState,
		Device_SetSamplerState,
		Device_ValidateDevice,
		Device_SetPaletteEntries,
		Device_GetPaletteEntries,
		Device_SetCurrentTexturePalette,
		Device_GetCurrentTexturePalette,
		Device_SetScissorRect,
		Device_GetScissorRect,
		Device_SetSoftwareVertexProcessing,
		Device_GetSoftwareVertexProcessing,
		Device_SetNPatchMode,
		Device_GetNPatchMode,
		Device_DrawPrimitive,
		Device_DrawIndexedPrimitive,
		Device_DrawPrimitiveUP,
		Device_DrawIndexedPrimitiveUP,
		Device_ProcessVertices,
		Device_CreateVertexDeclaration,
		Device_SetVertexDeclaration,
		Device_GetVertexDeclaration,
		Device_SetFVF,
		Device_GetFVF,
		Device_CreateVertexShader,
		Device_SetVertexShader,
		Device_GetVertexShader,
		Device_SetVertexShaderConstantF,
		Device_GetVertexShaderConstantF,
		Device_SetVertexShaderConstantI,
		Device_GetVertexShaderConstantI,
		Device_SetVertexShaderConstantB,
		Device_GetVertexShaderConstantB,
		Device_SetStreamSource,
		Device_GetStreamSource,
		Device_SetStreamSourceFreq,
		Device_GetStreamSourceFreq,
		Device_SetIndices,
		Device_GetIndices,
		Device_CreatePixelShader,
		Device_SetPixelShader,
		Device_GetPixelShader,
		Device_SetPixelShaderConstantF,
		Device_GetPixelShaderConstantF,
		Device_SetPixelShaderConstantI,
		Device_GetPixelShaderConstantI,
		Device_SetPixelShaderConstantB,
		Device_GetPixelShaderConstantB,
		Device_DrawRectPatch,
		Device_DrawTriPatch,
		Device_DeletePatch,
		Device_CreateQuery,
		Device_EntriesCount
	};

	static constexpr int DEVICE_ENTRIES = Device_EntriesCount;

}