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

bool BaseWeapon::collideWithGameElement(BaseElement* gameElement)
{
	if (this->ifCollide(gameElement->getBoundingBox()))
	{
		gameElement->onWeaponCollide(cocos2d::Point::ZERO, CollideOperate::CollideUp, this);
		return true;
	}
	return false;
}

WeaponType BaseWeapon::getWeaponType()
{
	return _WeaponType;
}

cocos2d::Rect BaseWeapon::getAttackBox()
{
	return _AttackArea;
}

bool BaseWeapon::ifSettleDown()
{
	return _IfSettle;
}