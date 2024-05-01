#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>

class Window {
public:
    WPARAM mWParam;

    Window(int width, int height, const std::wstring& title);
    ~Window();

    void setTitle(const std::wstring& title);
    void setSize(int width, int height);
    void show();
    void close();

private:
    HWND m_hWnd;
    int m_width;
    int m_height;
    std::wstring m_title;
};

#endif // WINDOW_H
