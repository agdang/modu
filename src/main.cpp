#include <cmath>

#include "tile.h"
#include "map.h"
#include "draw.h"
#include "gameworld.h"
#include "gamewindow.h"

int main(int argc, char* argv[])
{
	int WINDOW_WIDTH = (32 * TILE_SIZE) + TILE_SIZE; int WINDOW_HEIGHT = WINDOW_WIDTH;

	GameWindow* gameWindow = new GameWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	GameWorld* gameWorld = new GameWorld;

	map* m = new map(20, 20);

	gameWorld->AddMap(m);

	map& currentMap = gameWorld->LoadMap(m);

	unsigned short int viewRadius = 15; unsigned short int viewH;

	bool running = true;

	while (running)
	{
		int worldOffsetX = (gameWindow->width / 2) - (TILE_SIZE / 2);
		int worldOffsetY = (gameWindow->height / 2) - (TILE_SIZE / 2);

		int playerUpTileY	= currentMap.offsetY - 1;	int playerUpTileX	= currentMap.offsetX;
		int playerDownTileY	= currentMap.offsetY + 1;	int playerDownTileX	= currentMap.offsetX;
		int playerLeftTileY	= currentMap.offsetY;		int playerLeftTileX	= currentMap.offsetX - 1;
		int playerRightTileY= currentMap.offsetY;		int playerRightTileX= currentMap.offsetX + 1;

		SDL_Event event;

		if (SDL_WaitEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: running = false; break;
			case SDL_KEYDOWN:	
				switch (event.key.keysym.sym)
				{
				case SDLK_UP: case SDLK_KP_8:
					if (playerUpTileY >= 0
						&& currentMap.GetTile(playerUpTileX, playerUpTileY)->solid != true)
					{
						currentMap.offsetY--;
					}
					break;

				case SDLK_DOWN: case SDLK_KP_2:
					if (playerDownTileY < currentMap.height
						&& currentMap.GetTile(playerDownTileX, playerDownTileY)->solid != true)
					{
						currentMap.offsetY++;
					}
					break;

				case SDLK_LEFT: case SDLK_KP_4:
					if (playerLeftTileX >= 0
						&& currentMap.GetTile(playerLeftTileX, playerLeftTileY)->solid != true)
					{
						currentMap.offsetX--;
					}
					break;

				case SDLK_RIGHT: case SDLK_KP_6:
					if (playerRightTileX < currentMap.width
						&& currentMap.GetTile(playerRightTileX, playerRightTileY)->solid != true)
					{
						currentMap.offsetX++;
					}
					break;

				case SDLK_KP_7:
					if (playerUpTileY >= 0 
						&& playerLeftTileX >= 0 
						&& currentMap.GetTile(playerUpTileX - 1, playerUpTileY)->solid != true) 
					{
						currentMap.offsetY--;
						currentMap.offsetX--;
					}
					break;

				case SDLK_KP_9:
					if (playerUpTileY >= 0 
						&& playerRightTileX < currentMap.width 
						&& currentMap.GetTile(playerUpTileX + 1, playerUpTileY)->solid != true) 
					{
						currentMap.offsetY--;
						currentMap.offsetX++;
					}
					break;

				case SDLK_KP_1:
					if (playerDownTileY < currentMap.height 
						&& playerLeftTileX >= 0 
						&& currentMap.GetTile(playerDownTileX - 1, playerDownTileY)->solid != true) 
					{
						currentMap.offsetY++;
						currentMap.offsetX--;
					}
					break;

				case SDLK_KP_3:
					if (playerDownTileY < currentMap.height 
						&& playerRightTileX < currentMap.width 
						&& currentMap.GetTile(playerDownTileX + 1, playerDownTileY)->solid != true) 
					{
						currentMap.offsetY++;
						currentMap.offsetX++;
					}
					break;

				case SDLK_q:		running = false; break;
				case SDLK_EQUALS:	viewRadius += 1; break;
				case SDLK_MINUS:	if (viewRadius > 0) viewRadius -= 1; break;

				case SDLK_1:		currentMap = gameWorld->LoadMap(m); break;
				}
				break;
			}
		}

		SDL_SetRenderDrawColor(gameWindow->renderer, 0, 0, 0, 255);
		gameWindow->Clear();

		for (int i = -viewRadius; i < viewRadius + 1; i++)
		{
			viewH = static_cast<unsigned int> (sqrt(viewRadius * viewRadius - i * i));

			for (int j = -viewH; j < viewH + 1; j++)
			{
				int tileMapIndexX = i + currentMap.offsetX;
				int tileMapIndexY = j + currentMap.offsetY;

				int tileScreenPosX = worldOffsetX + i*TILE_SIZE;
				int tileScreenPosY = worldOffsetY + j*TILE_SIZE;

				if (tileScreenPosX >= 0
					&& tileScreenPosX < WINDOW_WIDTH
					&& tileScreenPosY >= 0
					&& tileScreenPosY < WINDOW_HEIGHT)
				{
					if (tileMapIndexY >= 0
						&& tileMapIndexY < currentMap.height
						&& tileMapIndexX >= 0 && tileMapIndexX < currentMap.width)

						Draw(gameWindow->renderer, 
							 *currentMap.GetTile(tileMapIndexX, tileMapIndexY),
							  currentMap.offsetX, 
							  currentMap.offsetY, 
							  worldOffsetX, worldOffsetY);
				}
			}
		}

		SDL_SetRenderDrawColor(gameWindow->renderer, 40, 40, 255, 255);

		static SDL_Rect player = { worldOffsetX, worldOffsetY, TILE_SIZE, TILE_SIZE };

		SDL_RenderFillRect(gameWindow->renderer, &player);

		gameWindow->Update();
	}

	delete gameWorld;
	delete gameWindow;

	SDL_Quit();

	return 0;
}
