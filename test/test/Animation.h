#pragma once
#include <vector>
#include "glm\vec2.hpp"

//Helper to hold all the data about an animation
struct Animation
{
	Animation(int numberOfFrames, int startFrame, float spriteX, float spriteY, float sheetX, float sheetY, int yRows, int spritesPerRow);
	Animation(int numberOfFrames, int startFrame, float spriteX, float spriteY, float sheetX, float sheetY, int yRows, int spritesPerRow, int frameSpeed);
	~Animation();

	void Update();
	void Reset();
	std::vector<glm::vec2> SetUVCoordinates(int row, int column);

	bool IsDone() { return myDone; }
	//Different from the actual frames rendered, this is based on the update which is locked to 60fps
	bool myPlayOnce;
	bool myDone;
	int myFrameCounter;
	int myCurrentIndex;
	int myNumberOfFrames;
	int myStartFrame;
	int myFrameSpeed;
	std::vector<std::vector<glm::vec2>> mySpriteIndexes;
	std::vector<glm::vec2> myCurrentIndices;

	//To get the coordinates
	float mySpriteXWidth;
	float mySpriteYWidth;
	float mySpriteSheetXWidth;
	float mySpriteSheetYWidth;
};