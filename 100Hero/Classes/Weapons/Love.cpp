#include "Love.h"

USING_NS_CC;

bool Love::init()
{
	this->_HurtValue = 1.0f;
	this->_BaseScale = 0.5f;
	this->_CanTurnDirection = true;
	this->setTag(ELEMENT_WEAPON_TAG);
	this->setName(WEAPON_LOVE_NAME);
	_WeaponType = WeaponType::Shoot;
	_WeaponMoveWays = WeaponMoveWays::Horizontal;
	_Sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Images/love.png"));
	this->addChild(_Sprite);
	_EnemyDieType = EnemyDieType::Transparent;
	initElement();
	return true;
}

bool Love::initElement()
{
	this->stopAllActions();
	_Sprite->setScale(_BaseScale);
	_IsValid = true;
	_CanClean = false;
	return true;
}

void Love::update(float delta)
{

}

void Love::deal(BaseElement* baseElement)
{
	_IsValid = false;
	this->stopAllActions();
	auto dealAction = Sequence::create(
		//TODO
		FadeTo::create(0.1f, 0),
		CallFunc::create([=](){
		_CanClean = true;
	}), NULL);

	CCParticleSystem* particleSystem = CCParticleFire::create();
	particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("Images/love.png"));
	particleSystem->setPosition(Vec2::ZERO);
	this->addChild(particleSystem);
	this->runAction(dealAction);
}

bool Love::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_ENEMY_TAG;
}

cocos2d::Size Love::getVisualSize()
{
	return _Sprite->getBoundingBox().size * this->getScale();
}

void Love::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!_IsValid)
		return;
	//TODO
	deal(gameElement);
}