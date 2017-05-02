
#include "weapon.h"

Weapon::Weapon() : Entity() {
	// current weapon
	currentWeapon = 1;
	weapon[1] = weapons[currentWeapon][2]; // 2 = max ammo
	weapon[0] = weapons[currentWeapon][3]; // 3 = clip ammo

	// activate timer
	t = new Timer();
	t->start();
	shootTimer = t->seconds();
	reloadTimer = t->seconds();

	setRandomWeapon();
}

Weapon::~Weapon() {}

void Weapon::update(float deltaTime) {}

void Weapon::shoot(float deltaTime, bool keyMouse, bool keyMouseDown, float mouseX, float mouseY, Map* map) {
	// on mouse down shoot
	if (keyMouse && t->seconds() >= shootTimer && (bool)weapons[currentWeapon][4] && t->seconds() >= reloadTimer || keyMouseDown && !(bool)weapons[currentWeapon][4] && t->seconds() >= reloadTimer){ // 4 = isFirerate
		// timer
		shootTimer = t->seconds() + (float)weapons[currentWeapon][1]/1000; // 1 = firerate

		//  check if ammo = 0
		if (weapon[0] <= 0 && weapon[1] <= 0) {
			std::cout << "you have no ammo!" << std::endl;
		}else{
			// create bullet 
			Bullet* b = new Bullet();
			b->setVelocity(mouseX, mouseY);
			b->position = this->parent()->position;
			b->rotation = this->parent()->rotation;
			b->sprite()->size = Point2(50, 50);
			b->damage = (float)weapons[currentWeapon][0]; // 0 = damage
			bullets.push_back(b);
			this->parent()->parent()->addChild(b);

			// bullet ammo - 1
			weapon[0] -= 1;

			std::cout << weapon[0] << "/" << weapon[1] << std::endl;
		}

		// check if bullet ammo == 0
		if (weapon[0] <= 0 && weapon[1] != 0) {
			reloadTimer = t->seconds() + 2;
			weapon[1] -= weapons[currentWeapon][3];
			weapon[0] += weapons[currentWeapon][3];
			std::cout << "reloading!" << std::endl;
		}

	}

	// update bullets
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->move(deltaTime, map);

		// remove bullet if it is dead
		if (bullets[i]->isDead) {
			this->parent()->parent()->removeChild(bullets[i]);
			bullets.erase(bullets.begin() + i);
		}
	}
}

// set weapon
void Weapon::setWeapon(int weaponId) {
	currentWeapon = weaponId;
	weapon[1] = weapons[weaponId][2]; // 2 = max ammo
	weapon[0] = weapons[weaponId][3]; // 3 = clip ammo
}

// set random weapon
void Weapon::setRandomWeapon() {
	int id = 0;
	// dmg , firerate (mili sec) , max ammo , clip ammo , autofire, cost, cost ammo
	weapons[id][0] = rand() % 80 + 10;
	weapons[id][1] = rand() % 300 + 100;

	weapons[id][3] = rand() % 60 + 5;
	weapons[id][2] = weapons[id][3] * (rand() % 8 + 3);

	std::cout << weapons[id][0] << "|" << weapons[id][1] <<std::endl;

	setWeapon(id);
}

