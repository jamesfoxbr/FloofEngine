#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>
#include <iostream>
#include <d3d11.h>
#include <dxgi.h>

class Window {
public:
    Window(int width, int height, const std::wstring& title);
    ~Window();

    void setTitle(const std::wstring& title);
    void setSize(int width, int height);
    void show();
    void close();

    bool KeyDown(int vkcode);
    void ClearScreen(float r, float g, float b, float a);

    // directx
    ID3D11Device* getDevice() const { return m_device; }
    ID3D11DeviceContext* getDeviceContext() const { return m_deviceContext; }

private:
    HWND m_hWnd;
    int m_width;
    int m_height;
    std::wstring m_title;

    // directx
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    IDXGISwapChain* m_swapChain;
    ID3D11RenderTargetView* m_renderTargetView;

};

#endif // WINDOW_H
