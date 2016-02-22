#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "Weapons/Bianbian.h"
#include "Enemys/Enemy360.h"

#define screenSizeWidth 2048 /*1136*/
#define screenSizeHeight 2048 /*1024*/
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	ifClickLeft = ClickState::None;
	ifClickRight = ClickState::None;
	ifClickJump = ClickState::None;
	ifClickAttack = ClickState::None;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	minX = -(screenSizeWidth - visibleSize.width) / 2;
	maxX = screenSizeWidth - visibleSize.width - minX;

	minY = -(screenSizeHeight - visibleSize.height);
	maxY = 0;

	floorLayer = Layer::create();
	floorLayer->setName("floorLayer");
	this->addChild(floorLayer);

	auto backSprite = Sprite::create("back0.png");
	backSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backSprite,-3);

	normalHero = HeroNormal::create();
	this->addChild(normalHero);
	normalHero->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	normalHero->_BaseScale = 0.4;
	normalHero->_Sprite->setScale(0.4);
	auto heroRect = Sprite::create("debugGreen.png");
	auto enemyRect = Sprite::create("debugGreen.png");
	auto floorRect0 = Sprite::create("debugRed.png");

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	this->scheduleUpdate();

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	auto leftButton = ui::Button::create("buttonLeft.png", "", "");
	leftButton->setScale(0.5f);
	this->addChild(leftButton);
	leftButton->setPosition(Vec2(visibleSize.width*0.1,visibleSize.height * 0.2));
	leftButton->addTouchEventListener([=](Ref* gameObj,cocos2d::ui::Widget::TouchEventType type){
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			normalHero->onMoveLeft(ClickState::Begin);
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			normalHero->onMoveLeft(ClickState::Still);
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			normalHero->onMoveLeft(ClickState::End);
			break;
		default:
			break;
		}
	});

	auto rightButton = ui::Button::create("buttonRight.png", "", "");
	rightButton->setScale(0.5f);
	this->addChild(rightButton);
	rightButton->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height * 0.2));
	rightButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			normalHero->onMoveRight(ClickState::Begin);
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			normalHero->onMoveRight(ClickState::Still);
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			normalHero->onMoveRight(ClickState::End);
			break;
		default:
			break;
		}
	});

	auto jumpButton = ui::Button::create("buttonJump.png", "", "");
	jumpButton->setScale(0.5f);
	this->addChild(jumpButton);
	jumpButton->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height * 0.2));
	jumpButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			normalHero->onJump(ClickState::Begin);
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			normalHero->onJump(ClickState::Still);
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			normalHero->onJump(ClickState::End);
			break;
		default:
			break;
		}
	});

	auto attackButton = ui::Button::create("buttonJump.png", "", "");
	attackButton->setScale(0.5f);
	this->addChild(attackButton);
	attackButton->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height * 0.2));
	attackButton->addTouchEventListener([=](Ref* gameObj, cocos2d::ui::Widget::TouchEventType type){
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			normalHero->onAttack(ClickState::Begin);
			CCLOG("clickBianbian %d", attackCounter);
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			normalHero->onAttack(ClickState::Still);
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			normalHero->onAttack(ClickState::End);
			break;
		default:
			break;
		}
	});
