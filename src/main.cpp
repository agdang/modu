#include <ctime>
#include <cmath>
#include <sstream>

#include <SDL.h>

#include "tile.hpp"
#include "map.hpp"
#include "draw.h"
#include "gameworld.hpp"
#include "gamewindow.hpp"

int main(int argc, char* argv[])
{
	srand(static_cast<long int> (time(NULL)));

	int WINDOW_WIDTH = 800; int WINDOW_HEIGHT = 600;

	int VERSION_MAJOR = 0; int VERSION_MINOR = 1; int VERSION_REVISION = 0;
	std::stringstream windowTitle; windowTitle << "modu v" << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_REVISION << ".alpha";

	GameWindow* gameWindow = new GameWindow(windowTitle.str().c_str(), WINDOW_WIDTH, WINDOW_HEIGHT);
	GameWorld* gameWorld = new GameWorld;

	map* m = new map(20, 20);
	gameWorld->AddMap(m);
	gameWorld->SetMap(m);

	int viewRadius = 15; int viewH;

	bool running = true;

	while (running)
	{
		int worldOffsetX = gameWindow->width / 2;
		int worldOffsetY = gameWindow->height / 2;

		int playerUpTileY = -1 + gameWorld->GetCurrentMap().mapOffsetY;		int playerUpTileX = gameWorld->GetCurrentMap().mapOffsetX;
		int playerDownTileY = 1 + gameWorld->GetCurrentMap().mapOffsetY;	int playerDownTileX = gameWorld->GetCurrentMap().mapOffsetX;
		int playerLeftTileY = gameWorld->GetCurrentMap().mapOffsetY;		int playerLeftTileX = -1 + gameWorld->GetCurrentMap().mapOffsetX;
		int playerRightTileY = gameWorld->GetCurrentMap().mapOffsetY;		int playerRightTileX = 1 + gameWorld->GetCurrentMap().mapOffsetX;

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: running = false; break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					if (playerUpTileY >= 0 && gameWorld->GetCurrentMap().GetTile(playerUpTileY, playerUpTileX)->solid != true)  gameWorld->GetCurrentMap().mapOffsetY--;
					break;

				case SDLK_DOWN:
					if (playerDownTileY < gameWorld->GetCurrentMap().height && gameWorld->GetCurrentMap().GetTile(playerDownTileY, playerDownTileX)->solid != true)  gameWorld->GetCurrentMap().mapOffsetY++;
					break;

				case SDLK_LEFT:
					if (playerLeftTileX >= 0 && gameWorld->GetCurrentMap().GetTile(playerLeftTileY, playerLeftTileX)->solid != true)  gameWorld->GetCurrentMap().mapOffsetX--;
					break;

				case SDLK_RIGHT:
					if (playerRightTileX < gameWorld->GetCurrentMap().width && gameWorld->GetCurrentMap().GetTile(playerRightTileY, playerRightTileX)->solid != true)  gameWorld->GetCurrentMap().mapOffsetX++;
					break;

				case SDLK_q:		running = false; break;
				case SDLK_EQUALS:	viewRadius += 1; break;
				case SDLK_MINUS:	if (viewRadius > 0) viewRadius -= 1; break;
				case SDLK_1:		gameWorld->SetMap(m); break;
				}
				break;
			}
		}

		SDL_SetRenderDrawColor(gameWindow->renderer, 0, 0, 0, 255);
		gameWindow->Clear();

		for (int i = -viewRadius; i < viewRadius + 1; i++)
		{
			viewH = (int)sqrt(viewRadius*viewRadius - i*i);
			for (int j = -viewH; j < viewH + 1; j++)
			{
				int relTX = i + gameWorld->GetCurrentMap().mapOffsetX;
				int relTY = j + gameWorld->GetCurrentMap().mapOffsetY;

				if (relTY >= 0 && relTY < gameWorld->GetCurrentMap().height && relTX >= 0 && relTX < gameWorld->GetCurrentMap().width)
					SetVisible(*gameWorld->GetCurrentMap().GetTile(relTY, relTX), true);
			}
		}

		int playerWorldPosY = worldOffsetY;
		int playerWorldPosX = worldOffsetX;

		Draw(gameWorld->GetCurrentMap(), gameWindow->renderer, worldOffsetX, worldOffsetY);

		SDL_SetRenderDrawColor(gameWindow->renderer, 20, 20, 255, 255);
		SDL_Rect player = { playerWorldPosX, playerWorldPosY, TILE_SIZE, TILE_SIZE };
		SDL_RenderFillRect(gameWindow->renderer, &player);

		gameWindow->Update();
	}
	
	delete gameWorld;
	delete gameWindow;

	SDL_Quit();

	return 0;
}