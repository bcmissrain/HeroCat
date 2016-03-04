#include "HeroController.h"

USING_NS_CC;
Map<int,BaseHero*> HeroController::_heros;
Node* HeroController::_makeUp;
Node*HeroController::_inner;
cocostudio::timeline::ActionTimeline* HeroController::_makeUpTimeLine;
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
	hero = IronCat::create();
	_heros.insert((int)hero->getHeroType(), hero);
	_ifInit = true;

	_makeUp = Node::create();
	_makeUp->retain();
	_inner = static_cast<cocostudio::timeline::SkeletonNode*>(CSLoader::createNode("MakeUp.csb"));
	_inner->retain();
	_makeUp->addChild(_inner);
	_makeUpTimeLine = CSLoader::createTimeline("MakeUp.csb");
	_makeUpTimeLine->retain();
	_inner->runAction(_makeUpTimeLine);
	_makeUpTimeLine->gotoFrameAndPause(20);
	_makeUp->setScale(0.25);

}

void HeroController::cleanHeros()
{
	if (!_ifInit)
		return;

	_heros.clear();
	_ifInit = false;
	_makeUp->release();
	_makeUpTimeLine->release();
	_inner->release();
}

BaseHero* HeroController::getHeroByType(HeroType heroType)
{
	//if (!_ifInit)
	//	return nullptr;

	//auto result = _heros.find((int)heroType);
	//if (result != _heros.end())
	//{
	//	auto hero = (*result).second;
	//	//hero->changeStateTo(ActionState::Stand);
	//	hero->initElement();
	//	return hero;
	//}

	BaseHero* hero = nullptr;
	switch (heroType)
	{
	case HeroType::CheetahCat:
		hero = CheetahCat::create();
		break;
	case HeroType::HuluCat:
		hero = HuluCat::create();
		break;
	case HeroType::CaptainCat:
		hero = CaptainCat::create();
		break;
	case HeroType::TangShengCat:
		hero = TangShengCat::create();
		break;
	case HeroType::IronCat:
		hero = IronCat::create();
		break;
	default:
		break;
	}
	hero->retain();
	return hero;
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

void HeroController::resetPosition(Vec2 pos,Direction dir)
{
	if (!_ifInit)
		return;

	_makeUp->setPosition(pos);
	/*don't change _inner to _makeUp or it will not show in Android*/
	if (dir == Direction::Left)
	{
		_inner->setScaleX(-abs(_inner->getScaleX()));
	}
	else
	{
		_inner->setScaleX(abs(_inner->getScaleX()));
	}
}

void HeroController::makeUp()
{
	if (!_ifInit)
		return;

	_makeUpTimeLine->gotoFrameAndPlay(0,20,false);
	_makeUpTimeLine->setLastFrameCallFunc([=](){
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MAKE_UP);
	});
}