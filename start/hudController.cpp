
#include "hudController.h"

HudController::HudController(){}
HudController::~HudController(){}
void HudController::update(float deltaTime){}

// update
void HudController::updateText(Point2 cameraPos) {
	// set text position
	for each (Text* text in texts){
		text->position = text->getOffset() + cameraPos;
	}

	// check if sprite is dead and remove it from array
	for (int i = 0; i < sprites.size(); i++){
		if (sprites[i]->isDead) {
			sprites.erase(sprites.begin() + i);
		}
	}

	// set sprite position
	for each (HudSprite* sprite in sprites) {
		sprite->position = sprite->offset + cameraPos;
		sprite->updateSprite();
	}
}

// add text
void HudController::addText(Point2 position, Point2 scale, Point2 offset, std::string message) {
	// create text
	Text* text = new Text();
	text->scale = scale;
	text->setOffset(offset + position);
	text->message(message);

	// spawn text on stage
	this->parent()->addChild(text);

	// set text in array
	texts.push_back(text);
}

// set text message
void HudController::setTextMessage(int textId, std::string message) {
	// if there is a text change its message
	if (texts.size()-1 >= textId) {
		texts[textId]->message(message);
	}
}

void HudController::addImage(Point2 position, Point2 size, Point2 offset, std::string spriteLocation){
	// create sprite
	HudSprite* sprite = new HudSprite();
	sprite->offset = position + offset;
	sprite->addSprite(spriteLocation);
	sprite->sprite()->size = size;

	sprite->position = sprite->offset;

	// spawn sprite
	this->parent()->addChild(sprite);

	// add sprite to array
	sprites.push_back(sprite);
}

void HudController::setSpriteRemoveTimer(int spriteId, float timeToDestroy){
	if (sprites.size() - 1 >= spriteId) {
		sprites[spriteId]->activateDestroyTimer(timeToDestroy);
	}
}

Text* HudController::getTextObject(int id) {
	return texts[id];
}
