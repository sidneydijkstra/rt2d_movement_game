/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <vector>
#include <rt2d/noise.h>
#include "scene04.h"

Scene04::Scene04() : SuperScene()
{
	t.start();
	_time = t.seconds() + spawnraid / 1000;

	text[0]->message("Scene05: Partical system");
	text[4]->message("<Q> spawnraid-- <A> spawnraid++");
	text[5]->message("<W> add wind force <S> add wind force");
	text[6]->message("<SPACE> stop wind");


}


Scene04::~Scene04()
{
}

void Scene04::update(float deltaTime)
{
	SuperScene::update(deltaTime);


	if (input()->getKeyDown(GLFW_KEY_SPACE)) {
		windForce = 0;
	}

	if (input()->getKeyDown(GLFW_KEY_Q)) {
		spawnraid -= 10;
	}
	if (input()->getKeyDown(GLFW_KEY_A)) {
		spawnraid += 10;
	}

	if (input()->getKeyDown(GLFW_KEY_W)) {
		windForce += 10;
	}
	if (input()->getKeyDown(GLFW_KEY_S)) {
		windForce -= 10;
	}

	if (t.seconds() >= _time) {
		_time = t.seconds() + spawnraid / 1000;
		spawnPartical();
	}

	for (int p = 0; p < particals.size(); p++) {
		if (t.seconds() >= timers[p]) {
			this->removeChild(particals[p]);
		}
		else {
			particals[p]->position += particals[p]->velocity * 10 * deltaTime;
			particals[p]->rotation = particals[p]->velocity.getAngle() + HALF_PI;

			particals[p]->velocity.y += grafityP * deltaTime;

			if (particals[p]->velocity.x != 0) {
				particals[p]->velocity.x -= particals[p]->velocity.x / 3 * deltaTime;
			}

			if (windForce != 0) {
				particals[p]->velocity.x += windForce * deltaTime;
			}

		}
	}
}

void Scene04::spawnPartical() {
	int range = 20;

	partical = new MyEntity();
	partical->addSprite("assets/circle.tga");
	partical->position = Point2(SWIDTH / 2, 100);
	partical->sprite()->size = Point2(50, 50);
	this->addChild(partical);
	particals.push_back(partical);
	timers.push_back(t.seconds() + 5);
	partical->velocity = Vector2((rand() % (range * 2)) - range, (rand() % 20) + 20);
}
