#ifndef __BASE_LEVEL__
#define  __BASE_LEVEL__
#include "../Base/BaseDefine.h"
#include "../Base/BaseElement.h"
#include "../Base/BaseHero.h"
#include "../Base/BaseFloor.h"
#include "../Base/BaseEnemy.h"
#include "../Base/BaseWeapon.h"

class BaseLevel:public cocos2d::Layer
{
public:
	BaseLevel(){};
	~BaseLevel(){};

	virtual bool init() = 0;
	virtual void update(float delta) override;

protected:
	virtual void updateInput(float delta){}
	virtual void updateBorn(float delta){}
	virtual void updateFloor(float delta){}
	virtual void updateWeapon(float delta){}
	virtual void updateEnemy(float delta){}
	virtual void updateHero(float delta){}
	virtual void updateLate(float delta){}
	virtual void updateRecyle(float delta){}

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) = 0;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) = 0;
	virtual void onButtonClick(cocos2d::ui::TouchEventType type) = 0;
	virtual void ResetPosition() = 0;

protected:
	ClickState _ifClickLeft;
	ClickState _ifClickRight;
	ClickState _ifClickJump;
	ClickState _ifClickAttack;
	Layer* _elementLayer = nullptr;
	BaseHero* _currentHero;
	cocos2d::Vector<BaseFloor*> _floors;
	cocos2d::Vector<BaseWeapon*> _weapons;
	cocos2d::Vector<BaseEnemy*> _enemys;
	float _minX;
	float _minY;
	float _maxX;
	float _maxY;
};

#endif