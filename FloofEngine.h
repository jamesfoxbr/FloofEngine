#ifndef H_ENGINE_H
#define H_ENGINE_H

#include <string>
#include <iostream>
#include "Window.h"

using std::string;

class FloofEngine
{
protected:
	string mGameTitle;
	int mWindowWidth;
	int mWindowHeight;
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

	FloofEngine();
	~FloofEngine();
};

#endif // !H_ENGINE_H

