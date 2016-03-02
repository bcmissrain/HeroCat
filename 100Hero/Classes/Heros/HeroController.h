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

public:
	static cocos2d::Map<int,BaseHero*> _heros;
private:
	static bool _ifInit;
	HeroController(){};
	~HeroController(){};
};
#endif