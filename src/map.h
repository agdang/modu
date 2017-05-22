#pragma once

#include <vector>

struct tile;

struct map
{
	std::vector<tile*> tiles;

	int width; int height;

	int startOffsetX; int startOffsetY;
	int offsetX; int offsetY;

	map(int w, int h);
	~map();

	void ResetOffset();

	tile* GetTile(int y, int x);
};