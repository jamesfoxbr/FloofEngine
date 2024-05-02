#ifndef H_ENGINE_H
#define H_ENGINE_H

#include <string>
#include <iostream>
#include <SDL.h>

using std::string;

class Graphic
{
public:
    Graphic(SDL_Window* window);
    ~Graphic();

    SDL_Renderer* GetRenderer() const { return m_renderer; }

    void ClearScreen();
    void ClearScreen(int r, int g, int b);    
    void DrawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);

private:
    SDL_Renderer* m_renderer = nullptr;
};

Graphic::Graphic(SDL_Window* window)
{
    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    }
}

Graphic::~Graphic()
{
    if (m_renderer != nullptr) {
        SDL_DestroyRenderer(m_renderer);
    }
}

void Graphic::ClearScreen()
{
    ClearScreen(0, 0, 0);
}

void Graphic::ClearScreen(int r, int g, int b)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, SDL_ALPHA_OPAQUE); // Set the color to black
    SDL_RenderClear(m_renderer); // Clear the renderer with the black color
}

void Graphic::DrawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(m_renderer, x, y);
    SDL_RenderPresent(m_renderer); // Render the changes immediately
}






class Window {
public:
    Window(int width, int height, const std::wstring& title);
    ~Window();

    SDL_Window* GetWindowHandler() { return m_window; }
    int GetWindowWidth() { return m_width; }
    int GetWindowHeight() { return m_height; }
    void setTitle(const std::wstring& title);
    void setSize(int width, int height);
    void show();
    void close();

    bool KeyDown(SDL_Scancode scancode);

private:
    SDL_Window* m_window = nullptr;
    int m_width;
    int m_height;
    std::wstring m_title;
};

bool Key[256] = {0};

Window::Window(int width, int height, const std::wstring& title)
    : m_window(nullptr), m_width(width), m_height(height), m_title(title) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return;
    }
}

Window::~Window() {
    close();
}

void Window::setTitle(const std::wstring& title) {
    m_title = title;
    SDL_SetWindowTitle(m_window, "Window Title");
}

void Window::setSize(int width, int height) {
    m_width = width;
    m_height = height;
    SDL_SetWindowSize(m_window, m_width, m_height);
}

void Window::show() {
    SDL_ShowWindow(m_window);
}

void Window::close() {
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}

bool Window::KeyDown(SDL_Scancode scancode)
{
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    return state[scancode];
}

class FloofEngine
{
protected:
    string mGameTitle;
    int mWindowWidth = 0;
    int mWindowHeight = 0;
    bool mGameRunning = true;

public:
    bool start();

private:
    virtual bool _init();
    virtual bool _processInput();
    virtual bool _update();
    virtual bool _draw();
    virtual bool _close();

public:
    Window* window;
    Graphic* graphic;

    FloofEngine();
    ~FloofEngine();

    void ClearScreen(float r, float g, float b, float a);
    bool KeyPressed(SDL_Scancode scancode) { return window->KeyDown(scancode); }
};

bool FloofEngine::start()
{
    _init();

    SDL_Event event;
    while (mGameRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                _close();
                return false;
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
    window = new Window(800, 600, L"Main Window");
    window->setTitle(L"New Title");
    window->setSize(1024, 768);

    graphic = new Graphic(window->GetWindowHandler());

    window->show();

    return true;
}

bool FloofEngine::_processInput()
{
    return true;
}

bool FloofEngine::_update()
{
    return true;
}

bool FloofEngine::_draw()
{
    ClearScreen(0, 0, 0, 1);
    return true;
}

bool FloofEngine::_close()
{
    delete graphic;
    delete window;
    mGameRunning = false;
    return true;
}

FloofEngine::FloofEngine()
{
    window = new Window(600, 600, L"Main Window");
    window->setTitle(L"New Title");
    window->setSize(1024, 768);

    graphic = new Graphic(window->GetWindowHandler());

    window->show();
}

FloofEngine::~FloofEngine()
{
}

void FloofEngine::ClearScreen(float r, float g, float b, float a)
{
    SDL_SetRenderDrawColor(graphic->GetRenderer(), static_cast<Uint8>(r * 255), static_cast<Uint8>(g * 255), static_cast<Uint8>(b * 255), static_cast<Uint8>(a * 255));
    SDL_RenderClear(graphic->GetRenderer());
    SDL_RenderPresent(graphic->GetRenderer());
}

#endif // !H_ENGINE_H
