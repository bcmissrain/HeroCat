#ifndef __TEACH_DOOR_H__
#define __TEACH_DOOR_H__
#include "Base/BaseWeapon.h"

class TeachDoor :public BaseWeapon
{
public:
	virtual bool init() override;
	virtual bool initElement() override;
	CREATE_FUNC(TeachDoor);
	virtual void deal() override;
	virtual bool isTarget(BaseElement* gameElement) override;
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
};

#endif