#pragma once

#include <map>

struct GameWorld
{
	std::map<unsigned int, map*> maps;

	unsigned int curMap;

	GameWorld();
	~GameWorld();

	void AddMap(map* m);
	void SetMap(map* m);

	map* GetCurrentMap();
};