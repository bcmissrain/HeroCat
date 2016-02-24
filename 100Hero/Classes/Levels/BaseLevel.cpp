#include "BaseLevel.h"

void BaseLevel::update(float delta)
{
	updateInput(delta);
	updateBorn(delta);
	updateFloor(delta);
	updateWeapon(delta);
	updateEnemy(delta);
	updateHero(delta);
	updateLate(delta);
	updateRecyle(delta);
}