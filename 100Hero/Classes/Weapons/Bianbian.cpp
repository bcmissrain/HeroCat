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
	return true;
}

void Bianbian::onFloorCollide(cocos2d::Point point, FloorOperate opType)
{
	auto tempPoint = this->getParent()->convertToNodeSpace(point);
	float currentHeight = _Sprite->getChildByName("bigBian_2")->getBoundingBox().size.height * _Sprite->getScale();

	switch (opType)
	{
	case FloorOperate::CollideLeft:
		break;
	case FloorOperate::CollideRight:
		break;
	case FloorOperate::CollideUp:
	case FloorOperate::CollideDown:
		this->setPositionY(tempPoint.y + currentHeight / 2);
		this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
		this->_IfSettle = true;
		break;
	default:
		break;
	}
}