
#ifndef WEAPON_H
#define WEAPON_H

#include <rt2d/entity.h>
#include "bullet.h"

class Weapon : public Entity
{
public:
	Weapon();
	virtual ~Weapon();

	virtual void update(float deltaTime);

	// weapon functions
	void shoot(float deltaTime, bool keyMouse, bool keyMouseDown, float mouseX, float mouseY, Map* map);
	void setWeapon(int weaponId);
	void setRandomWeapon();

	// weapon variabels
	int currentWeapon;

	// bullet list
	std::vector<Bullet*> bullets;

	int weapon[2]{ 0, 0 };

	int weapons[4][7] // dmg , firerate (mili sec) , max ammo , clip ammo , autofire, cost, cost ammo
	{
		{ 0, 0, 200, 20, true, 0, 0 },
		{ 20, 0, 56, 7, false, 800, 200 },
		{ 20, 330, 750, 75, true, 3100, 1200 },
		{ 40, 220, 300, 30, true, 2300, 700 }
	};

private:

	// timer
	Timer* t;
	float shootTimer;
	float reloadTimer;


};

#endif
