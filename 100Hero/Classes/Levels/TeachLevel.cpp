#include "TeachLevel.h"
#include "../Utils/ImageDoctor.h"

#include "../Heros/HeroController.h"
#include "../Heros/HuluCat.h"
#include "../Heros/CaptainCat.h"
#include "../Heros/TangShengCat.h"
#include "../Heros/CheetahCat.h"

#include "../Enemys/ChalkEnemy.h"

#include "../Floors/FloorNormal.h"
#include "../Floors/WallNormal.h"

#include "../Weapons/Bianbian.h"
#include "../Weapons/Shield.h"
#include "../Weapons/Biscuit.h"
#include "../Weapons/Lection.h"
#include "../Weapons/Cannon.h"
#include "../Weapons/TeachDoor.h"

#define GAME_SCREEN_SIZE_WIDTH 1136 /*1136*/
#define GAME_SCREEN_SIZE_HEIGHT 852 /*1024*/
#include "HelloWorldScene.h"

#define SPRITE_LEFT 20001
#define SPRITE_RIGHT 20002
#define SPRITE_JUMP 20003
#define SPRITE_ATTACK 20004
#define SPRITE_CAKE 20005
#define SPRITE_KILL 20006
#define SPRITE_GAME 20007

USING_NS_CC;

bool TeachLevel::init()
{
	if (!Layer::init())
	{
		return false;
	}

	HeroController::initHeros();
	BaseLevel::initRandom();

	_minX = 0; //-(GAME_SCREEN_SIZE_WIDTH - getVisibleSize().width) / 2;
	_maxX = 0; //GAME_SCREEN_SIZE_WIDTH - getVisibleSize().width - _minX;
	_minY = -(GAME_SCREEN_SIZE_HEIGHT - getVisibleSize().height);
	_maxY = 0;

	//Load resources
	TextureCache::getInstance()->addImage("Level0/back0.png");
	TextureCache::getInstance()->addImage("Images/shield.png");
	TextureCache::getInstance()->addImage("Images/bigBian.png");

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	TextureCache::getInstance()->addImage("blank_debug.png");
#else
	TextureCache::getInstance()->addImage("blank.png");
#endif
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Level0/Level0.plist");

	initBackground();
	initHero();
	initFloors();
	initEnemys();
	initWeapons();
	initControl();
	initTips();
	this->scheduleUpdate();

	return true;
}

void TeachLevel::onExit()
{
	HeroController::cleanHeros();
	_floors.clear();
	_weapons.clear();
	_enemys.clear();
	_elementLayer->removeAllChildren();
	this->removeAllChildren();
	TextureCache::getInstance()->removeUnusedTextures();
	Layer::onExit();
}


void TeachLevel::initBackground()
{
	_elementLayer = Layer::create();
	this->addChild(_elementLayer);
	auto backSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Level0/back0.png"));
	backSprite->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT / 2));
	_elementLayer->addChild(backSprite, -3);
}

void TeachLevel::initFloors()
{
	BaseFloor* floor0 = FloorNormal::create();
	auto sp0 = Sprite::createWithSpriteFrameName("Level0/floor9.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(GAME_SCREEN_SIZE_WIDTH / 2, 260);
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("Level0/floor5.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(970, 260 + 160);
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("Level0/floor4.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(710, 260 + 160 * 2);
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	auto _wall0 = WallNormal::create();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank_debug.png"));
#else
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank.png"));
#endif
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(820, 460));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);

	_wall0 = WallNormal::create();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank_debug.png"));
#else
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank.png"));
#endif
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(1125, 460));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);
}

