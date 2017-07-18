#pragma once

#include <string>

#include <SDL2\SDL.h>

namespace Display
{
	void Init(const int& width, const int& height, const int& frameRate, const std::string& windowTitle);
	void Close();
	void Clear();
	void Render();

	void SetWindowSize(const int& width, const int& height);
	void SetClearColor(SDL_Color color);

	void DrawTexture(SDL_Texture& texture, const SDL_Rect& rect);
	void DrawRect(SDL_Rect& rect);

	SDL_Rect& GetWindowSize();

	bool isOpen();
}