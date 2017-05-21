#pragma once

#include "tile.hpp"

tile::tile(int t, bool s)
{
	width = TILE_SIZE; height = TILE_SIZE;
	type = t; visible = false; solid = s;
}