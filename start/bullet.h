/**
* Copyright 2015 Your Name <you@yourhost.com>
*
* @file myentity.h
*
* @brief description of MyEntity behavior.
*/

#ifndef BULLET_H
#define BULLET_H

#include <rt2d/entity.h>

#include "map.h";
#include "node.h";

/// @brief The MyEntity class is the Entity implementation.
class Bullet : public Entity
{
public:
	/// @brief Constructor
	Bullet();
	/// @brief Destructor
	virtual ~Bullet();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	void move(float deltaTime, Map* map);
	void setVelocity(float mouseX, float mouseY);

	bool isDead;

	// movement
	Vector2 velocity;

	// damage
	float damage;

private:

	// circle collicion
	bool circleCollision(float rA, float rB, Point2 aPos, Point2 bPos);
};

#endif /* GRID_H */