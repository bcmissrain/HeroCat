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

cocos2d::Rect BaseFloor::getSmallCollideRect(BaseElement* gameElement)
{
	auto flrRec = getBoundingBox();
	auto herRec = gameElement->getBoundingBox();
	return cocos2d::Rect(flrRec.getMinX() + herRec.size.width * _getBorderScale(), flrRec.getMinY(), flrRec.size.width - 2 * _getBorderScale()*herRec.size.width, flrRec.size.height);
}

bool BaseFloor::collideWithGameElement(BaseElement* gameElement)
{
	auto boundingBox = getBoundingBox();
	if (boundingBox.intersectsRect(gameElement->getBoundingBox()))
	{
		auto collideRect = getSmallCollideRect(gameElement);

		if (collideRect.intersectsRect(gameElement->getBoundingBox()))
		{
			if (gameElement->getVisualCenter().y > boundingBox.getMidY())
			{
				gameElement->onFloorCollide(cocos2d::Point(0, boundingBox.getMaxY()), CollideOperate::CollideUp, this);
			}
			else
			{
				gameElement->onFloorCollide(cocos2d::Point(0, boundingBox.getMinY()), CollideOperate::CollideDown, this);
			}
		}
		else
		{
			if (gameElement->getVisualCenter().x > boundingBox.getMidX())
			{
				gameElement->onFloorCollide(cocos2d::Point(boundingBox.getMaxX(), 0), CollideOperate::CollideRight, this);
			}
			else
			{
				gameElement->onFloorCollide(cocos2d::Point(boundingBox.getMinX(), 0), CollideOperate::CollideLeft, this);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

float BaseFloor::_getBorderScale()
{
	return 0.25f;
}