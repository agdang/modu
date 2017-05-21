#pragma once

#include "map.h"
#include "gameworld.h"

GameWorld::GameWorld() {}

GameWorld::~GameWorld()
{
	for (unsigned int i = 0; i < maps.size(); i++)
	{
		delete maps[i];
	}

	maps.clear();
}

void GameWorld::AddMap(map* m) { maps[static_cast<unsigned int> (maps.size())] = m; }

void GameWorld::SetMap(map* m)
{
	for (unsigned int i = 0; i < maps.size(); i++)
	{
		if (maps[i] == m)
		{
			curMap = i;
			maps[curMap]->ResetOffset();
		}
	}
}

map* GameWorld::GetCurrentMap() { return maps[curMap]; }