void TeachLevel::initWeapons()
{
	//init biscuit
	auto biscuit = Biscuit::create();
	biscuit->setPosition(Vec2(420, 800));//260 + 120));
	_elementLayer->addChild(biscuit, -1);
	_weapons.pushBack(biscuit);

	//init door listener
	auto doorListener = EventListenerCustom::create(EVENT_TEACH_DOOR,
		[=](EventCustom* arg){
		playerInDoor();
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(doorListener, this);

	auto weaponListener = EventListenerCustom::create(EVENT_WEAPON_CREATE, [=](EventCustom* arg)
	{
		auto wType = (int)(arg->getUserData());
		if (wType == (int)WeaponEventType::ThrowShield)
		{
			throwShield();
		}
		else if (wType == (int)WeaponEventType::ThrowBianbian)
		{
			throwBianbian();
		}
		else if (wType == (int)WeaponEventType::CreateLection)
		{
			createLection();
		}
		else if (wType == (int)WeaponEventType::ThrowCannon)
		{
			throwCannon();
		}
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(weaponListener, this);

	auto eatCakeListener = EventListenerCustom::create(EVENT_BISCAKE_EAT, [=](EventCustom* arg)
	{
		this->_eatenCakeNum++;
		this->_cakeLabel->setString(Value(_eatenCakeNum).asString());
		auto cakeSp = _elementLayer->getChildByTag(SPRITE_CAKE);
		if (cakeSp)
		{
			cakeSp->stopAllActions();
			cakeSp->setScale(1);
			cakeSp->runAction(FadeTo::create(0.2f, 128));
			
			_currentHero->retain();
			this->removeChild(_currentHero, true);
			if (_currentHero->getHeroType() == HeroType::CheetahCat)
			{
				_currentHero = HeroController::initHeroAByB(HeroController::getHeroByType(HeroType::CaptainCat), _currentHero);
			}
			else if (_currentHero->getHeroType() == HeroType::CaptainCat)
			{
				_currentHero = HeroController::initHeroAByB(HeroController::getHeroByType(HeroType::TangShengCat), _currentHero);
			}
			else if (_currentHero->getHeroType() == HeroType::TangShengCat)
			{
				_currentHero = HeroController::initHeroAByB(HeroController::getHeroByType(HeroType::HuluCat), _currentHero);
			}
			else if (_currentHero->getHeroType() == HeroType::HuluCat)
			{
				_currentHero = HeroController::initHeroAByB(HeroController::getHeroByType(HeroType::IronCat), _currentHero);
			}
			else if (_currentHero->getHeroType() == HeroType::IronCat)
			{
				_currentHero = HeroController::initHeroAByB(HeroController::getHeroByType(HeroType::CheetahCat), _currentHero);
			}
			HeroController::makeUp();
		}
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eatCakeListener, this);
}

void TeachLevel::initEnemys()
{
	auto enemy = ChalkEnemy::create();
	enemy->setPosition(Vec2(970, 510));
	_elementLayer->addChild(enemy, 1);
	_enemys.pushBack(enemy);
}

void TeachLevel::initHero()
{
	_currentHero = HeroController::getHeroByType(HeroType::TransparentCat);
	this->addChild(_currentHero);
	this->addChild(HeroController::_makeUp);
	_currentHero->setPosition(GAME_SCREEN_SIZE_WIDTH / 2, 300);
	auto makeUpAction = EventListenerCustom::create(EVENT_MAKE_UP, [=](EventCustom* arg)
	{
		if (_currentHero->getParent() == nullptr){
			CCLOG("cocos ok  hero %d", _currentHero->getHeroType());
			this->addChild(_currentHero);
			this->runAction(CallFunc::create([=](){
				auto biscuit = Biscuit::create();
				biscuit->setPosition(Vec2(420, 800));//260 + 120));
				_elementLayer->addChild(biscuit, -1);
				_weapons.pushBack(biscuit);
			}));
		}
		else
		{
			CCLOG("cocos action bug");
		}
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(makeUpAction, this);
}

void TeachLevel::initControl()
{
	_ifClickLeft = ClickState::None;
	_ifClickRight = ClickState::None;
	_ifClickJump = ClickState::None;
	_ifClickAttack = ClickState::None;

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	//add key listener
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(TeachLevel::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(TeachLevel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
#else
	auto leftButton = ui::Button::create("Level0/button_left.png", "", "");
	this->addChild(leftButton);
	leftButton->setPosition(Vec2(110, 100));
	leftButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
		if (!ifTouchLeft)
		{
			ifTouchLeft = true;
			auto tempTip = _elementLayer->getChildByTag(SPRITE_LEFT);
			tempTip->stopAllActions();
			tempTip->runAction(FadeTo::create(0.5, 64));
		}

		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			_currentHero->onMoveLeft(ClickState::Begin);
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			_currentHero->onMoveLeft(ClickState::Still);
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			_currentHero->onMoveLeft(ClickState::End);
			break;
		default:
			break;
		}
	});

	auto rightButton = ui::Button::create("Level0/button_right.png", "", "");
	this->addChild(rightButton);
	rightButton->setPosition(Vec2(325, 100));
	rightButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
		if (!ifTouchRight)
		{
			ifTouchRight = true;
			auto tempTip = _elementLayer->getChildByTag(SPRITE_RIGHT);
			tempTip->stopAllActions();
			tempTip->runAction(FadeTo::create(0.5, 64));
		}

		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			_currentHero->onMoveRight(ClickState::Begin);
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			_currentHero->onMoveRight(ClickState::Still);
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			_currentHero->onMoveRight(ClickState::End);
			break;
		default:
			break;
		}
	});

	auto jumpButton = ui::Button::create("Level0/button_jump.png", "", "");
	this->addChild(jumpButton);
	jumpButton->setPosition(Vec2(getVisibleSize().width - 110, 100));
	jumpButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
		if (!ifTouchJump)
		{
			ifTouchJump = true;
			auto tempTip = _elementLayer->getChildByTag(SPRITE_JUMP);
			tempTip->stopAllActions();
			tempTip->runAction(FadeTo::create(0.5, 64));
		}

		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			_currentHero->onJump(ClickState::Begin);
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			_currentHero->onJump(ClickState::Still);
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			_currentHero->onJump(ClickState::End);
			break;
		default:
			break;
		}
	});

	auto attackButton = ui::Button::create("Level0/button_attack.png", "", "");
	this->addChild(attackButton);
	attackButton->setPosition(Vec2(getVisibleSize().width - 270, 100));
	attackButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
		if (!ifTouchAttack)
		{
			ifTouchAttack = true;
			auto tempTip = _elementLayer->getChildByTag(SPRITE_ATTACK);
			tempTip->stopAllActions();
			tempTip->runAction(FadeTo::create(0.5, 64));
		}

		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			_currentHero->onAttack(ClickState::Begin);
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			_currentHero->onAttack(ClickState::Still);
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			_currentHero->onAttack(ClickState::End);
			break;
		default:
			break;
		}
	});
