#pragma once

#include <vector>

struct map;

struct GameWorld
{
	std::vector<map*> maps;

	GameWorld();
	~GameWorld();

	void AddMap(map* m);
	map& LoadMap(map* m);
};