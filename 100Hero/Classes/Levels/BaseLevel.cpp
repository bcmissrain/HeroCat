#include "BaseLevel.h"

BaseHero* BaseLevel::_currentHero;
cocos2d::Vector<BaseFloor*> BaseLevel::_floors;
cocos2d::Vector<BaseWeapon*> BaseLevel::_weapons;
cocos2d::Vector<BaseEnemy*> BaseLevel::_enemys;
std::vector<cocos2d::Vec2> BaseLevel::_cakeBornPoints;
std::vector<cocos2d::Vec2> BaseLevel::_enemysBornPoints;

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