#endif
}

void TeachLevel::initTips()
{
	auto tipAction = RepeatForever::create(Sequence::create(ScaleTo::create(1.2f, 1.1f), ScaleTo::create(0.8f, 1.0f), NULL));

	auto tip_moveLeft = Sprite::createWithSpriteFrameName("Level0/text_left.png");
	tip_moveLeft->setTag(SPRITE_LEFT);
	tip_moveLeft->runAction(tipAction->clone());
	tip_moveLeft->setPosition(Vec2(100, 195));
	_elementLayer->addChild(tip_moveLeft);

	auto tip_moveRight = Sprite::createWithSpriteFrameName("Level0/text_right.png");
	tip_moveRight->setTag(SPRITE_RIGHT);
	tip_moveRight->runAction(tipAction->clone());
	tip_moveRight->setPosition(Vec2(340, 195));
	_elementLayer->addChild(tip_moveRight);

	auto tip_jump = Sprite::createWithSpriteFrameName("Level0/text_jump.png");
	tip_jump->setTag(SPRITE_JUMP);
	tip_jump->runAction(tipAction->clone());
	tip_jump->setPosition(Vec2(1060, 195));
	_elementLayer->addChild(tip_jump);

	auto tip_attack = Sprite::createWithSpriteFrameName("Level0/text_attack.png");
	tip_attack->setTag(SPRITE_ATTACK);
	tip_attack->runAction(tipAction->clone());
	tip_attack->setPosition(Vec2(815, 195));
	_elementLayer->addChild(tip_attack);

	auto tip_kill = Sprite::createWithSpriteFrameName("Level0/text_kill_enemy.png");
	tip_kill->setTag(SPRITE_KILL);
	tip_kill->runAction(tipAction->clone());
	tip_kill->setPosition(Vec2(970, 560));
	_elementLayer->addChild(tip_kill);

	_cakeLabel = Label::create(Value(_eatenCakeNum).asString(), "Fonts/a_song_for_jennifer.ttf", 48);
	_cakeLabel->setPosition(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT - 80);
	_elementLayer->addChild(_cakeLabel);

	auto tip_cake_text = Sprite::createWithSpriteFrameName("Level0/text_cake.png");
	tip_cake_text->setOpacity(128);
	tip_cake_text->setPosition(Vec2(460, GAME_SCREEN_SIZE_HEIGHT - 110));
	_elementLayer->addChild(tip_cake_text);

	auto tip_cake_icon = Sprite::createWithSpriteFrameName("Level0/icon_heart.png");
	//tip_cake_icon->setOpacity(128);
	tip_cake_icon->setTag(SPRITE_CAKE);
	tip_cake_icon->setPosition(Vec2(515, GAME_SCREEN_SIZE_HEIGHT - 60));
	tip_cake_icon->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(1.0, 1.28f), ScaleTo::create(1.0, 1.0f), NULL)));
	_elementLayer->addChild(tip_cake_icon);
}

