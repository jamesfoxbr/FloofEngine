#ifndef H_GRAPHIC_H
#define H_GRAPHIC_H

#include <d3d11.h>
#include <dxgi.h>
#include <Windows.h>

class Graphic
{
public:
	// directx
	ID3D11Device* getDevice() const { return m_device; }
	ID3D11DeviceContext* getDeviceContext() const { return m_deviceContext; }

	Graphic(HWND m_hWnd, int m_width, int m_height);
	~Graphic();

	ID3D11DeviceContext* GetDeviceContext() {return m_deviceContext; }
	IDXGISwapChain* GetSwapChain() { return m_swapChain; }
	ID3D11RenderTargetView* GetRenderTargetView() { return m_renderTargetView; }

private:
	// directx
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_renderTargetView;

};

#endif // !H_GRAPHIC_H

