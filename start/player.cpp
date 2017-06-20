
#include "player.h"

Player::Player() : Entity() {
	// timer
	t = new Timer();
	t->start();
	noDmgTime = 0.8f;
	timer = t->seconds() + noDmgTime;

	// is player dead set false
	isDead = false;

	// set weapon
	weapon = new Weapon();
	this->addChild(weapon);

	// set points
	points = 1000;
}

Player::~Player() {}

void Player::update(float deltaTime) {}

// player movement
void Player::playerMove(float deltaTime, Map* map, bool keyW, bool keyS, bool keyA, bool keyD) {
	moveSpeed = 600.0f;
	Point2 rightPos = Point2(1, 0);
	Point2 upPos = Point2(0, 1);
	Vector2 direction = Vector2(0, 0);

	// get derection
	if (keyW) {
		direction -= upPos;
	}
	if (keyS) {
		direction += upPos;
	}
	if (keyD) {
		direction += rightPos;
	}
	if (keyA) {
		direction -= rightPos;
	}

	direction.normalize();
	direction *= deltaTime * moveSpeed;
	this->position += direction;

	// collision check
	std::vector<Node*> arr = map->collisionGrid;
	for (int i = 0; i < arr.size(); i++){
		if (squareCollision(arr[i]->position, arr[i]->sprite()->size, Point2(this->position.x, this->position.y + direction.y), this->sprite()->size)) {
			this->position.y -= direction.y;
		}
		if (squareCollision(arr[i]->position, arr[i]->sprite()->size, Point2(this->position.x + direction.x, this->position.y), this->sprite()->size)) {
			this->position.x -= direction.x;
		}
	}

}

// player shoot
void Player::playerShoot(float deltaTime, bool keyMouse, bool keyMouseDown, bool keyBuyGun, float mouseX, float mouseY, Map* map) {
	// cheack if buy a weapon
	for (int i = 0; i < map->gunBuyListSize(); i++){
		if (map->inMysteryGrid(this->position, i)) { // mystery box
			hudController->setTextMessage(2, "Mystery gun cost: 2000");
			if (keyBuyGun && points >= 2000) {
				points -= 2000;
				weapon->setRandomWeapon();
			}
		}else if (map->inBuyGrid(this->position, i)) { // nomral weapons
			if (weapon->currentWeapon == map->getGunFromNode(i)) {
				hudController->setTextMessage(2, "Gun ammo cost: " + std::to_string(weapon->weapons[map->getGunFromNode(i)][6]));
				if (keyBuyGun && points >= weapon->weapons[i][6]) {
					points -= weapon->weapons[i][6];
					weapon->setWeapon(map->getGunFromNode(i));
				}
			}else {
				hudController->setTextMessage(2, "Gun cost: " + std::to_string(weapon->weapons[i][5]));
				if (keyBuyGun && points >= weapon->weapons[i][5]) {
					points -= weapon->weapons[i][5];
					weapon->setWeapon(map->getGunFromNode(i));
				}
			}
		}
	}


	// update the shoot in weapon
	weapon->shoot(deltaTime, keyMouse, keyMouseDown, mouseX, mouseY, map);
}	

void Player::playerDmg(float dmg) {
	if (t->seconds() >= timer) {
		// set timer
		timer = t->seconds() + 3.5f;
		// set sprite
		hudController->addImage(Point2(0, 0), Point2(SWIDTH, SHEIGHT), hudController->center, "assets/sprite_hit.tga");
		hudController->setSpriteRemoveTimer(0, 3.5f);
	}else if(t->seconds() >= timer - 2){
		isDead = true;
		this->parent()->removeChild(this);
	}
	
}

// player looks at mouse
void Player::lookAtMouse(float mouseX, float mouseY) {
	// line from player to mouse
	Vector2 mouse = Vector2(mouseX - SWIDTH/2, mouseY - SHEIGHT/2);
	// set angle
	this->rotation = mouse.getAngle();
}

// square collision
bool Player::squareCollision(Point2 nodePos, Point2 nodeSize, Point2 playerPos, Point2 playerSize) {
	if (nodePos.x < playerPos.x + playerSize.x &&
		nodePos.x + nodeSize.x > playerPos.x &&
		nodePos.y < playerPos.y + playerSize.y &&
		nodeSize.y + nodePos.y > playerPos.y) {
		return true;
	}
	else {
		return false;
	}
}