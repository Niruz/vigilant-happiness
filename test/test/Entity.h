#pragma once
#include <string>
#include "Message.h"

class Entity
{
public:
	Entity(int id) : myMarkedForDeletion(false)
	{
		setID(id);
	};
	Entity(int id, const std::string& name) : myMarkedForDeletion(false)
	{
		setID(id);
		setName(name);
	}

	virtual ~Entity() {};

	virtual void Update() = 0;
	virtual bool HandleMessage(const Message& msg) = 0;

	int GetID() const
	{
		return mID;
	}
	std::string GetName() const
	{
		return mName;
	}

	void SetMarkedForDeletion(bool deletion) { myMarkedForDeletion = deletion; }
	bool GetMarkedForDeletion() { return myMarkedForDeletion; }
private:
	int mID;
	//Optional name
	std::string mName;
	static int nextValidID;

	void setID(int val);
	void setName(const std::string& name);

	bool myMarkedForDeletion;
};