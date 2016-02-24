#include "BaseWall.h"

bool BaseWall::collideWithGameElement(BaseElement* gameElement)
{
	auto boundingBox = getBoundingBox();
	if (boundingBox.intersectsRect(gameElement->getBoundingBox()))
	{
		auto collideRect = getSmallCollideRect(gameElement);

		if (collideRect.intersectsRect(gameElement->getBoundingBox()))
		{
			if (gameElement->getVisualCenter().y > boundingBox.getMidY())
			{
				gameElement->onWallCollide(cocos2d::Point(0, boundingBox.getMaxY()), CollideOperate::CollideUp, this);
			}
			else
			{
				gameElement->onWallCollide(cocos2d::Point(0, boundingBox.getMinY()), CollideOperate::CollideDown, this);
			}
		}
		else
		{
			if (gameElement->getVisualCenter().x > boundingBox.getMidX())
			{
				gameElement->onWallCollide(cocos2d::Point(boundingBox.getMaxX(), 0), CollideOperate::CollideRight, this);
			}
			else
			{
				gameElement->onWallCollide(cocos2d::Point(boundingBox.getMinX(), 0), CollideOperate::CollideLeft, this);
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

float BaseWall::_getBorderScale()
{
	return 1.0f;
}