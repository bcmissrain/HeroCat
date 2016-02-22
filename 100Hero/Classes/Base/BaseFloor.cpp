#include "BaseFloor.h"

void BaseFloor::initBySprite(cocos2d::Node* sprite)
{
	this->removeAllChildren();
	this->addChild(sprite);
	this->_Sprite = sprite;
}

cocos2d::Rect BaseFloor::getBoundingBox()
{
	return cocos2d::Rect(getVisualCenter() - getVisualSize() / 2, getVisualSize());
}

cocos2d::Size BaseFloor::getVisualSize()
{
	return _Sprite->getBoundingBox().size;
}

cocos2d::Point BaseFloor::getVisualCenter()
{
	return this->convertToWorldSpace(cocos2d::Vec2(_Sprite->getBoundingBox().getMidX(), _Sprite->getBoundingBox().getMidY()));
}

FloorType BaseFloor::getFloorType()
{
	return _FloorType;
}

cocos2d::Rect BaseFloor::getSmallCollideRect(BaseHero* baseHero)
{
	auto flrRec = getBoundingBox();
	auto herRec = baseHero->getBoundingBox();
	return cocos2d::Rect(flrRec.getMinX() + herRec.size.width*_borderScale, flrRec.getMinY(), flrRec.size.width - 2 * _borderScale*herRec.size.width, flrRec.size.height);
}

cocos2d::Rect BaseFloor::getSmallCollideRect(BaseWeapon* baseWeapon)
{
	auto flrRec = getBoundingBox();
	auto wepRec = baseWeapon->getBoundingBox();
	return cocos2d::Rect(flrRec.getMinX() + wepRec.size.width*_borderScale, flrRec.getMinY(), flrRec.size.width - 2 * _borderScale*wepRec.size.width, flrRec.size.height);
}

cocos2d::Rect BaseFloor::getSmallCollideRect(BaseEnemy* baseEnemy)
{
	auto flrRec = getBoundingBox();
	auto eneRec = baseEnemy->getBoundingBox();
	return cocos2d::Rect(flrRec.getMinX() + eneRec.size.width*_borderScale, flrRec.getMinY(), flrRec.size.width - 2 * _borderScale*eneRec.size.width, flrRec.size.height);
}

bool BaseFloor::CollideWithHero(BaseHero* baseHero)
{
	auto boundingBox = getBoundingBox();
	if (boundingBox.intersectsRect(baseHero->getBoundingBox()))
	{
		auto collideRect = getSmallCollideRect(baseHero);

		if (collideRect.intersectsRect(baseHero->getBoundingBox()))
		{
			if (baseHero->getVisualCenter().y > boundingBox.getMidY())
			{
				baseHero->onFloorCollide(cocos2d::Point(0, boundingBox.getMaxY()), FloorOperate::CollideUp);
			}
			else
			{
				baseHero->onFloorCollide(cocos2d::Point(0, boundingBox.getMinY()), FloorOperate::CollideDown);
			}
		}
		else
		{
			if (baseHero->getVisualCenter().x > boundingBox.getMidX())
			{
				baseHero->onFloorCollide(cocos2d::Point(boundingBox.getMaxX(), 0), FloorOperate::CollideRight);
			}
			else
			{
				baseHero->onFloorCollide(cocos2d::Point(boundingBox.getMinX(), 0), FloorOperate::CollideLeft);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool BaseFloor::CollideWithWeapon(BaseWeapon* baseWeapon)
{
	if (baseWeapon->ifSettleDown())
	{
		return true;
	}
	auto boundingBox = getBoundingBox();

	if (boundingBox.intersectsRect(baseWeapon->getBoundingBox()))
	{
		auto collideRect = getSmallCollideRect(baseWeapon);

		if (collideRect.intersectsRect(baseWeapon->getBoundingBox()))
		{
			baseWeapon->onFloorCollide(cocos2d::Point(0, boundingBox.getMaxY()), FloorOperate::CollideUp);
		}
		else
		{
			if (baseWeapon->getVisualCenter().x > boundingBox.getMidX())
			{
				baseWeapon->onFloorCollide(cocos2d::Point(boundingBox.getMaxX(), 0), FloorOperate::CollideRight);
			}
			else
			{
				baseWeapon->onFloorCollide(cocos2d::Point(boundingBox.getMinX(), 0), FloorOperate::CollideLeft);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool BaseFloor::CollideWithEnemy(BaseEnemy* baseEnemy)
{
	auto boundingBox = getBoundingBox();

	if (boundingBox.intersectsRect(baseEnemy->getBoundingBox()))
	{
		auto collideRect = getSmallCollideRect(baseEnemy);

		if (collideRect.intersectsRect(baseEnemy->getBoundingBox()))
		{
			baseEnemy->onFloorCollide(cocos2d::Point(0, boundingBox.getMaxY()), FloorOperate::CollideUp);
		}
		else
		{
			if (baseEnemy->getVisualCenter().x > boundingBox.getMidX())
			{
				baseEnemy->onFloorCollide(cocos2d::Point(boundingBox.getMaxX(), 0), FloorOperate::CollideRight);
			}
			else
			{
				baseEnemy->onFloorCollide(cocos2d::Point(boundingBox.getMinX(), 0), FloorOperate::CollideLeft);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}