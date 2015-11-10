#include <d3d11.h>
#pragma once

#define GETR(Type, MemberName, FaceName) \
    Type Get##FaceName() { \
        return MemberName; \
    }

class CContextManager
{
private:
	ID3D11Device *m_D3DDevice; // esta clase, el device, nos sirve para crear objetos de DirectX
	ID3D11DeviceContext *m_DeviceContext; // el contexto nos va a servir para usar objetos de DirectX
	IDXGISwapChain *m_SwapChain; // la cadena de swap
	ID3D11RenderTargetView *m_RenderTargetView;
	ID3D11Texture2D *m_DepthStencil;
	ID3D11DepthStencilView *m_DepthStencilView;

public:
	CContextManager(void);
	~CContextManager(void);
	HRESULT InitDevice(HWND hWnd, int WIDTH_APPLICATION, int HEIGHT_APPLICATION);
	HRESULT CreateRenderTarget();
	HRESULT CreateDepthStencil();
	HRESULT CreateDepthStencilView();
	void BeginRender();
	void EndRender();
	GETR(ID3D11Device *, m_D3DDevice, Device);
	GETR(ID3D11DeviceContext *, m_DeviceContext, DeviceContext);
	GETR(IDXGISwapChain *, m_SwapChain, SwapChain);
	GETR(ID3D11RenderTargetView *, m_RenderTargetView, RenderTargetView);
	GETR(ID3D11DepthStencilView *, m_DepthStencilView, DepthStencilView);
};

