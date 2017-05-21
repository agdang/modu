#pragma once
#include "tile.hpp"
#include "map.hpp"
#include <SDL.h>

extern void Draw(tile& t, SDL_Renderer* ren, int worldTilePositionX, int worldTilePositionY);
extern void Draw(map& m, SDL_Renderer* ren, int worldOffsetX, int worldOffsetY);
extern void SetVisible(tile& t, bool v);
extern void SetSolid(tile& t, bool s);
