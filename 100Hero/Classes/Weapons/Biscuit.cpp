#include "Biscuit.h"
#define  ACTION_TAG_BREATH 100100
USING_NS_CC;

bool Biscuit::init()
{
	this->_HurtValue = 0;
	this->_BaseScale = 0.3f;
	this->setTag(ELEMENT_WEAPON_TAG);
	this->setName(WEAPON_BISCUIT_NAME);
	
	_WeaponType = WeaponType::Biscuit;
	_WeaponMoveWays = WeaponMoveWays::Vertical;
	_Sprite = Sprite::create("biscuit.png");
	this->addChild(_Sprite);
	_EnemyDieType = EnemyDieType::Transparent;
	initElement();
	return true;
}

bool Biscuit::initElement()
{
	_IsValid = true;
	_CanClean = false;
	_Sprite->setScale(_BaseScale);
	_Sprite->stopActionByTag(ACTION_TAG_BREATH);
	auto breathAction =RepeatForever::create(Sequence::create(
		ScaleTo::create(1.0f, 1.2f*_BaseScale),
		ScaleTo::create(1.0f, 1.0f*_BaseScale),
		NULL
		));
	breathAction->setTag(ACTION_TAG_BREATH);
	_Sprite->runAction(breathAction);
	
	auto jumpDownAction = Sequence::create(DelayTime::create(0.5f), EaseIn::create(MoveBy::create(0.6, Vec2(0, -840)), 2.0), NULL);
	jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
	this->runAction(jumpDownAction);
	
	_Sprite->setOpacity(0);
	auto colorAction = FadeTo::create(0.5f, 255);
	_Sprite->runAction(colorAction);
	return true;
}

void Biscuit::deal()
{
	_IsValid = false;
	this->stopAllActions();
	auto dieAction = Sequence::create(
		FadeTo::create(0.3f,0),
		CallFunc::create([=](){_CanClean = true; _Sprite->setOpacity(255); }),
		NULL);
	_Sprite->runAction(dieAction);
	_eventDispatcher->dispatchCustomEvent(EVENT_BISCAKE_EAT, nullptr);
}

bool Biscuit::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_HERO_TAG;
}

void Biscuit::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!_IsValid)
	{
		return;
	}

	auto tempPoint = this->getParent()->convertToNodeSpace(point);
	float currentHeight = _Sprite->getBoundingBox().size.height;
	CCLOG("Biscuit %f %f %f", _Sprite->getBoundingBox().size.width, _Sprite->getBoundingBox().size.height, _Sprite->getScale());
	switch (opType)
	{
	case CollideOperate::CollideLeft:
		break;
	case CollideOperate::CollideRight:
		break;
	case CollideOperate::CollideUp:
		this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
		this->setPositionY(tempPoint.y + currentHeight / 2);
		break;
	default:
		break;
	}
}