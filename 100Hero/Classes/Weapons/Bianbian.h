#ifndef __BIANBIAN_H__
#define __BIANBIAN_H__
#include "Base/BaseWeapon.h"

class Bianbian :public BaseWeapon
{
public:
	virtual bool init() override;
	CREATE_FUNC(Bianbian);
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType,BaseElement* gameElement) override;
	virtual void onHeroCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
	virtual void onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
};

#endif