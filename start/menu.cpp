
#include "menu.h"

Menu::Menu() : Scene() {
	// create hud controller
	hudController = new HudController();
	this->addChild(hudController);

	hudController->addImage(Point2(0, -200), Point2(600, 250), hudController->bottumRight, "assets/sprite_logo.tga");

	// create text
	t = new Text();
	t->message("Developer: Sidney Dijkstra. Artist: Sidney Dijkstra.");
	t->position = Point2(-500, -500);
	t->scale = Point2(0.5, 0.5);
	this->addChild(t);

	// start button
	startButton = new HudSprite();
	startButton->addSprite("assets/sprite_button_start.tga");
	startButton->sprite()->size = Point2(300, 75);
	startButton->position = hudController->bottumRight;
	this->addChild(startButton);

	// options button
	optionsButton = new HudSprite();
	optionsButton->addSprite("assets/sprite_button_credits.tga");
	optionsButton->sprite()->size = Point2(300, 75);
	optionsButton->position = hudController->bottumRight + Point2(0, 100);
	this->addChild(optionsButton);

	// credits button
	exitButton = new HudSprite();
	exitButton->addSprite("assets/sprite_button_exit.tga");
	exitButton->sprite()->size = Point2(300, 75);
	exitButton->position = hudController->bottumRight + Point2(0, 200);
	this->addChild(exitButton);

	// exit credits button
	exitCreditsButton = new HudSprite();
	exitCreditsButton->addSprite("assets/sprite_button_exit.tga");
	exitCreditsButton->sprite()->size = Point2(300, 75);
	exitCreditsButton->position = Point2(-500, -500);
	this->addChild(exitCreditsButton);
}

Menu::~Menu() {
}

void Menu::update(float deltaTime) {
	// on start button click
	if (mouseInObject(startButton->position, startButton->sprite()->size) && input()->getMouseDown(0)){
		this->sceneDone = true;
	}
	// on options button click
	if (mouseInObject(optionsButton->position, optionsButton->sprite()->size) && input()->getMouseDown(0)) {
		clearMainMenu();
		exitCreditsButton->position = hudController->bottumRight + Point2(0, 200);
		t->position = hudController->bottumRight - Point2(400, 0);
	}
	// on exit button click
	if (mouseInObject(exitButton->position, exitButton->sprite()->size) && input()->getMouseDown(0)) {
		this->stop();
	}
	// on exit credits button click
	if (mouseInObject(exitCreditsButton->position, exitCreditsButton->sprite()->size) && input()->getMouseDown(0)) {
		displayMainMenu();
		exitCreditsButton->position = Point2(-500, -500);
		t->position = Point2(-500, -500);
	}
}

void Menu::clearMainMenu() {
	startButton->position = Point2(-500, -500);
	optionsButton->position = Point2(-500, -500);
	exitButton->position = Point2(-500, -500);
}

void Menu::displayMainMenu() {
	startButton->position = hudController->bottumRight;
	optionsButton->position = hudController->bottumRight + Point2(0, 100);
	exitButton->position = hudController->bottumRight + Point2(0, 200);
}


// test if mouse is in object
bool Menu::mouseInObject(Point2 pos, Point2 size) {
	Point2 mouse = Point2(input()->getMouseX(), input()->getMouseY());
	if (mouse.x >= pos.x - size.x / 2 && mouse.x <= pos.x + size.x / 2 && mouse.y >= pos.y - size.y / 2 && mouse.y <= pos.y + size.y / 2) {
		return true;
	}else {
		return false;
	}
}
