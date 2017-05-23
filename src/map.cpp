#include "tile.h"
#include "map.h"

map::map(int w, int h)
{
	width = w; height = h;
	offsetX = 0; offsetY = 0;
	startOffsetX = 0; startOffsetY = 0;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			tiles.push_back(new tile(FLOOR, false, i, j));		
		}
	}

	GetTile(5, 5)->type = ENTRANCE;
	GetTile(5, 5)->solid = false;

	startOffsetX = offsetX = 5; startOffsetY = offsetY = 5;
}

map::~map()
{
	for (auto it : tiles) delete it;
}

void map::ResetOffset()
{
	offsetX = startOffsetX; offsetY = startOffsetY;
}

tile* map::GetTile(int x, int y) { return tiles[(y * width) + x]; }
