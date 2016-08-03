#ifndef __BASEFLOOR_H__
#define __BASEFLOOR_H__

#include "BaseElement.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BaseDefine.h"
#include "BaseHero.h"
#include "BaseWeapon.h"
#include "BaseEnemy.h"

class BaseHero;
class BaseWeapon;

class BaseFloor : public BaseElement
{
public:
	BaseFloor(){}
	~BaseFloor(){}

	virtual bool initElement() override;

	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;
	virtual DropState getJumpState() override;
	virtual float getMaxJumpSpeed()override;

	virtual bool collideWithGameElement(BaseElement* gameElement) override;

	virtual void initBySprite(cocos2d::Node* sprite);
	inline FloorType getFloorType();
	virtual cocos2d::Rect getSmallCollideRect(BaseElement* gameElement);

	int _SupportJumpSpeed = 0;
protected:
	FloorType _FloorType = FloorType::Normal;
	cocos2d::Node* _Sprite = nullptr;
	cocostudio::timeline::ActionTimeline* _SpriteTimeLine = nullptr;
	virtual float _getBorderScale();
};
#endif