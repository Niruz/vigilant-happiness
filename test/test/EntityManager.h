#pragma once


#include <map>
#include <cassert>
#include <string>

class Entity;

#define EntityMan EntityManager::Instance()

class EntityManager
{
private:
	typedef std::map<int, Entity*> EntityMap;
public:

	static EntityManager* Instance();

	void registerEntity(Entity* entity);
	void removeEntity(Entity* entity);

	Entity* getEntityFromID(int id) const;

	void Update();

	void DeleteAllEntities();

private:

	EntityMap mEntityMap;

	EntityManager() {}
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);
};