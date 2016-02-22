#ifndef __BASE_ELEMENT__
#define __BASE_ELEMENT__
#include "BaseDefine.h"
#include "cocos2d.h"

class BaseElemnt : public cocos2d::Node
{
public:
	BaseElemnt(){};
	~BaseElemnt(){};

	virtual cocos2d::Rect getBoundingBox() = 0;
	virtual cocos2d::Size getVisualSize() = 0;
	virtual cocos2d::Point getVisualCenter() = 0;

	virtual bool ifCollide(cocos2d::Rect rect)
	{
		return getBoundingBox().intersectsRect(rect);
	}

	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElemnt* gameElement){};
	virtual void onWeaponCollide(cocos2d::Point point, CollideOperate opType, BaseElemnt* gameElement){};
	virtual void onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElemnt* gameElement){};
	
	virtual void collideWithGameElement(BaseElemnt* gameElement){};
};
#endif