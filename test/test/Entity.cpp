#include "Entity.h"

int Entity::nextValidID = 0;

void Entity::setID(int val)
{
	mID = val;
	nextValidID++;
}
void Entity::setName(const std::string& name)
{
	mName = name;
}