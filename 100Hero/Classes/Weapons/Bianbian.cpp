#include "Bianbian.h"

USING_NS_CC;

bool Bianbian::init()
{
	this->setTag(ELEMENT_WEAPON_TAG);
	_WeaponType = WeaponType::Hulu;
	_WeaponMoveWays = WeaponMoveWays::Horizontal;
	_Sprite = CSLoader::createNode("Bianbian.csb");
	this->addChild(_Sprite);
	_SpriteTimeLine = CSLoader::createTimeline("Bianbian.csb");
	_SpriteTimeLine->retain();
	_Sprite->runAction(_SpriteTimeLine);
	initElement();
	return true;
}

bool Bianbian::initElement()
{
	_IsValid = true;
	_CanClean = false;
	_SpriteTimeLine->gotoFrameAndPlay(0, 30, true);
	return true;
}

void Bianbian::deal()
{
	_IsValid = false;
	_SpriteTimeLine->gotoFrameAndPlay(40, 60, false);
	_SpriteTimeLine->setLastFrameCallFunc([=](){_CanClean = true; });
}

bool Bianbian::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_ENEMY_TAG;
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
	case CollideOperate::CollideDown:
		this->setPositionY(tempPoint.y + currentHeight / 2);
		this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
		break;
	default:
		break;
	}
}