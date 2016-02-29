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

class BaseEnemy :public BaseElement
{
public:
	//base
	BaseEnemy(){}
	~BaseEnemy(){}
	virtual void check();
	virtual void update(float delta) override;
	virtual void afterUpdate() override;

	//info
	virtual cocos2d::Rect getBoundingBox() override;
	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;
	virtual DropState getJumpState() override{ return DropState::Down; };
	virtual float getMaxJumpSpeed() override{ return 0; };

	virtual bool collideWithGameElement(BaseElement* gameElement) override;
	
	//control
	virtual void _Run(float deltaTime);
	virtual void _Fly(float deltaTime);
	virtual void _TurnDirection();
	virtual void _Hurt(float lostBlood,EnemyDieType dieType = EnemyDieType::Transparent);
	virtual void _JumpDown();
	virtual void _JumpFinish();
	virtual void _Die(EnemyDieType dieType = EnemyDieType::Transparent);
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
	float _BaseBlood = 1;
	float _Blood = 1;
	bool _CanFly = false;
	bool _IfHaveSupport = false;
};
#endif