#ifndef __BASE_ENEMY_H__
#define __BASE_ENEMY_H__
#include "BaseDefine.h"
#include "Base/BaseElement.h"

enum class EnemyState
{
	Stand,
	Run, 
	Fly,
	JumpDown,
	JumpFinish,
	//Hurt,
	Die
};

class BaseEnemy :public BaseElemnt
{
public:
	//base
	BaseEnemy(){}
	~BaseEnemy(){}
	virtual bool init(){ return true; }
	virtual void check();
	virtual void update(float delta);
	virtual void afterUpdate();

	//info
	virtual cocos2d::Rect getBoundingBox() override;
	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;

	//control
	virtual void _Run(float deltaTime);
	virtual void _Fly(float deltaTime);
	virtual void _TurnDirection();
	virtual void _Hurt(float lostBlood);
	virtual void _JumpDown();
	virtual void _JumpFinish();
	virtual void _Die();
	virtual void changeStateTo(EnemyState state);

public:
	cocos2d::Node* _Sprite = nullptr;
	EnemyState _CurrentState = EnemyState::Stand;
	Direction _Direction = Direction::Right;
	MoveState _MoveState = MoveState::None;
	float _BaseScale = 1.0f;
	float _Scale = 1.0f;
	float _BaseRunSpeed;
	float _RunSpeed;
	float _JumpTime;
	float _JumpHeight;
	float _BaseBlood;
	float _Blood;
	bool _CanClean = false;
	bool _CanFly = false;
	bool _IfHaveSupport = false;
};
#endif