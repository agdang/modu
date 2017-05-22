#pragma once

#include <SDL2/SDL.h>

struct tile;
struct map;

extern void Draw(SDL_Renderer* ren, int worldTilePositionX, int worldTilePositionY);
extern void Draw(map& m, SDL_Renderer* ren, int worldOffsetX, int worldOffsetY);
extern void SetVisible(tile& t, bool v);
extern void SetSolid(tile& t, bool s);
