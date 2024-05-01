#include <iostream>
#include "FloofEngine.h"

class Game : public FloofEngine
{
public:
	Game()
	{
		window->setTitle(L"hard");
		window->setSize(800, 400);
	}

	bool _init() override
	{
		// called when a new game starts
		return true;
	}

	bool _processInput() override
	{
		// called one time per frame to preocess controls inputs
		return true;
	}

	bool _update() override
	{
		// called one time per frame to to update game logic
		return true;
	}

	bool _draw() override
	{
		// called one time per frame to to draw the screen
		if (window->KeyDown(VK_UP))
		{
			std::cout << "UP\n";
		}
		window->ClearScreen(0.0f, 1.0f, 0.0f, 1.0f);
		
		return true;
	}

	bool _close() override
	{
		// called when a game is closed to delete dynamic loaded stuff.
		std::cout << "game closed\n";
		return true;
	}
};

int main()
{
	Game game;
	game.start();

	return 0;
}