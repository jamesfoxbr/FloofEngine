#ifndef H_ENGINE_H
#define H_ENGINE_H

#include <string>

using std::string;

class FloofEngine
{
protected:
	string mGameTitle;
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
	FloofEngine();
};

#endif // !H_ENGINE_H

