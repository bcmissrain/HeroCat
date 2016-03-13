#include "Cannon.h"

USING_NS_CC;

bool Cannon::init()
{
	this->_HurtValue = 0.5f;
	this->_BaseScale = 0.5f;
	this->_CanTurnDirection = false;
	this->setTag(ELEMENT_WEAPON_TAG);
	this->setName(WEAPON_CANNON_NAME);
	_WeaponType = WeaponType::Shoot;
	_WeaponMoveWays = WeaponMoveWays::Horizontal;
	_Sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Images/cannon.png"));
	this->addChild(_Sprite);
	_EnemyDieType = EnemyDieType::Transparent;
	initElement();
	return true;
}

bool Cannon::initElement()
{
	this->stopAllActions();
	_Sprite->setScale(_BaseScale);
	_IsValid = true;
	_CanClean = false;
	return true;
}

void Cannon::update(float delta)
{
}

void Cannon::deal(BaseElement* baseElement)
{
	_CanHurt = false;
	auto bomb = [=]()
	{
		_IsValid = false;
		this->stopAllActions();
		auto dealAction = Sequence::create(
			FadeTo::create(0.1f, 0),
			CallFunc::create([=](){
			_CanClean = true;
		}), NULL);

		CCParticleSystem* particleSystem = CCParticleFire::create();
		particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/cannon.png"));
		particleSystem->setPosition(Vec2::ZERO);
		this->addChild(particleSystem);

		this->runAction(dealAction);
	};

	if (baseElement)
	{
		if (isTarget(baseElement))
		{
			if (_currentCollideId != baseElement->_elementCode) // new collide
			{
				_dealTimes--;
				_currentCollideId = baseElement->_elementCode;
				_CanHurt = true;
				if (_dealTimes < 0)
				{
					bomb();
				}
			}
		}
		else
		{
			bomb();
		}
	}
}

bool Cannon::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_ENEMY_TAG;
}

cocos2d::Size Cannon::getVisualSize()
{
	return _Sprite->getBoundingBox().size * this->getScaleY();
}

void Cannon::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!_IsValid)
		return;

	//TODO
	deal(gameElement);
}