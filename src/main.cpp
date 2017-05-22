#include <ctime>
#include <cmath>

#include "tile.h"
#include "map.h"
#include "draw.h"
#include "gameworld.h"
#include "gamewindow.h"

int main(int argc, char* argv[])
{
	srand(static_cast<long int> (time(NULL)));

	unsigned int WINDOW_WIDTH = (32 * TILE_SIZE) + TILE_SIZE; unsigned int WINDOW_HEIGHT = WINDOW_WIDTH;

	GameWindow* gameWindow = new GameWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	GameWorld* gameWorld = new GameWorld;

	map* m = new map(50, 50);

	gameWorld->AddMap(m);
	gameWorld->SetMap(m);

	unsigned short int viewRadius = 15; unsigned short int viewH;

	bool running = true;

	while (running)
	{
		int worldOffsetX = (gameWindow->width / 2) - (TILE_SIZE / 2);
		int worldOffsetY = (gameWindow->height / 2) - (TILE_SIZE / 2);

		int playerUpTileY		= gameWorld->GetCurrentMap()->offsetY - 1;	int playerUpTileX		= gameWorld->GetCurrentMap()->offsetX;
		int playerDownTileY		= gameWorld->GetCurrentMap()->offsetY + 1;	int playerDownTileX		= gameWorld->GetCurrentMap()->offsetX;
		int playerLeftTileY		= gameWorld->GetCurrentMap()->offsetY;		int playerLeftTileX		= gameWorld->GetCurrentMap()->offsetX - 1;
		int playerRightTileY	= gameWorld->GetCurrentMap()->offsetY;		int playerRightTileX	= gameWorld->GetCurrentMap()->offsetX + 1;

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
					if (playerUpTileY >= 0 && gameWorld->GetCurrentMap()->GetTile(playerUpTileY, playerUpTileX)->solid != true) gameWorld->GetCurrentMap()->offsetY--;
					break;

				case SDLK_DOWN: case SDLK_KP_2:
					if (playerDownTileY < gameWorld->GetCurrentMap()->height && gameWorld->GetCurrentMap()->GetTile(playerDownTileY, playerDownTileX)->solid != true) gameWorld->GetCurrentMap()->offsetY++;
					break;

				case SDLK_LEFT: case SDLK_KP_4:
					if (playerLeftTileX >= 0 && gameWorld->GetCurrentMap()->GetTile(playerLeftTileY, playerLeftTileX)->solid != true) gameWorld->GetCurrentMap()->offsetX--;
					break;

				case SDLK_RIGHT: case SDLK_KP_6:
					if (playerRightTileX < gameWorld->GetCurrentMap()->width && gameWorld->GetCurrentMap()->GetTile(playerRightTileY, playerRightTileX)->solid != true) gameWorld->GetCurrentMap()->offsetX++;
					break;

				case SDLK_KP_7:
					if (playerUpTileY >= 0 && playerLeftTileX >= 0 && gameWorld->GetCurrentMap()->GetTile(playerUpTileY, playerUpTileX - 1)->solid != true) {
						gameWorld->GetCurrentMap()->offsetY--;
						gameWorld->GetCurrentMap()->offsetX--;
					}
					break;

				case SDLK_KP_9:
					if (playerUpTileY >= 0 && playerRightTileX < gameWorld->GetCurrentMap()->width && gameWorld->GetCurrentMap()->GetTile(playerUpTileY, playerUpTileX + 1)->solid != true) {
						gameWorld->GetCurrentMap()->offsetY--;
						gameWorld->GetCurrentMap()->offsetX++;
					}
					break;

				case SDLK_KP_1:
					if (playerDownTileY < gameWorld->GetCurrentMap()->height && gameWorld->GetCurrentMap()->offsetX >= 0 && gameWorld->GetCurrentMap()->GetTile(playerDownTileY , playerDownTileX - 1)->solid != true) {
						gameWorld->GetCurrentMap()->offsetY++;
						gameWorld->GetCurrentMap()->offsetX--;
					}
					break;

				case SDLK_KP_3:
					if (playerDownTileY < gameWorld->GetCurrentMap()->height && gameWorld->GetCurrentMap()->offsetX < gameWorld->GetCurrentMap()->width && gameWorld->GetCurrentMap()->GetTile(playerDownTileY, playerDownTileX + 1)->solid != true) {
						gameWorld->GetCurrentMap()->offsetY++;
						gameWorld->GetCurrentMap()->offsetX++;
					}
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
			viewH = static_cast<unsigned int> (sqrt(viewRadius * viewRadius - i * i));

			for (int j = -viewH; j < viewH + 1; j++)
			{
				int relTX = i + gameWorld->GetCurrentMap()->offsetX;
				int relTY = j + gameWorld->GetCurrentMap()->offsetY;

				int tileWorldPosX = worldOffsetX + i*TILE_SIZE;
				int tileWorldPosY = worldOffsetY + j*TILE_SIZE;

				if (tileWorldPosX >= 0 && tileWorldPosX < WINDOW_WIDTH && tileWorldPosY >= 0 && tileWorldPosY < WINDOW_HEIGHT)
				{
					if (relTY >= 0 && relTY < gameWorld->GetCurrentMap()->height && relTX >= 0 && relTX < gameWorld->GetCurrentMap()->width)
						SetVisible(*gameWorld->GetCurrentMap()->GetTile(relTY, relTX), true);
				}
			}
		}

		Draw(*gameWorld->GetCurrentMap(), gameWindow->renderer, worldOffsetX, worldOffsetY);

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