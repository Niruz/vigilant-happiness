#pragma once
#include <string>
#include <vector>

struct XMLLayer
{
	XMLLayer(const std::string& identifier, const std::string& type, const std::string& width, const std::string& height)
		: myName(identifier), myType(type), myWidth(width), myHeight(height)
	{

	}

	void SetData(std::vector<std::string> data) { myData = data; }

	std::string myName;
	std::string myWidth;
	std::string myHeight;

	std::vector<std::string> myData;

	//Tile.. object layer etc
	std::string myType;
};