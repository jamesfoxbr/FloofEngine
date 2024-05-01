#include "Window.h"

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
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
