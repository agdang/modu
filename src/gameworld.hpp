#pragma once

#include <map>

struct GameWorld
{
	std::map<int, map*> maps;
	int curMap;

	GameWorld();
	~GameWorld();

	void AddMap(map* m);
	void SetMap(map* m);

	map& GetCurrentMap();
};