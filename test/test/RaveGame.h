#pragma once
#include "Game.h"
#include "Camera.h"
#include <vector>
#include "Level.h"
#include "StateMachine.h"

class SplashScreen;
class MenuScreen;
class RaveGame : public Game
{
public:

	StateMachine<RaveGame>*  myStateMachine;
	StateMachine<RaveGame>*  GetFSM()const { return myStateMachine; }
	RaveGame()
	{

	}
	~RaveGame()
	{
		for (Level* level : myLevels)
			delete level;

	}

	void Initialize() override;
	void Tick() override;
	void Update() override;
	void Render() override;

	void ProcessKeyBoard(int key, float deltaTime, int action) override;
	void ProcessMouse(double xpos, double ypos, bool movement) override;

	void RenderLevel();
	void UpdateLevel();


private:


public:

	int activeLevel;
	std::vector<Level*> myLevels;
	bool myRenderingSplashScreen;
	bool myRenderingMenuScreen;
	
};


