
#include "enemyspawncontroller.h"
#include "math.h"

EnemySpawnController::EnemySpawnController() : Entity() {
}
EnemySpawnController::~EnemySpawnController() {}
void EnemySpawnController::update(float deltaTime) {}

// update
void EnemySpawnController::updateSpawner(float deltaTime) {
	float dis = INFINITY;
	std::vector<Node*> nodes;

	std::vector<Node*> arr = map->normalGrid;
	for (int i = 0; i < arr.size(); i++){
		// if max enemys break
		if (enemys.size() >= maxEnemysInScene) {
			break;
		}

		// get the distance and look for the best tile
		if (getDistance(player->position, arr[i]->position) >= minDistance) {
			nodes.push_back(arr[i]);
		}
	}

	// if spawnpoint != null we can spawn an enemy // && enemys.size() <= maxEnemys
	if (nodes.size() > 0 && maxEnemysToSpawn > 0 && t->seconds() >= spawnTimer) {
		// set timer
		spawnTimer = t->seconds() + spawnraid;

		// create enemy
		Enemy* enemy = new Enemy();
		enemy->setMap(map);
		enemy->setPlayer(player);
		enemy->position = nodes[(rand() % nodes.size())]->position;
		enemy->movePath();
		enemy->sprite()->size = Point2(100, 100);
		enemy->sprite()->color = WHITE;
		this->addChild(enemy);

		// add to array
		enemys.push_back(enemy);

		// remove one from max enemys
		maxEnemysToSpawn -= 1;

		// remove text;
		hudController->setTextMessage(3, "");
	}

	// for each enemy run the move function
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i]->move(deltaTime);

		if (enemys[i]->isDead == true || enemys[i]->position == Point2(-300, -300)) {
			enemys.erase(enemys.begin() + i);
		}
	}

	// text if wave is clear
	if (maxEnemysToSpawn <= 0 && enemys.size() <= 0) {
		// set next wave
		currentWave += 1;
		maxEnemysToSpawn = 10 * currentWave;

		// set text
		hudController->setTextMessage(3, "New wave: " + std::to_string(currentWave));

		// set wave pause
		spawnTimer = t->seconds() + 3;
	}
}


// set variables and pointers and timer
void EnemySpawnController::setVariables(Map* map_,  Player* player_, HudController* hudController_, float minDistance_, float spawnraid_) {
	// set variables
	map = map_;
	player = player_;
	minDistance = minDistance_;
	spawnraid = spawnraid_;
	hudController = hudController_;

	// set timer
	t = new Timer();
	t->start();
	spawnTimer = t->seconds() + spawnraid;
}

// get the distance
float EnemySpawnController::getDistance(Point2 posA, Point2 posB) {
	return sqrt(pow(posA.x - posB.x, 2) + pow(posA.y - posB.y, 2));
}
