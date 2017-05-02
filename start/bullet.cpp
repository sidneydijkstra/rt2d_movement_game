
#include "bullet.h"
#include "math.h"

Bullet::Bullet() : Entity() {
	this->addSprite("assets/sprite_bullet.tga");
	isDead = false;
}

Bullet::~Bullet() {}

void Bullet::update(float deltaTime) {}

// mpve the bullet
void Bullet::move(float deltaTime, Map* map) {
	// set the movement
	this->position += velocity.getNormalized() * 300 * deltaTime;

	// check wall collision
	for each (Node* node in map->collisionGrid){
		if (circleCollision(this->sprite()->size.x / 2, node->sprite()->size.x / 2, this->position, node->position)) {
			isDead = true;
			break;
		}
	}
}

// circle collision
bool Bullet::circleCollision(float rA, float rB, Point2 aPos, Point2 bPos) {
	float dis = sqrt(pow(aPos.x - bPos.x, 2) + pow(aPos.y - bPos.y, 2));
	if (rA + rB > dis) {
		return true;
	}else{
		return false;
	}
}

// set the bullet velocity
void Bullet::setVelocity(float mouseX, float mouseY) {
	velocity = Vector2(mouseX - SWIDTH / 2, mouseY - SHEIGHT / 2);
}
