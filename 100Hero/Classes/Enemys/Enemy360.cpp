#include "Enemy360.h"
#include "../Base/BaseWeapon.h"

bool Enemy360::init()
{
	
	_Sprite = cocos2d::Sprite::create("360.png");
	_Direction = Direction::Right;
	_MoveState = MoveState::MoveRight;
	_RunSpeed = _BaseRunSpeed = 200;
	_JumpTime = 0.3f;
	_JumpHeight = 200;
	_Scale = _BaseScale = 0.6f;
	_Sprite->setScale(_Scale);
	this->addChild(_Sprite);
	changeStateTo(EnemyState::JumpDown);
	this->setTag(ELEMENT_ENEMY_TAG);
	return true;
}

void Enemy360::onFloorCollide(cocos2d::Point point, CollideOperate opType,BaseElement* gameElement)
{
	//Attention Convert the position
	point = this->getParent()->convertToNodeSpace(point);
	
	switch (opType)
	{
	case CollideOperate::CollideLeft:
		this->setPositionX(point.x - _Sprite->getBoundingBox().size.width / 2);
		break;
	case CollideOperate::CollideRight:
		this->setPositionX(point.x + _Sprite->getBoundingBox().size.width / 2);
		break;
	case CollideOperate::CollideUp:
		_IfHaveSupport = true;
		if (_CurrentState == EnemyState::JumpDown)
		{
			changeStateTo(EnemyState::JumpFinish);
			this->setPositionY(point.y + _Sprite->getBoundingBox().size.height * 0.49);
		}
		break;
	case CollideOperate::CollideDown:
		this->setPositionY(point.y - _Sprite->getBoundingBox().size.height * 0.5);
		changeStateTo(EnemyState::JumpDown);
		break;
	default:
		break;
	}
}

void Enemy360::onWallCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	//Attention Convert the position
	point = this->getParent()->convertToNodeSpace(point);

	switch (opType)
	{
	case CollideOperate::CollideLeft:
		this->setPositionX(point.x - _Sprite->getBoundingBox().size.width / 2);
		_TurnDirection();
		break;
	case CollideOperate::CollideRight:
		this->setPositionX(point.x + _Sprite->getBoundingBox().size.width / 2);
		_TurnDirection();
		break;
	case CollideOperate::CollideUp:
		_IfHaveSupport = true;
		if (_CurrentState == EnemyState::JumpDown)
		{
			changeStateTo(EnemyState::JumpFinish);
			this->setPositionY(point.y + _Sprite->getBoundingBox().size.height * 0.49);
		}
		break;
	case CollideOperate::CollideDown:
		this->setPositionY(point.y - _Sprite->getBoundingBox().size.height * 0.5);
		changeStateTo(EnemyState::JumpDown);
		break;
	default:
		break;
	}
}

void Enemy360::onWeaponCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	auto weaponElement = (BaseWeapon*)gameElement;
	weaponElement->deal();
	this->_Hurt(weaponElement->_HurtValue);
}