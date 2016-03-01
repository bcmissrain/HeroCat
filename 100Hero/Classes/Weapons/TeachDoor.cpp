#include "TeachDoor.h"
USING_NS_CC;

bool TeachDoor::init()
{
	this->_HurtValue = 0;
	this->_BaseScale = 1.0f;
	this->setTag(ELEMENT_WEAPON_TAG);
	this->setName(WEAPON_TEACH_DOOR_NAME);

	_WeaponType = WeaponType::None;
	_WeaponMoveWays = WeaponMoveWays::Vertical;
	_Sprite = Sprite::createWithSpriteFrameName("Level0/door.png");
	this->addChild(_Sprite);
	_EnemyDieType = EnemyDieType::Transparent;
	initElement();
	return true;
}

bool TeachDoor::initElement()
{
	_IsValid = true;
	_CanClean = false;
	_Sprite->setScale(_BaseScale);
	_Sprite->stopAllActions();

	_Sprite->setOpacity(0);
	auto colorAction = FadeTo::create(1.0f, 255);
	_Sprite->runAction(colorAction);
	return true;
}

void TeachDoor::deal()
{
	_IsValid = false;
	this->stopAllActions();
	auto dieAction = Sequence::create(
		FadeTo::create(1.0f, 0),
		CallFunc::create([=](){_CanClean = true; _Sprite->setOpacity(255); }),
		NULL);
	_Sprite->runAction(dieAction);
	_eventDispatcher->dispatchCustomEvent(EVENT_TEACH_DOOR, this);
}

bool TeachDoor::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_HERO_TAG;
}

void TeachDoor::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
}