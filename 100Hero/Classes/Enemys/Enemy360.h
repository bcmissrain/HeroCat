#ifndef __ENEMY360_H__
#define __ENEMY360_H__

#include "Base/BaseEnemy.h"

class Enemy360 : public BaseEnemy
{
public:
	virtual bool init() override;
	virtual bool initElement() override;
	CREATE_FUNC(Enemy360);
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType,BaseElement* gameElement) override;
	virtual void onWallCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
	virtual void onWeaponCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
};

class Enemy360Hurt : public Enemy360
{
public:
	CREATE_FUNC(Enemy360Hurt);
	virtual bool init() override;
};
#endif