#include "Bianbian.h"
#define  ACTION_TAG_BREATH 100100
#define  ACTION_TAG_INVALID 100101
USING_NS_CC;

bool Bianbian::init()
{
	this->_HurtValue = 1.0f;
	this->_BaseScale = 0.3f;
	this->_InValidTime = 2.5f;
	this->setTag(ELEMENT_WEAPON_TAG);
	this->setName(WEAPON_BIANBIAN_NAME);
	_WeaponType = WeaponType::Hulu;
	_WeaponMoveWays = WeaponMoveWays::Vertical;
	_Sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Images/bigBian.png"));
	this->addChild(_Sprite);
	auto breathAction = RepeatForever::create(Sequence::create(
		ScaleTo::create(1.0f, 1.2f*_BaseScale),
		ScaleTo::create(1.0f, 1.0f*_BaseScale),
		NULL
	));
	breathAction->setTag(ACTION_TAG_BREATH);
	_Sprite->runAction(breathAction);
	if (this->_InValidTime > 0)
	{
		auto invalidAction = Sequence::create(DelayTime::create(_InValidTime), CallFunc::create([=](){
			deal();
		}), NULL);
		this->runAction(invalidAction);
	}
	_EnemyDieType = EnemyDieType::ScaleDown;
	initElement();
	return true;
}

bool Bianbian::initElement()
{
	_Sprite->setScale(_BaseScale);
	_IsValid = true;
	_CanClean = false;
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
	//_IsValid = false;
	this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
	_Sprite->stopActionByTag(ACTION_TAG_BREATH);
	auto dieAction = Spawn::create(
		RotateBy::create(0.3f,180),
		Sequence::create(ScaleTo::create(0.2f, 2), ScaleTo::create(0.1f,0),NULL)
		,NULL);
	auto dealAction = Sequence::create(
		dieAction,
		CallFunc::create([=](){
		_CanClean = true; 
	}), NULL);
	this->runAction(dealAction);
}

bool Bianbian::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_ENEMY_TAG;
}

cocos2d::Size Bianbian::getVisualSize()
{
	return _Sprite->getBoundingBox().size *this->getScale();
}

void Bianbian::onFloorCollide(cocos2d::Point point, CollideOperate opType,BaseElement* gameElement)
{
	if (!_IsValid)
		return;

	auto tempPoint = this->getParent()->convertToNodeSpace(point);
	float currentHeight = _Sprite->getBoundingBox().size.height * this->getScale();

	switch (opType)
	{
	case CollideOperate::CollideLeft:
		break;
	case CollideOperate::CollideRight:
		break;
	case CollideOperate::CollideUp:
		if (!_ifThrowUp){
			this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
			this->setPositionY(tempPoint.y + currentHeight / 2);
		}
		break;
	default:
		break;
	}
}