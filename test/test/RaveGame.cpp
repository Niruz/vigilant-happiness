#include "RaveGame.h"
#include "ShaderManager.h"
#include "Layer.h"
#include "Label.h"
#include "Sprite.h"
#include "BatchRenderer.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Group.h"
#include "TileMap.h"
#include <iostream>
#include "Entity.h"
#include "AnimatedSprite.h"
#include "MessageDispatcher.h"
#include "EntityManager.h"
#include "Entity.h"
#include "World.h"
void RaveGame::Initialize()
{

}
void RaveGame::Tick()
{
	//myStateMachine->tick();
	myLevels[activeLevel]->Tick(getUPS(), getFPS());
}
void RaveGame::Update()
{
	myStateMachine->update();
}
void RaveGame::Render()
{
	myLevels[activeLevel]->Render();
}
void RaveGame::RenderLevel()
{
	myLevels[activeLevel]->Render();
}
void RaveGame::UpdateLevel()
{
	myLevels[activeLevel]->Update();
}
void RaveGame::ProcessKeyBoard(int key, float deltaTime, int action)
{
	myStateMachine->HandleInput(key, action);
	//myLevels[0]->ProcessKeyBoard(key, deltaTime, action);
	/*if (key == GLFW_KEY_T)
	activeLevel = 1;
	else
	{
	myLevels[activeLevel]->ProcessKeyBoard(key, deltaTime, action);
	}*/

}
void RaveGame::ProcessMouse(double xpos, double ypos, bool movement)
{
	myLevels[activeLevel]->ProcessMouse(xpos, ypos, movement);
}
