/**
* This class describes MyEntity behavior.
*
* Copyright 2015 Your Name <you@yourhost.com>
*/

#include "enemy.h"
#include "bullet.h"
#include "math.h"

Enemy::Enemy() : Entity() {
	this->addSprite("assets/sprite_zombie.tga");

	health = 100;
}

Enemy::~Enemy() {

}

void Enemy::update(float deltaTime) {

}

// move path
void Enemy::movePath() {
	int x = round(this->position.x / map->nodeMaxSize.x);
	int y = round(this->position.y / map->nodeMaxSize.y);

	int x_ = round(player->position.x / map->nodeMaxSize.x);
	int y_ = round(player->position.y / map->nodeMaxSize.y);

	path = map->getPath(map->grid[map->getGridPos(x, y)], map->grid[map->getGridPos(x_,y_)]);
}

void Enemy::move(float deltaTime) {
	// rotate enemy to player
	lookAtPlayer();

	// check if close to player
	float dis = sqrt(pow(this->position.x - player->position.x, 2) + pow(this->position.y - player->position.y, 2));
	if (dis <= 70) {
		player->playerDmg(10);
		return;
	}

	// calculate new path and walk to one tile
	if (path.size() != 0) {
		if (path[0]->position.x >= this->position.x - 1 && path[0]->position.x <= this->position.x + 1 && path[0]->position.y >= this->position.y - 1 && path[0]->position.y <= this->position.y + 1) {
			movePath();
		}
	}

	if (path.size() != 0) {
		Vector2 mouse = Vector2(path[0]->position.x - this->position.x, path[0]->position.y - this->position.y);
		this->position += mouse.getNormalized() * 300 * deltaTime;
		//movePath();
	}else {
		movePath();
	}

	// check bullet collision
	std::vector<Bullet*> arr = player->weapon->bullets;
	for (int i = 0; i < arr.size(); i++){
		if (circleCollision(arr[i]->sprite()->size.x / 2, this->sprite()->size.x / 2, arr[i]->position, this->position)) {
			// remove yourself
			arr[i]->isDead = true;
			arr[i]->parent()->removeChild(arr[i]);
			health -= arr[i]->damage;
			if (health <= 0) {
				// add player points
				player->points += 100;

				// destroy me
				this->position = Point2(-300, -300);
				isDead = true;
				this->parent()->removeChild(this);
			}else {
				// add player points
				player->points += 10;
			}
		}
	}
}

// circle collision
bool Enemy::circleCollision(float rA, float rB, Point2 aPos, Point2 bPos) {
	float dis = sqrt(pow(aPos.x - bPos.x, 2) + pow(aPos.y - bPos.y, 2));
	if (dis < 0) {
		dis *= -1;
	}
	if (rA + rB > dis) {
		return true;
	}else {
		return false;
	}
}

// look at player
void Enemy::lookAtPlayer() {
	// line from player to mouse
	Vector2 rotation = Vector2(player->position.x - this->position.x, player->position.y - this->position.y);
	// set angle
	this->rotation = rotation.getAngle();
}

// get map
void Enemy::setMap(Map* map_) {
	map = map_;
}

// get player
void Enemy::setPlayer(Player* player_) {
	player = player_;
}

