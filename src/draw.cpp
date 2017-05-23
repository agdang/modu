#include "tile.h"
#include "map.h"

#include "draw.h"

extern void Draw(SDL_Renderer* ren, tile& t, int mapOffsetX, int mapOffsetY, int worldOffsetX, int worldOffsetY)
{
	int tileWorldPosX = worldOffsetX + t.x*TILE_SIZE - mapOffsetX*TILE_SIZE;
	int tileWorldPosY = worldOffsetY + t.y*TILE_SIZE - mapOffsetY*TILE_SIZE;

	switch (t.type)
	{
	case EMPTY: return;
	case FLOOR: SDL_SetRenderDrawColor(ren, 100, 100, 100, 255);	break;
	case WALL:  SDL_SetRenderDrawColor(ren, 40, 30, 10, 255);		break;
	case ENTRANCE: SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);		break;
	}

	SDL_Rect r = { tileWorldPosX, tileWorldPosY, TILE_SIZE, TILE_SIZE };
	SDL_RenderFillRect(ren, &r);
}
