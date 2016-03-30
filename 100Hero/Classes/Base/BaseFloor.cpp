#include "BaseFloor.h"

bool BaseFloor::initElement()
{
	BaseElement::initElement();
	return true;
}

void BaseFloor::initBySprite(cocos2d::Node* sprite)
{
	this->removeAllChildren();
	this->addChild(sprite);
	this->_Sprite = sprite;
}

cocos2d::Size BaseFloor::getVisualSize()
{
	return _Sprite->getContentSize();
}

cocos2d::Point BaseFloor::getVisualCenter()
{
	return this->convertToWorldSpace(_Sprite->getPosition());
}

DropState BaseFloor::getJumpState()
{
	return DropState::Still;
}

float BaseFloor::getMaxJumpSpeed()
{
	return 0;
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
	if (!_IsValid)
		return false;
	auto elementBox = gameElement->getBoundingBox();
	auto elementCenter = gameElement->getVisualCenter();
	auto boundingBox = getBoundingBox();
	/*
	if ((elementBox.getMinX()>=boundingBox.getMinX()&&elementBox.getMinX() <= boundingBox.getMaxX())
	||(elementBox.getMaxX() >= boundingBox.getMinX() && elementBox.getMaxX() <= boundingBox.getMaxX()))
	{
		if (gameElement->_LastRect.getMidY() - elementBox.getMidY() >= 0)//down
		{
			if (gameElement->_LastRect.getMaxY() > boundingBox.getMinY())
			{
				if (elementBox.getMinY() <= boundingBox.getMaxY())
				{
					gameElement->onFloorCollide(cocos2d::Point(0, boundingBox.getMaxY()), CollideOperate::CollideUp, this);
					return true;
				}
			}
		}
		else if (gameElement->_LastRect.getMidY() - elementBox.getMidY() < 0)//up
		{
			if (gameElement->_LastRect.getMinY() < boundingBox.getMaxY())
			{
				if (elementBox.getMaxY() >= boundingBox.getMinY())
				{
					gameElement->onFloorCollide(cocos2d::Point(0, boundingBox.getMinY()), CollideOperate::CollideDown, this);
					return true;
				}
			}
		}
	}

	return false;
	*/
	if (boundingBox.intersectsRect(elementBox))
	{
		auto collideRect = getSmallCollideRect(gameElement);

		if (collideRect.intersectsRect(elementBox))
		{
			if (elementCenter.y > boundingBox.getMidY())
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
			if (elementCenter.x > boundingBox.getMidX())
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