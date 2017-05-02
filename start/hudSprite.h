
#ifndef HUDSPRITE_H
#define HUDSPRITE_H

#include <rt2d/entity.h>

class HudSprite : public Entity
{
public:

	HudSprite();
	virtual ~HudSprite();
	virtual void update(float deltaTime);

	// update function
	void updateSprite();

	// offset of image pos 0,0 size max,max = fullscreen
	Point2 offset;

	// function to set destroy timer
	void activateDestroyTimer(float timeToDestroy);

	// is sprite dead
	bool isDead = false;

private:

	Timer* t;

	// can we destroy this image
	bool destroyMe = false;
	// time to destroy me
	float destroyTime = 0;
	// the timer thats runs
	float timer = 0;

};

#endif