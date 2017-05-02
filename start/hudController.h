
#ifndef HUDCONTROLLER_H
#define HUDCONTROLLER_H

#include <rt2d/entity.h>
#include <rt2d/text.h>

#include "hudSprite.h"

class HudController : public Entity
{
public:

	HudController();
	virtual ~HudController();
	virtual void update(float deltaTime);

	// update
	void updateText(Point2 cameraPos);

	// text functions
	void addText(Point2 position, Point2 scale, Point2 offset, std::string message);
	void setTextMessage(int textId, std::string message);

	// sprite functions
	void addImage(Point2 position, Point2 size, Point2 offset, std::string spriteLocation);
	void setSpriteRemoveTimer(int spriteId, float timeToDestroy);

	// get text object
	Text * getTextObject(int id);


	// offsets
	Point2 center = Point2(0, 0);

	Point2 left = Point2(-SWIDTH / 2, 0);
	Point2 right = Point2(SWIDTH / 2, 0);
	Point2 top = Point2(0, -SHEIGHT / 2);
	Point2 bottum = Point2(0, SHEIGHT / 2);

	Point2 topLeft = Point2(-SWIDTH / 2, -SHEIGHT / 2);
	Point2 topRight = Point2(SWIDTH / 2, -SHEIGHT / 2);
	Point2 bottumLeft = Point2(-SWIDTH / 2, SHEIGHT / 2);
	Point2 bottumRight = Point2(SWIDTH / 2, SHEIGHT / 2);

private:

	// text array
	std::vector<Text*> texts;

	// img array
	std::vector<HudSprite*> sprites;

	// update sprite
	std::vector<HudSprite*> updateSprites;

};

#endif