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

class BaseFloor : public BaseElemnt
{
public:
	BaseFloor(){}
	~BaseFloor(){}

	virtual cocos2d::Rect getBoundingBox() override;
	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;

	virtual bool init(){ return true; }
	virtual void initBySprite(cocos2d::Node* sprite);
	inline FloorType getFloorType();
	virtual cocos2d::Rect getSmallCollideRect(BaseHero* baseHero);
	virtual cocos2d::Rect getSmallCollideRect(BaseWeapon* baseWeapon);
	virtual cocos2d::Rect getSmallCollideRect(BaseEnemy* baseEnemy);
	virtual bool CollideWithHero(BaseHero* baseHero);
	virtual bool CollideWithWeapon(BaseWeapon* baseWeapon);
	virtual bool CollideWithEnemy(BaseEnemy* baseEnemy);
protected:
	FloorType _FloorType = FloorType::Normal;
	cocos2d::Node* _Sprite = nullptr;
	cocostudio::timeline::ActionTimeline* _SpriteTimeLine = nullptr;
	float _borderScale = 0.25f;
};
#endif