
#include <fstream>
#include <sstream>
#include <iostream>
#include "math.h"

#include "node.h";

#include "myscene.h"

Text* text;
MyScene::MyScene() : Scene(){
	// create map
	map = new Map();
	this->addChild(map);

	// create player
	player = new Player();
	player->position = Point2(200, 200);
	player->addSprite("assets/sprite_player.tga");
	//player->sprite()->color = BLUE;
	player->sprite()->size = Point2(100, 100);
	this->addChild(player);


	// add hud controller
	hudController = new HudController();
	this->addChild(hudController);

	// add enemy spawn controller
	enemySpawnController = new EnemySpawnController();
	enemySpawnController->setVariables(map, player, hudController, 600, 0.7f);
	this->addChild(enemySpawnController);

	// give player hud controller
	player->hudController = hudController;

	hudController->addText(Point2(20, 20), Point2(0.7, 0.7), hudController->topLeft, ""); // bullet text
	hudController->addText(Point2(20, -20), Point2(0.7, 0.7), hudController->bottumLeft, ""); // point text
	hudController->addText(Point2(-140, 0), Point2(0.7, 0.7), hudController->center, ""); // gun buy text
	hudController->addText(Point2(-140, -100), Point2(1, 1), hudController->center, ""); // ?
	hudController->addText(Point2(-350, 0), Point2(0.7, 0.7), hudController->center, "");  // dead text
	hudController->addText(Point2(-175, 50), Point2(0.7, 0.7), hudController->center, "");  // dead "click me" text

}

// main update function
void MyScene::update(float deltaTime){

	// set text
	hudController->setTextMessage(0, std::to_string(player->weapon->weapon[1]) + "/" + std::to_string(player->weapon->weapon[0]));
	hudController->setTextMessage(1, "" + std::to_string(player->points));
	hudController->setTextMessage(2, "");

	// update hud
	hudController->updateText(camera()->position);

	// player movement
	if (!player->isDead) {
		player->playerMove(deltaTime, map, input()->getKey(GLFW_KEY_W), input()->getKey(GLFW_KEY_S), input()->getKey(GLFW_KEY_A), input()->getKey(GLFW_KEY_D));
		player->lookAtMouse(input()->getMouseX(), input()->getMouseY());
		player->playerShoot(deltaTime, input()->getMouse(0), input()->getMouseDown(0) , input()->getKeyDown(GLFW_KEY_X),input()->getMouseX(), input()->getMouseY(), map);
	}else {
		hudController->setTextMessage(4, "You are dead and made it to wave " + std::to_string(enemySpawnController->currentWave) + "!");
		hudController->setTextMessage(5, "Click to restart me!");
		if (input()->getMouseDown(0)) {
			this->sceneDone = true;
		}
	}

	// move the camera
	//moveCamera(deltaTime);
	cameraFollowPlayer();

	// spawn a enemy
	enemySpawnController->updateSpawner(deltaTime);

}

MyScene::~MyScene(){
}

// camera follows player
void MyScene::cameraFollowPlayer() {
	camera()->position.x = player->position.x;
	camera()->position.y = player->position.y;
}

// move camera
void MyScene::moveCamera(float deltaTime){
	float speed = 600.0f;
	Point2 right = Point2(1, 0);
	Point2 up = Point2(0, 1);
	Vector2 direction = Vector2(0, 0);

	if (input()->getKey(GLFW_KEY_W)) {
		direction -= up;
	}
	if (input()->getKey(GLFW_KEY_S)) {
		direction += up;
	}
	if (input()->getKey(GLFW_KEY_D)) {
		direction += right;
	}
	if (input()->getKey(GLFW_KEY_A)) {
		direction -= right;
	}
	direction.normalize();
	direction *= deltaTime * speed;
	camera()->position += direction;
}