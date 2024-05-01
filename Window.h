#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>
#include <iostream>

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
    void ClearScreen(float r, float g, float b, float a);
};

#endif // WINDOW_H
