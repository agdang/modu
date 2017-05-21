#pragma once

#include <vector>

struct tile;

struct map
{
	std::vector<tile*> tiles;
	int width; int height;
	int startOffsetX; int startOffsetY;
	int mapOffsetX; int mapOffsetY;

	map(int w, int h);
	~map();

	void ResetOffset();

	tile* GetTile(int y, int x);
};