#include "SpringLevel.h"

#include "../Heros/HeroController.h"
#include "../Heros/HuluCat.h"
#include "../Heros/CaptainCat.h"
#include "../Heros/TangShengCat.h"
#include "../Heros/CheetahCat.h"

#include "../Enemys/Enemy360.h"

#include "../Floors/FloorNormal.h"
#include "../Floors/WallNormal.h"

#include "../Weapons/Bianbian.h"
#include "../Weapons/Shield.h"
#include "../Weapons/Biscuit.h"
#include "../Weapons/Lection.h"
#include "../Weapons/Cannon.h"
#include "../Weapons/Love.h"
#include "SimpleAudioEngine.h"

#define GAME_SCREEN_SIZE_WIDTH 1136 /*1136*/
#define GAME_SCREEN_SIZE_HEIGHT 1136 /*1024*/

USING_NS_CC;

bool SpringLevel::init()
{
	if (!Layer::init())
	{
		return false;
	}
	HeroController::initHeros();
	BaseLevel::initRandom();

	_minX = 0;
	_maxX = 0;
	_minY = -(GAME_SCREEN_SIZE_HEIGHT - getVisibleSize().height);
	_maxY = 0;

	//Load resources
	TextureCache::getInstance()->addImage("360.png");
	TextureCache::getInstance()->addImage("360_hurt.png");
	TextureCache::getInstance()->addImage("360_boss.png");
	TextureCache::getInstance()->addImage("springback.png");
	TextureCache::getInstance()->addImage("Images/bigBian.png");
	TextureCache::getInstance()->addImage("Images/love.png");
	TextureCache::getInstance()->addImage("Images/cannon.png");
	TextureCache::getInstance()->addImage("Images/shield.png");

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	TextureCache::getInstance()->addImage("blank_debug.png");
#else
	TextureCache::getInstance()->addImage("blank.png");
#endif
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Level1/SpringLevel.plist");

	_baseMaxBornTime = 10;
	_baseMinBornTime = 6;
	_currentBornTime = _baseMaxBornTime;
	_bornTimeSpeed = 4.0f / 20.0f;
	_bornBetweenTime = 0.8f;

	initBackground();
	initBornPoints();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32	
	auto heroRect = Sprite::create("debugGreen.png");
	auto enemyRect = Sprite::create("debugGreen.png");
	heroRect->setTag(1000);
	this->addChild(heroRect, 0);
	enemyRect->setTag(1011);
	this->addChild(enemyRect, 0);
#endif
	initHero();
	initFloors();
	initEnemys();
	initWeapons();

	_cakeLabel = Label::create(Value(_eatenCakeNum).asString(), "Fonts/a_song_for_jennifer.ttf", 48);
	_cakeLabel->setPosition(GAME_SCREEN_SIZE_WIDTH / 2, getVisibleSize().height - 80);
	this->addChild(_cakeLabel);

	initControl();
	this->scheduleUpdate();
	return true;
}

void SpringLevel::onExit()
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

void SpringLevel::updateInput(float delta)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	_currentHero->onMoveLeft(_ifClickLeft);
	_currentHero->onMoveRight(_ifClickRight);
	_currentHero->onJump(_ifClickJump);
	_currentHero->onAttack(_ifClickAttack);
#endif
}

void SpringLevel::updateBorn(float delta)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	ifSupport = false;
	ifDrawDebug = false;
#endif
	bornEnemys();
	bornCake();

	if (_currentHero->getBoundingBox().getMaxY() < 0 && !_currentHero->_IsValid)
	{
		_currentHero->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT / 2));
		_currentHero->initElement();
		//_currentHero->changeStateTo(ActionState::JumpDown);
		for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
		{
			if ((*wea)->getName() == WEAPON_BIANBIAN_NAME)
			{
				(*wea)->deal(_currentHero);
			}
		}

		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("changeScene",(void*)4);
	}
}

