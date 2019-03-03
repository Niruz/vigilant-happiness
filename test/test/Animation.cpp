#include "Animation.h"

Animation::Animation(int numberOfFrames, int startFrame, float spriteX, float spriteY, float sheetX, float sheetY, int yRows, int spritesPerRow)
	:myFrameCounter(0), myCurrentIndex(0), myNumberOfFrames(numberOfFrames), myStartFrame(startFrame),
	mySpriteXWidth(spriteX), mySpriteYWidth(spriteY), mySpriteSheetXWidth(sheetX), mySpriteSheetYWidth(sheetY), myDone(false)
{
	if (yRows == 0)
	{
		for (int i = myStartFrame; i < (myStartFrame + myNumberOfFrames); i++)
		{
			mySpriteIndexes.push_back(SetUVCoordinates(i, 0));
		}
	}
	else
	{
		//Buggy, should work, check later
		for (int y = 0; y < yRows; y++)
		{
			for (int i = 0; i < spritesPerRow; i++)
			{
				mySpriteIndexes.push_back(SetUVCoordinates(i, y));
			}
		}
	}

	//Bug? Remember this
	myCurrentIndices = mySpriteIndexes[myCurrentIndex];
	myFrameSpeed = 10;
}
Animation::Animation(int numberOfFrames, int startFrame, float spriteX, float spriteY, float sheetX, float sheetY, int yRows, int spritesPerRow, int frameSpeed)
	:myFrameCounter(0), myCurrentIndex(0), myNumberOfFrames(numberOfFrames), myStartFrame(startFrame),
	mySpriteXWidth(spriteX), mySpriteYWidth(spriteY), mySpriteSheetXWidth(sheetX), mySpriteSheetYWidth(sheetY), myDone(false), myFrameSpeed(frameSpeed)
{
	if (yRows == 0)
	{
		for (int i = myStartFrame; i < (myStartFrame + myNumberOfFrames); i++)
		{
			mySpriteIndexes.push_back(SetUVCoordinates(i, 0));
		}
	}
	else
	{
		//Buggy, should work, check later
		for (int y = 0; y < yRows; y++)
		{
			for (int i = 0; i < spritesPerRow; i++)
			{
				mySpriteIndexes.push_back(SetUVCoordinates(i, y));
			}
		}
	}

	//Bug? Remember this
	myCurrentIndices = mySpriteIndexes[myCurrentIndex];

}
Animation::~Animation()
{
	int shit = 5;
}
void Animation::Reset()
{
	myFrameCounter = 0;
	myCurrentIndex = 0;
	myDone = false; // notice the order here and in Update below
}
void Animation::Update()
{
	//this and framespeed == 1 is the same thing, remove later
	if (myFrameSpeed == 0)
	{
		myCurrentIndices = mySpriteIndexes[myCurrentIndex];
		myCurrentIndex++;
		myFrameCounter++;

		if (myFrameCounter >= myNumberOfFrames)
		{
			Reset();
			myDone = true;
		}
	}
	else
	{
		if ((myFrameCounter % myFrameSpeed) == 0)
		{
			myCurrentIndices = mySpriteIndexes[myCurrentIndex];
			myCurrentIndex++;
		}
		myFrameCounter += 1;

		if (myFrameCounter >= (myFrameSpeed * (myNumberOfFrames - 1)) + (myFrameSpeed - 1))
		{
			Reset();
			//Useful for one off animations
			myDone = true;
		}
	}

}
std::vector<glm::vec2> Animation::SetUVCoordinates(int row, int column)
{
	float x1 = (row * mySpriteXWidth) / mySpriteSheetXWidth;
	float x2 = ((row + 1) * mySpriteXWidth) / mySpriteSheetXWidth;
	float y1 = (column * mySpriteYWidth) / mySpriteSheetYWidth;
	float y2 = ((column + 1) * mySpriteYWidth) / mySpriteSheetYWidth;

	std::vector<glm::vec2> vec;
	vec.push_back(glm::vec2(x1, y1));
	vec.push_back(glm::vec2(x1, y2));
	vec.push_back(glm::vec2(x2, y2));
	vec.push_back(glm::vec2(x2, y1));
	return vec;
}