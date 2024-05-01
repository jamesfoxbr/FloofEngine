#include "Window.h"

bool Key[256] = {0};                      // mouse and keyboard button/key states

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Window::Window(int width, int height, const std::wstring& title)
    : m_hWnd(nullptr), m_width(width), m_height(height), m_title(title) {
    
    // Register window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"WindowClass";
    RegisterClass(&wc);

    // Create window
    m_hWnd = CreateWindow(L"WindowClass", m_title.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        m_width, m_height, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!m_hWnd) {
        // Handle window creation failure
        MessageBox(NULL, L"Window creation failed!", L"Error", MB_ICONERROR | MB_OK);
    }

    // Initialize DirectX 11
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = m_width;
    swapChainDesc.BufferDesc.Height = m_height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = m_hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0};
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, numFeatureLevels,
        D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, nullptr, &m_deviceContext);
    if (FAILED(hr)) {
        MessageBox(nullptr, L"Failed to initialize DirectX 11!", L"Error", MB_OK | MB_ICONERROR);
        close();
        return;
    }

    // Get the back buffer
    ID3D11Texture2D* backBuffer = nullptr;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
    if (FAILED(hr)) {
        MessageBox(nullptr, L"Failed to get back buffer!", L"Error", MB_OK | MB_ICONERROR);
        close();
        return;
    }

    // Create render target view
    hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
    backBuffer->Release();
    if (FAILED(hr)) {
        MessageBox(nullptr, L"Failed to create render target view!", L"Error", MB_OK | MB_ICONERROR);
        close();
        return;
    }

    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);
}

Window::~Window() {
    close();
}

void Window::setTitle(const std::wstring& title) {
    m_title = title;
    SetWindowText(m_hWnd, m_title.c_str());
}

void Window::setSize(int width, int height) {
    m_width = width;
    m_height = height;
    RECT rect = {0, 0, m_width, m_height};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(m_hWnd, NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
}

void Window::show() {
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
}

void Window::close() {
    if (m_hWnd) {
        if (m_renderTargetView) m_renderTargetView->Release();
        if (m_swapChain) m_swapChain->Release();
        if (m_deviceContext) m_deviceContext->Release();
        if (m_device) m_device->Release();

        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }
}

bool Window::KeyDown(int vkcode)
{
    return Key[vkcode];
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {    
    switch (msg) {
    case WM_KEYDOWN:
    {
        std::cout << "key pressed\n";
        Key[wParam] = true;
        break;
    }
    case WM_KEYUP:
    {
        std::cout << "key released\n";
        Key[wParam] = false;
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}