void SpringLevel::updateFloor(float delta)
{
	for (auto itr = _floors.begin(); itr != _floors.end(); itr++)
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		//collide with hero
		ifSupport = (*itr)->collideWithGameElement(_currentHero);
		if (ifSupport)
		{
			ifDrawDebug = true;
		}
#else
		(*itr)->collideWithGameElement(_currentHero);
#endif

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

void SpringLevel::updateWeapon(float delta)
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

void SpringLevel::updateEnemy(float delta)
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

void SpringLevel::updateHero(float delta)
{
	_currentHero->_CurrentState->checkState(_currentHero);
	_currentHero->_CurrentState->updateState(_currentHero, delta);

	if (_currentHero->getBoundingBox().getMaxY() < 0)
	{
		_currentHero->_IsValid = false;
	}
}

void SpringLevel::updateLate(float delta)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto enemyDebug = getChildByTag(1011);

	if (_enemys.size() > 0)
	{
		if ((*_enemys.begin())->_IfHaveSupport)
		{
			enemyDebug->setColor(Color3B::RED);
		}
		else
		{
			enemyDebug->setColor(Color3B::WHITE);
		}
	}
#endif

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

	if (_currentHero->_IsValid == false)
	{
		if (ifHeroValid)
		{
			ifHeroValid = false;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Music/Die.wav");
		}
	}
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

void SpringLevel::updateRecyle(float delta)
{
	//late update enemy
	for (auto ene = _enemys.begin(); ene != _enemys.end();)
	{
		if (_elementLayer->convertToNodeSpace((*ene)->getVisualCenter() + (*ene)->getVisualSize() / 2).y < 0)
		{
			if (!(*ene)->_CanClean)
			{
				(*ene)->_CanClean = true;
				bornHurtEnemys(*ene);
			}
		}

		if ((*ene)->_CanClean)
		{
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
			_elementLayer->removeChild(*wea, true);
			wea = _weapons.erase(wea);
		}
		else
		{
			wea++;
		}
	}

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	//debug
	auto debugNode = getChildByTag(1000);
	auto enemyDebug = getChildByTag(1011);

	if (_enemys.size() > 0)
	{
		enemyDebug->setPosition((*_enemys.begin())->getVisualCenter());
		enemyDebug->setScaleX((*_enemys.begin())->getVisualSize().width / enemyDebug->getContentSize().width);
		enemyDebug->setScaleY((*_enemys.begin())->getVisualSize().height / enemyDebug->getContentSize().height);
	}

	if (ifDrawDebug)
	{
		debugNode->setColor(Color3B::RED);
	}
	else
	{
		debugNode->setColor(Color3B::WHITE);
	}
	debugNode->setPosition(_currentHero->getVisualCenter());
	debugNode->setScaleX(_currentHero->getVisualSize().width / debugNode->getContentSize().width);
	debugNode->setScaleY(_currentHero->getVisualSize().height / debugNode->getContentSize().height);
#endif
}

void SpringLevel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
}

void SpringLevel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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

void SpringLevel::onButtonClick(cocos2d::ui::TouchEventType type)
{

}

void SpringLevel::ResetPosition()
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

	if (_currentHero->getPositionX() < 0)
	{
		_currentHero->setPositionX(0);
	}
	else if (_currentHero->getPositionX() > visibleSize.width)
	{
		_currentHero->setPositionX(visibleSize.width);
	}

	HeroController::resetPosition(_currentHero->getPosition(), _currentHero->_Direction);
}

void SpringLevel::bornCake()
{
	bool ifHaveCake = false;
	for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
	{
		if ((*wea)->getName() == WEAPON_BISCUIT_NAME)
		{
			ifHaveCake = true;
			break;
		}
	}
	if (!ifHaveCake)
	{
		//born cake
		int index = getRandomPercent(0, _cakeBornPoints.size() - 1);

		auto biscuit = Biscuit::create();
		biscuit->setPosition(_cakeBornPoints.at(index));
		_elementLayer->addChild(biscuit, -1);
		_weapons.pushBack(biscuit);
	}
}

