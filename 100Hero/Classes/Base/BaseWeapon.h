#ifndef __BASEWEAPON_H__
#define __BASEWEAPON_H__

#include "BaseDefine.h"
#include "BaseHero.h"
#include "BaseFloor.h"
#include "BaseEnemy.h"
#include "Base/BaseElement.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class BaseWeapon :public BaseElement
{
public:
	BaseWeapon(){}
	~BaseWeapon(){}
	virtual void deal(BaseElement* gameElement){};

	virtual cocos2d::Rect getAttackBox();
	inline WeaponType getWeaponType();
	virtual bool isTarget(BaseElement* gameElement){ return false; }

	virtual cocos2d::Size getVisualSize() override;
	virtual cocos2d::Point getVisualCenter() override;
	virtual bool collideWithGameElement(BaseElement* gameElement) override;
	virtual DropState getJumpState() override{ return DropState::Down; }
	virtual float getMaxJumpSpeed() override{ return 0; }

	void hurtEnemy(BaseEnemy* enemy);
	void notifyTurn();
public:
	float _BaseScale = 1;
	float _InValidTime = -1;
	int _currentCollideId = -1;
	WeaponType _WeaponType = WeaponType::Hand;
	WeaponMoveWays _WeaponMoveWays = WeaponMoveWays::Horizontal;
	WeaponDirection _Direction = WeaponDirection::Right;
	cocos2d::Node* _Sprite = nullptr;
	cocostudio::timeline::ActionTimeline* _SpriteTimeLine = nullptr;
	cocos2d::Rect _AttackArea;
	EnemyDieType _EnemyDieType = EnemyDieType::Transparent;
	float _HurtValue = 1;
	bool _CanTurnDirection = false;
	bool _CanHurt = true;
};

#endif // !__BASE_WEAPON_H__
