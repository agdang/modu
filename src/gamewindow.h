#pragma once

#include <sstream>

static const unsigned int VERSION_MAJOR		= 0;
static const unsigned int VERSION_MINOR		= 1;
static const unsigned int VERSION_REVISION	= 0;

struct GameWindow
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	int width; int height;

	std::stringstream windowTitle;

	GameWindow(int w, int h);

	~GameWindow();

	void Clear();
	void Update();
};