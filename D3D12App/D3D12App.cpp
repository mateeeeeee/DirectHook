#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include "d3dx12.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

const char* const ShaderString =
"struct VertexShaderOutput\n"
"{\n"
"    float4 position : SV_POSITION;\n"
"    float2 uv : TEXCOORD;\n"
"};\n"
"VertexShaderOutput DefaultVertexShader(float4 position : POSITION, float2 uv : TEXCOORD)\n"
"{\n"
"    VertexShaderOutput output;\n"
"    output.position = position;\n"
"    output.uv = uv;\n"
"    return output;\n"
"}\n"
"float4 DefaultFragmentShader(VertexShaderOutput input) : SV_TARGET\n"
"{\n"
"    // Define four corner colors for interpolation\n"
"    float4 colorTL = float4(1.0f, 0.0f, 0.0f, 1.0f); // Top-Left (Red)\n"
"    float4 colorTR = float4(0.0f, 1.0f, 0.0f, 1.0f); // Top-Right (Green)\n"
"    float4 colorBL = float4(0.0f, 0.0f, 1.0f, 1.0f); // Bottom-Left (Blue)\n"
"    float4 colorBR = float4(1.0f, 1.0f, 0.0f, 1.0f); // Bottom-Right (Yellow)\n"
"\n"
"    // Interpolate colors based on UV coordinates\n"
"    float4 topColor = lerp(colorTL, colorTR, input.uv.x); // Interpolate top colors\n"
"    float4 bottomColor = lerp(colorBL, colorBR, input.uv.x); // Interpolate bottom colors\n"
"    float4 finalColor = lerp(topColor, bottomColor, input.uv.y); // Interpolate between top and bottom\n"
"\n"
"    return finalColor;\n"
"}\n";
static const wchar_t* const ClassName = L"TRIANGLE 3D12";
static const wchar_t* const WindowTitle = L"Hello Triangle D3D12";
static const unsigned int WindowWidth = 960U;
static const unsigned int WindowHeight = 544U;
static const unsigned int BackBufferCount = 3U;


LRESULT WINAPI WindowCallback(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(wnd, WM_CLOSE, 0U, 0U);
			break;
		}
		return 0;
	}

	return DefWindowProc(wnd, msg, wParam, lParam);
}


int WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR, _In_ int)
{
	ID3D12Device* device;
	IDXGISwapChain* swapChain;
	ID3D12Fence* frameFences[BackBufferCount];
	UINT64 fenceValues[BackBufferCount];
	HANDLE frameFenceEvents[BackBufferCount];
	UINT64 currentFenceValue = 1U;
	ID3D12Resource* renderTargets[BackBufferCount];
	ID3D12DescriptorHeap* renderTargetDescriptorHeap;
	UINT renderTargetViewDescriptorSize;
	ID3D12CommandQueue* commandQueue;
	ID3D12CommandAllocator* commandAllocators[BackBufferCount];
	ID3D12GraphicsCommandList* commandLists[BackBufferCount];
	unsigned int currentBackBuffer = 0U;
	ID3D12RootSignature* rootSignature;
	ID3D12PipelineState* pso;
	D3D12_VIEWPORT viewport;
	D3D12_RECT scissorRect;
	ID3D12Resource* uploadBuffer;
	ID3D12Resource* vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView;

	HWND hwnd;
	WNDCLASSEX wndClass;
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wndClass.hbrBackground = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = instance;
	wndClass.lpfnWndProc = &WindowCallback;
	wndClass.lpszClassName = ClassName;
	RegisterClassEx(&wndClass);

	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	DWORD exStyle = 0U;
	RECT rect = { 0, 0, (LONG)WindowWidth, (LONG)WindowHeight };
	AdjustWindowRectEx(&rect, style, FALSE, exStyle);

	hwnd = CreateWindowEx(
		exStyle,
		ClassName,
		WindowTitle,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		instance,
		NULL
	);

	HRESULT result = D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

	D3D12_COMMAND_QUEUE_DESC queueDesc;
	ZeroMemory(&queueDesc, sizeof(queueDesc));
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	result = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));
	if (FAILED(result)) return EXIT_FAILURE;

	IDXGIFactory4* dxgiFactory;
	result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferDesc.Width = WindowWidth;
	sd.BufferDesc.Height = WindowHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1U;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = BackBufferCount;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	result = dxgiFactory->CreateSwapChain(commandQueue, &sd, &swapChain);
	dxgiFactory->Release();

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
	ZeroMemory(&heapDesc, sizeof(heapDesc));
	heapDesc.NumDescriptors = BackBufferCount;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&renderTargetDescriptorHeap));
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle{ renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart() };
	renderTargetViewDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	unsigned int i;
	for (i = 0U; i < BackBufferCount; ++i)
	{
		D3D12_RENDER_TARGET_VIEW_DESC viewDesc;
		ZeroMemory(&viewDesc, sizeof(viewDesc));
		viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		viewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		viewDesc.Texture2D.MipSlice = 0U;
		viewDesc.Texture2D.PlaneSlice = 0U;
		swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargets[i]));
		device->CreateRenderTargetView(renderTargets[i], &viewDesc, rtvHandle);
		rtvHandle.Offset(renderTargetViewDescriptorSize);
	}

	scissorRect = { 0, 0, (LONG)WindowWidth, (LONG)WindowHeight };
	viewport = { 0.0f, 0.0f, (FLOAT)WindowWidth, (FLOAT)WindowHeight, 0.0f, 1.0f };

	static const D3D12_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0U, DXGI_FORMAT_R32G32B32_FLOAT, 0U, 0U, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0U},
		{"TEXCOORD", 0U, DXGI_FORMAT_R32G32_FLOAT, 0U, 12U, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0U}
	};

	CD3DX12_ROOT_PARAMETER parameters[1U];
	parameters[0U].InitAsConstantBufferView(0U, 0U, D3D12_SHADER_VISIBILITY_VERTEX);
	CD3DX12_ROOT_SIGNATURE_DESC descRootSignature;
	descRootSignature.Init(1U, parameters, 0U, NULL, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	ID3DBlob* rootBlob;
	ID3DBlob* errorBlob;
	D3D12SerializeRootSignature(&descRootSignature, D3D_ROOT_SIGNATURE_VERSION_1, &rootBlob, &errorBlob);
	device->CreateRootSignature(0U, rootBlob->GetBufferPointer(), rootBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));

	ID3DBlob* vertexShader;
	result = D3DCompile(ShaderString, strlen(ShaderString), "", NULL, NULL, "DefaultVertexShader", "vs_5_0", 0U, 0U, &vertexShader, NULL);
	ID3DBlob* pixelShader;
	result = D3DCompile(ShaderString, strlen(ShaderString), "", NULL, NULL, "DefaultFragmentShader", "ps_5_0", 0U, 0U, &pixelShader, NULL);

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(psoDesc));
	psoDesc.VS.BytecodeLength = vertexShader->GetBufferSize();
	psoDesc.VS.pShaderBytecode = vertexShader->GetBufferPointer();
	psoDesc.PS.BytecodeLength = pixelShader->GetBufferSize();
	psoDesc.PS.pShaderBytecode = pixelShader->GetBufferPointer();
	psoDesc.pRootSignature = rootSignature;
	psoDesc.NumRenderTargets = 1U;
	psoDesc.RTVFormats[0U] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	psoDesc.DSVFormat = DXGI_FORMAT_UNKNOWN;
	psoDesc.InputLayout.NumElements = 2U;
	psoDesc.InputLayout.pInputElementDescs = layout;
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.SampleDesc.Count = 1U;
	psoDesc.DepthStencilState.DepthEnable = FALSE;
	psoDesc.DepthStencilState.StencilEnable = FALSE;
	psoDesc.SampleMask = 0xffffffff;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	result = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pso));
	if (FAILED(result)) return EXIT_FAILURE;

	struct Vertex
	{
		float position[3U];
		float uv[2U];
	};
	static const Vertex vertices[3U] =
	{
		{{-1.0f, -1.0f, 0.0f}, { 0.0f, 0.0f}},
		{{ 0.0f,  1.0f, 0.0f}, { 1.0f, 0.0f}},
		{{ 1.0f, -1.0f, 0.0f}, { 1.0f, 1.0f}}
	};

	static const UINT64 uploadBufferSize = sizeof(vertices);
	static const CD3DX12_HEAP_PROPERTIES uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	static const CD3DX12_RESOURCE_DESC uploadBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);

	result = device->CreateCommittedResource(
		&uploadHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&uploadBufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		NULL,
		IID_PPV_ARGS(&uploadBuffer)
	);
	if (FAILED(result)) return EXIT_FAILURE;

	void* p;
	uploadBuffer->Map(0U, NULL, &p);
	memcpy(p, vertices, sizeof(vertices));
	uploadBuffer->Unmap(0U, NULL);

	static const CD3DX12_HEAP_PROPERTIES defaultHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	static const CD3DX12_RESOURCE_DESC vertexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(vertices));
	result = device->CreateCommittedResource(
		&defaultHeapProperties,
		D3D12_HEAP_FLAG_NONE,
		&vertexBufferDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		NULL,
		IID_PPV_ARGS(&vertexBuffer)
	);
	if (FAILED(result)) return EXIT_FAILURE;
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(vertices);
	vertexBufferView.StrideInBytes = sizeof(Vertex);

	ID3D12CommandAllocator* uploadCommandAllocator;
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&uploadCommandAllocator));
	if (FAILED(result)) return EXIT_FAILURE;
	ID3D12GraphicsCommandList* uploadCommandList;
	device->CreateCommandList(0U, D3D12_COMMAND_LIST_TYPE_DIRECT, uploadCommandAllocator, NULL, IID_PPV_ARGS(&uploadCommandList));
	uploadCommandList->CopyBufferRegion(vertexBuffer, 0U, uploadBuffer, 0U, sizeof(vertices));
	const CD3DX12_RESOURCE_BARRIER barriers[1U] =
	{
		CD3DX12_RESOURCE_BARRIER::Transition(vertexBuffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER)
	};
	uploadCommandList->ResourceBarrier(1U, barriers);
	uploadCommandList->Close();

	/* execute the upload and finish the command list */
	ID3D12CommandList* uploadCommandLists[] = { uploadCommandList };
	commandQueue->ExecuteCommandLists(1U, uploadCommandLists);
	ID3D12Fence* uploadFence;
	device->CreateFence(0U, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&uploadFence));
	commandQueue->Signal(uploadFence, 1U); /* let gpu signal the fence when uploadCommandList has finished */
	HANDLE waitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (NULL == waitEvent) return EXIT_FAILURE;
	if (uploadFence->GetCompletedValue() < 1U)
	{
		uploadFence->SetEventOnCompletion(1U, waitEvent);
		WaitForSingleObject(waitEvent, INFINITE);
	}
	uploadCommandAllocator->Reset();
	CloseHandle(waitEvent);
	uploadFence->Release();
	uploadCommandList->Release();
	uploadCommandAllocator->Release();

	for (i = 0U; i < BackBufferCount; ++i)
	{
		frameFenceEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (NULL == frameFenceEvents[i]) return EXIT_FAILURE;
		fenceValues[i] = 0U;
		result = device->CreateFence(0U, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&frameFences[i]));
		if (FAILED(result)) return EXIT_FAILURE;
	}

	for (i = 0U; i < BackBufferCount; ++i)
	{
		result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocators[i]));
		if (FAILED(result)) return EXIT_FAILURE;
		device->CreateCommandList(0U, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocators[i], NULL, IID_PPV_ARGS(&commandLists[i]));
		commandLists[i]->Close();
	}

	//usually the dll would be injected, not loaded by the app, this is just for demonstration
	LoadLibrary(L"D3D12Hook.dll");

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (frameFences[currentBackBuffer]->GetCompletedValue() < fenceValues[currentBackBuffer])
		{
			frameFences[currentBackBuffer]->SetEventOnCompletion(fenceValues[currentBackBuffer], frameFenceEvents[currentBackBuffer]);
			WaitForSingleObject(frameFenceEvents[currentBackBuffer], INFINITE);
		}

		commandAllocators[currentBackBuffer]->Reset();
		ID3D12GraphicsCommandList* commandList = commandLists[currentBackBuffer];
		commandList->Reset(commandAllocators[currentBackBuffer], NULL);

		D3D12_CPU_DESCRIPTOR_HANDLE renderTargetHandle;
		CD3DX12_CPU_DESCRIPTOR_HANDLE::InitOffsetted(
			renderTargetHandle,
			renderTargetDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
			currentBackBuffer,
			renderTargetViewDescriptorSize
		);
		commandList->OMSetRenderTargets(1U, &renderTargetHandle, TRUE, NULL);
		commandList->RSSetViewports(1U, &viewport);
		commandList->RSSetScissorRects(1U, &scissorRect);

		D3D12_RESOURCE_BARRIER rtBarrier;
		rtBarrier.Transition.pResource = renderTargets[currentBackBuffer];
		rtBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		rtBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		rtBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		rtBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		rtBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		commandList->ResourceBarrier(1U, &rtBarrier);

		static const float ClearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		commandList->ClearRenderTargetView(renderTargetHandle, ClearColor, 0U, NULL);
		commandList->SetPipelineState(pso);
		commandList->SetGraphicsRootSignature(rootSignature);
		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		commandList->IASetVertexBuffers(0U, 1U, &vertexBufferView);
		commandList->DrawInstanced(3U, 1U, 0U, 0U);

		D3D12_RESOURCE_BARRIER presentBarrier;
		presentBarrier.Transition.pResource = renderTargets[currentBackBuffer];
		presentBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		presentBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		presentBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		presentBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		presentBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		commandList->ResourceBarrier(1U, &presentBarrier);

		commandList->Close();
		ID3D12CommandList* renderCommandLists[] = { commandList };
		commandQueue->ExecuteCommandLists(1, renderCommandLists);

		swapChain->Present(1U, 0U);

		const UINT64 fenceValue = currentFenceValue;
		commandQueue->Signal(frameFences[currentBackBuffer], fenceValue);
		fenceValues[currentBackBuffer] = fenceValue;
		++currentFenceValue;
		currentBackBuffer = (currentBackBuffer + 1U) % BackBufferCount;
	}

	uploadBuffer->Release();
	vertexBuffer->Release();
	rootSignature->Release();
	vertexShader->Release();
	pixelShader->Release();
	commandQueue->Release();
	for (i = 0U; i < BackBufferCount; ++i)
	{
		renderTargets[i]->Release();
		commandLists[i]->Release();
		commandAllocators[i]->Release();
		CloseHandle(frameFenceEvents[i]);
		frameFences[i]->Release();
	}
	pso->Release();
	renderTargetDescriptorHeap->Release();
	device->Release();
	swapChain->Release();

	return 0;
}