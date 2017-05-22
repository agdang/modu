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
			tiles.push_back(new tile(EMPTY, false));
		}
	}

	GetTile(0, 0)->type = ENTRANCE;
	GetTile(0, 0)->solid = false;

	for (int j = 5; j < 17; j++)
	{
		GetTile(j, 5)->type = WALL; GetTile(j, 5)->solid = true;
		GetTile(j, 17)->type = WALL; GetTile(j, 17)->solid = true;
		for (int i = 5; i < 18; i++)
		{
			GetTile(5, i)->type = WALL; GetTile(5, i)->solid = true;
			GetTile(17, i)->type = WALL; GetTile(17, i)->solid = true;

			if (i == 11)
			{
				GetTile(5, i)->type = EMPTY; GetTile(5, i)->solid = false;
				GetTile(17, i)->type = EMPTY; GetTile(17, i)->solid = false;
			}
		}

		if (j == 11)
		{
			GetTile(j, 5)->type = EMPTY; GetTile(j, 5)->solid = false;
			GetTile(j, 17)->type = EMPTY; GetTile(j, 17)->solid = false;
		}
	}

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