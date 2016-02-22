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
	virtual void updateState(BaseHero* hero, float deltaTime = 0) override{}
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
	virtual bool init(){ return true; }
	virtual void update(float delta){}
	virtual void afterUpdate();

	//control
	virtual void onMoveLeft(ClickState clickState);
	virtual void onMoveRight(ClickState clickState);
	virtual void onJump(ClickState clickState);
	virtual void onAttack(ClickState clickState);

	//behave
	virtual void _BeginStand();
	virtual void _Stand();
	virtual void _BeginRun();
	virtual void _BeginStop();
	virtual void _BeginJumpUp();
	virtual void _BeginJumpUp2();
	virtual void _BeginJumpDown();
	virtual void _BeginJumpFinish();
	virtual void _BeginAttack();

	virtual void _Run(float deltaTime);
	virtual void _Stop(float deltaTime);
	virtual void _JumpUp(float deltaTime);
	virtual void _JumpUp2(float deltaTime);
	virtual void _JumpDown(float deltaTime);
	virtual void _JumpFinish(float deltaTime);
	virtual void _Attack(ClickState clickState);
	virtual void _Hurt();
	//state
	virtual void changeStateTo(ActionState state);

	//info
	virtual cocos2d::Rect getBoundingBox() override;
	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;
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
	CollideState _CollideState;
	MoveState    _MoveState;
	MoveState    _MoveStateCache;
	Direction    _Direction;
	AttackState  _AttackState;
	float _BaseScale;
	float _BaseRunSpeed;
	float _BaseAcceleration = 1024;
	float _RunSpeed;
	float _JumpMoveSpeed;
	float _JumpHeight;
	float _JumpTime;
	float _JumpHeight2;
	float _JumpTime2;
	float _AttackColdTime;
	int   _AttackMaxTimes = -1;
	int	  _AttackCount;
	bool _CanDoubleJump;
	bool _IsDoubleJump;
};
#endif