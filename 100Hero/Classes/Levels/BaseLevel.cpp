#include "BaseLevel.h"
#include <stdlib.h>

void BaseLevel::initRandom()
{
	//compile error in android
	struct timeval now;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	cocos2d::gettimeofday(&now, NULL);
#else
	gettimeofday(&now, NULL);
#endif
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