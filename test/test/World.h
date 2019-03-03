#pragma once

#include <map>
#include <cassert>
#include <string>

#define GameWorld World::Instance()

class Level;
class World
{
private:
	typedef std::map<std::string, Level*> LevelMap;
public:

	static World* Instance();

	void RegisterLevel(Level* level);
	void RemoveLevel(Level* entity);

	Level* GetLevelFromName(const std::string& name) const;
	Level* GetActiveLevel() const;
	void   SetActiveLevel(const std::string& name);

private:

	LevelMap myLevelMap;

	World() {}
	World(const World&);
	World& operator=(const World&);

	Level* myCurrentActiveLevel;
};