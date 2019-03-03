#include "TileMap.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include "TextureManager.h"
#include "ShaderManager.h"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include "XMLTile.h"
#include "EngineUtilities.h"
#include "TiledMapManager.h"

TileMap::TileMap(const std::string& mapName, const std::string& tileSet)
{
	if (!InitializeFromTiledMap(mapName, tileSet))
		std::cout << "\nCould not initialize map with name: " + mapName + "\n" << std::endl;

}
TileMap::~TileMap()
{
	myMapTiles.clear();
}
bool TileMap::InitializeFromTiledMap(const std::string& mapName, const std::string& tileSet)
{

	//TODO: Technically we dont need to do it this way, it's better to just create a Tiled layer called "Collision Layer" and create the tilemap based off of that.
	std::map<std::string, XMLTile*> xmlTiles = TiledMan->GetTileset(tileSet);

	XMLMap* xmlMap = TiledMan->GetMap(mapName);
	XMLLayer* xmlLayer = xmlMap->GetLayer("Tile Layer");

	int tileMapWidth = std::stoi(xmlLayer->myWidth);
	int tileMapHeight = std::stoi(xmlLayer->myHeight);

	myMapTiles.resize(tileMapWidth*tileMapHeight);
	myRespawnTiles.resize(10);

	int lineIndex = 0;
	int currentX = 0;
	int iterator = 0;
	for (int i = 0; i < xmlLayer->myData.size(); i++)
	{
		if ((i > 0) && (i % (tileMapWidth) == 0))
		{
			lineIndex++;
			currentX = 0;
		}
		//Tile* tile = nullptr;
		if (xmlLayer->myData[i] == "0")
		{
			//Comment this out if we want to close off the map in some other way later
			if (currentX == 0 || currentX == tileMapWidth - 1)
			{
				myMapTiles.at(iterator).Initialize(currentX, lineIndex, true, false, false, false, "-1");
				//tile = new Tile(currentX, lineIndex, true, false, false, false, "-1");
			}
			else
			{
				myMapTiles.at(iterator).Initialize(currentX, lineIndex, false, false, false, false, "-1");
			}
		}
		else
		{
			if (xmlTiles.count(xmlLayer->myData[i]))
			{
				bool oneway = xmlTiles.find(xmlLayer->myData[i])->second->HasProperty("OneWay");
				bool blocking = xmlTiles.find(xmlLayer->myData[i])->second->HasProperty("Blocking");
				bool spikedfloor = xmlTiles.find(xmlLayer->myData[i])->second->HasProperty("SpikedFloor");

				myMapTiles.at(iterator).Initialize(currentX, lineIndex, blocking, spikedfloor, oneway, false, std::to_string(std::stoi(xmlLayer->myData[i]) - 1));
			}
			else
			{
				myMapTiles.at(iterator).Initialize(currentX, lineIndex, false, false, false, false, std::to_string(std::stoi(xmlLayer->myData[i]) - 1));
			}

		}



		//myMapTiles.push_back(tile);
		currentX++;
		iterator++;
	}

	GenerateGraph();


	int mapWidth = std::stoi(xmlLayer->myWidth) - 1;
	int mapHeight = std::stoi(xmlLayer->myHeight) - 1;

	myWorldXRange = glm::vec2(0, mapWidth * 32.0f);
	myWorldYRange = glm::vec2(0, -mapHeight * 32.0f);

	myWorldXTileRange = glm::vec2(0, mapWidth);
	myWorldYTileRange = glm::vec2(0, mapHeight);


	myPlayerStartTile = GetTile2(5, 8);
	myRespawnTiles.at(0) = *myPlayerStartTile;
	return true;
}

int TileMap::GetTileIndex(int x, int y)
{
	return (y * myMapWidth) + x;
}
bool TileMap::validIndex(int checkX, int checkY)
{
	return (checkX >= 0 && checkX < myMapWidth && checkY >= 0 && checkY < myMapHeight);
}
bool TileMap::IsDirectionWalkable(int checkX, int checkY)
{
	if (!validIndex(checkX, checkY))
		return false;
	return !myMapTiles[GetTileIndex(checkX, checkY)].myIsBlockingFlag;
}
bool TileMap::IsDirectionJumpable(int checkX, int checkY)
{
	if (!validIndex(checkX, checkY))
		return false;
	if (myMapTiles[GetTileIndex(checkX, checkY)].myIsOneWayTile)
		return true;
	else
		return !myMapTiles[GetTileIndex(checkX, checkY)].myIsBlockingFlag;
}
Tile* TileMap::getClosestRespawnTile(const glm::vec2& position)
{
	Tile* closest = &myRespawnTiles[0];
	float distance = glm::length(position - myRespawnTiles[0].myWorldPosition);
	for (int i = 1; i < myRespawnTiles.size(); i++)
	{
		if (glm::length(position - myRespawnTiles[i].myWorldPosition) < distance)
		{
			closest = &myRespawnTiles[i];
			distance = glm::length(position - myRespawnTiles[i].myWorldPosition);
		}

	}
	return closest;
}
void TileMap::GenerateGraph()
{
	float mapHeight = myMapTiles.back().myY + 1;
	float mapWidth = myMapTiles.back().myX + 1;

	myMapHeight = myMapTiles.back().myY + 1;
	myMapWidth = myMapTiles.back().myX + 1;

	int lineIndex = 0;
	int currentX = 0;
	for (int i = 0; i < myMapTiles.size(); i++)
	{
		if ((i > 0) && (i % (myMapWidth) == 0))
		{
			lineIndex++;
			currentX = 0;
		}
		myMapTiles[i].SetPosition(32.0f*currentX, -lineIndex * 32.0f);
		currentX++;
	}
}
Tile* TileMap::GetTile(int fromX, int fromY)
{
	for(int i = 0; i < myMapTiles.size(); i++)
	{
		Tile* tile = &myMapTiles.at(i);
		if (tile->myX == fromX && tile->myY == fromY)
		{
			return tile;
		}
	}
	return nullptr;
}
Tile* TileMap::GetTile2(int fromX, int fromY)
{
	return &myMapTiles[GetTileIndex(fromX, fromY)];
}
std::vector<Tile>& TileMap::GetMap()
{
	return myMapTiles;
}
float TileMap::map(float s, float a1, float a2, float b1, float b2)
{
	return b1 + (s - a1)*(b2 - b1) / (a2 - a1);
}
void TileMap::printMap()
{

	std::cout << "\n";
	int lastY = 0;
	for(int i = 0; i < myMapTiles.size(); i++)
	{
		Tile* tile = &myMapTiles.at(i);

		if (tile->myY != lastY)
		{
			std::cout << "\n";
			lastY++;
		}
		bool isPath = false;
		if (isPath)
			std::cout << "o";
		else if (tile->myIsBlockingFlag)
			std::cout << "X";
		else
			std::cout << ".";
	}
	std::cout << "\n";

}