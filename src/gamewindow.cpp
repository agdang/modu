#include <ctime>

#include <SDL2/SDL.h>

#include "gamewindow.h"

GameWindow::GameWindow(int w, int h)
{
	int err = SDL_Init(SDL_INIT_VIDEO);

	if (err != 0)
	{
		SDL_ShowSimpleMessageBox(0, "Fatal Error", SDL_GetError(), NULL);
		exit(err);
	}

	width = w;
	height = h;

	windowTitle << "modu v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_REVISION << ".alpha";

	window = SDL_CreateWindow(windowTitle.str().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		SDL_ShowSimpleMessageBox(0, "Fatal Error", SDL_GetError(), NULL);
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
	{
		SDL_ShowSimpleMessageBox(0, "Fatal Error", SDL_GetError(), window);
		exit(1);
	}

	srand(static_cast<long int> (time(NULL)));
}

GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void GameWindow::Clear() { SDL_RenderClear(renderer); }
void GameWindow::Update() { SDL_RenderPresent(renderer); }
