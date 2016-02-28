#include "Bianbian.h"

USING_NS_CC;

bool Bianbian::init()
{
	this->_HurtValue = 1.0f;
	this->_BaseScale = 0.3f;
	this->setTag(ELEMENT_WEAPON_TAG);
	this->setName(WEAPON_BIANBIAN_NAME);
	_WeaponType = WeaponType::Hulu;
	_WeaponMoveWays = WeaponMoveWays::Vertical;
	_Sprite = CSLoader::createNode("Bianbian.csb");
	this->addChild(_Sprite);
	_SpriteTimeLine = CSLoader::createTimeline("Bianbian.csb");
	_SpriteTimeLine->retain();
	_Sprite->runAction(_SpriteTimeLine);
	_EnemyDieType = EnemyDieType::ScaleDown;
	initElement();
	return true;
}

bool Bianbian::initElement()
{
	_Sprite->setScale(_BaseScale);
	_IsValid = true;
	_CanClean = false;
	_SpriteTimeLine->gotoFrameAndPlay(0, 30, true);
	return true;
}

void Bianbian::update(float delta)
{
	float currentPosY = this->getVisualCenter().y;
	if (_lastPosY < currentPosY)
	{
		_ifThrowUp = true;
	}
	else
	{
		_ifThrowUp = false;
	}

	_lastPosY = currentPosY;
}

void Bianbian::deal()
{
	_IsValid = false;
	this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
	_SpriteTimeLine->gotoFrameAndPlay(40, 60, false);
	_SpriteTimeLine->setLastFrameCallFunc([=](){_CanClean = true; });
}

bool Bianbian::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_ENEMY_TAG;
}

cocos2d::Size Bianbian::getVisualSize()
{
	return _Sprite->getChildByName("bigBian_2")->getBoundingBox().size *_Sprite->getScale();
}


void Bianbian::onFloorCollide(cocos2d::Point point, CollideOperate opType,BaseElement* gameElement)
{
	if (!_IsValid)
		return;

	auto tempPoint = this->getParent()->convertToNodeSpace(point);
	//tempPoint.y = gameElement->getBoundingBox().getMaxY();
	float currentHeight = _Sprite->getChildByName("bigBian_2")->getBoundingBox().size.height * _Sprite->getScale();

	switch (opType)
	{
	case CollideOperate::CollideLeft:
		break;
	case CollideOperate::CollideRight:
		break;
	case CollideOperate::CollideUp:
	//case CollideOperate::CollideDown:
		if (!_ifThrowUp){
			this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
			this->setPositionY(tempPoint.y + currentHeight / 2);
		}
		break;
	default:
		break;
	}
}