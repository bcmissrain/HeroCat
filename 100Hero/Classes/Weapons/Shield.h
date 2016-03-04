#ifndef __SHIELD_H__
#define __SHIELD_H__
#include "Base/BaseWeapon.h"

class Shield :public BaseWeapon
{
public:
	virtual bool init() override;
	virtual bool initElement() override;
	virtual void update(float delta) override;
	CREATE_FUNC(Shield);
	virtual void deal(BaseElement* gameElement) override;
	virtual bool isTarget(BaseElement* gameElement) override;
	virtual cocos2d::Size getVisualSize() override;
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;

private:
	float _lastPosY = 0;
	bool _ifThrowUp = false;
};

#endif