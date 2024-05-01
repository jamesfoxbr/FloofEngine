#include "FloofEngine.h"

bool FloofEngine::start()
{
	// Called first time when a game is loaded
	_init();

	// Game Loop
	while (mGameRunning)
	{
		_processInput();
		_update();
		_draw();
	}

	// game finished
	_close();

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

	// Show the window
	window->show();
}

FloofEngine::~FloofEngine()
{
	delete window;
}
