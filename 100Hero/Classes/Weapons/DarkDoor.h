#ifndef __DARKDOOR_H__
#define __DARKDOOR_H__
#include "Base/BaseWeapon.h"

class DarkDoor :public BaseWeapon
{
public:
	virtual bool init() override;
	virtual bool initElement() override;
	CREATE_FUNC(DarkDoor);
	virtual void deal(BaseElement* gameElement) override;
	virtual bool isTarget(BaseElement* gameElement) override;
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
private:
	bool _canTransform = true;
};
#endif