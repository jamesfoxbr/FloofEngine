#include "FloofEngine.h"

bool FloofEngine::start()
{
	// Called first time when a game is loaded
	_init();

	// Game Loop
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
					// game finished
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
