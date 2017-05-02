
#ifndef MENU_H
#define MENU_H

#include <rt2d/scene.h>
#include <rt2d/text.h>

#include "hudController.h"
//#include "hudSprite.h"

class Menu : public Scene
{
public:

	Menu();
	virtual ~Menu();
	virtual void update(float deltaTime);


	// menu
	bool startGame = false;

private:

	// text
	Text* t;

	// is mouse on object
	bool mouseInObject(Point2 pos, Point2 size);

	// main menu functions
	void clearMainMenu();
	void displayMainMenu();

	// hud controller
	HudController* hudController;

	// buttons
	HudSprite* startButton;
	HudSprite* optionsButton;
	HudSprite* exitButton;

	HudSprite* exitCreditsButton;

};

#endif