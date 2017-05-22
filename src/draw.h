#pragma once

#include <SDL2/SDL.h>

struct tile;
struct map;

extern void Draw(SDL_Renderer* ren, tile& t, int mapOffsetX, int mapOffsetY, int worldOffsetX, int worldOffsetY);
extern void SetSolid(tile& t, bool s);
