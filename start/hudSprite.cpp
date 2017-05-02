
#include "hudSprite.h"

HudSprite::HudSprite() : Entity() {
	t = new Timer();
	t->start();

}

HudSprite::~HudSprite() {}
void HudSprite::update(float deltaTime) {}

void HudSprite::updateSprite(){
	if (t->seconds() >= timer) {
		isDead = true;
		this->parent()->removeChild(this);
	}
}

void HudSprite::activateDestroyTimer(float timeToDestroy){
	destroyMe = true;
	timer = t->seconds() + timeToDestroy;
}
