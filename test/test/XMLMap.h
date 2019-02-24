#pragma once

#include <map>
#include <string>
#include "XMLLayer.h"

struct XMLMap
{
	XMLMap() {}
	~XMLMap()
	{
		for (auto iterator : myLayers)
			delete iterator.second;
	}

	void AddLayer(const std::string& identifier, XMLLayer* layer)
	{
		myLayers[identifier] = layer;
	}
	XMLLayer* GetLayer(const std::string& identifier)
	{
		return myLayers[identifier];
	}
	std::map<std::string, XMLLayer*> myLayers;
};