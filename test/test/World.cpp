#include "World.h"
#include "Level.h"

World* World::Instance()
{
	static World instance;

	return &instance;
}

Level* World::GetLevelFromName(const std::string& name)const
{
	//find the entity
	LevelMap::const_iterator ent = myLevelMap.find(name);

	//assert that the entity is a member of the map
	assert((ent != myLevelMap.end()) && "<World::GetLevelFromName>: invalid Name");

	return ent->second;
}

void World::RemoveLevel(Level* level)
{
	myLevelMap.erase(myLevelMap.find(level->GetName()));
}

void World::RegisterLevel(Level* level)
{
	myLevelMap.insert(std::make_pair(level->GetName(), level));
}
Level* World::GetActiveLevel() const
{
	return myCurrentActiveLevel;
}
void World::SetActiveLevel(const std::string& name)
{
	myCurrentActiveLevel = GetLevelFromName(name);
}