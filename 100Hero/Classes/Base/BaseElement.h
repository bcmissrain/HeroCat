#ifndef __BASE_ELEMENT__
#define __BASE_ELEMENT__
#include "BaseDefine.h"
#include "cocos2d.h"

class BaseElement : public cocos2d::Node
{
public:
	BaseElement();
	~BaseElement(){}

	virtual bool init();
	virtual bool initElement();
	virtual void update(float delta){}
	virtual void afterUpdate();

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
	virtual void onWallCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement){};
	virtual void onWeaponCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement){};
	virtual void onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement){};
	virtual void onHeroCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement){};

	//tell up or down or still
	virtual DropState getJumpState() = 0;
	virtual float getMaxJumpSpeed() = 0;
	cocos2d::Rect getDetectingBox();
public:
	static int elementCodeCounter;
	int _elementCode = -1;
	bool _IsValid = true;
	bool _CanClean = false;
	cocos2d::Rect _LastRect = cocos2d::Rect(-10000,10000,10,10);
};
#endif