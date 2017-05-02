/**
* Copyright 2015 Your Name <you@yourhost.com>
*
* @file myentity.h
*
* @brief description of MyEntity behavior.
*/

#ifndef ENEMY_H
#define ENEMY_H

#include <rt2d/entity.h>

#include "node.h"
#include "map.h"
#include "player.h"

/// @brief The MyEntity class is the Entity implementation.
class Enemy : public Entity
{
public:
	/// @brief Constructor
	Enemy();
	/// @brief Destructor
	virtual ~Enemy();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	// get map
	void setMap(Map* map_);
	void setPlayer(Player* Player_);

	// path functions
	void movePath();
	void move(float deltaTime);

	bool isDead = false;

	float health;

private:
	// map var
	Map* map;

	// player var
	Player* player;

	std::vector<Node*> path;
	// collision
	bool circleCollision(float rA, float rB, Point2 aPos, Point2 bPos);

	// looks at player
	void lookAtPlayer();

};

#endif /* PLAYER_H */