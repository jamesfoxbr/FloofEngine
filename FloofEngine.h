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
    
    void ClearScreen(float r, float g, float b, float a);
    void ClearScreen();
    void DrawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
    void drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

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
    ClearScreen(0, 0, 0, 255);
}

void Graphic::ClearScreen(float r, float g, float b, float a)
{
    SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(r * 255), static_cast<Uint8>(g * 255), static_cast<Uint8>(b * 255), static_cast<Uint8>(a * 255));
    SDL_RenderClear(m_renderer);
}

void Graphic::DrawPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(m_renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(m_renderer, x, y);
    //SDL_RenderPresent(m_renderer); // Render the changes immediately
}

inline void Graphic::drawRect(int x, int y, int width, int height, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    SDL_RenderDrawRect(m_renderer, &rect);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(m_renderer);

}


/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                                WINDOW CLASS                                         //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//                              FLOOFFY ENGINE CLASS                                   //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////

class FloofEngine
{
protected:
    string mGameTitle;
    int    mWindowWidth = 0;
    int    mWindowHeight = 0;
    bool   mGameRunning = true;

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

    bool start();

    bool KeyPressed[256];

    int rectx = 100;
};

bool FloofEngine::start()
{
    _init();

    SDL_Event event;
    while (mGameRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                // Handle quit event
                _close();
                return false;
            case SDL_KEYDOWN:
                // Handle key press event
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    // Handle UP arrow key press
                    // Example action: Move character up
                    break;
                case SDLK_DOWN:
                    // Handle DOWN arrow key press
                    // Example action: Move character down
                    break;
                case SDLK_LEFT:
                    // Handle LEFT arrow key press
                    // Example action: Move character left
                    break;
                case SDLK_RIGHT:
                    // Handle RIGHT arrow key press
                    // Example action: Move character right
                    break;
                    // You can handle other keys similarly
                }
                break;
            case SDL_KEYUP:
                // Handle key release event
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    // Handle UP arrow key release
                    // Example action: Stop moving character up
                    break;
                case SDLK_DOWN:
                    // Handle DOWN arrow key release
                    // Example action: Stop moving character down
                    break;
                case SDLK_LEFT:
                    // Handle LEFT arrow key release
                    // Example action: Stop moving character left
                    break;
                case SDLK_RIGHT:
                    // Handle RIGHT arrow key release
                    // Example action: Stop moving character right
                    break;
                    // You can handle other keys similarly
                }
                break;
            }

        }
        if (KeyPressed[event.key.keysym.sym] == true)
            rectx += 5;
        _processInput();
        _update();
        SDL_RenderClear(graphic->m_renderer);
        _draw();
        SDL_RenderPresent(graphic->m_renderer);
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


#endif // !H_ENGINE_H