void SpringLevel::bornEnemys()
{
	if (isBorningEnemy)
	{
		return;
	}
	//temp limit
	if (_enemys.size() >= 7)
		return;

	if (canBornEnemy)
	{
		isBorningEnemy = true;
		canBornEnemy = false;

		bool ifLeft = getRandomPercent(1, 100) <= 50;
		//create 3 enemy (50): create 1 boss (25): create 2 enemy& 1 boss(15) :create 2 boss(10)
		int createEnemyType = getRandomPercent(1, 100);

		auto bornNormal = Sequence::create(CallFunc::create([=](){
			auto enemy = Enemy360::create();
			enemy->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT));
			if (ifLeft)
			{
				enemy->_TurnDirection();
			}
			_elementLayer->addChild(enemy, 1);
			_enemys.pushBack(enemy);
		}), DelayTime::create(_bornBetweenTime), NULL);

		auto bornBoss = Sequence::create(CallFunc::create([=](){
			auto enemy = Enemy360Big::create();
			enemy->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT));
			if (ifLeft)
			{
				enemy->_TurnDirection();
			}
			_elementLayer->addChild(enemy, 1);
			_enemys.pushBack(enemy);
		}), DelayTime::create(_bornBetweenTime), NULL);

		auto bornEnd = Sequence::create(
			CallFunc::create([=](){
			isBorningEnemy = false;
		}),
			DelayTime::create(_currentBornTime),
			CallFunc::create([=](){
			canBornEnemy = true;
		}), NULL);

		Sequence* bornAction = nullptr;
		if (createEnemyType <= 50)
		{
			bornAction = Sequence::create(Repeat::create(bornNormal, 3), bornEnd, NULL);
		}
		else if (createEnemyType <= 75)
		{
			bornAction = Sequence::create(bornBoss, bornEnd, NULL);
		}
		else if (createEnemyType <= 90)
		{
			bornAction = Sequence::create(Repeat::create(bornNormal, 2), bornBoss, bornEnd, NULL);
		}
		else
		{
			bornAction = Sequence::create(Repeat::create(bornBoss, 2), bornEnd, NULL);
		}
		this->runAction(bornAction);

		_currentBornTime -= _bornTimeSpeed;
		if (_currentBornTime < _baseMinBornTime)
		{
			_currentBornTime = _baseMinBornTime;
		}
	}
}

void SpringLevel::bornHurtEnemys(BaseEnemy* baseEnemy)
{
	//temp limit
	if (_enemys.size() >= 6)
		return;

	bool ifTurnLeft = baseEnemy->_Direction == Direction::Left;
	bool ifBig = baseEnemy->_EnemyType == EnemyType::Big;
	auto bornAction = CallFunc::create([=](){
		BaseEnemy* enemy = nullptr;
		if (ifBig)
		{
			enemy = Enemy360HurtBig::create();
		}
		else
		{
			enemy = Enemy360Hurt::create();
		}
		
		enemy->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT));
		if (ifTurnLeft)
		{
			enemy->_TurnDirection();
		}
		_elementLayer->addChild(enemy, 1);
		_enemys.pushBack(enemy);
	});
	this->runAction(bornAction);
}

void SpringLevel::initBornPoints()
{
	_cakeBornPoints.push_back(Vec2(400, 410));
	_cakeBornPoints.push_back(Vec2(GAME_SCREEN_SIZE_WIDTH - 400, 410));
	_cakeBornPoints.push_back(Vec2(150, 280));
	_cakeBornPoints.push_back(Vec2(GAME_SCREEN_SIZE_WIDTH - 150, 280));
	_cakeBornPoints.push_back(Vec2(400, 190));
	_cakeBornPoints.push_back(Vec2(GAME_SCREEN_SIZE_WIDTH - 400, 190));

	_cakeBornPoints.push_back(Vec2(400, 410 + 400));
	_cakeBornPoints.push_back(Vec2(GAME_SCREEN_SIZE_WIDTH - 400, 410 + 400));
	_cakeBornPoints.push_back(Vec2(150, 280 + 400));
	_cakeBornPoints.push_back(Vec2(GAME_SCREEN_SIZE_WIDTH - 150, 280 + 400));

	_enemysBornPoints.push_back(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT));

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	for (auto p = _cakeBornPoints.begin(); p != _cakeBornPoints.end(); p++)
	{
		auto sp = Sprite::create("cakePoint.png");
		sp->setPosition(*p);
		_elementLayer->addChild(sp);

		auto biscuit = Biscuit::create();
		biscuit->setPosition(*p);
		_elementLayer->addChild(biscuit, -1);
		_weapons.pushBack(biscuit);
	}

	for (auto p = _enemysBornPoints.begin(); p != _enemysBornPoints.end(); p++)
	{
		auto sp = Sprite::create("enemyPoint.png");
		sp->setPosition(*p);
		_elementLayer->addChild(sp);
	}
#endif
}

