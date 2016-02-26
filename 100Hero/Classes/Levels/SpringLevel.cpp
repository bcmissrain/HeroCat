#include "SpringLevel.h"

#include "../Heros/HuluCat.h"
#include "../Floors/FloorNormal.h"
#include "../Weapons/Bianbian.h"
#include "../Floors/WallNormal.h"
#include "../Enemys/Enemy360.h"

#define GAME_SCREEN_SIZE_WIDTH 1024 /*1136*/
#define GAME_SCREEN_SIZE_HEIGHT 1280 /*1024*/

USING_NS_CC;

bool SpringLevel::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_minX = -(GAME_SCREEN_SIZE_WIDTH - visibleSize.width) / 2;
	_maxX = GAME_SCREEN_SIZE_WIDTH - visibleSize.width - _minX;

	_minY = -(GAME_SCREEN_SIZE_HEIGHT - visibleSize.height);
	_maxY = 0;

	_ifClickLeft = ClickState::None;
	_ifClickRight = ClickState::None;
	_ifClickJump = ClickState::None;
	_ifClickAttack = ClickState::None;

	_elementLayer = Layer::create();
	this->addChild(_elementLayer);
	
	//init back
	auto backSprite = Sprite::create("back0.png");
	backSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backSprite, -3);
	
	//init debug
	auto heroRect = Sprite::create("debugGreen.png");
	auto enemyRect = Sprite::create("debugGreen.png");
	heroRect->setTag(1000);
	this->addChild(heroRect, 0);
	enemyRect->setTag(1011);
	this->addChild(enemyRect, 0);

	//init hero
	_currentHero = HuluCat::create();
	this->addChild(_currentHero);
	_currentHero->setPosition(visibleSize.width / 2, GAME_SCREEN_SIZE_HEIGHT / 2);
	_currentHero->_BaseScale = 0.3;
	_currentHero->_Sprite->setScale(0.3);

	//init floor
	BaseFloor* floor0 = FloorNormal::create();
	cocos2d::ui::Scale9Sprite* sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(256, 60));
	floor0->initBySprite(sp0);
	floor0->setPosition(Vec2(visibleSize.width *0.3, 0));
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(256, 60));
	floor0->initBySprite(sp0);
	floor0->setPosition(Vec2(visibleSize.width *0.7, 0));
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(300, 40));
	floor0->initBySprite(sp0);
	floor0->setPosition(Vec2(visibleSize.width * 0.125, 200));
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(300, 40));
	floor0->initBySprite(sp0);
	floor0->setPosition(Vec2(visibleSize.width * 0.875, 200));
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(512, 40));
	floor0->initBySprite(sp0);
	floor0->setPosition(Vec2(visibleSize.width * 0.5, 400));
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(300, 40));
	floor0->initBySprite(sp0);
	floor0->setPosition(Vec2(visibleSize.width * 0.25, 600));
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(300, 40));
	floor0->initBySprite(sp0);
	floor0->setPosition(Vec2(visibleSize.width * 0.75, 600));
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);

	floor0 = FloorNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(512, 40));
	floor0->initBySprite(sp0);
	floor0->setPosition(Vec2(visibleSize.width * 0.5, 800));
	_elementLayer->addChild(floor0, -1);
	_floors.pushBack(floor0);
	
	auto _wall0 = WallNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(40, 40));
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(visibleSize.width * 0.8+100,600+50));
	_elementLayer->addChild(_wall0,-1);
	_floors.pushBack(_wall0);

	_wall0 = WallNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(40, 40));
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(visibleSize.width * 0.2 - 100, 600 + 50));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);

	_wall0 = WallNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(40, 40));
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(visibleSize.width * 0, 200 + 50));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);

	_wall0 = WallNormal::create();
	sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(40, 40));
	_wall0->initBySprite(sp0);
	_wall0->setPosition(Vec2(visibleSize.width * 1 , 200 + 50));
	_elementLayer->addChild(_wall0, -1);
	_floors.pushBack(_wall0);

	//init weapon listener
	auto eventListener = EventListenerCustom::create("Bianbian",
		[=](EventCustom* arg){
		CCLOG("GetBianbian");
		AddBianbianByPos(Vec2());
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	//init enemy
	auto enemy = Enemy360Boss::create();
	enemy->setPosition(Vec2(visibleSize.width / 2, GAME_SCREEN_SIZE_HEIGHT));
	_elementLayer->addChild(enemy, 1);
	_enemys.pushBack(enemy);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	//add key listener
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(SpringLevel::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(SpringLevel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
#else
	auto leftButton = ui::Button::create("buttonLeft.png", "", "");
	leftButton->setScale(0.8f);
	this->addChild(leftButton);
	leftButton->setPosition(Vec2(100, visibleSize.height * 0.2));
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
	rightButton->setScale(0.8f);
	this->addChild(rightButton);
	rightButton->setPosition(Vec2(300, visibleSize.height * 0.2));
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
	jumpButton->setScale(0.8f);
	this->addChild(jumpButton);
	jumpButton->setPosition(Vec2(1024 - 100, visibleSize.height * 0.2));
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

	auto attackButton = ui::Button::create("buttonJump.png", "", "");
	attackButton->setScale(0.8f);
	this->addChild(attackButton);
	attackButton->setPosition(Vec2(1024 - 300, visibleSize.height * 0.2));
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
	this->scheduleUpdate();
	return true;
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
	ifSupport = false;
	ifDrawDebug = false;

	if (_enemys.size() == 0)
	{
		//init enemy
		if (ifBornHurt)
		{
			auto enemy = Enemy360Hurt::create();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			enemy->setPosition(Vec2(visibleSize.width / 2, GAME_SCREEN_SIZE_HEIGHT));
			_elementLayer->addChild(enemy, 1);
			_enemys.pushBack(enemy);
			ifBornHurt = false;
		}
		else
		{
			auto enemy = Enemy360::create();
			Size visibleSize = Director::getInstance()->getVisibleSize();
			enemy->setPosition(Vec2(visibleSize.width / 2, GAME_SCREEN_SIZE_HEIGHT));
			_elementLayer->addChild(enemy, 1);
			_enemys.pushBack(enemy);
		}

	}

	if (_currentHero->getBoundingBox().getMaxY() < 0 || _currentHero->_CanClean)
	{
		_currentHero->setPosition(Vec2(GAME_SCREEN_SIZE_WIDTH / 2, GAME_SCREEN_SIZE_HEIGHT));
		_currentHero->_CanClean = false;
		_currentHero->changeStateTo(ActionState::JumpDown);
		for (auto wea = _weapons.begin(); wea != _weapons.end(); wea++)
		{
			(*wea)->deal();
		}
	}
}

void SpringLevel::updateFloor(float delta)
{
	for (auto itr = _floors.begin(); itr != _floors.end(); itr++)
	{
		//collide with hero
		ifSupport = (*itr)->collideWithGameElement(_currentHero);
		if (ifSupport)
		{
			ifDrawDebug = true;
		}

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
}

void SpringLevel::updateLate(float delta)
{
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

	//late update enemy
	for (auto ene = _enemys.begin(); ene != _enemys.end(); ene++)
	{
		(*ene)->afterUpdate();
	}
	
	_currentHero->afterUpdate();

	ResetPosition();

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
		if ((*ene)->getBoundingBox().getMaxY() < 0)
		{
			(*ene)->_CanClean = true;
			ifBornHurt = true;
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
}

void SpringLevel::AddBianbianByPos(cocos2d::Vec2 pos)
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
		weapon->_Sprite->setScale(0.3);
		weapon->setPosition(_elementLayer->convertToNodeSpace(_currentHero->getWeaponPosByIndex(0)));
		_elementLayer->addChild(weapon, -1);
		_weapons.pushBack(weapon);
		auto jumpDownAction = Sequence::create(EaseOut::create(MoveBy::create(0.2, Vec2(0, 128)), 2.0), EaseIn::create(MoveBy::create(_currentHero->_JumpTime * 2, Vec2(0, -_currentHero->_JumpHeight * 4)), 2.0), NULL);
		jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
		weapon->runAction(jumpDownAction);
	}
}