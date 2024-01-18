#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "GOL.h"

class Renderer
{
public:
	Renderer(const char* title, int xpos, int ypos, int width, int height);
	~Renderer();
	void render(GOL* gol);
private:
	void DrawGrid(GOL* gol);
	SDL_Window* window;
	SDL_Renderer* renderer;
};

