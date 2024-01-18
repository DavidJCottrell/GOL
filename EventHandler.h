#pragma once

#include <SDL.h>
#include "GOL.h"

class EventHandler
{
public:
	void handleEvents(GOL* gol, bool* play);
	void handleClick(GOL* gol, int key);
private:
	bool leftMouseDown = false;
	bool rightMouseDown = false;
};

