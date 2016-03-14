#ifndef __TEACH_LEVEL__
#define  __TEACH_LEVEL__
#include "../Base/BaseDefine.h"
#include "BaseLevel.h"

class TeachLevel : public BaseLevel
{
public:
	virtual bool init() override;
	virtual void onExit() override;

	CREATE_FUNC(TeachLevel);

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

	virtual void bornCake() override{}
	virtual void bornEnemys() override{}
protected:
	virtual void initBackground();
	virtual void initFloors();
	virtual void initWeapons();
	virtual void initEnemys();
	virtual void initHero();
	virtual void initControl();
private:
	void initTips();
	void playerInDoor();
	void throwShield();
	void throwBianbian();
	void throwCannon();
	void giveLove();
	void createLection();

	cocos2d::Label* _cakeLabel;
	int _eatenCakeNum = 0;
private:
	bool ifBornHurt = false;
	bool isBorningEnemy = false;
	bool canBornEnemy = true;

	bool ifTouchLeft = false;
	bool ifTouchRight = false;
	bool ifTouchAttack = false;
	bool ifTouchJump = false;
	bool ifEatCake = false;
	bool ifKillEnemy = false;
	bool ifDoorOpen = false;

	bool ifHeroValid = true;
};

#endif