void TeachLevel::updateInput(float delta)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	_currentHero->onMoveLeft(_ifClickLeft);
	_currentHero->onMoveRight(_ifClickRight);
	_currentHero->onJump(_ifClickJump);
	_currentHero->onAttack(_ifClickAttack);
#endif
}

void TeachLevel::updateBorn(float delta)
{
	if (_currentHero->getBoundingBox().getMaxY() < 0 && !_currentHero->_IsValid)
	{
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("changeScene",(void*)0);

		_currentHero->setPosition(GAME_SCREEN_SIZE_WIDTH / 2, 300);
		_currentHero->initElement();

		for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
		{
			if ((*wea)->getName() == WEAPON_BIANBIAN_NAME)
			{
				(*wea)->deal(_currentHero);
			}
		}
	}

	if (!ifDoorOpen)
	{
		if (ifTouchLeft && ifTouchRight && ifTouchAttack &&ifTouchJump&&ifEatCake&&ifKillEnemy)
		{
			ifDoorOpen = true;
			auto bornAction = FadeIn::create(1.0f);
			auto tip_door = Sprite::createWithSpriteFrameName("Level0/text_begin_game.png");
			tip_door->setTag(SPRITE_GAME);
			tip_door->runAction(bornAction->clone());
			tip_door->setPosition(Vec2(680, 720));
			_elementLayer->addChild(tip_door);

			auto door = TeachDoor::create();
			door->setPosition(Vec2(680, 640));
			_elementLayer->addChild(door, -1);
			_weapons.pushBack(door);
		}
	}
}

void TeachLevel::updateFloor(float delta)
{
	for (auto itr = _floors.begin(); itr != _floors.end(); itr++)
	{
		(*itr)->collideWithGameElement(_currentHero);

		//collide with weapons
		for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
		{
			(*itr)->collideWithGameElement(*wea);
		}

		//collide with enemy
		for (auto ene = _enemys.begin(); ene != _enemys.end(); ene++)
		{
			(*itr)->collideWithGameElement((*ene));
		}
	}
}

void TeachLevel::updateWeapon(float delta)
{
	for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
	{
		//weapon collide with hero
		(*wea)->collideWithGameElement(_currentHero);

		//weapon collide with enemy
		for (auto ene = _enemys.begin(); ene != _enemys.end(); ene++)
		{
			(*wea)->collideWithGameElement(*ene);
		}
	}
}

void TeachLevel::updateEnemy(float delta)
{
	//enemy collide with hero
	for (auto ene = _enemys.begin(); ene != _enemys.end(); ene++)
	{
		(*ene)->collideWithGameElement(_currentHero);
	}

	for (auto ene = _enemys.begin(); ene != _enemys.end(); ene++)
	{
		(*ene)->check();
		(*ene)->update(delta);
	}

}

void TeachLevel::updateHero(float delta)
{
	_currentHero->_CurrentState->checkState(_currentHero);
	_currentHero->_CurrentState->updateState(_currentHero, delta);

	if (_currentHero->getBoundingBox().getMaxY() < 0)
	{
		_currentHero->_IsValid = false;
	}
}

