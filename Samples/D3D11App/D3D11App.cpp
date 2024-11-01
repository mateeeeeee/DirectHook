#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <windows.h>
#include <d3d11_2.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <iostream>
#include <string>


HINSTANCE hInst;
HWND hWnd;
ID3D11Device* device = nullptr;
ID3D11DeviceContext* context = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;
ID3D11Buffer* vertexBuffer = nullptr;
ID3D11VertexShader* vertexShader = nullptr;
ID3D11PixelShader* pixelShader = nullptr;
ID3D11InputLayout* inputLayout = nullptr;
IDXGISwapChain* swapChain = nullptr;

struct Vertex 
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;
};


const char* vertexShaderSource = R"(
struct VS_INPUT {
    float4 position : POSITION;
    float4 color : COLOR;
};
struct PS_INPUT {
    float4 position : SV_POSITION;
    float4 color : COLOR;
};
PS_INPUT VS(VS_INPUT input) {
    PS_INPUT output;
    output.position = input.position; // No transformation needed
    output.color = input.color;
    return output;
}
)";

const char* pixelShaderSource = R"(
struct PS_INPUT {
    float4 position : SV_POSITION;
    float4 color : COLOR;
};
float4 PS(PS_INPUT input) : SV_TARGET {
    return input.color;
}
)";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateTriangle() 
{
	Vertex vertices[] = 
	{
		{ { 0.0f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }, // Vertex 1 (Red)
		{ { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }, // Vertex 2 (Green)
		{ {-0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }  // Vertex 3 (Blue)
	};

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;

	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
	if (FAILED(hr)) 
	{
		std::cerr << "Failed to create vertex buffer." << std::endl;
	}
}

ID3DBlob* CompileShader(const char* source, const char* entryPoint, const char* target) 
{
	ID3DBlob* blob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = D3DCompile(source, strlen(source), nullptr, nullptr, nullptr, entryPoint, target, 0, 0, &blob, &errorBlob);

	if (FAILED(hr)) 
	{
		if (errorBlob) 
		{
			std::cerr << "Shader compilation error: " << (char*)errorBlob->GetBufferPointer() << std::endl;
			errorBlob->Release();
		}
		return nullptr;
	}

	return blob;
}

void InitD3D() 
{
	UINT flags = 0;
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = 800;
	swapChainDesc.BufferDesc.Height = 600;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd; 
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain, 
		&device,
		nullptr,
		&context
	);

	if (FAILED(hr)) 
	{
		std::cerr << "Failed to create D3D device and swap chain." << std::endl;
		exit(-1);
	}

	ID3D11Texture2D* backBuffer = nullptr;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (FAILED(hr)) 
	{
		std::cerr << "Failed to get back buffer." << std::endl;
		exit(-1);
	}

	hr = device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
	backBuffer->Release();

	if (FAILED(hr)) 
	{
		std::cerr << "Failed to create render target view." << std::endl;
		exit(-1);
	}

	context->OMSetRenderTargets(1, &renderTargetView, nullptr);

	ID3DBlob* vsBlob = CompileShader(vertexShaderSource, "VS", "vs_5_0");
	device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);

	ID3DBlob* psBlob = CompileShader(pixelShaderSource, "PS", "ps_5_0");
	device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = device->CreateInputLayout(layout, ARRAYSIZE(layout), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
	if (FAILED(hr)) 
	{
		std::cerr << "Failed to create input layout." << std::endl;
	}

	context->IASetInputLayout(inputLayout);

	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);

	CreateTriangle();

	D3D11_VIEWPORT viewport;
	viewport.Width = 800;   
	viewport.Height = 600;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	context->RSSetViewports(1, &viewport);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) 
{
	hInst = hInstance;
	WNDCLASS wc{};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInst;
	wc.lpszClassName = L"D3D11App";

	RegisterClass(&wc);
	hWnd = CreateWindowEx(0, L"D3D11App", L"Direct3D 11 Triangle", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInst, nullptr);
	ShowWindow(hWnd, nShowCmd);

	InitD3D();

	//LoadLibrary(L"D3D11Hook.dll");

	MSG msg{};
	while (msg.message != WM_QUIT) 
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Black
		context->ClearRenderTargetView(renderTargetView, clearColor);
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->Draw(3, 0); 
		swapChain->Present(1, 0);
	}

	if (swapChain) swapChain->Release();
	if (renderTargetView) renderTargetView->Release();
	if (vertexBuffer) vertexBuffer->Release();
	if (vertexShader) vertexShader->Release();
	if (pixelShader) pixelShader->Release();
	if (inputLayout) inputLayout->Release();
	if (context) context->Release();
	if (device) device->Release();

	return static_cast<int>(msg.wParam);
}