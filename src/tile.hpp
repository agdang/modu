#pragma once

#define TILE_SIZE 16

// Enum to help readability when generating map
enum TILE_TYPE { EMPTY = 0, WALL = 1, ENTRANCE = 2, STAIR = 3 };

// Tile data structure, holds solidity and visibility
struct tile
{
	int type;
	bool visible; bool solid;
	int width; int height;

	tile(int t,  bool s);
	~tile() {}
};