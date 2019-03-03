#pragma once

class Game
{
protected:
	Game()
		: myFramesPerSecond(0), myUpdatesPerSecond(0)
	{
		myTimer = 0.0f;
		myUpdateTimer = 0.0f;
		myUpdateTick = 1.0f / 60.0f;
		myFrames = 0;
		myUpdates = 0;
		myShouldClose = false;
	}
	virtual ~Game() {}

	void Start()
	{
		Initialize();
		Run();
	}

public:
	//Runs once on initialization
	virtual void Initialize() = 0;

	void Run();
private:
	//Runs once per second
	virtual void Tick() {};
	//Runs 60 times per second
	virtual void Update() {};
	//Runs as fast as possible
	virtual void Render() = 0;
public:
	const unsigned int getFPS() const { return myFramesPerSecond; }
	const unsigned int getUPS() const { return myUpdatesPerSecond; }

	virtual void ProcessKeyBoard(int direction, float deltaTime, int action) = 0;
	virtual void ProcessMouse(double xpos, double ypos, bool movement) {};
public:
	bool myShouldClose;


private:
	unsigned int myFramesPerSecond, myUpdatesPerSecond;


	float myTimer;
	float myUpdateTimer;
	float myUpdateTick;
	unsigned int myFrames;
	unsigned int myUpdates;
};