#ifndef __BIANBIAN_H__
#define __BIANBIAN_H__
#include "Base/BaseWeapon.h"

class Bianbian :public BaseWeapon
{
public:
	virtual bool init() override;
	CREATE_FUNC(Bianbian);
	virtual void onFloorCollide(cocos2d::Point point, FloorOperate opType) override;
};

#endif