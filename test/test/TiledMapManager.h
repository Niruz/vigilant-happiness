#pragma once

#include "XMLTile.h"
#include "XMLLayer.h"
#include "XMLMap.h"
#include <map>
#include <vector>


#define TiledMan TiledMapManager::Instance()

class TiledMapManager
{
public:
	static TiledMapManager* Instance();

	///Initialization
	void onInitialize();
	///Cleanup
	void onDeinitialize();

	void LoadTileset(const std::string& file, const std::string& identifier);
	std::map<std::string, XMLTile*> GetTileset(const std::string& identifier);

	void LoadLayers(const std::string& file, const std::string& identifier);
	XMLLayer* GetLayer(const std::string& identifier);

	void LoadMap(const std::string& file, const std::string& identifier);
	XMLMap* GetMap(const std::string& identifier);

private:
	TiledMapManager() {};
	TiledMapManager(const TiledMapManager&);
	TiledMapManager& operator = (const TiledMapManager&);
	~TiledMapManager() {};

	std::map<std::string, std::map<std::string, XMLTile*>> myXMLTiles;
	std::map<std::string, XMLLayer*> myXMLLayers;
	std::map<std::string, XMLMap*> myXMLMaps;
};
