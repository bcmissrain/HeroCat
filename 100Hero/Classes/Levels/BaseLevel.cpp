#include "BaseLevel.h"
#include <stdlib.h>

BaseHero* BaseLevel::_currentHero;
cocos2d::Vector<BaseFloor*> BaseLevel::_floors;
cocos2d::Vector<BaseWeapon*> BaseLevel::_weapons;
cocos2d::Vector<BaseEnemy*> BaseLevel::_enemys;
std::vector<cocos2d::Vec2> BaseLevel::_cakeBornPoints;
std::vector<cocos2d::Vec2> BaseLevel::_enemysBornPoints;

void BaseLevel::initRandom()
{
	struct timeval now;
	cocos2d::gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
	srand(rand_seed);
}
/**
[begin,end]
*/
int BaseLevel::getRandomPercent(int begin, int end)
{
	return begin + rand() % (end - begin + 1);
}

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

cocos2d::Size BaseLevel::getVisibleSize()
{
	return  cocos2d::Director::getInstance()->getVisibleSize();
}