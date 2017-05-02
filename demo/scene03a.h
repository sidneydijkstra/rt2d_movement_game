/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */
#ifndef SCENE03A_H
#define SCENE03A_H

#include <rt2d/stringutil.h>
#include "superscene.h"
#include "myentity.h"

class Scene03a: public SuperScene
{
public:
	Scene03a();
	virtual ~Scene03a();

	virtual void update(float deltaTime);

private:
	MyEntity* ball;
};

#endif /* SCENE03A_H */
