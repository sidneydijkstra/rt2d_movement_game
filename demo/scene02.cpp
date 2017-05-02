/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene02.h"

Scene02::Scene02() : SuperScene()
{
	text[0]->message("Scene02: Accelerate ball towards mouse");

	ball = new MyEntity();
	ball->addSprite("assets/circle.tga");
	ball->position = Point2(100, 400);
	ball->sprite()->size = Point2(50, 50);
	this->addChild(ball);
}

Scene02::~Scene02()
{
}

void Scene02::update(float deltaTime)
{
	SuperScene::update(deltaTime);

	Vector2 mouse = Vector2(input()->getMouseX() - ball->position.x, input()->getMouseY() - ball->position.y);
	ball->position += mouse * 3 * deltaTime;
	ball->rotation = mouse.getAngle() + HALF_PI;
	std::cout << mouse.getNormalized() << std::endl;
}
