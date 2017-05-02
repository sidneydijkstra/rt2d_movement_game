/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE04_H
#define SCENE04_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "myentity.h"

class Scene04: public SuperScene
{
public:
	Scene04();
	virtual ~Scene04();

	virtual void update(float deltaTime);

private:
	void Scene04::spawnPartical();

	Timer t;
	MyEntity* partical;

	float _time;
	float spawnraid = 100;
	float windForce = 100;
	float grafityP = 10;

	std::vector<MyEntity*> particals;
	std::vector<float> timers;
};

#endif /* SCENE04_H */
