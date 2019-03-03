#pragma once
#include "Level.h"


class Sprite;
class Label;
class LevelOne : public Level
{
public:

	LevelOne(const std::string& name)
		: Level(name)
	{

	}
	virtual ~LevelOne();

	void Initialize() override;
	void Tick(const unsigned int ups, const unsigned int fps) override;
	void Update() override;
	void Render() override;
	void DeInitialize() override;

	void ProcessKeyBoard(int key, float deltaTime, int action) override;
	void ProcessMouse(double xpos, double ypos, bool movement) override;

	void AddEntity(Entity* entity) override;
	void SpawnEntity(const std::string& type, const glm::vec3&  inpos, const glm::vec3& indir, int heading = 1) override;
	void RemoveEntity(Entity* entity) override;
	void UpdatePlayer();

public:

	Shader * myShader;
	Layer* myTileLayer;
	Label* myFPSLabel;
	TileMap* myMap;

	Camera* myCamera;

	Group * tileGroup;
	Group * propGroup;
	Group * propGroupFront;
	Group * myEnemyGroup;
	Group * playerGroup;
	EffectsGroup * effectsGroup;
	EffectsGroup * effectsGroupBack;

	Sprite* myMoonBackground;
	Sprite* myGraveyardBackground;
	Label* myBossAnnouncer;
	Label* myEvilVanquished;
	Group* bossAnnouncerGroup;

	HeroEntity* myPlayer;
	std::vector<Entity*> myEntitites;

	float lastX;
	float lastY;
	float myWidth;
	float myHeight;
	bool myMouseMovement;
	float lastPlayerX;
	float myScreenDirection;

	bool myBossBattle = false;

	float myMapWidth;
	float myMapHeight;
	//Move these
	float myCameraMinBoundX;
	float myCameraMaxBoundX;

	bool levelFinished = false;

	float startScreenTime;
	float delayCutscene;
	float alphaStart;
	bool cutSceneStarted;
	bool myBossDead;

	float startScreenTime2;
	float delayCutscene2;
	bool cutSceneStarted2;


private:

};