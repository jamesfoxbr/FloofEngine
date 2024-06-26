#include <iostream>
#include "FloofEngine.h"

class Game : public FloofEngine
{
public:
	Game()
	{
		window->setTitle(L"hard");
		//window->setSize(800, 400);
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
		graphic->DrawPixel(50, 50, 255, 255, 255); // Black pixel at (50, 50)
		graphic->DrawPixel(10, 10, 255, 255, 255); // White pixel at (10, 10)

		graphic->drawRect(rectx, 100, 100, 100, 255, 255, 255);

		return true;
	}

	bool _close() override
	{
		// called when a game is closed to delete dynamic loaded stuff.
		std::cout << "game closed\n";
		return true;
	}
};

/******************************************************************************************
*	MAIN FUNCTION                                                                         *
******************************************************************************************/

int main(int argc, char* argv[])
{
	Game game;
	game.start();

	return 0;
}