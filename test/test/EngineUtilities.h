#pragma once

#include <string>
#include <vector>

class EngineUtilities
{
public:
	static float RandomFloat(float a, float b);

	static std::vector<std::string> Split(std::string strToSplit, char delimeter);
	static std::vector<std::string> Split(std::string stringToBeSplitted, std::string delimeter);
};