#endif
	//normalHero->_Sprite->setDebugDrawEnabled(true);

	heroRect->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	heroRect->setTag(1000);
	this->addChild(heroRect, 0);

	enemyRect->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	enemyRect->setTag(1011);
	this->addChild(enemyRect, 0);

	//init floor
	auto floor0 = FloorNormal::create();
	cocos2d::ui::Scale9Sprite* sp0 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp0->setContentSize(Size(2048, 50));
	floor0->initBySprite(sp0);
	floor0->setPosition(Vec2(visibleSize.width / 2, 0));
	floorLayer->addChild(floor0, -1);
	floors.pushBack(floor0);

	auto floor1 = FloorNormal::create();
	auto sp1 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp1->setContentSize(Size(200, 30));
	floor1->initBySprite(sp1);
	floor1->setPosition(Vec2(floor1->getVisualSize().width/2 + 50,250));
	floorLayer->addChild(floor1, -1);
	floors.pushBack(floor1);

	floor1 = FloorNormal::create();
	sp1 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp1->setContentSize(Size(200, 30));
	floor1->initBySprite(sp1);
	floor1->setPosition(Vec2(visibleSize.width-floor1->getVisualSize().width/2 - 50, 250));
	floorLayer->addChild(floor1, -1);
	floors.pushBack(floor1);

	floor1 = FloorNormal::create();
	sp1 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp1->setContentSize(Size(300, 30));
	floor1->initBySprite(sp1);
	floor1->setPosition(Vec2(visibleSize.width/2, 400));
	floorLayer->addChild(floor1, -1);
	floors.pushBack(floor1);

	floor1 = FloorNormal::create();
	sp1 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp1->setContentSize(Size(400, 30));
	floor1->initBySprite(sp1);
	floor1->setPosition(Vec2(visibleSize.width / 2, 160));
	floorLayer->addChild(floor1, -1);
	floors.pushBack(floor1);

	floor1 = FloorNormal::create();
	sp1 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp1->setContentSize(Size(30, 800));
	floor1->initBySprite(sp1);
	floor1->setPosition(Vec2(0, 0));
	floorLayer->addChild(floor1, -1);
	floors.pushBack(floor1);

	floor1 = FloorNormal::create();
	sp1 = cocos2d::ui::Scale9Sprite::create("ninesis2.png");
	sp1->setContentSize(Size(30, 800));
	floor1->initBySprite(sp1);
	floor1->setPosition(Vec2(visibleSize.width, 0));
	floorLayer->addChild(floor1, -1);
	floors.pushBack(floor1);

	auto eventListener = EventListenerCustom::create("Bianbian",
		[=](EventCustom* arg){
		CCLOG("GetBianbian");
		AddBianbianByPos(Vec2());
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	//init enemy
	auto enemy = Enemy360::create();
	enemy->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
	enemy->setTag(1010);
	floorLayer->addChild(enemy,1);

    return true;
}

void HelloWorld::update(float delta)
{
	//DEBUG
	auto debugNode = getChildByTag(1000);
	auto enemyDebug = getChildByTag(1011);
	auto enemy = (BaseEnemy *)floorLayer->getChildByTag(1010);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	normalHero->onMoveLeft(ifClickLeft);
	normalHero->onMoveRight(ifClickRight);
	normalHero->onJump(ifClickJump);
	normalHero->onAttack(ifClickAttack);
#endif

	bool ifSupport = false;
	bool ifDrawDebug = false;
	for (auto itr = floors.begin(); itr != floors.end(); itr++)
	{
		ifSupport = (*itr)->collideWithGameElement(normalHero);
		if (ifSupport)
		{
			ifDrawDebug = true;
			debugNode->setColor(Color3B::RED);
			//break;
		}

		for (auto wea = weapons.begin(); wea != weapons.end(); wea++)
		{
			(*itr)->collideWithGameElement(*wea);

			if ((*wea)->ifCollide(normalHero->getBoundingBox()))
			{
				normalHero->onWeaponCollide(Point(), CollideOperate::CollideUp, (*wea));
			}

			if (enemy)
			{
				if ((*wea)->ifCollide(enemy->getBoundingBox()))
				{
					enemy->onWeaponCollide(Point(), CollideOperate::CollideUp, (*wea));
				}
			}
		}
		if (enemy)
		{
			(*itr)->collideWithGameElement(enemy);
		}
	}

	if (enemy)
	{
		if (enemy->ifCollide(normalHero->getBoundingBox()))
		{
			normalHero->onEnemyCollide(Point(0, 0), CollideOperate::CollideUp, enemy);
		}

		enemy->check();
		enemy->update(delta);
	}

	normalHero->_CurrentState->checkState(normalHero);
	normalHero->_CurrentState->updateState(normalHero, delta);


#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (ifClickLeft == ClickState::Begin)
	{
		ifClickLeft = ClickState::Still;
	}
	else if (ifClickLeft == ClickState::End)
	{
		ifClickLeft = ClickState::None;
	}

	if (ifClickRight == ClickState::Begin)
	{
		ifClickRight = ClickState::Still;
	}
	else if (ifClickRight == ClickState::End)
	{
		ifClickRight = ClickState::None;
	}

	if (ifClickJump == ClickState::Begin)
	{
		ifClickJump = ClickState::Still;
	}
	else if (ifClickJump == ClickState::End)
	{
		ifClickJump = ClickState::None;
	}

	if (ifClickAttack == ClickState::Begin)
	{
		ifClickAttack = ClickState::Still;
	}
	else if (ifClickAttack == ClickState::End)
	{
		ifClickAttack = ClickState::None;
	}
#endif
	if (enemy)
	{
		if (enemy->_IfHaveSupport)
		{
			enemyDebug->setColor(Color3B::RED);
		}
		else
		{
			enemyDebug->setColor(Color3B::WHITE);
		}
		enemy->afterUpdate();

		if (enemy->_CanClean)
		{
			enemy->removeFromParentAndCleanup(true);
			enemy = nullptr;
		}
	}
	normalHero->afterUpdate();

	if (!ifDrawDebug)
	{
		debugNode->setColor(Color3B::WHITE);
	}
	ResetPosition();
	debugNode->setPosition(normalHero->getVisualCenter());
	debugNode->setScaleX(normalHero->getVisualSize().width / debugNode->getContentSize().width);
	debugNode->setScaleY(normalHero->getVisualSize().height / debugNode->getContentSize().height);
	if (enemy)
	{
		enemyDebug->setPosition(enemy->getVisualCenter());
		enemyDebug->setScaleX(enemy->getVisualSize().width / enemyDebug->getContentSize().width);
		enemyDebug->setScaleY(enemy->getVisualSize().height / enemyDebug->getContentSize().height);
		CCLOG("debug pos %f,%f", enemy->getVisualCenter().x, enemy->getVisualCenter().y);
	}
}
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		ifClickLeft = ClickState::Begin;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		ifClickRight = ClickState::Begin;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		ifClickJump = ClickState::Begin;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_K)
	{
		ifClickAttack = ClickState::Begin;
	}
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		ifClickLeft = ClickState::End;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		ifClickRight = ClickState::End;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		ifClickJump = ClickState::End;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_K)
	{
		ifClickAttack = ClickState::End;
	}
}
void HelloWorld::ResetPosition()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 tempPos = normalHero->getPosition();
	Vec2 deltaPos = tempPos - Vec2(visibleSize.width / 2, visibleSize.height / 2);
	normalHero->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	floorLayer->setPosition(floorLayer->getPosition() - deltaPos);
	if (floorLayer->getPositionX() < minX)
	{
		float tempX = floorLayer->getPositionX() - minX;
		floorLayer->setPositionX(minX);
		normalHero->setPositionX(normalHero->getPositionX() - tempX);
	}
	else if (floorLayer->getPositionX() > maxX)
	{
		float tempX = floorLayer->getPositionX() - maxX;
		floorLayer->setPositionX(maxX);
		normalHero->setPositionX(normalHero->getPositionX() - tempX);
	}

	if (floorLayer->getPositionY() < minY)
	{
		float tempY = floorLayer->getPositionY() - minY;
		floorLayer->setPositionY(minY);
		normalHero->setPositionY(normalHero->getPositionY() - tempY);
	}
	else if (floorLayer->getPositionY() > maxY)
	{
		float tempY = floorLayer->getPositionY() - maxY;
		floorLayer->setPositionY(maxY);
		normalHero->setPositionY(normalHero->getPositionY() - tempY);
	}

	if (normalHero->getPositionX() < 0)
	{
		normalHero->setPositionX(0);
	}
	else if (normalHero->getPositionX() > visibleSize.width)
	{
		normalHero->setPositionX(visibleSize.width);
	}
}
void HelloWorld::AddBianbianByPos(cocos2d::Vec2 pos)
{
	auto weapon = Bianbian::create();
	weapon->_Sprite->setScale(0.3);
	weapon->setPosition(floorLayer->convertToNodeSpace(normalHero->getWeaponPosByIndex(0)));
	floorLayer->addChild(weapon, -1);
	weapons.pushBack(weapon);
	auto jumpDownAction = EaseIn::create(MoveBy::create(normalHero->_JumpTime * 2, Vec2(0, -normalHero->_JumpHeight * 4)), 2.0);
	jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
	weapon->runAction(jumpDownAction);

	attackCounter++;
}