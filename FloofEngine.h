#ifndef H_ENGINE_H
#define H_ENGINE_H

#include <string>
#include <iostream>
#include "Window.h"
#include "Graphic.h"

using std::string;

class FloofEngine
{
protected:
	string mGameTitle;                        // game and window title are stored here
	int mWindowWidth;                         // window width
	int mWindowHeight;                        // window height
	bool mGameRunning = true;

public:
	bool start();                             // start the game engine when a game is read

private:
	virtual bool _init();                     // Called first time when a game is loaded
	virtual bool _processInput();             // process player inputs like keyboard and mouse presses 
	virtual bool _update();                   // updates the game logic every  frame
	virtual bool _draw();                     // used to put stuff to draw on screen
	virtual bool _close();                    // called when the game is closed to delete stuff you dynamic loaded.

public:
	Window* window;
	Graphic* graphic;

	FloofEngine();
	~FloofEngine();

	void ClearScreen(float r, float g, float b, float a);
};

#endif // !H_ENGINE_H

