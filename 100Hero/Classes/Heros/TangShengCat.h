#ifndef __TANGSHENG_CAT_H__
#define __TANGSHENG_CAT_H__
#include "../Base/BaseHero.h"
class TangShengCat :public BaseHero
{
public:
	virtual bool init() override;
	CREATE_FUNC(TangShengCat);
	virtual bool initElement() override;

	virtual bool collideWithGameElement(BaseElement* gameElement) override { return false; }
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
	virtual void onWallCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
	virtual void onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;

	virtual void _BeginStand() override;
	virtual void _BeginRun() override;
	virtual void _BeginJumpUp() override;
	virtual void _BeginJumpUp2() override;
	virtual void _BeginJumpDown() override;
	virtual void _BeginJumpFinish() override;
	virtual void _BeginAttack() override;

	virtual void _Attack(ClickState clickState) override;
};
#endif