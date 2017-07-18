#pragma once

#include <SDL2\SDL.h>

#include "game.h"
#include "display.h"
#include "gameworld.h"
#include "map.h"
#include "tile.h"
#include "draw.h"

namespace Game
{
	static constexpr SDL_Color COLOR_PLAYER = { 40, 40, 255, 255 };
	static constexpr SDL_Color COLOR_FLOOR	= { 100, 100, 100, 255 };
	static constexpr SDL_Color COLOR_STAIR	= { 0, 255, 0, 255 };
	static constexpr SDL_Color COLOR_WALL	= { 40, 30, 10, 255 };
	static constexpr SDL_Color COLOR_CURSOR = { 255, 255, 255, 255 };

	static constexpr int TILE_SIZE = 16;
	static constexpr SDL_Rect viewport = { 0, 0, 32 * TILE_SIZE, 32 * TILE_SIZE };

	unsigned short int viewRadius = 15;
	unsigned short int viewH;

	SDL_Event gameEvent;

	GameWorld* gameWorld;
	map* m;
	map currentMap;

	int worldOffsetX;
	int worldOffsetY;

	int oldWorldOffsetX;
	int oldWorldOffsetY;

	int playerUpTileY;		int playerUpTileX;
	int playerDownTileY;	int playerDownTileX;
	int playerLeftTileY;	int playerLeftTileX;
	int playerRightTileY;	int playerRightTileX;

	bool looking;

	void Load()
	{
		Display::SetWindowSize(viewport.w, viewport.h);

		gameWorld = new GameWorld;
		m = new map(20, 20);

		currentMap = gameWorld->LoadMap(m);

		looking = false;
	}

	void Update()
	{
		worldOffsetX = (viewport.w / 2) - (TILE_SIZE / 2);
		worldOffsetY = (viewport.h / 2) - (TILE_SIZE / 2);

		playerUpTileY	 = currentMap.offsetY - 1;	playerUpTileX	 = currentMap.offsetX;
		playerDownTileY  = currentMap.offsetY + 1;	playerDownTileX	 = currentMap.offsetX;
		playerLeftTileY	 = currentMap.offsetY;		playerLeftTileX	 = currentMap.offsetX - 1;
		playerRightTileY = currentMap.offsetY;		playerRightTileX = currentMap.offsetX + 1;
	}

	void Close()
	{
		delete gameWorld;
	}

	void Input()
	{
		while (SDL_PollEvent(&gameEvent))
		{
			switch (gameEvent.type)
			{
			case SDL_QUIT:
				Display::Close();
				break;
			case SDL_KEYDOWN:
				switch (gameEvent.key.keysym.sym)
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

				case SDLK_q:		Display::Close(); break;
				case SDLK_EQUALS:	viewRadius += 1; break;
				case SDLK_MINUS:	if (viewRadius > 0) viewRadius -= 1; break;

				case SDLK_1:		currentMap = gameWorld->LoadMap(m); break;

				case SDLK_l:		looking = !looking; 
									if (looking)
									{
										oldWorldOffsetX = worldOffsetX;
										oldWorldOffsetY = worldOffsetY;							
									}
									else
									{
										worldOffsetX = oldWorldOffsetX;
										worldOffsetY = oldWorldOffsetY;
									}
									break;
				}
				break;
			}
		}
	}
	
	void Draw()
	{
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
					&& tileScreenPosX < viewport.w
					&& tileScreenPosY >= 0
					&& tileScreenPosY < viewport.h)
				{
					if (tileMapIndexY >= 0
						&& tileMapIndexY < currentMap.height
						&& tileMapIndexX >= 0 && tileMapIndexX < currentMap.width)
					{
						tile& currentTile = *currentMap.GetTile(tileMapIndexX, tileMapIndexY);

						int tileWorldPosX = worldOffsetX + currentTile.x * TILE_SIZE - currentMap.offsetX * TILE_SIZE;
						int tileWorldPosY = worldOffsetY + currentTile.y * TILE_SIZE - currentMap.offsetY * TILE_SIZE;

						switch (currentTile.type)
						{
						case EMPTY:		return;
						case FLOOR:		Display::SetClearColor(COLOR_FLOOR);	break;
						case WALL:		Display::SetClearColor(COLOR_WALL);		break;
						case ENTRANCE:	Display::SetClearColor(COLOR_STAIR);	break;
						}

						SDL_Rect r = { tileWorldPosX, tileWorldPosY, TILE_SIZE, TILE_SIZE };
						Display::DrawRect(r);
					}
				}
			}
		}



		static SDL_Rect player = { worldOffsetX, worldOffsetY, TILE_SIZE, TILE_SIZE };
		static SDL_Rect cursor = { worldOffsetX, worldOffsetY, TILE_SIZE, TILE_SIZE };

		if (looking)
		{
			player.x = oldWorldOffsetX;
			player.y = oldWorldOffsetY;

			Display::SetClearColor(COLOR_PLAYER);
			Display::DrawRect(player);

			Display::SetClearColor(COLOR_CURSOR);
			Display::DrawRect(cursor);
		}
		else
		{
			Display::SetClearColor(COLOR_PLAYER);
			Display::DrawRect(player);
		}
	}
}