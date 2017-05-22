#pragma once

static const unsigned short int TILE_SIZE = 16;

enum TILE_TYPE { EMPTY = 0, WALL = 1, ENTRANCE = 2, STAIR = 3 };

struct tile
{
	unsigned short int type;

	unsigned int width; unsigned int height;

	bool visible; bool solid;

	tile(unsigned short int t,  bool s);
	~tile() {}
};