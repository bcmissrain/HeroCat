#ifndef __BASE_ELEMENT__
#define __BASE_ELEMENT__
#include "BaseDefine.h"
#include "cocos2d.h"

class BaseElement : public cocos2d::Node
{
public:
	BaseElement(){};
	~BaseElement(){};

	virtual cocos2d::Rect getBoundingBox() = 0;
	virtual cocos2d::Size getVisualSize() = 0;
	virtual cocos2d::Point getVisualCenter() = 0;
	virtual cocos2d::Rect getEffectiveBox(){ return getBoundingBox(); }
	virtual bool ifCollide(cocos2d::Rect rect)
	{
		return getBoundingBox().intersectsRect(rect);
	}
	//tell him I collide him,this handle the collide detect and dispatch
	virtual bool collideWithGameElement(BaseElement* gameElement) = 0;

	//be told I've been collided
	virtual void onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement){};
	virtual void onWeaponCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement){};
	virtual void onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement){};
	virtual void onHeroCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement){};
};
#endif