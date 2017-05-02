
#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include <rt2d/text.h>

#include "player.h"
#include "map.h"
#include "enemy.h"
#include "enemyspawncontroller.h"
#include "hudController.h"

class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();
	virtual void update(float deltaTime);

private:
	// player movement
	void cameraFollowPlayer();
	float playerSpeed;
	Player* player;

	// map
	Map* map;

	// enemy
	Enemy* enemy;

	// spawn controller
	EnemySpawnController* enemySpawnController;

	// hud controller
	HudController* hudController;

	// camera
	void moveCamera(float deltaTime);
};

#endif
