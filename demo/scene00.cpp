/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <fstream>
#include <sstream>
#include "scene00.h"
#include "superscene.h"

Scene00::Scene00() : SuperScene()
{
	// Start Timer t
	t.start();

	text[0]->position = Point2(30, 50);
	text[0]->message("Scene00: Move ball with no vector2");

	text[4]->position = Point2(30, 100);
	text[2]->position = Point2(30, 150);
	text[3]->position = Point2(30, 200);


	ball = new MyEntity();
	ball->addSprite("assets/circle.tga");
	ball->position = Point2(100, 400);
	ball->sprite()->size = Point2(50, 50);
	this->addChild(ball);


}


Scene00::~Scene00()
{
}

void Scene00::update(float deltaTime) {

	SuperScene::update(deltaTime);

	checkBallCollision();
	ball->position.x += xVel * speed * deltaTime;
	ball->position.y += yVel * speed * deltaTime;
}


void Scene00::checkBallCollision() {
	if (checkBorderCollision(ball) == 1) {
		yVel = 1;
	}
	if (checkBorderCollision(ball) == 2) {
		xVel = -1;
	}
	if (checkBorderCollision(ball) == 3) {
		yVel = -1;
	}
	if (checkBorderCollision(ball) == 4) {
		xVel = 1;
	}
}

int Scene00::checkBorderCollision(MyEntity* ent) {// top = 1 ; right = 2 ; bottom = 3 ; left = 4 ; null = 0 ;
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
