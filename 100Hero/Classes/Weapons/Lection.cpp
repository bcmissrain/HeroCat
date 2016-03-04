#include "Lection.h"
USING_NS_CC;

bool Lection::init()
{
	this->_HurtValue = 1024;
	this->_BaseScale = 1;
	this->_InValidTime = 3.0f;
	this->setTag(ELEMENT_WEAPON_TAG);
	this->setName(WEAPON_LECTION_NAME);
	_WeaponType = WeaponType::None;
	_WeaponMoveWays = WeaponMoveWays::Vertical;

	if (this->_InValidTime > 0)
	{
		auto invalidAction = Sequence::create(DelayTime::create(_InValidTime), CallFunc::create([=](){
			_CanClean = true;
		}), NULL);
		this->runAction(invalidAction);
	}
	ParticleSystem* m_emitter1 = ParticleSystemQuad::create("Particles/Lection.plist");
	m_emitter1->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(m_emitter1->getTexture());
	batch->addChild(m_emitter1);
	_Sprite = batch;
	this->addChild(batch);
	m_emitter1->release();
	_EnemyDieType = EnemyDieType::Transparent;
	initElement();
	return true;
}

bool Lection::initElement()
{
	_Sprite->setScale(_BaseScale);
	_IsValid = true;
	_CanClean = false;
	return true;
}

void Lection::update(float delta)
{
}

void Lection::deal(BaseElement* gameElement)
{
	//always effective
	//_IsValid = false;
}

bool Lection::isTarget(BaseElement* gameElement)
{
	return gameElement->getTag() == ELEMENT_ENEMY_TAG;
}

cocos2d::Size Lection::getVisualSize()
{
	return Director::getInstance()->getWinSize();
}

cocos2d::Point Lection::getVisualCenter()
{
	return Director::getInstance()->getWinSize() / 2;
}

void Lection::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
}