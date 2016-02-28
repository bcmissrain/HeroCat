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

	static BaseHero* _currentHero;
	static cocos2d::Vector<BaseFloor*> _floors;
	static cocos2d::Vector<BaseWeapon*> _weapons;
	static cocos2d::Vector<BaseEnemy*> _enemys;
	static std::vector<cocos2d::Vec2> _cakeBornPoints;
	static std::vector<cocos2d::Vec2> _enemysBornPoints;

protected:
	cocos2d::Size getVisibleSize();
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

	virtual void bornCake() = 0;
protected:
	ClickState _ifClickLeft;
	ClickState _ifClickRight;
	ClickState _ifClickJump;
	ClickState _ifClickAttack;
	Layer* _elementLayer = nullptr;
	float _baseMaxBornTime;
	float _baseMinBornTime;
	float _currentBornTime;
	float _bornTimeSpeed;
	float _minX;
	float _minY;
	float _maxX;
	float _maxY;
};
#endif