#include "map.h"
#include "gameworld.h"

GameWorld::GameWorld() {}

GameWorld::~GameWorld()
{
	for (auto it : maps) delete it;
}

void GameWorld::AddMap(map* m) 
{ 
	maps.push_back(m); 
}

map& GameWorld::LoadMap(map* m)
{
	m->ResetOffset();
	return *m;
}