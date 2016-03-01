#ifndef __LECTION_H__
#define __LECTION_H__
#include "Base/BaseWeapon.h"

class Lection :public BaseWeapon
{
public:
	virtual bool init() override;
	virtual bool initElement() override;
	virtual void update(float delta) override;
	CREATE_FUNC(Lection);
	virtual void deal() override;
	virtual bool isTarget(BaseElement* gameElement) override;
	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
};

#endif