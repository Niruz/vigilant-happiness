#pragma once
#include "Tile.h"
#include <string>

class TileMap
{
public:
	TileMap() {}
	TileMap(const std::string& mapName, const std::string& tileSet);
	~TileMap();

	bool InitializeFromTiledMap(const std::string& mapName, const std::string& tileSet);
	Tile* GetTile(int fromX, int fromY);
	Tile* GetTile2(int fromX, int fromY);

	void GenerateGraph();

	bool validIndex(int checkX, int checkY);

	bool IsDirectionWalkable(int checkX, int checkY);
	bool IsDirectionJumpable(int checkX, int checkY);
	float map(float s, float a1, float a2, float b1, float b2);

	std::vector<Tile>& GetMap();

	void printMap();


	Tile* getClosestRespawnTile(const glm::vec2& position);
	Tile* GetPlayerStartTile() { return myPlayerStartTile; }


	glm::vec2 myPlayerWorldPosition;
private:

	int GetTileIndex(int x, int y);

	std::vector<Tile> myMapTiles;

	int myMapHeight;
	int myMapWidth;

	glm::vec2 myWorldXRange;
	glm::vec2 myWorldYRange;
	glm::vec2 myWorldXTileRange;
	glm::vec2 myWorldYTileRange;

	std::vector<Tile> myRespawnTiles;

	Tile* myPlayerStartTile;

};