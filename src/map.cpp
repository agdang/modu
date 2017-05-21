#pragma once

#include "tile.h"
#include "map.h"

map::map(unsigned int w, unsigned int h)
{
	width = w; height = h;
	offsetX = 0; offsetY = 0;
	startOffsetX = 0; startOffsetY = 0;

	for (unsigned int j = 0; j < height; j++)
	{
		for (unsigned int i = 0; i < width; i++)
		{
			if (rand() % 10 + 1 == 1)
				tiles.push_back(new tile(WALL, true));
			else
				tiles.push_back(new tile(EMPTY, false));
		}
	}

	GetTile(5, 5)->type = ENTRANCE;
	GetTile(5, 5)->solid = false;

	for (unsigned int j = 0; j < height; j++)
	{
		for (unsigned int i = 0; i < width; i++)
		{
			if (GetTile(j, i)->type == ENTRANCE)
			{
				startOffsetX = offsetX = i; startOffsetY = offsetY = j;
			}
		}
	}
}

map::~map()
{
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		delete tiles[i];
	}

	tiles.clear();
}

void map::ResetOffset()
{
	offsetX = startOffsetX; offsetY = startOffsetY;
}

tile* map::GetTile(unsigned int y, unsigned int x) { return tiles[(y * width) + x]; }