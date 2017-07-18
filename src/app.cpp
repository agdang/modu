#pragma once

#include "app.h"
#include "display.h"
#include "game.h"

#include <iostream>

namespace App
{
	void Init()
	{
		std::cout << "Starting application\n";

		Display::Init(WINDOW_WIDTH, WINDOW_HEIGHT, FRAMERATE, "modu running on Unnamed Engine");

		std::cout << "Loading game\n";
		Game::Load();
	}

	void Close()
	{
		std::cout << "Closing application";

		SDL_Quit();
	}

	void Cycle()
	{
		while (Display::isOpen())
		{
			Game::Input();

			Display::Clear();
	
			Game::Update();
			Game::Draw();

			Display::Render();
		}

		Display::Close();
	}
}