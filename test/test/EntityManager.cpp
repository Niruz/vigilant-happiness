#include "EntityManager.h"
#include "Entity.h"

EntityManager* EntityManager::Instance()
{
	static EntityManager instance;

	return &instance;
}

Entity* EntityManager::getEntityFromID(int id)const
{
	//find the entity
	EntityMap::const_iterator ent = mEntityMap.find(id);

	//assert that the entity is a member of the map
	assert((ent != mEntityMap.end()) && "<EntityManager::getEntityFromID>: invalid ID");

	return ent->second;
}

void EntityManager::removeEntity(Entity* entity)
{
	mEntityMap.erase(mEntityMap.find(entity->GetID()));
}

void EntityManager::registerEntity(Entity* NewEntity)
{
	mEntityMap.insert(std::make_pair(NewEntity->GetID(), NewEntity));
}

void EntityManager::DeleteAllEntities()
{
	for (auto iterator : mEntityMap)
		delete iterator.second;
	mEntityMap.clear();
}

void EntityManager::Update()
{
	std::map<int, Entity*>::iterator it = mEntityMap.begin();

	while (it != mEntityMap.end())
	{
		//TODO: remove this once the entity component system is in place
		Entity* entity = it->second;

		entity->Update();
		it++;

	}
}
