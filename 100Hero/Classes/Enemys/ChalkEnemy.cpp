#include "ChalkEnemy.h"

bool ChalkEnemy::init()
{
	this->setTag(ELEMENT_ENEMY_TAG);
	_Sprite = cocos2d::Sprite::createWithSpriteFrameName("Level0/teach_enemy.png");
	_Direction = Direction::Right;
	_MoveState = MoveState::None;
	_RunSpeed = _BaseRunSpeed = 100;
	_JumpTime = 0.3f;
	_JumpHeight = 200;
	_Scale = _BaseScale = 1.0f;
	_Sprite->setScale(_Scale);
	this->addChild(_Sprite);
	initElement();
	return true;
}