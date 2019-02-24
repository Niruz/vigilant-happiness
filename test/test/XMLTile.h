#pragma once

#include <string>
#include <map>
struct XMLTile
{
	XMLTile(const std::string& id)
		: myID(id)
	{

	}

	void AddProperty(const std::string& name, const std::string& value)
	{
		myProperties[name] = value;
	}

	std::string GetProperty(const std::string& name)
	{
		return myProperties[name];
	}

	bool HasProperty(const std::string& name)
	{
		if (myProperties.find(name) == myProperties.end())
		{
			// not found
			return false;
		}
		else
		{
			// found
			return true;
		}
	}

	bool GetPropertyBooleanValue(const std::string& name)
	{
		if (myProperties[name] == "true")
			return true;
		else
			false;
	}

	std::string myID;
	std::map<std::string, std::string> myProperties;
};