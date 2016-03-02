#include "HeroController.h"

USING_NS_CC;
Map<int,BaseHero*> HeroController::_heros;
bool HeroController::_ifInit = false;
void HeroController::initHeros()
{
	if (_ifInit)
		return;

	BaseHero* hero = CheetahCat::create();
	_heros.insert((int)hero->getHeroType(), hero);
	hero = HuluCat::create();
	_heros.insert((int)hero->getHeroType(), hero);
	hero = CaptainCat::create();
	_heros.insert((int)hero->getHeroType(), hero);
	hero = TangShengCat::create();
	_heros.insert((int)hero->getHeroType(), hero);
	_ifInit = true;
}

void HeroController::cleanHeros()
{
	if (!_ifInit)
		return;

	_heros.clear();
	_ifInit = false;
}

BaseHero* HeroController::getHeroByType(HeroType heroType)
{
	if (!_ifInit)
		return nullptr;

	auto result = _heros.find((int)heroType);
	if (result != _heros.end())
	{
		auto hero = (*result).second;
		hero->changeStateTo(ActionState::Stand);
		hero->initElement();
		return hero;
	}
	//BaseHero* hero = nullptr;
	//switch (heroType)
	//{
	//case HeroType::CheetahCat:
	//	hero = CheetahCat::create();
	//	break;
	//case HeroType::HuluCat:
	//	hero = HuluCat::create();
	//	break;
	//case HeroType::CaptainCat:
	//	hero = CaptainCat::create();
	//	break;
	//case HeroType::TangShengCat:
	//	hero = TangShengCat::create();
	//	break;
	//default:
	//	break;
	//}

	//return hero;
}

BaseHero* HeroController::initHeroAByB(BaseHero* A, BaseHero* B)
{
	if (!_ifInit)
		return nullptr;

	if (A && B)
	{
		A->setPosition(B->getPosition());
		A->_Direction = B->_Direction;
		A->_MoveState = B->_MoveState;
		A->_Sprite->setScaleX(B->_Sprite->getScaleX());
		return A;
	}
	return nullptr;
}