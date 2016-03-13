#include "DarkDoor.h"
USING_NS_CC;

bool DarkDoor::init()
{
	this->_HurtValue = 0;
	this->_BaseScale = 1.0f;
	this->setTag(ELEMENT_WEAPON_TAG);
	this->setName(WEAPON_TEACH_DOOR_NAME);

	_WeaponType = WeaponType::None;
	_WeaponMoveWays = WeaponMoveWays::Vertical;
	_Sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Images/darkdoor.png"));
	this->addChild(_Sprite);
	_EnemyDieType = EnemyDieType::Transparent;
	initElement();
	return true;
}

bool DarkDoor::initElement()
{
	_IsValid = true;
	_CanClean = false;
	_Sprite->setScale(_BaseScale);
	_Sprite->stopAllActions();

	auto rotateAction = RotateBy::create(1.0f, 360);
	auto fadeOutAction = FadeOut::create(1.0);
	auto fadeInAction = FadeIn::create(1.0);
	auto repeatAction = Sequence::create(
		Repeat::create(rotateAction, 3),
		fadeOutAction,
		CallFunc::create([=](){this->_canTransform = false; }),
		DelayTime::create(3.0f),
		CallFunc::create([=](){this->_canTransform = true; }),
		fadeInAction,
		NULL);

	_Sprite->runAction(RepeatForever::create(repeatAction));
	return true;
}

void DarkDoor::deal(BaseElement* gameElement)
{
	if (this->_canTransform)
	{
		_eventDispatcher->dispatchCustomEvent(EVENT_DARK_DOOR, (void*)this->getTag());
	}
}

bool DarkDoor::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_HERO_TAG;
}

void DarkDoor::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
}