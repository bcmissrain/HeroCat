#ifndef __BASEHERO_H__
#define __BASEHERO_H__

#include "Base/BaseElement.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BaseDefine.h"
#include "BaseFloor.h"
#include "BaseWeapon.h"

class BaseHero;

class BaseStatus
{
public:
	virtual ActionState getState() = 0;
	virtual void initState(BaseHero* hero) = 0;
	virtual void checkState(BaseHero* hero) = 0;
	virtual void updateState(BaseHero* hero,float deltaTime = 0) = 0;
};

class StandStatus:public BaseStatus
{
public:
	virtual ActionState getState() override;
	virtual void initState(BaseHero* hero) override;
	virtual void checkState(BaseHero* hero) override;
	virtual void updateState(BaseHero* hero, float deltaTime = 0) override;
};

class RunStatus :public BaseStatus
{
public:
	virtual ActionState getState() override;
	virtual void initState(BaseHero* hero) override;
	virtual void checkState(BaseHero* hero) override;
	virtual void updateState(BaseHero* hero, float deltaTime = 0) override;
};

class StopStatus :public BaseStatus
{
public:
	virtual ActionState getState() override;
	virtual void initState(BaseHero* hero) override;
	virtual void checkState(BaseHero* hero) override;
	virtual void updateState(BaseHero* hero, float deltaTime = 0) override;
};

class JumpUpStatus :public BaseStatus
{
public:
	virtual ActionState getState() override;
	virtual void initState(BaseHero* hero) override;
	virtual void checkState(BaseHero* hero) override;
	virtual void updateState(BaseHero* hero, float deltaTime = 0) override;
};

class JumpUp2Status :public BaseStatus
{
public:
	virtual ActionState getState() override;
	virtual void initState(BaseHero* hero) override;
	virtual void checkState(BaseHero* hero) override;
	virtual void updateState(BaseHero* hero, float deltaTime = 0) override;
};

class JumpDownStatus :public BaseStatus
{
public:
	virtual ActionState getState() override;
	virtual void initState(BaseHero* hero) override;
	virtual void checkState(BaseHero* hero) override;
	virtual void updateState(BaseHero* hero, float deltaTime = 0) override;
};

class JumpFinishStatus :public BaseStatus
{
public:
	virtual ActionState getState() override;
	virtual void initState(BaseHero* hero) override;
	virtual void checkState(BaseHero* hero) override;
	virtual void updateState(BaseHero* hero, float deltaTime = 0) override;
};

class BaseHero : public BaseElement
{
public:
	//base
	BaseHero(){}
	~BaseHero(){}
	virtual HeroType getHeroType() = 0;
	virtual void afterUpdate() override;

	//control
	virtual void onMoveLeft(ClickState clickState);
	virtual void onMoveRight(ClickState clickState);
	virtual void onJump(ClickState clickState);
	virtual void onAttack(ClickState clickState);

	//behave
	virtual void _BeginStand();
	virtual void _BeginRun();
	virtual void _BeginStop();
	virtual void _BeginJumpUp();
	virtual void _BeginJumpUp2();
	virtual void _BeginJumpDown();
	virtual void _BeginJumpFinish();
	virtual void _BeginAttack();
	virtual void _BeginBorn();

	virtual void _Stand(float deltaTime);
	virtual void _Run(float deltaTime);
	virtual void _Jump(float deltaTime,bool ifFirst);
	virtual void _Stop(float deltaTime);
	virtual void _JumpUp(float deltaTime);
	virtual void _JumpUp2(float deltaTime);
	virtual void _JumpDown(float deltaTime);
	virtual void _JumpFinish(float deltaTime);
	virtual void _onWallCollide();
	virtual void _Attack(ClickState clickState);
	virtual void _Hurt();
	//state
	virtual void changeStateTo(ActionState state);

	//info
	virtual cocos2d::Rect getBoundingBox() override;
	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;
	virtual DropState getJumpState() override;
	virtual float getMaxJumpSpeed()override;

	virtual void onWeaponCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
	virtual void onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement) override;
	virtual cocos2d::Point getWeaponPosByIndex(int index);
public:
	//flag
	ClickState _ifClickLeft = ClickState::None;
	ClickState _ifClickRight = ClickState::None;
	ClickState _ifClickJump = ClickState::None;
	ClickState _ifClickAttack = ClickState::None;
protected:
	//state
	virtual void updateState(float delta){}

public:
	cocos2d::Vector<Node*> _Weapons;
	cocostudio::timeline::SkeletonNode*  _Sprite = nullptr;
	cocostudio::timeline::ActionTimeline* _SpriteTimeline = nullptr;
	BaseStatus*	 _CurrentState = nullptr;
	CollideState _CollideState = CollideState::NoneSupport;
	MoveState    _MoveState = MoveState::None;
	MoveState    _MoveStateCache = MoveState::None;
	Direction    _Direction = Direction::Right;
	AttackState  _AttackState = AttackState::NotAttack;
	float _BaseScale = 0;
	float _BaseRunSpeed = 0;
	float _BaseAcceleration = 1024;
	float _BaseJumpAcceleration = 0;
	float _BaseJumpAcceleration2 = 0;
	float _BaseJumpSpeed = 0;
	float _BaseJumpSpeed2 = 0;
	float _JumpSpeed = 0;
	float _SupportSpeed = 0;
	float _JumpSpeed2 = 0;
	float _RunSpeed = 0;
	float _JumpMoveSpeed = 0;
	float _JumpHeight = 0;
	float _JumpTime = 0;
	float _JumpHeight2 = 0;
	float _JumpTime2 = 0;

	float _AttackColdTime = 0;
	int   _AttackMaxTimes = -1;
	int	  _AttackCount = 0;
	bool _CanDoubleJump = false;
	bool _IsDoubleJump = false;

	bool _IsBorning = true;
};
#endif