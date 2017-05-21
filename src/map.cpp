#pragma once

#include "tile.hpp"
#include "map.hpp"

map::map(int w, int h)
{
	width = w; height = h;
	mapOffsetX = 0; mapOffsetY = 0;
	startOffsetX = 0; startOffsetY = 0;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (rand() % 10 + 1 == 1)
				tiles.push_back(new tile(WALL, true));
			else
				tiles.push_back(new tile(EMPTY, false));
		}
	}

	GetTile(0, 0)->type = ENTRANCE;
	GetTile(0, 0)->solid = false;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (GetTile(j, i)->type == ENTRANCE)
			{
				startOffsetX = mapOffsetX = i; startOffsetY = mapOffsetY = j;
			}
		}
	}
}

map::~map()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		delete tiles[i];
	};
	tiles.clear();
}

void map::ResetOffset()
{
	mapOffsetX = startOffsetX; mapOffsetY = startOffsetY;
}

tile* map::GetTile(int y, int x) { return tiles[(y * width) + x]; }