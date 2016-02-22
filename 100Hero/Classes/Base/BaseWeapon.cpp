#include "BaseWeapon.h"

cocos2d::Rect BaseWeapon::getBoundingBox()
{
	return cocos2d::Rect(getVisualCenter() - getVisualSize() / 2, getVisualSize());
}

cocos2d::Size BaseWeapon::getVisualSize()
{
	return _Sprite->getBoundingBox().size;
}

cocos2d::Point BaseWeapon::getVisualCenter()
{
	return this->convertToWorldSpace(cocos2d::Vec2(_Sprite->getBoundingBox().getMidX(), _Sprite->getBoundingBox().getMidY()));
}

WeaponType BaseWeapon::getWeaponType()
{
	return _WeaponType;
}

void BaseWeapon::onFloorCollide(cocos2d::Point point, FloorOperate opType){}

cocos2d::Rect BaseWeapon::getAttackBox()
{
	return _AttackArea;
}

bool BaseWeapon::ifSettleDown()
{
	return _IfSettle;
}