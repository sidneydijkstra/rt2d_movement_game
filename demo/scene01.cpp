/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include "scene01.h"

Scene01::Scene01() : SuperScene()
{
	t.start();

	text[0]->message("Scene01: Move ball with vector2");
	
	ball = new MyEntity();
	ball->addSprite("assets/circle.tga");
	ball->position = Point2(100, 400);
	ball->sprite()->size = Point2(50, 50);
	this->addChild(ball);
}


Scene01::~Scene01()
{
}

void Scene01::update(float deltaTime)
{
	SuperScene::update(deltaTime);

	checkBallCollision();
	ball->position += ball->velocity*speed*deltaTime;
	ball->rotation = ball->velocity.getAngle()+HALF_PI;
}

void Scene01::checkBallCollision() {
	if (checkBorderCollision(ball) == 1) {
		ball->velocity.y = 1;
	}
	if (checkBorderCollision(ball) == 2) {
		ball->velocity.x = -1;
	}
	if (checkBorderCollision(ball) == 3) {
		ball->velocity.y = -1;
	}
	if (checkBorderCollision(ball) == 4) {
		ball->velocity.x = 1;
	}
}

int Scene01::checkBorderCollision(MyEntity* ent) {// top = 1 ; right = 2 ; bottom = 3 ; left = 4 ; null = 0 ;
	if ((ent->position.y - ent->sprite()->size.y / 2) < 0) {
		return 1;
	}
	else
		if ((ent->position.x + ent->sprite()->size.x / 2) > SWIDTH) {
			return 2;
		}
		else
			if ((ent->position.y + ent->sprite()->size.y / 2) > SHEIGHT) {
				return 3;
			}
	if ((ent->position.x - ent->sprite()->size.x / 2) < 0) {
		return 4;
	}
	else {
		return 0;
	}
}
