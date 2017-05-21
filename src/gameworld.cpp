#pragma once

#include <map>

#include "map.hpp"
#include "gameworld.hpp"

GameWorld::GameWorld() {}

GameWorld::~GameWorld()
{
	for (int i = 0; i < maps.size(); i++)
	{
		delete maps[i];
	}
	maps.clear();
}

void GameWorld::AddMap(map* m) { maps[maps.size()] = m; }

void GameWorld::SetMap(map* m)
{
	for (int i = 0; i < maps.size(); i++)
	{
		if (maps[i] == m)
		{
			curMap = i;
			maps[curMap]->ResetOffset();
		}
	}
}

map& GameWorld::GetCurrentMap() { return *maps[curMap]; }