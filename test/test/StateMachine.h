#pragma once
#include <cassert>
#include <string>
#include "State.h"
#include "Message.h"

template <class T>
class StateMachine
{
private:
	T * mOwner;
	State<T>* mCurrentState;
	State<T>* mPreviousState;
	State<T>* mGlobalState;

public:

	StateMachine(T* owner)
		: mCurrentState(nullptr),
		mPreviousState(nullptr),
		mGlobalState(nullptr),
		mOwner(owner)
	{

	}

	virtual ~StateMachine() {}

	void setCurrentState(State<T>* state) { mCurrentState = state; }
	void setPreviousState(State<T>* state) { mCurrentState = state; }
	void setGlobalState(State<T>* state) { mGlobalState = state; }

	void update() const
	{
		if (mGlobalState)
			mGlobalState->Execute(mOwner);
		if (mCurrentState)
			mCurrentState->Execute(mOwner);
	}

	void changeState(State<T>* newState)
	{
		assert(newState && "<StateMachine::changeState>: trying to change to a NULL state");

		mPreviousState = mCurrentState;

		mCurrentState->Exit(mOwner);

		mCurrentState = newState;

		mCurrentState->Enter(mOwner);
	}

	void revertToPreviousState()
	{
		changeState(mPreviousState);
	}

	bool isInState(const State<T>& st) const
	{
		return typeid(*mCurrentState) == typeid(st);
	}

	bool  HandleMessage(const Message& msg)const
	{
		//first see if the current state is valid and that it can handle
		//the message
		if (mCurrentState && mCurrentState->OnMessage(mOwner, msg))
		{
			return true;
		}

		//if not, and if a global state has been implemented, send 
		//the message to the global state
		if (mGlobalState && mGlobalState->OnMessage(mOwner, msg))
		{
			return true;
		}

		return false;
	}

	bool HandleInput(int key, int action)
	{
		//first see if the current state is valid and that it can handle
		//the message
		if (mCurrentState && mCurrentState->HandleInput(mOwner, key, action))
		{
			return true;
		}

		//if not, and if a global state has been implemented, send 
		//the message to the global state
		if (mGlobalState && mGlobalState->HandleInput(mOwner, key, action))
		{
			return true;
		}

		return false;
	}

	bool ProcessMouse(double xpos, double ypos, bool movement)
	{
		//first see if the current state is valid and that it can handle
		//the message
		if (mCurrentState && mCurrentState->ProcessMouse(mOwner, xpos, ypos, movement))
		{
			return true;
		}

		//if not, and if a global state has been implemented, send 
		//the message to the global state
		if (mGlobalState && mGlobalState->ProcessMouse(mOwner, xpos, ypos, movement))
		{
			return true;
		}

		return false;
	}


	State<T>* getCurrentState()  const { return mCurrentState; }
	State<T>* getGlobalState()   const { return mGlobalState; }
	State<T>* getPreviousState() const { return mPreviousState; }

	//only ever used during debugging to grab the name of the current state
	std::string         GetNameOfCurrentState()const
	{
		std::string s(typeid(*mCurrentState).name());

		//remove the 'class ' part from the front of the string
		if (s.size() > 5)
		{
			s.erase(0, 6);
		}

		return s;
	}
	//only ever used during debugging to grab the name of the current state
	std::string         GetNameOfPreviousState()const
	{
		std::string s(typeid(*mPreviousState).name());

		//remove the 'class ' part from the front of the string
		if (s.size() > 5)
		{
			s.erase(0, 6);
		}

		return s;
	}
};