void SpringLevel::initBackground()
{
	_elementLayer = Layer::create();
	this->addChild(_elementLayer);
	auto backSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("springback.png"));
	backSprite->setScale(GAME_SCREEN_SIZE_WIDTH / backSprite->getContentSize().width);
	backSprite->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT / 2));
	_elementLayer->addChild(backSprite, -3);
}

void SpringLevel::initFloors()
{
	//LD
	BaseFloor* floor0 = FloorNormal::create();
	Node* sp0 = Sprite::createWithSpriteFrameName("spring_floor1.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(127, 100);
	floor0->_SupportJumpSpeed = 300;
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	//RD
	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("spring_floor1.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(GAME_SCREEN_SIZE_WIDTH - 127, 100);
	floor0->_SupportJumpSpeed = 300;
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	//LDL
	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("spring_floor0.png");
	floor0->initBySprite(sp0);
	floor0->setPosition( 180, 0);
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	//RDL
	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("spring_floor0.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(GAME_SCREEN_SIZE_WIDTH - 180, 0);
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	//CM
	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("spring_floor0.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(GAME_SCREEN_SIZE_WIDTH / 2, 300);
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	//LT
	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("spring_floor1.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(127, 500);
	floor0->_SupportJumpSpeed = 300;
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	//RT
	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("spring_floor1.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(GAME_SCREEN_SIZE_WIDTH - 127, 500);
	floor0->_SupportJumpSpeed = 300;
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	//CM
	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("spring_floor0.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(GAME_SCREEN_SIZE_WIDTH / 2, 700);
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	//LD
	auto _wall0 = WallNormal::create();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank_debug.png"));
#else
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank.png"));
#endif
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(-20, 128));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);

	//RD
	_wall0 = WallNormal::create();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank_debug.png"));
#else
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank.png"));
#endif
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH + 20, 128));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);

	//LT
	_wall0 = WallNormal::create();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank_debug.png"));
#else
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank.png"));
#endif
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(-20, 550));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);

	//RT
	_wall0 = WallNormal::create();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank_debug.png"));
#else
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank.png"));
#endif
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH+20, 550));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);

	//LDL
	_wall0 = WallNormal::create();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank_debug.png"));
#else
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank.png"));
#endif
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(230, 50));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);

	//RDL
	_wall0 = WallNormal::create();
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank_debug.png"));
#else
	sp0 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("blank.png"));
#endif
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH - 230, 50));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);
}

void SpringLevel::initEnemys()
{
	/*auto enemy = Enemy360Boss::create();
	enemy->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT));
	_elementLayer->addChild(enemy, 1);
	_enemys.pushBack(enemy);*/
}

