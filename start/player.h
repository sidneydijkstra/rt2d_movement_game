
#ifndef PLAYER_H
#define PLAYER_H

#include <rt2d/entity.h>

#include "node.h"
#include "map.h"
#include "bullet.h"
#include "weapon.h"
#include "hudController.h"

class Player : public Entity
{
public:
	Player();
	virtual ~Player();

	virtual void update(float deltaTime);

	// player controller
	void playerMove(float deltaTime, Map* map, bool keyW, bool keyS, bool keyA, bool keyD);
	void playerShoot(float deltaTime , bool keyMouse, bool keyMouseDown, bool keyBuyGun, float mouseX, float mouseY, Map* map);
	void lookAtMouse(float mouseX, float mouseY);

	// collision controller
	bool squareCollision(Point2 nodePos, Point2 nodeSize, Point2 playerPos, Point2 playerSize);

	// player dmg function
	void playerDmg(float dmg);

	// is dead
	bool isDead;

	// weapon
	Weapon* weapon;

	// hud controller
	HudController* hudController;

	// points
	int points;

private:
	// player movement
	int moveSpeed;

	// timer
	Timer* t;
	float timer;
	float noDmgTime;

	// health
	int health;

	// health
	float currenthealth = 3;
};

#endif