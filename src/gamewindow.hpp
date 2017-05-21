#pragma once

struct GameWindow
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	int width; int height;

	GameWindow(const char* title, int w, int h);

	~GameWindow();

	void Clear();
	void Update();
};