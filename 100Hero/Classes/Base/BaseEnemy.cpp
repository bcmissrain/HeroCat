#include "BaseEnemy.h"

void BaseEnemy::check()
{
	if (_CurrentState == EnemyState::Run || _CurrentState == EnemyState::Fly)
	{
		if (_IfHaveSupport == false)
		{
			changeStateTo(EnemyState::JumpDown);
		}
	}
	else if (_CurrentState == EnemyState::JumpDown)
	{
		if (_IfHaveSupport)
		{
			changeStateTo(EnemyState::JumpFinish);
		}
	}
	else if (_CurrentState == EnemyState::JumpFinish)
	{
		if (!_CanFly)
		{
			changeStateTo(EnemyState::Run);
		}
		else
		{
			changeStateTo(EnemyState::Fly);
		}
	}
}

void BaseEnemy::update(float delta)
{
	if (_CurrentState == EnemyState::Stand)
	{
		
	}
	else if (_CurrentState == EnemyState::Run)
	{
		_Run(delta);
	}
	else if( _CurrentState == EnemyState::Fly)
	{
		_Fly(delta);
	}
	else if (_CurrentState == EnemyState::JumpDown)
	{
		
	}
	else if (_CurrentState == EnemyState::JumpFinish)
	{
		//if (!_CanFly)
		//{
		//	changeStateTo(EnemyState::Run);
		//}
		//else
		//{
		//	changeStateTo(EnemyState::Fly);
		//}
	}
	else if (_CurrentState == EnemyState::Die)
	{
		
	}
}

void BaseEnemy::afterUpdate()
{
	this->_IfHaveSupport = false;
}

cocos2d::Rect BaseEnemy::getBoundingBox()
{
	return cocos2d::Rect(getVisualCenter() - getVisualSize() / 2, getVisualSize());
}

cocos2d::Size BaseEnemy::getVisualSize()
{
	return _Sprite->getBoundingBox().size;
}

cocos2d::Point BaseEnemy::getVisualCenter()
{
	return this->convertToWorldSpace(cocos2d::Vec2(_Sprite->getBoundingBox().getMidX(), _Sprite->getBoundingBox().getMidY()));
}

void BaseEnemy::onWeaponCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{

}

void BaseEnemy::_Run(float deltaTime)
{
	if (_MoveState == MoveState::MoveLeft)
	{
		this->setPositionX(this->getPositionX() - _RunSpeed*deltaTime);
	}
	else if (_MoveState == MoveState::MoveRight)
	{
		this->setPositionX(this->getPositionX() + _RunSpeed*deltaTime);
	}
}

void BaseEnemy::_Fly(float deltaTime)
{
	_Run(deltaTime);
}

void BaseEnemy::_TurnDirection()
{
	if (this->_Direction == Direction::Left)
	{
		this->_Direction = Direction::Right;
		if (_MoveState != MoveState::None)
		{
			_MoveState = MoveState::MoveRight;
		}
	}
	else if (this->_Direction == Direction::Right)
	{
		this->_Direction = Direction::Left;
		if (_MoveState != MoveState::None)
		{
			_MoveState = MoveState::MoveLeft;
		}
	}
}

void BaseEnemy::_Hurt(float lostBlood)
{
	this->_Blood -= lostBlood;
	if (this->_Blood >= 0.001)
	{

	}
	else
	{
		_Die();
	}
}

void BaseEnemy::_JumpDown()
{
	auto jumpDownAction = cocos2d::EaseIn::create(cocos2d::MoveBy::create(_JumpTime * 2, cocos2d::Vec2(0, -_JumpHeight * 4)), 2.0);
	jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
	this->runAction(jumpDownAction);
}

void BaseEnemy::_JumpFinish()
{
	this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
}

void BaseEnemy::_Die()
{
	auto dieActions = cocos2d::Sequence::create(
		cocos2d::FadeOut::create(0.5),
		cocos2d::CallFunc::create([=](){_CanClean = true; }),
		NULL);
	this->runAction(dieActions);
}

void BaseEnemy::changeStateTo(EnemyState state)
{
	switch (state)
	{
	case EnemyState::Stand:
		this->_CurrentState = EnemyState::Stand;
		break;
	case EnemyState::Run:
		this->_CurrentState = EnemyState::Run;
		break;
	case EnemyState::Fly:
		this->_CurrentState = EnemyState::Fly;
		break;
	case EnemyState::JumpDown:
		this->_CurrentState = EnemyState::JumpDown;
		_JumpDown();
		break;
	case EnemyState::JumpFinish:
		this->_CurrentState = EnemyState::JumpFinish;
		_JumpFinish();
		break;
	case EnemyState::Die:
		this->_CurrentState = EnemyState::Die;
		_Die();
		break;
	default:
		break;
	}
}
