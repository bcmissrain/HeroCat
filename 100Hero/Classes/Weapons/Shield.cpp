#include "Shield.h"

USING_NS_CC;

bool Shield::init()
{
	this->_HurtValue = 1.0f;
	this->_BaseScale = 0.5f;
	this->_CanTurnDirection = true;
	this->setTag(ELEMENT_WEAPON_TAG);
	this->setName(WEAPON_SHIELD_NAME);
	_WeaponType = WeaponType::Shoot;
	_WeaponMoveWays = WeaponMoveWays::Horizontal;
	_Sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Images/shield.png"));
	this->addChild(_Sprite);
	_EnemyDieType = EnemyDieType::Transparent;
	initElement();
	return true;
}

bool Shield::initElement()
{
	this->stopAllActions();
	_Sprite->setScale(_BaseScale);
	_IsValid = true;
	_CanClean = false;
	return true;
}

void Shield::update(float delta)
{

}

void Shield::deal(BaseElement* baseElement)
{
	_IsValid = false;
	this->stopAllActions();
	auto dealAction = Sequence::create(
		//TODO
		FadeTo::create(0.1f,0),
		CallFunc::create([=](){
		_CanClean = true;
	}), NULL);
	//CCParticleSystem* particleSystem = CCParticleExplosion::create();
	//particleSystem->setTexture(TextureCache::getInstance()->addImage("Images/shield.png"));
	CCParticleSystem* particleSystem = CCParticleFire::create();
	particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/shield.png"));
	particleSystem->setPosition(Vec2::ZERO);
	this->addChild(particleSystem);
	this->runAction(dealAction);
}

bool Shield::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_ENEMY_TAG;
}

cocos2d::Size Shield::getVisualSize()
{
	return _Sprite->getBoundingBox().size * this->getScale();
}

void Shield::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!_IsValid)
		return;

	//TODO
	deal(gameElement);
}