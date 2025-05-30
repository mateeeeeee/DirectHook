#pragma once
#include <d3d10.h>
#include <dxgi.h> 

namespace directhook::d3d10
{
	using PFN_DXGISwapChain_QueryInterface = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFIID, void**);
	using PFN_DXGISwapChain_AddRef = ULONG(STDMETHODCALLTYPE*)(IDXGISwapChain*);
	using PFN_DXGISwapChain_Release = ULONG(STDMETHODCALLTYPE*)(IDXGISwapChain*);
	using PFN_DXGISwapChain_SetPrivateData = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFGUID, UINT, const void*);
	using PFN_DXGISwapChain_SetPrivateDataInterface = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFGUID, const IUnknown*);
	using PFN_DXGISwapChain_GetPrivateData = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFGUID, UINT*, void*);
	using PFN_DXGISwapChain_GetParent = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFIID, void**);
	using PFN_DXGISwapChain_GetDevice = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, REFIID, void**);
	using PFN_DXGISwapChain_Present = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
	using PFN_DXGISwapChain_GetBuffer = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, REFIID, void**);
	using PFN_DXGISwapChain_SetFullscreenState = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, BOOL, IDXGIOutput*);
	using PFN_DXGISwapChain_GetFullscreenState = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, BOOL*, IDXGIOutput**);
	using PFN_DXGISwapChain_GetDesc = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, DXGI_SWAP_CHAIN_DESC*);
	using PFN_DXGISwapChain_ResizeBuffers = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
	using PFN_DXGISwapChain_ResizeTarget = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, const DXGI_MODE_DESC*);
	using PFN_DXGISwapChain_GetContainingOutput = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, IDXGIOutput**);
	using PFN_DXGISwapChain_GetFrameStatistics = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, DXGI_FRAME_STATISTICS*);
	using PFN_DXGISwapChain_GetLastPresentCount = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT*);

	using PFN_D3D10Device_QueryInterface = HRESULT(STDMETHODCALLTYPE*)(IUnknown*, REFIID, void**);
	using PFN_D3D10Device_AddRef = ULONG(STDMETHODCALLTYPE*)(IUnknown*);
	using PFN_D3D10Device_Release = ULONG(STDMETHODCALLTYPE*)(IUnknown*);
	using PFN_D3D10Device_VSSetConstantBuffers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10Buffer**);
	using PFN_D3D10Device_PSSetShaderResources = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10ShaderResourceView**);
	using PFN_D3D10Device_PSSetShader = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10PixelShader*);
	using PFN_D3D10Device_PSSetSamplers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10SamplerState**);
	using PFN_D3D10Device_VSSetShader = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10VertexShader*);
	using PFN_D3D10Device_DrawIndexed = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, INT);
	using PFN_D3D10Device_Draw = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT);
	using PFN_D3D10Device_PSSetConstantBuffers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10Buffer**);
	using PFN_D3D10Device_IASetInputLayout = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10InputLayout*);
	using PFN_D3D10Device_IASetVertexBuffers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10Buffer**, const UINT*, const UINT*);
	using PFN_D3D10Device_IASetIndexBuffer = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Buffer*, DXGI_FORMAT, UINT);
	using PFN_D3D10Device_DrawIndexedInstanced = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, UINT, INT, UINT);
	using PFN_D3D10Device_DrawInstanced = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, UINT, UINT);
	using PFN_D3D10Device_GSSetConstantBuffers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10Buffer**);
	using PFN_D3D10Device_GSSetShader = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10GeometryShader*);
	using PFN_D3D10Device_IASetPrimitiveTopology = void (STDMETHODCALLTYPE*)(ID3D10Device*, D3D10_PRIMITIVE_TOPOLOGY);
	using PFN_D3D10Device_VSSetShaderResources = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10ShaderResourceView**);
	using PFN_D3D10Device_VSSetSamplers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10SamplerState**);
	using PFN_D3D10Device_SetPredication = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Predicate*, BOOL);
	using PFN_D3D10Device_GSSetShaderResources = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10ShaderResourceView**);
	using PFN_D3D10Device_GSSetSamplers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10SamplerState**);
	using PFN_D3D10Device_OMSetRenderTargets = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, ID3D10RenderTargetView**, ID3D10DepthStencilView*);
	using PFN_D3D10Device_OMSetBlendState = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10BlendState*, const FLOAT[4], UINT);
	using PFN_D3D10Device_OMSetDepthStencilState = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10DepthStencilState*, UINT);
	using PFN_D3D10Device_SOSetTargets = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, ID3D10Buffer**, const UINT*);
	using PFN_D3D10Device_DrawAuto = void (STDMETHODCALLTYPE*)(ID3D10Device*);
	using PFN_D3D10Device_RSSetState = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10RasterizerState*);
	using PFN_D3D10Device_RSSetViewports = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, const D3D10_VIEWPORT*);
	using PFN_D3D10Device_RSSetScissorRects = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, const D3D10_RECT*);
	using PFN_D3D10Device_CopySubresourceRegion = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Resource*, UINT, UINT, UINT, UINT, ID3D10Resource*, UINT, const D3D10_BOX*);
	using PFN_D3D10Device_CopyResource = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Resource*, ID3D10Resource*);
	using PFN_D3D10Device_UpdateSubresource = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Resource*, UINT, const D3D10_BOX*, const void*, UINT, UINT);
	using PFN_D3D10Device_ClearRenderTargetView = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10RenderTargetView*, const FLOAT[4]);
	using PFN_D3D10Device_ClearDepthStencilView = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10DepthStencilView*, UINT, FLOAT, UINT8);
	using PFN_D3D10Device_GenerateMips = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10ShaderResourceView*);
	using PFN_D3D10Device_ResolveSubresource = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Resource*, UINT, ID3D10Resource*, UINT, DXGI_FORMAT);
	using PFN_D3D10Device_VSGetConstantBuffers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10Buffer**);
	using PFN_D3D10Device_PSGetShaderResources = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10ShaderResourceView**);
	using PFN_D3D10Device_PSGetShader = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10PixelShader**);
	using PFN_D3D10Device_PSGetSamplers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10SamplerState**);
	using PFN_D3D10Device_VSGetShader = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10VertexShader**);
	using PFN_D3D10Device_PSGetConstantBuffers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10Buffer**);
	using PFN_D3D10Device_IAGetInputLayout = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10InputLayout**);
	using PFN_D3D10Device_IAGetVertexBuffers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10Buffer**, UINT*, UINT*);
	using PFN_D3D10Device_IAGetIndexBuffer = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Buffer**, DXGI_FORMAT*, UINT*);
	using PFN_D3D10Device_GSGetConstantBuffers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10Buffer**);
	using PFN_D3D10Device_GSGetShader = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10GeometryShader**);
	using PFN_D3D10Device_IAGetPrimitiveTopology = void (STDMETHODCALLTYPE*)(ID3D10Device*, D3D10_PRIMITIVE_TOPOLOGY*);
	using PFN_D3D10Device_VSGetShaderResources = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10ShaderResourceView**);
	using PFN_D3D10Device_VSGetSamplers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10SamplerState**);
	using PFN_D3D10Device_GetPredication = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Predicate**, BOOL*);
	using PFN_D3D10Device_GSGetShaderResources = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10ShaderResourceView**);
	using PFN_D3D10Device_GSGetSamplers = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT, ID3D10SamplerState**);
	using PFN_D3D10Device_OMGetRenderTargets = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, ID3D10RenderTargetView**, ID3D10DepthStencilView**);
	using PFN_D3D10Device_OMGetBlendState = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10BlendState**, FLOAT[4], UINT*);
	using PFN_D3D10Device_OMGetDepthStencilState = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10DepthStencilState**, UINT*);
	using PFN_D3D10Device_SOGetTargets = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, ID3D10Buffer**);
	using PFN_D3D10Device_RSGetState = void (STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10RasterizerState**);
	using PFN_D3D10Device_RSGetViewports = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT*, D3D10_VIEWPORT*);
	using PFN_D3D10Device_RSGetScissorRects = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT*, D3D10_RECT*);
	using PFN_D3D10Device_GetDeviceRemovedReason = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*);
	using PFN_D3D10Device_SetExceptionMode = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, UINT);
	using PFN_D3D10Device_GetExceptionMode = UINT(STDMETHODCALLTYPE*)(ID3D10Device*);
	using PFN_D3D10Device_GetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, REFGUID, UINT*, void*);
	using PFN_D3D10Device_SetPrivateData = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, REFGUID, UINT, const void*);
	using PFN_D3D10Device_SetPrivateDataInterface = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, REFGUID, const IUnknown*);
	using PFN_D3D10Device_ClearState = void (STDMETHODCALLTYPE*)(ID3D10Device*);
	using PFN_D3D10Device_Flush = void (STDMETHODCALLTYPE*)(ID3D10Device*);
	using PFN_D3D10Device_CreateBuffer = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_BUFFER_DESC*, const D3D10_SUBRESOURCE_DATA*, ID3D10Buffer**);
	using PFN_D3D10Device_CreateTexture1D = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_TEXTURE1D_DESC*, const D3D10_SUBRESOURCE_DATA*, ID3D10Texture1D**);
	using PFN_D3D10Device_CreateTexture2D = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_TEXTURE2D_DESC*, const D3D10_SUBRESOURCE_DATA*, ID3D10Texture2D**);
	using PFN_D3D10Device_CreateTexture3D = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_TEXTURE3D_DESC*, const D3D10_SUBRESOURCE_DATA*, ID3D10Texture3D**);
	using PFN_D3D10Device_CreateShaderResourceView = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Resource*, const D3D10_SHADER_RESOURCE_VIEW_DESC*, ID3D10ShaderResourceView**);
	using PFN_D3D10Device_CreateRenderTargetView = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Resource*, const D3D10_RENDER_TARGET_VIEW_DESC*, ID3D10RenderTargetView**);
	using PFN_D3D10Device_CreateDepthStencilView = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, ID3D10Resource*, const D3D10_DEPTH_STENCIL_VIEW_DESC*, ID3D10DepthStencilView**);
	using PFN_D3D10Device_CreateInputLayout = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_INPUT_ELEMENT_DESC*, UINT, const void*, SIZE_T, ID3D10InputLayout**);
	using PFN_D3D10Device_CreateVertexShader = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const void*, SIZE_T, ID3D10VertexShader**);
	using PFN_D3D10Device_CreateGeometryShader = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const void*, SIZE_T, ID3D10GeometryShader**);
	using PFN_D3D10Device_CreatePixelShader = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const void*, SIZE_T, ID3D10PixelShader**);
	using PFN_D3D10Device_CreateBlendState = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_BLEND_DESC*, ID3D10BlendState**);
	using PFN_D3D10Device_CreateDepthStencilState = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_DEPTH_STENCIL_DESC*, ID3D10DepthStencilState**);
	using PFN_D3D10Device_CreateRasterizerState = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_RASTERIZER_DESC*, ID3D10RasterizerState**);
	using PFN_D3D10Device_CreateSamplerState = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_SAMPLER_DESC*, ID3D10SamplerState**);
	using PFN_D3D10Device_CreateQuery = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_QUERY_DESC*, ID3D10Query**);
	using PFN_D3D10Device_CreatePredicate = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_QUERY_DESC*, ID3D10Predicate**);
	using PFN_D3D10Device_CreateCounter = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_COUNTER_DESC*, ID3D10Counter**);
	using PFN_D3D10Device_CheckFormatSupport = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, DXGI_FORMAT, UINT*);
	using PFN_D3D10Device_CheckMultisampleQualityLevels = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, DXGI_FORMAT, UINT, UINT*);
	using PFN_D3D10Device_CheckCounterInfo = void (STDMETHODCALLTYPE*)(ID3D10Device*, D3D10_COUNTER_INFO*);
	using PFN_D3D10Device_CheckCounter = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, const D3D10_COUNTER_DESC*, D3D10_COUNTER_TYPE*, UINT*, LPSTR, UINT*, LPSTR, UINT*, LPSTR, UINT*);
	using PFN_D3D10Device_GetCreationFlags = UINT(STDMETHODCALLTYPE*)(ID3D10Device*);
	using PFN_D3D10Device_OpenSharedResource = HRESULT(STDMETHODCALLTYPE*)(ID3D10Device*, HANDLE, REFIID, void**);
	using PFN_D3D10Device_SetTextFilterSize = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT, UINT);
	using PFN_D3D10Device_GetTextFilterSize = void (STDMETHODCALLTYPE*)(ID3D10Device*, UINT*, UINT*);
}