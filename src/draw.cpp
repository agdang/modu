#pragma once

#include "draw.h"

extern void Draw(tile& t, SDL_Renderer* ren, int worldTilePositionX, int worldTilePositionY)
{
	SDL_Rect r = { worldTilePositionX, worldTilePositionY, TILE_SIZE, TILE_SIZE };
	SDL_RenderFillRect(ren, &r);
}

extern void Draw(map& m, SDL_Renderer* ren, int worldOffsetX, int worldOffsetY)
{
	// Draw the map
	// To find the window coordinates of a tile, the tiles index is multiplied
	// by the TILE_SIZE value
	for (int j = 0; j < m.height; j++)
	{
		for (int i = 0; i < m.width; i++)
		{
			tile& cur = *m.GetTile(j, i);

			if (cur.visible == true)
			{
				int tileWorldPosX = worldOffsetX + i*TILE_SIZE - m.mapOffsetX*TILE_SIZE;
				int tileWorldPosY = worldOffsetY + j*TILE_SIZE - m.mapOffsetY*TILE_SIZE;

				switch (cur.type)
				{
				case EMPTY: SDL_SetRenderDrawColor(ren, 120, 120, 120, 255); Draw(cur, ren, tileWorldPosX, tileWorldPosY); break;
				case WALL:  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); Draw(cur, ren, tileWorldPosX, tileWorldPosY); break;
				case ENTRANCE: SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);	 Draw(cur, ren, tileWorldPosX, tileWorldPosY); break;
				}

				// Reset the visibility of the tile for the next loop
				SetVisible(cur, false);
			}
		}
	}
}

extern void SetVisible(tile& t, bool v) { t.visible = v; }
extern void SetSolid(tile& t, bool s) { t.solid = s; }