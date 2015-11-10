#include "ContextManager.h"

CContextManager::CContextManager(void)
{
	m_D3DDevice = 0;
	m_DeviceContext = 0;
	m_SwapChain = 0;
	m_RenderTargetView = 0;
	m_DepthStencilView = 0;
}

CContextManager::~CContextManager(void)
{
	m_D3DDevice->Release();
	m_DeviceContext->Release();
	m_SwapChain->Release();
	m_RenderTargetView->Release();
	m_DepthStencilView->Release();
}

HRESULT CContextManager::InitDevice(HWND hWnd, int WIDTH_APPLICATION, int HEIGHT_APPLICATION) {
	// Tendremos que crear y rellenar una estructura de este tipo
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// o
	//DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferCount = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Windowed = TRUE;
	desc.BufferDesc.Width = WIDTH_APPLICATION;
	desc.BufferDesc.Height = HEIGHT_APPLICATION;
	desc.BufferDesc.RefreshRate.Numerator = 1;
	desc.BufferDesc.RefreshRate.Denominator = 60;
	desc.OutputWindow = hWnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	// Que DirectX queremos
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	HRESULT result = FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &desc, &m_SwapChain, &m_D3DDevice, NULL, &m_DeviceContext));

	return result;
}

HRESULT CContextManager::CreateRenderTarget() {
	ID3D11Texture2D *pBackBuffer;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
		return FALSE;
	HRESULT hr = m_D3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_RenderTargetView);
	pBackBuffer->Release();

	return hr;
}

HRESULT CContextManager::CreateDepthStencil() {
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	// TODO:
	//desc.Width;
	//desc.Height;
	//desc.MipLevels;
	//desc.ArraySize;
	//desc.SampleDesc.Count;
	//desc.SampleDesc.Quality;
	HRESULT hr = m_D3DDevice->CreateTexture2D(&desc, NULL, &m_DepthStencil);
	return hr;
}

HRESULT CContextManager::CreateDepthStencilView() {
	D3D11_DEPTH_STENCIL_VIEW_DESC desc = {};
	desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;
	// TODO
	//desc.Format;
	HRESULT hr = m_D3DDevice->CreateDepthStencilView(m_DepthStencil, &desc, &m_DepthStencilView);
	return hr;
}

void CContextManager::BeginRender() {
	// Limpiar el framebuffer:
	// ID3D11DeviceContext::ClearRenderTargetView
	// ID3D11DeviceContext::ClearDepthStencilView

	// definir a que target vamos a pintar:
	// ID3D11DeviceContext::OMSetRenderTargets

	// definir el viewport:
	// ID3D11DeviceContext::RSSetViewports

	// TODO renderizar aqui

	// presentar lo pintado:
	// IDXGISwapChain::Present

	// Añadir aquí el Init de la applicacioón
	float color[4] = {1, 1, 0, 1};

	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, color);
	//m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, 0, 1, 1);
	
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);

	D3D11_VIEWPORT viewport = {0, 0, 800, 600, 0, 1};
	m_DeviceContext->RSSetViewports(1, &viewport);

	m_SwapChain->Present(0, 0);
}

void CContextManager::EndRender() {
	m_SwapChain->Present(0, 0);
}