#ifndef __SPRING_LEVEL__
#define  __SPRING_LEVE__
#include "../Base/BaseDefine.h"
#include "BaseLevel.h"

class SpringLevel : public BaseLevel
{
public:
	virtual bool init() override;
	CREATE_FUNC(SpringLevel);

	virtual void updateInput(float delta) override;
	virtual void updateBorn(float delta) override;
	virtual void updateFloor(float delta) override;
	virtual void updateWeapon(float delta) override;
	virtual void updateEnemy(float delta) override;
	virtual void updateHero(float delta) override;
	virtual void updateLate(float delta) override;
	virtual void updateRecyle(float delta) override;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
	virtual void onButtonClick(cocos2d::ui::TouchEventType type) override;
	virtual void ResetPosition() override;

private:
	bool ifSupport;
	bool ifDrawDebug;
	void AddBianbianByPos(cocos2d::Vec2 pos);
};

#endif