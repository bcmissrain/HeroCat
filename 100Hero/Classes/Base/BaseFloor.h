#ifndef __BASEFLOOR_H__
#define __BASEFLOOR_H__

#include "Base/BaseElement.h"
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

	virtual cocos2d::Rect getBoundingBox() override;
	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;
	virtual bool collideWithGameElement(BaseElement* gameElement) override;

	virtual bool init(){ return true; }
	virtual void initBySprite(cocos2d::Node* sprite);
	inline FloorType getFloorType();
	virtual cocos2d::Rect getSmallCollideRect(BaseElement* gameElement);

protected:
	FloorType _FloorType = FloorType::Normal;
	cocos2d::Node* _Sprite = nullptr;
	cocostudio::timeline::ActionTimeline* _SpriteTimeLine = nullptr;
	virtual float _getBorderScale();
};
#endif