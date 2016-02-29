#include "TeachLevel.h"

#include "../Heros/HuluCat.h"
#include "../Heros/CheetahCat.h"
#include "../Floors/FloorNormal.h"
#include "../Weapons/Bianbian.h"
#include "../Weapons/Biscuit.h"
#include "../Floors/WallNormal.h"
#include "../Enemys/Enemy360.h"

#define GAME_SCREEN_SIZE_WIDTH 1136 /*1136*/
#define GAME_SCREEN_SIZE_HEIGHT 852 /*1024*/

USING_NS_CC;

bool TeachLevel::init()
{
	if (!Layer::init())
	{
		return false;
	}

	BaseLevel::initRandom();

	_minX = -(GAME_SCREEN_SIZE_WIDTH - getVisibleSize().width) / 2;
	_maxX = GAME_SCREEN_SIZE_WIDTH - getVisibleSize().width - _minX;
	_minY = -(GAME_SCREEN_SIZE_HEIGHT - getVisibleSize().height);
	_maxY = 0;

	//Load resources
	TextureCache::getInstance()->addImage("Level0/back0.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Level0/Level0.plist");

	initBackground();
	initBornPoints();

	initHero();
	initFloors();
	initEnemys();
	initWeapons();
	initControl();
	this->scheduleUpdate();
	return true;
}

void TeachLevel::onExit()
{
	_floors.clear();
	_weapons.clear();
	_enemys.clear();
	_elementLayer->removeAllChildren();
	this->removeAllChildren();
	TextureCache::getInstance()->removeUnusedTextures();
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
		_currentHero->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT));
		_currentHero->initElement();
		//_currentHero->changeStateTo(ActionState::JumpDown);
		for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
		{
			if ((*wea)->getName() == WEAPON_BIANBIAN_NAME)
			{
				(*wea)->deal();
			}
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

	if (_currentHero->getPositionX() < 0)
	{
		_currentHero->setPositionX(0);
	}
	else if (_currentHero->getPositionX() > visibleSize.width)
	{
		_currentHero->setPositionX(visibleSize.width);
	}
}

void TeachLevel::bornCake()
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

void TeachLevel::bornEnemys()
{
	if (isBorningEnemy)
	{
		return;
	}

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
			auto enemy = Enemy360::create();
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

void TeachLevel::bornHurtEnemys(BaseEnemy* baseEnemy)
{
	bool ifTurnLeft = baseEnemy->_Direction == Direction::Left;
	auto bornAction = CallFunc::create([=](){
		auto enemy = Enemy360Hurt::create();

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

void TeachLevel::AddBianbianByPos(cocos2d::Vec2 pos)
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
		auto jumpDownAction = Sequence::create(EaseOut::create(MoveBy::create(0.2, Vec2(0, 128)), 2.0), EaseIn::create(MoveBy::create(_currentHero->_JumpTime * 2, Vec2(0, -_currentHero->_JumpHeight * 4)), 2.0), NULL);
		jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
		weapon->runAction(jumpDownAction);
	}
}

void TeachLevel::initBornPoints()
{
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
	floor0->setPosition(970, 260+160);
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = Sprite::createWithSpriteFrameName("Level0/floor4.png");
	floor0->initBySprite(sp0);
	floor0->setPosition(710, 260 + 160*2);
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);
}

void TeachLevel::initWeapons()
{
	auto biscuit = Biscuit::create();
	biscuit->setPosition(Vec2(420,260+120));
	_elementLayer->addChild(biscuit, -1);
	_weapons.pushBack(biscuit);

	//init weapon listener
	auto eventListener = EventListenerCustom::create("Bianbian",
		[=](EventCustom* arg){
		CCLOG("GetBianbian");
		AddBianbianByPos(Vec2());
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void TeachLevel::initEnemys()
{
	/*auto enemy = Enemy360Boss::create();
	enemy->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT));
	_elementLayer->addChild(enemy, 1);
	_enemys.pushBack(enemy);*/
}

void TeachLevel::initHero()
{
	_currentHero = CheetahCat::create();//HuluCat::create();
	this->addChild(_currentHero);
	_currentHero->setPosition(GAME_SCREEN_SIZE_WIDTH/2, 600);
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
	auto leftButton = ui::Button::create("buttonLeft.png", "", "");
	leftButton->setScale(0.45f);
	this->addChild(leftButton);
	leftButton->setPosition(Vec2(110, 80));
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
	rightButton->setScale(0.45f);
	this->addChild(rightButton);
	rightButton->setPosition(Vec2(325, 80));
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
	jumpButton->setScale(0.45f);
	this->addChild(jumpButton);
	jumpButton->setPosition(Vec2(getVisibleSize().width - 110, 80));
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
	attackButton->setScale(0.45f);
	this->addChild(attackButton);
	attackButton->setPosition(Vec2(getVisibleSize().width - 270, 80));
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