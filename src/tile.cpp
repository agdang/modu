#include "tile.h"
#include "draw.h"

tile::tile(unsigned short int t, bool s, int x, int y)
{
	width = TILE_SIZE;
	type = t; solid = s;
	this->x = x; this->y = y;
}
