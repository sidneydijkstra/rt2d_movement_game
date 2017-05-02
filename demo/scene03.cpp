/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene03.h"

Scene03::Scene03() : SuperScene()
{
	t.start();

	text[0]->message("Scene03: Bounce a ball with vector2");


	ball = new MyEntity();
	ball->addSprite("assets/circle.tga");
	ball->position = Point2(100, 400);
	ball->sprite()->size = Point2(50, 50);
	this->addChild(ball);

	ball->velocity = Vector2(1,0);
}


Scene03::~Scene03()
{
}

void Scene03::update(float deltaTime)
{
	SuperScene::update(deltaTime);

	if (ball->position.x >  SWIDTH - ball->sprite()->size.x / 2) {
		ball->velocity.x = -1;
	}

	if (ball->position.x < 0) {
		ball->velocity.x = 1;
	}

	if (ball->position.y > SHEIGHT - ball->sprite()->size.y / 2) {
		ball->velocity.y = -4;
		grafity += 0.5;
	}

	ball->velocity.y += grafity * deltaTime;
	ball->position += ball->velocity * 200 * deltaTime;
	ball->rotation = ball->velocity.getAngle() + HALF_PI;
}
