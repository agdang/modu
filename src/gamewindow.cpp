#pragma once

#include <SDL.h>

#include "gamewindow.hpp"

GameWindow::GameWindow(const char* title, int w, int h)
{
	SDL_Init(SDL_INIT_VIDEO);

	width = w;
	height = h;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
}

GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void GameWindow::Clear() { SDL_RenderClear(renderer); }
void GameWindow::Update() { SDL_RenderPresent(renderer); }