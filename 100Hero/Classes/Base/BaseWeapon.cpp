#include "BaseWeapon.h"

cocos2d::Size BaseWeapon::getVisualSize()
{
	return _Sprite->getBoundingBox().size;
}

cocos2d::Point BaseWeapon::getVisualCenter()
{
	return this->convertToWorldSpace(_Sprite->getPosition());
}

bool BaseWeapon::collideWithGameElement(BaseElement* gameElement)
{
	if (!_IsValid)
		return false;

	if (this->getEffectiveBox().intersectsRect(gameElement->getEffectiveBox()))
	{
		if (isTarget(gameElement))
		{
			gameElement->onWeaponCollide(cocos2d::Point::ZERO, CollideOperate::CollideUp, this);
		}
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

void BaseWeapon::notifyTurn()
{
	this->_currentCollideId = -1;
}

void BaseWeapon::hurtEnemy(BaseEnemy* enemy)
{
	if (_CanHurt)
	{
		enemy->_Hurt(_HurtValue, _EnemyDieType, _CanTurnDirection);
	}
}