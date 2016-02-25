#include "WallNormal.h"

bool WallNormal::init()
{
	this->setTag(ELEMENT_FLOOR_TAG);
	initElement();
	return true;
}

bool WallNormal::collideWithGameElement(BaseElement* gameElement)
{
	if (!_IsValid)
		return false;

	if (gameElement->getTag() == ELEMENT_ENEMY_TAG)
	{
		auto boundingBox = getBoundingBox();
		if (boundingBox.intersectsRect(gameElement->getBoundingBox()))
		{
			auto collideRect = getSmallCollideRect(gameElement);

			if (gameElement->getVisualCenter().x > boundingBox.getMidX())
			{
				gameElement->onWallCollide(cocos2d::Point(boundingBox.getMaxX(), 0), CollideOperate::CollideRight, this);
			}
			else
			{
				gameElement->onWallCollide(cocos2d::Point(boundingBox.getMinX(), 0), CollideOperate::CollideLeft, this);
			}
			return true;
		}
	}
	return false;
}