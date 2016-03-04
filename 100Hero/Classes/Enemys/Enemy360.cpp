#include "Enemy360.h"
#include "../Base/BaseWeapon.h"

bool Enemy360::init()
{
	this->setTag(ELEMENT_ENEMY_TAG);
	_Sprite = cocos2d::Sprite::createWithTexture(cocos2d::TextureCache::getInstance()->addImage("360.png"));
	_Direction = Direction::Right;
	_MoveState = MoveState::None;
	_RunSpeed = _BaseRunSpeed = 200;
	_JumpTime = 0.3f;
	_JumpHeight = 200;
	_Scale = _BaseScale = 0.4f;
	_Sprite->setScale(_Scale);
	_Blood = _BaseBlood = 1;
	this->addChild(_Sprite);
	initElement();
	return true;
}

bool Enemy360::initElement()
{
	_IsValid = true;
	_CanClean = false;
	changeStateTo(EnemyState::JumpDown);
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
	weaponElement->deal(this);
	this->_Hurt(weaponElement->_HurtValue,weaponElement->_EnemyDieType,weaponElement->_CanTurnDirection);
}

bool Enemy360Hurt::init()
{
	this->setTag(ELEMENT_ENEMY_TAG);
	_Sprite = cocos2d::Sprite::createWithTexture(cocos2d::TextureCache::getInstance()->addImage("360_hurt.png"));
	_Direction = Direction::Right;
	_MoveState = MoveState::None;
	_RunSpeed = _BaseRunSpeed = 300;
	_JumpTime = 0.3f;
	_JumpHeight = 200;
	_Scale = _BaseScale = 0.4f;
	_Sprite->setScale(_Scale);
	this->addChild(_Sprite);
	initElement();
	return true;
}

bool Enemy360Boss::init()
{
	this->setTag(ELEMENT_ENEMY_TAG);
	_Sprite = cocos2d::Sprite::createWithTexture(cocos2d::TextureCache::getInstance()->addImage("360_boss.png"));
	_Direction = Direction::Right;
	_MoveState = MoveState::None;
	_RunSpeed = _BaseRunSpeed = 0;
	_JumpTime = 40;
	_JumpHeight = 80;
	_Scale = _BaseScale = 0.6f;
	_Sprite->setScale(_Scale);
	this->addChild(_Sprite);
	initElement();
	return true;
}

void Enemy360Boss::_JumpDown()
{
	auto jumpDownAction =cocos2d::MoveBy::create(_JumpTime, cocos2d::Vec2(0, -_JumpHeight));
	jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
	this->runAction(jumpDownAction);
}
