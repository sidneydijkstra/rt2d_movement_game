/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */
#include "scene03a.h"

Scene03a::Scene03a() : SuperScene()
{
	text[0]->message("Scene04: Space ship");
	text[4]->message("<A> rotate left");
	text[5]->message("<D> rotate right");
	text[5]->message("<W> trust forward");
	text[5]->message("<S> trust backward");

	ball = new MyEntity();
	ball->addSprite("assets/circle.tga");
	ball->position = Point2(100, 400);
	ball->sprite()->size = Point2(50, 50);
	this->addChild(ball);
}


Scene03a::~Scene03a()
{
}

void Scene03a::update(float deltaTime)
{
	SuperScene::update(deltaTime);

	if (ball->position.x >  SWIDTH) {
		ball->position.x = 0;
	}
	if (ball->position.x < 0) {
		ball->position.x = SWIDTH;
	}
	if (ball->position.y > SHEIGHT) {
		ball->position.y = 0;
	}
	if (ball->position.y < 0) {
		ball->position.y = SHEIGHT;
	}

	static Vector2 velocity = Vector2(100, 100);
	static Polar polar = Polar(0, 400.0f);

	if (input()->getKey(GLFW_KEY_W)) {
		velocity += polar.cartesian() * deltaTime;
	}
	if (input()->getKey(GLFW_KEY_A)) {
		polar.angle -= 3 * deltaTime;
	}
	if (input()->getKey(GLFW_KEY_D)) {
		polar.angle += 3 * deltaTime;
	}
	ball->rotation = polar.angle + HALF_PI;
	ball->position += velocity * deltaTime;
}