void TeachLevel::updateLate(float delta)
{
	ResetPosition();

	//late update enemy
	for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
	{
		(*wea)->afterUpdate();
	}

	for (auto ene = _enemys.begin(); ene != _enemys.end(); ene++)
	{
		(*ene)->afterUpdate();
	}

	_currentHero->afterUpdate();


	//reset input
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (_ifClickLeft == ClickState::Begin)
	{
		_ifClickLeft = ClickState::Still;
	}
	else if (_ifClickLeft == ClickState::End)
	{
		_ifClickLeft = ClickState::None;
	}

	if (_ifClickRight == ClickState::Begin)
	{
		_ifClickRight = ClickState::Still;
	}
	else if (_ifClickRight == ClickState::End)
	{
		_ifClickRight = ClickState::None;
	}

	if (_ifClickJump == ClickState::Begin)
	{
		_ifClickJump = ClickState::Still;
	}
	else if (_ifClickJump == ClickState::End)
	{
		_ifClickJump = ClickState::None;
	}

	if (_ifClickAttack == ClickState::Begin)
	{
		_ifClickAttack = ClickState::Still;
	}
	else if (_ifClickAttack == ClickState::End)
	{
		_ifClickAttack = ClickState::None;
	}
#endif
}

void TeachLevel::updateRecyle(float delta)
{
	//late update enemy
	for (auto ene = _enemys.begin(); ene != _enemys.end();)
	{
		if (_elementLayer->convertToNodeSpace((*ene)->getVisualCenter() + (*ene)->getVisualSize() / 2).y < 0)
		{
			if (!(*ene)->_CanClean)
			{
				(*ene)->_CanClean = true;
			}
		}

		if ((*ene)->_CanClean)
		{
			if (!ifKillEnemy)
			{
				ifKillEnemy = true;
				auto tempTip = _elementLayer->getChildByTag(SPRITE_KILL);
				tempTip->stopAllActions();
				tempTip->runAction(FadeTo::create(0.5, 64));
			}
			(*ene)->removeFromParentAndCleanup(true);
			ene = _enemys.erase(ene);
		}
		else
		{
			ene++;
		}
	}

	for (auto wea = _weapons.begin(); wea != _weapons.end();)
	{
		if ((*wea)->_CanClean)
		{
			if ((*wea)->getName() == WEAPON_BISCUIT_NAME)
			{
				if (!ifEatCake)
				{
					ifEatCake = true;
				}
			}
			_elementLayer->removeChild(*wea, true);
			wea = _weapons.erase(wea);
		}
		else
		{
			wea++;
		}
	}
}

void TeachLevel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		_ifClickLeft = ClickState::Begin;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		_ifClickRight = ClickState::Begin;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		_ifClickJump = ClickState::Begin;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_K)
	{
		_ifClickAttack = ClickState::Begin;
	}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (keyCode == EventKeyboard::KeyCode::KEY_V)
	{
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("changeScene", (void*)1);
	}
#endif
}

void TeachLevel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		_ifClickLeft = ClickState::End;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		_ifClickRight = ClickState::End;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		_ifClickJump = ClickState::End;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_K)
	{
		_ifClickAttack = ClickState::End;
	}
}

void TeachLevel::onButtonClick(cocos2d::ui::TouchEventType type)
{

}

void TeachLevel::ResetPosition()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 tempPos = _currentHero->getPosition();
	Vec2 deltaPos = tempPos - Vec2(visibleSize.width / 2, visibleSize.height / 2);
	_currentHero->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	_elementLayer->setPosition(_elementLayer->getPosition() - deltaPos);
	if (_elementLayer->getPositionX() < _minX)
	{
		float tempX = _elementLayer->getPositionX() - _minX;
		_elementLayer->setPositionX(_minX);
		_currentHero->setPositionX(_currentHero->getPositionX() - tempX);
	}
	else if (_elementLayer->getPositionX() > _maxX)
	{
		float tempX = _elementLayer->getPositionX() - _maxX;
		_elementLayer->setPositionX(_maxX);
		_currentHero->setPositionX(_currentHero->getPositionX() - tempX);
	}

	if (_elementLayer->getPositionY() < _minY)
	{
		float tempY = _elementLayer->getPositionY() - _minY;
		_elementLayer->setPositionY(_minY);
		_currentHero->setPositionY(_currentHero->getPositionY() - tempY);
	}
	else if (_elementLayer->getPositionY() > _maxY)
	{
		float tempY = _elementLayer->getPositionY() - _maxY;
		_elementLayer->setPositionY(_maxY);
		_currentHero->setPositionY(_currentHero->getPositionY() - tempY);
	}

	if (_currentHero->getPositionX() < 50)
	{
		_currentHero->setPositionX(50);
	}
	else if (_currentHero->getPositionX() > GAME_SCREEN_SIZE_WIDTH - 50)
	{
		_currentHero->setPositionX(GAME_SCREEN_SIZE_WIDTH - 50);
	}

	HeroController::resetPosition(_currentHero->getPosition(),_currentHero->_Direction);
}

