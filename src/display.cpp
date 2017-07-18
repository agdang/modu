#include "display.h"

namespace Display
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool open;

	void Init(const int& width, const int& height, const int& frameRate, const std::string& windowTitle)
	{
		int error = SDL_Init(SDL_INIT_VIDEO);

		if (error != 0) exit(error);

		window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, NULL);
		renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		open = true;
	}

	void Close()
	{
		open = false;

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	void Clear()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}

	void Render()
	{
		SDL_RenderPresent(renderer);
	}

	void SetWindowSize(const int& width, const int& height)
	{
		SDL_SetWindowSize(window, width, height);
	}

	void SetClearColor(SDL_Color color)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	}

	void DrawTexture(SDL_Texture& texture, const SDL_Rect& rect)
	{
		SDL_RenderCopy(renderer, &texture, nullptr, &rect);
	}

	void DrawRect(SDL_Rect& rect) 
	{
		SDL_RenderFillRect(renderer, &rect);
	}

	bool isOpen() { return open; }

	SDL_Rect& GetWindowSize()
	{
		SDL_DisplayMode dm;
		SDL_GetDesktopDisplayMode(0, &dm);

		SDL_Rect r;
		r.w = dm.w;
		r.h = dm.h;

		return r;
	}
}