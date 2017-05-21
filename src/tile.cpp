#pragma once

#include "tile.h"

tile::tile(unsigned short int t, bool s)
{
	width = TILE_SIZE; height = TILE_SIZE;
	type = t; solid = s; visible = false;
}