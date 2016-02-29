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
	virtual void deal(){};

	virtual cocos2d::Rect getAttackBox();
	inline WeaponType getWeaponType();
	virtual bool isTarget(BaseElement* gameElement){ return false; }

	virtual cocos2d::Rect getBoundingBox() override;
	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;
	virtual bool collideWithGameElement(BaseElement* gameElement) override;
	virtual DropState getJumpState() override{ return DropState::Down; }
	virtual float getMaxJumpSpeed() override{ return 0; }

public:
	float _BaseScale = 1;
	WeaponType _WeaponType = WeaponType::Hand;
	WeaponMoveWays _WeaponMoveWays = WeaponMoveWays::Horizontal;
	WeaponDirection _Direction = WeaponDirection::Right;
	cocos2d::Node* _Sprite = nullptr;
	cocostudio::timeline::ActionTimeline* _SpriteTimeLine = nullptr;
	cocos2d::Rect _AttackArea;
	EnemyDieType _EnemyDieType = EnemyDieType::Transparent;
	float _HurtValue = 1;
};

#endif // !__BASE_WEAPON_H__
