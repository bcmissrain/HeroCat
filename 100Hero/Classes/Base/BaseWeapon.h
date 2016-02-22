#ifndef __BASEWEAPON_H__
#define __BASEWEAPON_H__

#include "BaseDefine.h"
#include "BaseHero.h"
#include "BaseFloor.h"
#include "Base/BaseElement.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class BaseWeapon :public BaseElement
{
public:
	BaseWeapon(){}
	~BaseWeapon(){}
	virtual bool init(){ return true; }
	virtual void update(float deltaTime){}

	virtual cocos2d::Rect getAttackBox();
	inline WeaponType getWeaponType();
	bool ifSettleDown();
	
	virtual cocos2d::Rect getBoundingBox() override;
	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;
public:
	WeaponType _WeaponType = WeaponType::Hand;
	WeaponMoveWays _WeaponMoveWays = WeaponMoveWays::Horizontal;
	WeaponDirection _Direction = WeaponDirection::Right;
	cocos2d::Node* _Sprite = nullptr;
	cocostudio::timeline::ActionTimeline* _SpriteTimeLine;
	cocos2d::Rect _AttackArea;
	bool _IfSettle = false;
};

#endif // !__BASE_WEAPON_H__
