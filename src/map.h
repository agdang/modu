#pragma once

#include <vector>

struct tile;

struct map
{
	std::vector<tile*> tiles;

	unsigned int width; unsigned int height;

	int startOffsetX; int startOffsetY;
	int offsetX; int offsetY;

	map(unsigned int w, unsigned int h);
	~map();

	void ResetOffset();

	tile* GetTile(unsigned int y, unsigned int x);
};