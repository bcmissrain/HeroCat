#include "Bianbian.h"

USING_NS_CC;

bool Bianbian::init()
{
	_WeaponType = WeaponType::Hulu;
	_WeaponMoveWays = WeaponMoveWays::Horizontal;
	_Sprite = CSLoader::createNode("Bianbian.csb");
	_IfSettle = false;
	this->addChild(_Sprite);
	_SpriteTimeLine = CSLoader::createTimeline("Bianbian.csb");
	_SpriteTimeLine->retain();
	_Sprite->runAction(_SpriteTimeLine);
	_SpriteTimeLine->gotoFrameAndPlay(0, 30, true);
	this->setTag(ELEMENT_WEAPON_TAG);
	return true;
}

void Bianbian::onFloorCollide(cocos2d::Point point, CollideOperate opType,BaseElement* gameElement)
{
	auto tempPoint = this->getParent()->convertToNodeSpace(point);
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
		this->_IfSettle = true;
		break;
	default:
		break;
	}
}

void Bianbian::onHeroCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{

}

void Bianbian::onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	
}