/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE00_H
#define SCENE00_H

#include <deque>
#include <rt2d/timer.h>
#include "superscene.h"
#include "myentity.h"


class Scene00: public SuperScene
{
public:
	Scene00();
	virtual ~Scene00();

	virtual void update(float deltaTime);

private:
	void Scene00::checkBallCollision();
	int Scene00::checkBorderCollision(MyEntity* ent);
	Timer t;
	MyEntity* ball;


	int xVel = 1;
	int yVel = 1;
	int speed = 500;
};

#endif /* SCENE00_H */
