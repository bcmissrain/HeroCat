#ifndef __WINTER_LEVEL__
#define  __WINTER_LEVEL__
#include "../Base/BaseDefine.h"
#include "BaseLevel.h"

class WinterLevel : public BaseLevel
{
public:
	virtual bool init() override;
	virtual void onExit() override;

	CREATE_FUNC(WinterLevel);

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

	virtual void bornCake() override;
	virtual void bornEnemys() override;
	void bornHurtEnemys(BaseEnemy* baseEnemy);
protected:
	virtual void initBornPoints();
	virtual void initBackground();
	virtual void initFloors();
	virtual void initWeapons();
	virtual void initEnemys();
	virtual void initHero();
	virtual void initControl();
private:
	void throwShield();
	void throwBianbian();
	void throwCannon();
	void createLection();
private:
	cocos2d::Label* _cakeLabel;
	int _eatenCakeNum = 0;

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	bool ifSupport;
	bool ifDrawDebug;
#endif
	bool ifBornHurt = false;
	bool isBorningEnemy = false;
	bool canBornEnemy = true;
};

#endif