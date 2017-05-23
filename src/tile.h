#pragma once

static const unsigned short int TILE_SIZE = 16;

enum TILE_TYPE { EMPTY, FLOOR, WALL, ENTRANCE, STAIR, };

struct tile
{
	unsigned short int type;

	unsigned int width;

	int x; int y;

	bool solid;

	tile(unsigned short int t,  bool s, int x, int y);
	~tile() {}
};