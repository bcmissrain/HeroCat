#ifndef __ENEMY360_H__
#define __ENEMY360_H__

#include "Base/BaseEnemy.h"

class Enemy360 : public BaseEnemy
{
public:
	virtual bool init() override;
	CREATE_FUNC(Enemy360);
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType,BaseElement* gameElement) override;
};
#endif