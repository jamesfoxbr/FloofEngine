/******************************************************************************************
* FloofEngine DirectX Framework Version 0.1.1                                             *
* Author: Jamesfoxbr                                                                      *
*                                                                                         *
******************************************************************************************/

#ifndef H_ENGINE_H
#define H_ENGINE_H

/******************************************************************************************
*	Includes                                                                              *
******************************************************************************************/
#include <string>
#include <iostream>
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>

using std::string;



/******************************************************************************************
*                                                                                         *
*	Graphic                                                                               *
*                                                                                         *
******************************************************************************************/

class Graphic
{
public:

    // directx
    ID3D11Device* getDevice() const { return m_device; }
    ID3D11DeviceContext* getDeviceContext() const { return m_deviceContext; }

    Graphic(HWND m_hWnd, int m_width, int m_height);
    ~Graphic();

    ID3D11DeviceContext* GetDeviceContext() { return m_deviceContext; }
    IDXGISwapChain* GetSwapChain() { return m_swapChain; }
    ID3D11RenderTargetView* GetRenderTargetView() { return m_renderTargetView; }

private:
    // directx
    ID3D11Device* m_device = nullptr;
    ID3D11DeviceContext* m_deviceContext = nullptr;
    IDXGISwapChain* m_swapChain = nullptr;
    ID3D11RenderTargetView* m_renderTargetView = nullptr;

};

Graphic::Graphic(HWND m_hWnd, int m_width, int m_height)
{
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
        return;
    }

    // Get the back buffer
    ID3D11Texture2D* backBuffer = nullptr;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
    if (FAILED(hr)) {
        MessageBox(nullptr, L"Failed to get back buffer!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Create render target view
    hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
    backBuffer->Release();
    if (FAILED(hr)) {
        MessageBox(nullptr, L"Failed to create render target view!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);
}

Graphic::~Graphic()
{
    // Releasing directx stuff
    if (m_renderTargetView) m_renderTargetView->Release();
    if (m_swapChain) m_swapChain->Release();
    if (m_deviceContext) m_deviceContext->Release();
    if (m_device) m_device->Release();
}






/******************************************************************************************
*                                                                                         *
*	Window                                                                                *
*                                                                                         *
******************************************************************************************/


class Window {
public:

    Window(int width, int height, const std::wstring& title);
    ~Window();

    HWND GetWindowHandler() { return m_hWnd; }
    int GetWindowWidth() { return m_width; }
    int GetWindowHeight() { return m_height; }
    void setTitle(const std::wstring& title);
    void setSize(int width, int height);
    void show();
    void close();

    bool KeyDown(int vkcode);

private:
    HWND m_hWnd;
    int m_width;
    int m_height;
    std::wstring m_title;
};

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





/******************************************************************************************
*                                                                                         *
*	Engine                                                                                *
*                                                                                         *
******************************************************************************************/

class FloofEngine
{
protected:
	string mGameTitle;                                        // game and window title are stored here
	int mWindowWidth = NULL;                                  // window width
	int mWindowHeight = NULL;                                 // window height
	bool mGameRunning = true;                                 // variable to tell if the game is running
                                                             
public:                                                      
	bool start();                                             // start the game engine when a game is read
                                                             
private:                                                     
	virtual bool _init();                                     // Called first time when a game is loaded
	virtual bool _processInput();                             // process player inputs like keyboard and mouse presses 
	virtual bool _update();                                   // updates the game logic every  frame
	virtual bool _draw();                                     // used to put stuff to draw on screen
	virtual bool _close();                                    // called when the game is closed to delete stuff you dynamic loaded.
                                                             
public:                                                      
	Window* window;                                           // The game window
	Graphic* graphic;                                         // the graphics (Direct11 at moment)

	FloofEngine();
	~FloofEngine();

	void ClearScreen(float r, float g, float b, float a);      // Clear the screen to a choose color
	bool KeyPressed(int key) { return window->KeyDown(key); }  // Detect the key pressed
};

bool FloofEngine::start()
{
    // Called first time when a game is loaded
    _init();
    
    /////////////////////////////////////////////////////////////////////////////////////
    //                                  GAME LOOP                                      //
    /////////////////////////////////////////////////////////////////////////////////////
    MSG msg = {};
    while (true) {
        // Message loop
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            switch (msg.message)
            {
            case WM_QUIT:
            {
                // game closed
                _close();

                return static_cast<int>(msg.wParam);
            }
            }
        }

        _processInput();
        _update();
        _draw();
    }

    return false;
}

bool FloofEngine::_init()
{
    return false;
}

bool FloofEngine::_processInput()
{
    return false;
}

bool FloofEngine::_update()
{
    return false;
}

bool FloofEngine::_draw()
{
    return false;
}

bool FloofEngine::_close()
{
    return false;
}

FloofEngine::FloofEngine()
{
    // Create a Window object
    window = new Window(800, 600, L"Main Window");

    // Set window title and size
    window->setTitle(L"New Title");
    window->setSize(1024, 768);

    // start graphic
    graphic = new Graphic(window->GetWindowHandler(), window->GetWindowWidth(), window->GetWindowHeight());

    // Show the window
    window->show();
}

FloofEngine::~FloofEngine()
{
    delete graphic;
    delete window;
}

void FloofEngine::ClearScreen(float r, float g, float b, float a)
{
    // Define the clear color as green (RGBA format)
    const float clearColor[4] = {r, g, b, a}; // R, G, B, A

    // Clear the render target view (back buffer) with the green color
    graphic->GetDeviceContext()->ClearRenderTargetView(graphic->GetRenderTargetView(), clearColor);

    // Present the back buffer to the screen
    graphic->GetSwapChain()->Present(0, 0);
}

#endif // !H_ENGINE_H

