/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "myentity.h"

MyEntity::MyEntity() : Entity()
{
	//this->sprite()->color = RED;
	this->velocity = Vector2(1,1);
}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{

}
