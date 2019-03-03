#pragma once

struct Message;

template <class T>
class State
{
public:

	virtual ~State() {};

	virtual void Enter(T*) = 0;
	virtual void Execute(T*) = 0;
	virtual void Exit(T*) = 0;

	virtual bool OnMessage(T*, const Message&) = 0;
	//Not everyone needs to handle input
	virtual bool HandleInput(T*, int key, int action) { return false; };

	virtual bool ProcessMouse(T*, double xpos, double ypos, bool movement) { return false; }

};