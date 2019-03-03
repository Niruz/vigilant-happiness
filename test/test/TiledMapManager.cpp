#include "TiledMapManager.h"
#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits>

#include "XMLTile.h"
#include "EngineUtilities.h"
#include <string>
TiledMapManager* TiledMapManager::Instance()
{
	static TiledMapManager instance;
	return &instance;
}
void TiledMapManager::onInitialize()
{
	//"Tilesets/cemetarytileset.tsx"
	LoadTileset("Levels/cemetarytileset.tsx", "CemetaryTileset");
	LoadTileset("Levels/bridgetileset.tsx", "BridgeTileset");
	LoadTileset("Levels/dungeontileset.tsx", "DungeonTileset");

	//Layers
	LoadLayers("Levels/cemetary.tmx", "CemetaryLayer");
	//	LoadLayers("Levels/bridge.tmx", "BridgeLayer");

	//Maps
	LoadMap("Levels/cemetary.tmx", "CemetaryMap");
	LoadMap("Levels/bridge.tmx", "BridgeMap");
	LoadMap("Levels/dungeon.tmx", "DungeonMap");


}
void TiledMapManager::LoadTileset(const std::string& name, const std::string& identifier)
{
	rapidxml::file<> tileFile(name.c_str()); // Default template is char
	rapidxml::xml_document<> tilesetDoc;
	tilesetDoc.parse<0>(tileFile.data());

	std::cout << tilesetDoc.first_node()->name() << std::endl;

	rapidxml::xml_node<> *tileSetRoot = tilesetDoc.first_node();

	std::map<std::string, XMLTile*> xmlTiles;

	//Load the tilesets with their 
	for (rapidxml::xml_node<> *pNode = tileSetRoot->first_node("tile"); pNode; pNode = pNode->next_sibling())
	{
		rapidxml::xml_node<>* propertiesNode = pNode->first_node("properties");

		std::string currentID = std::to_string(std::stoi(pNode->first_attribute("id")->value()) + 1);

		xmlTiles[currentID] = new XMLTile(currentID);

		for (rapidxml::xml_node<> *propertyNode = propertiesNode->first_node("property"); propertyNode; propertyNode = propertyNode->next_sibling())
		{
			xmlTiles[currentID]->AddProperty(propertyNode->first_attribute("name")->value(), propertyNode->first_attribute("value")->value());
		}
	}

	myXMLTiles[identifier] = xmlTiles;
}
std::map<std::string, XMLTile*> TiledMapManager::GetTileset(const std::string& identifier)
{
	return myXMLTiles[identifier];
}
XMLLayer* TiledMapManager::GetLayer(const std::string& identifier)
{
	return myXMLLayers[identifier];
}
void TiledMapManager::LoadLayers(const std::string& file, const std::string& identifier)
{
	rapidxml::file<> mapFile(file.c_str());
	rapidxml::xml_document<> mapDoc;
	mapDoc.parse<0>(mapFile.data());

	std::cout << mapDoc.first_node()->name() << std::endl;

	rapidxml::xml_node<> *mapRoot = mapDoc.first_node();

	rapidxml::xml_node<> *pNode = mapRoot->first_node("layer")->next_sibling();

	std::string name = pNode->first_attribute("name")->value();
	std::string width = pNode->first_attribute("width")->value();
	std::string height = pNode->first_attribute("height")->value();

	std::string tileData = pNode->first_node("data")->value();
	tileData.erase(std::remove(tileData.begin(), tileData.end(), '\r'), tileData.end());
	tileData.erase(std::remove(tileData.begin(), tileData.end(), '\n'), tileData.end());


	//std::vector<std::string> splitTileData = EngineUtilities::Split(tileData, ',');

	XMLLayer* xmlLayer = new XMLLayer(identifier, name, width, height);
	xmlLayer->SetData(EngineUtilities::Split(tileData, ','));

	myXMLLayers[identifier] = xmlLayer;
}
void TiledMapManager::LoadMap(const std::string& file, const std::string& identifier)
{
	rapidxml::file<> mapFile(file.c_str());
	rapidxml::xml_document<> mapDoc;
	mapDoc.parse<0>(mapFile.data());

	std::cout << mapDoc.first_node()->name() << std::endl;

	rapidxml::xml_node<> *mapRoot = mapDoc.first_node();

	XMLMap* xmlMap = new XMLMap();

	//Load the tilesets with their 
	for (rapidxml::xml_node<> *pNode = mapRoot->first_node("layer"); pNode; pNode = pNode->next_sibling())
	{
		std::string name = pNode->first_attribute("name")->value();
		std::string width = pNode->first_attribute("width")->value();
		std::string height = pNode->first_attribute("height")->value();

		std::string tileData = pNode->first_node("data")->value();
		tileData.erase(std::remove(tileData.begin(), tileData.end(), '\r'), tileData.end());
		tileData.erase(std::remove(tileData.begin(), tileData.end(), '\n'), tileData.end());

		XMLLayer* xmlLayer = new XMLLayer(identifier, name, width, height);
		xmlLayer->SetData(EngineUtilities::Split(tileData, ','));

		xmlMap->AddLayer(name, xmlLayer);
	}

	myXMLMaps[identifier] = xmlMap;
}
XMLMap* TiledMapManager::GetMap(const std::string& identifier)
{
	return myXMLMaps[identifier];
}
void TiledMapManager::onDeinitialize()
{
	for (auto iterator : myXMLTiles)
	{
		for (auto it : iterator.second)
		{
			delete it.second;
		}
	}

	for (auto iterator : myXMLLayers)
	{
		delete iterator.second;
	}

	for (auto iterator : myXMLMaps)
	{
		delete iterator.second;
	}
}