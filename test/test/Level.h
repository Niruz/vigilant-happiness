#pragma once

#include "Camera.h"
#include "Layer.h"

class Group;
class EffectsGroup;
class Level
{
public:
	Level(const std::string& name)
		:myName(name), myNumberOfEntities(0)
	{

	};
	virtual ~Level()
	{
		for (Layer* layer : myLayers)
			delete layer;
		delete myCamera;
		myLayers.clear();
		myRenderGroups.clear();
		my…ffectsGroups.clear();
	};

	virtual void Initialize() = 0;
	virtual void Tick(const unsigned int ups, const unsigned int fps) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void DeInitialize() = 0;

	virtual void ProcessKeyBoard(int key, float deltaTime, int action) = 0;
	virtual void ProcessMouse(double xpos, double ypos, bool movement) = 0;

	virtual void AddEntity(Entity* entity) = 0;
	virtual void SpawnEntity(const std::string& type, const glm::vec3&  inpos, const glm::vec3& indir, int heading = 1) = 0;
	virtual void RemoveEntity(Entity* entity) = 0;

	std::string GetName() const { return myName; }

	Camera* myCamera;
	std::vector<Layer*> myLayers;
	std::vector<Group*> myRenderGroups;
	std::vector<EffectsGroup*> my…ffectsGroups;
	std::string myName;
	int myNumberOfEntities;
};
