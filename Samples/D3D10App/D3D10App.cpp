#include <Windows.h>
#include <D3D10.h>

#pragma comment(lib, "d3d10.lib")

// Parameters
const int WIDTH = 800;
const int HEIGHT = 600;

// Shader
#define SHADER(x) #x

const char* shaderSource = SHADER(
	struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VOut vs_shader(float4 position : POSITION, float4 color : COLOR)
{
	VOut output;

	output.position = position;
	output.color = color;

	return output;
}

float4 ps_shader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
}
);

// Types
struct vec3
{
	float x, y, z;
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct vec4
{
	float x, y, z, w;
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};

struct vertex
{
	vec3 pos;
	vec4 color;
	vertex(vec3 pos, vec4 color) : pos(pos), color(color) {}
};

D3D10_INPUT_ELEMENT_DESC layout[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0}
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"D3DWindow";
	RegisterClass(&wc);

	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	HWND hWnd = CreateWindow(L"D3DWindow", L"Direct3D 10 Triangle", WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE, rect.right / 2 - WIDTH / 2, rect.bottom / 2 - HEIGHT / 2, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = WIDTH;
	swapChainDesc.BufferDesc.Height = HEIGHT;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = true;

	IDXGISwapChain* swapChain;
	ID3D10Device* d3dDevice;
	D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &swapChainDesc, &swapChain, &d3dDevice);
	ID3D10Texture2D* backBuffer;
	ID3D10RenderTargetView* renderTargetView;
	swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&backBuffer);
	d3dDevice->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();
	d3dDevice->OMSetRenderTargets(1, &renderTargetView, NULL);

	D3D10_VIEWPORT viewport;
	viewport.Width = WIDTH;
	viewport.Height = HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	d3dDevice->RSSetViewports(1, &viewport);

	ID3D10Blob* vertexBlob, * pixelBlob;
	ID3D10VertexShader* vertexShader;
	ID3D10PixelShader* pixelShader;

	D3D10CompileShader(shaderSource, strlen(shaderSource), NULL, NULL, NULL, "vs_shader", "vs_4_0", 0, &vertexBlob, NULL);
	d3dDevice->CreateVertexShader((DWORD*)vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &vertexShader);
	d3dDevice->VSSetShader(vertexShader);

	D3D10CompileShader(shaderSource, strlen(shaderSource), NULL, NULL, NULL, "ps_shader", "ps_4_0", 0, &pixelBlob, NULL);
	d3dDevice->CreatePixelShader((DWORD*)pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), &pixelShader);
	d3dDevice->PSSetShader(pixelShader);

	ID3D10InputLayout* vertexLayout;
	d3dDevice->CreateInputLayout(layout, 2, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &vertexLayout);
	d3dDevice->IASetInputLayout(vertexLayout);

	ID3D10Buffer* vertexBuffer;
	D3D10_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(vertex) * 3;
	bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	d3dDevice->CreateBuffer(&bufferDesc, NULL, &vertexBuffer);

	UINT stride = sizeof(vertex);
	UINT offset = 0;
	d3dDevice->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	vertex* vertices;
	vertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&vertices);
	vertices[0] = vertex(vec3(-0.5, -0.5, 0), vec4(1, 0, 0, 1));
	vertices[1] = vertex(vec3(0, 0.5, 0), vec4(0, 1, 0, 1));
	vertices[2] = vertex(vec3(0.5, -0.5, 0), vec4(0, 0, 1, 1));
	vertexBuffer->Unmap();

	D3D10_RASTERIZER_DESC rasterizerDesc;
	rasterizerDesc.CullMode = D3D10_CULL_NONE;
	rasterizerDesc.FillMode = D3D10_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = true;
	rasterizerDesc.DepthBias = false;
	rasterizerDesc.DepthBiasClamp = 0;
	rasterizerDesc.SlopeScaledDepthBias = 0;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.AntialiasedLineEnable = true;

	ID3D10RasterizerState* rasterizerState;
	d3dDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	d3dDevice->RSSetState(rasterizerState);

	d3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//LoadLibrary(L"D3D10Hook.dll");
	while (true)
	{
		// Handle messages
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) break;

		// Clear screen
		float black[4] = { 0, 0, 0, 1 };
		d3dDevice->ClearRenderTargetView(renderTargetView, black);

		// Draw triangle
		d3dDevice->Draw(3, 0);

		// Present
		swapChain->Present(0, 0);
	}

	// Cleanup
	rasterizerState->Release();
	vertexLayout->Release();
	vertexBuffer->Release();
	pixelBlob->Release();
	pixelShader->Release();
	vertexBlob->Release();
	vertexShader->Release();
	renderTargetView->Release();
	swapChain->Release();
	d3dDevice->Release();

	UnregisterClass(L"D3DWindow", hInstance);

	return 0;
}