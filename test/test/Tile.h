#pragma once
#include <vector>
#include "glm\vec2.hpp"
#include "glm\mat4x4.hpp"

#include "AABB.h"
struct Tile
{
	Tile(){}
	Tile(float inX, float inY, bool blocking, bool spikedFloor, bool oneWay, bool isPillar, const std::string& tiletype);
	~Tile() {}
	float myX;
	float myY;

	bool myIsBlockingFlag;
	bool myIsSpikedFloor;
	bool myIsOneWayTile;
	bool myIsPillar;
	//TODO: use this later when adding several AIs to avoid stacking
	//The idea is, get a list of tiles as my path
	//On every frame move close to the next tile in the list
	//But if its occupied, we simply wait
	//They might still stack if they move to the same tile from two adjacent tiles,
	//Maybe use a pointer to the person occupying the tile
	//Then set an Entity as the owner before it starts moving and then just check
	//If isOccupied && entityOccupying != me
	//dont move
	//else
	//move
	//They will probably stand in line to defeat the player
	//So if the tile is occupied AND the distance to the player is less than some radius
	//We can try getting a new path
	bool isOccupied;
	bool isPlayerOnTile;//Maybe not needed

	glm::vec2 myWorldPosition;
	void SetPosition(int x, int y);
	AABB myAABB;

	//TODO: improve upon this so its more flexible
	std::string myTileType;

	void Initialize(float inX, float inY, bool blocking, bool spikedFloor, bool oneWay, bool isPillar, const std::string& tiletype);
};