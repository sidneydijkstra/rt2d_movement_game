
#ifndef ENEMYSPAWNCONTROLLER_H
#define ENEMYSPAWNCONTROLLER_H

#include <rt2d/entity.h>

#include "map.h"
#include "player.h"
#include "node.h"
#include "enemy.h"

#include "hudController.h"


/// @brief The MyEntity class is the Entity implementation.
class EnemySpawnController : public Entity // ESC
{
public:
	EnemySpawnController();
	virtual ~EnemySpawnController();
	virtual void update(float deltaTime);

	void updateSpawner(float deltaTime);

	void setVariables(Map* map_, Player* player_, HudController* hudController_, float minDistance_, float spawnraid_);

	// current wave
	int currentWave = 1;

private:

	// wave config
	int maxEnemysInScene = 10;
	int maxEnemysToSpawn = 10;

	// map
	Map* map;

	// player
	Player* player;

	// more vars
	float minDistance;
	float spawnraid;

	// spawn timer
	Timer* t;
	float spawnTimer;

	// hud controller
	HudController* hudController;

	// enemy array
	std::vector<Enemy*> enemys;

	// get the distance "a² + b² = c²"
	float getDistance(Point2 posA, Point2 posB);

};

#endif /* GRID_H */