void SpringLevel::initHero()
{
	_currentHero = HeroController::getHeroByType(HeroType::CheetahCat);
	this->addChild(_currentHero);
	this->addChild(HeroController::_makeUp);
	_currentHero->setPosition(GAME_SCREEN_SIZE_WIDTH / 2, 500);

	auto makeUpAction = EventListenerCustom::create(EVENT_MAKE_UP, [=](EventCustom* arg)
	{
		if (_currentHero->getParent() == nullptr){
			CCLOG("cocos ok  hero %d", (int)_currentHero->getHeroType());
			this->addChild(_currentHero);
			this->runAction(CallFunc::create([=](){
				//recreate biscuits
				bornCake();
			}));
		}
		else
		{
			CCLOG("cocos action bug");
		}
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(makeUpAction, this);
}

void SpringLevel::initWeapons()
{
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
		else if (wType == (int)WeaponEventType::GiveLove)
		{
			giveLove();
		}
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(weaponListener, this);

	auto eatCakeListener = EventListenerCustom::create(EVENT_BISCAKE_EAT, [=](EventCustom* arg)
	{
		this->_eatenCakeNum++;
		this->_cakeLabel->setString(Value(_eatenCakeNum).asString());
		_currentHero->retain();

		this->removeChild(_currentHero, true);
		_currentHero = HeroController::getRandNewHero(_currentHero);
		HeroController::makeUp();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Music/Grow.wav");
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eatCakeListener, this);
}

void SpringLevel::initControl()
{
	_ifClickLeft = ClickState::None;
	_ifClickRight = ClickState::None;
	_ifClickJump = ClickState::None;
	_ifClickAttack = ClickState::None;

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	//add key listener
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(SpringLevel::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(SpringLevel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
#else
	auto leftButton = ui::Button::create("buttonLeft.png", "", "");
	this->addChild(leftButton);
	leftButton->setPosition(Vec2(110, 100));
	leftButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
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

	auto rightButton = ui::Button::create("buttonRight.png", "", "");
	this->addChild(rightButton);
	rightButton->setPosition(Vec2(325, 100));
	rightButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
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

	auto jumpButton = ui::Button::create("buttonJump.png", "", "");
	this->addChild(jumpButton);
	jumpButton->setPosition(Vec2(getVisibleSize().width - 110, 100));
	jumpButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
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

	auto attackButton = ui::Button::create("buttonAttack.png", "", "");
	this->addChild(attackButton);
	attackButton->setPosition(Vec2(getVisibleSize().width - 270, 100));
	attackButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
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

void SpringLevel::throwShield()
{
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
		CallFunc::create([=](){weapon->notifyTurn();}),
		EaseIn::create(MoveBy::create(0.8f, -shieldDirection), 1.5f),
		CallFunc::create([=](){weapon->deal(_currentHero); }),
		NULL);
	weapon->runAction(attackAction);
}

void SpringLevel::throwBianbian()
{
	//bool haveBianbian = false;
	//for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
	//{
	//	if ((*wea)->_IsValid)
	//	{
	//		if ((*wea)->getName() == WEAPON_BIANBIAN_NAME)
	//		{
	//			haveBianbian = true;
	//		}
	//	}
	//}

	//if (!haveBianbian){
		auto weapon = Bianbian::create();
		weapon->setPosition(_elementLayer->convertToNodeSpace(_currentHero->getWeaponPosByIndex(0)));
		_elementLayer->addChild(weapon, -1);
		_weapons.pushBack(weapon);
		auto jumpDownAction = Sequence::create(EaseOut::create(MoveBy::create(0.2f, Vec2(0, 128)), 2.0f), EaseIn::create(MoveBy::create(_currentHero->_JumpTime * 2, Vec2(0, -_currentHero->_JumpHeight * 4)), 2.0f), NULL);
		jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
		weapon->runAction(jumpDownAction);
	//}
}

void SpringLevel::throwCannon()
{
	auto weapon = Cannon::create();
	weapon->setPosition(_elementLayer->convertToNodeSpace(_currentHero->getWeaponPosByIndex(0)));
	_elementLayer->addChild(weapon, -1);
	_weapons.pushBack(weapon);
	Vec2 cannonDirection;
	if (_currentHero->_Direction == Direction::Left)
	{
		cannonDirection = Vec2(-1600, 0);
		weapon->setScaleX(-weapon->getScaleX());
	}
	else if (_currentHero->_Direction == Direction::Right)
	{
		cannonDirection = Vec2(1600, 0);
	}

	auto attackAction = Sequence::create(
		EaseOut::create(MoveBy::create(2.0f, cannonDirection), 1.5f),
		CallFunc::create([=](){weapon->deal(_currentHero); }),
		NULL);
	weapon->runAction(attackAction);
}

void SpringLevel::giveLove()
{
	auto weapon = Love::create();
	weapon->setPosition(_elementLayer->convertToNodeSpace(_currentHero->getWeaponPosByIndex(0)));
	_elementLayer->addChild(weapon, -1);
	_weapons.pushBack(weapon);
	Vec2 loveDirection;
	if (_currentHero->_Direction == Direction::Left)
	{
		loveDirection = Vec2(-400, 0);
	}
	else if (_currentHero->_Direction == Direction::Right)
	{
		loveDirection = Vec2(400, 0);
	}

	auto moveUD = Repeat::create(Sequence::create(MoveBy::create(0.5, Vec2(0, 20)), MoveBy::create(0.5, Vec2(0, -20)), NULL), 4);
	auto moveRight = EaseInOut::create(MoveBy::create(4.0f, loveDirection), 1.5f);
	auto attackAction = Sequence::create(
		Spawn::create(moveUD, moveRight, NULL),
		CallFunc::create([=](){weapon->deal(_currentHero); }),
		NULL);
	weapon->runAction(attackAction);
}

void SpringLevel::createLection()
{
	auto lection = Lection::create();
	_elementLayer->addChild(lection);
	_weapons.pushBack(lection);
}