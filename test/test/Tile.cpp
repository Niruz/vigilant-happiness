#include "Tile.h"
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>
Tile::Tile(float inX, float inY, bool blocking, bool spikedFloor, bool oneWay, bool isPillar, const std::string& tiletype)
	:myX(inX), myY(inY), myIsBlockingFlag(blocking), isOccupied(false), isPlayerOnTile(false),
	myIsSpikedFloor(spikedFloor), myIsOneWayTile(oneWay), myIsPillar(isPillar), myTileType(tiletype)
{

}
void Tile::SetPosition(int x, int y)
{
	myWorldPosition = glm::vec2(x, y);
	myAABB.myOrigin = myWorldPosition;
	myAABB.halfX = 16.0f;
	myAABB.halfY = 16.0f;
	glm::vec2 tilePos = glm::vec2(x, y);
}

void Tile::Initialize(float inX, float inY, bool blocking, bool spikedFloor, bool oneWay, bool isPillar, const std::string& tiletype)
{
	myX = inX;
	myY = inY;
	myIsBlockingFlag = blocking;
	isOccupied = false;
	isPlayerOnTile = false;
	myIsSpikedFloor = spikedFloor;
	myIsOneWayTile = oneWay;
	myIsPillar = isPillar;
	myTileType = tiletype;

}