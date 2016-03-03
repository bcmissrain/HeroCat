#ifndef __HERO_CONTROLLER_H__
#define __HERO_CONTROLLER_H__
#include "cocos2d.h"
#include "../Base/BaseDefine.h"
#include "CheetahCat.h"
#include "HuluCat.h"
#include "CaptainCat.h"
#include "TangShengCat.h"

class HeroController
{
public:
	static void initHeros();
	static void cleanHeros();
	static BaseHero* getHeroByType(HeroType heroType);
	static BaseHero* initHeroAByB(BaseHero* A, BaseHero* B);
	static void resetPosition(cocos2d::Vec2 pos,Direction dir);
	static void makeUp();
public:
	static cocos2d::Map<int,BaseHero*> _heros;
	static cocos2d::Node* _makeUp;
	static cocos2d::Node* _inner;
	static cocostudio::timeline::ActionTimeline* _makeUpTimeLine;
private:
	static bool _ifInit;
	HeroController(){};
	~HeroController(){};
};
#endif