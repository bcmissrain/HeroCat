#ifndef __BIANBIAN_H__
#define __BIANBIAN_H__
#include "Base/BaseWeapon.h"

class Bianbian :public BaseWeapon
{
public:
	virtual bool init() override;
	virtual bool initElement() override;
	CREATE_FUNC(Bianbian);
	virtual void deal() override;
	virtual bool isTarget(BaseElement* gameElement) override;
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType,BaseElement* gameElement) override;
};

#endif