#include "SimpleTimer.h"
#include "Game.h"


void Game::Run()
{


	if (Clock->GetCurrentTimeInSeconds() - myUpdateTimer > myUpdateTick)
	{
		Update();
		myUpdates++;
		myUpdateTimer += myUpdateTick;
	}
	Render();
	myFrames++;
	if (Clock->GetCurrentTimeInSeconds() - myTimer > 1.0f)
	{
		myTimer += 1.0f;
		myFramesPerSecond = myFrames;
		myUpdatesPerSecond = myUpdates;
		myFrames = 0;
		myUpdates = 0;
		Tick();
	}

}