void TeachLevel::playerInDoor()
{
	CCLOG("IN DOOR");
	auto tempTip = _elementLayer->getChildByTag(SPRITE_GAME);
	tempTip->stopAllActions();
	tempTip->runAction(FadeTo::create(0.5, 64));
	//TODO
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("changeScene", (void*)1);
	//Director::getInstance()->end();
}

void TeachLevel::throwShield()
{
	/*bool haveShield = false;
	for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
	{
		if ((*wea)->_IsValid)
		{
			if ((*wea)->getName() == WEAPON_SHIELD_NAME)
			{
				haveShield = true;
			}
		}
	}

	if (!haveShield){*/
		auto weapon = Shield::create();
		weapon->setPosition(_elementLayer->convertToNodeSpace(_currentHero->getWeaponPosByIndex(0)));
		_elementLayer->addChild(weapon, -1);
		_weapons.pushBack(weapon);
		Vec2 shieldDirection;
		if (_currentHero->_Direction == Direction::Left)
		{
			shieldDirection = Vec2(-400, 0);
		}
		else if (_currentHero->_Direction == Direction::Right)
		{
			shieldDirection = Vec2(400, 0);
		}

		auto attackAction = Sequence::create(
			EaseOut::create(MoveBy::create(0.8f, shieldDirection), 1.5f),
			CallFunc::create([=](){weapon->notifyTurn(); }),
			EaseIn::create(MoveBy::create(0.8f, -shieldDirection), 1.5f),
			CallFunc::create([=](){weapon->deal(_currentHero); }),
			NULL);
		weapon->runAction(attackAction);
	/*}*/
}

void TeachLevel::throwBianbian()
{
	bool haveBianbian = false;
	for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
	{
		if ((*wea)->_IsValid)
		{
			if ((*wea)->getName() == WEAPON_BIANBIAN_NAME)
			{
				haveBianbian = true;
			}
		}
	}

	if (!haveBianbian){
		auto weapon = Bianbian::create();
		weapon->setPosition(_elementLayer->convertToNodeSpace(_currentHero->getWeaponPosByIndex(0)));
		_elementLayer->addChild(weapon, -1);
		_weapons.pushBack(weapon);
		auto jumpDownAction = Sequence::create(EaseOut::create(MoveBy::create(0.2f, Vec2(0, 128)), 2.0f), EaseIn::create(MoveBy::create(_currentHero->_JumpTime * 2, Vec2(0, -_currentHero->_JumpHeight * 4)), 2.0f), NULL);
		jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
		weapon->runAction(jumpDownAction);
	}
}

void TeachLevel::throwCannon()
{
	auto weapon = Cannon::create();
	weapon->setPosition(_elementLayer->convertToNodeSpace(_currentHero->getWeaponPosByIndex(0)));
	_elementLayer->addChild(weapon, -1);
	_weapons.pushBack(weapon);
	Vec2 cannonDirection;
	if (_currentHero->_Direction == Direction::Left)
	{
		cannonDirection = Vec2(-400, 0);
	}
	else if (_currentHero->_Direction == Direction::Right)
	{
		cannonDirection = Vec2(400, 0);
	}

	auto attackAction = Sequence::create(
		EaseOut::create(MoveBy::create(0.8f, cannonDirection), 1.5f),
		CallFunc::create([=](){weapon->notifyTurn(); }),
		EaseIn::create(MoveBy::create(0.8f, -cannonDirection), 1.5f),
		CallFunc::create([=](){weapon->deal(_currentHero); }),
		NULL);
	weapon->runAction(attackAction);
}

void TeachLevel::createLection()
{
	auto lection = Lection::create();
	_elementLayer->addChild(lection);
	_weapons.pushBack(lection);
}