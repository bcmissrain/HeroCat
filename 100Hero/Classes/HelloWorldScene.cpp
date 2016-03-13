#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "Levels/TestLevel.h"
#include "Levels/TeachLevel.h"
#include "Levels/SpringLevel.h"
#include "Levels/WinterLevel.h"

USING_NS_CC;
int BetweenScene::SceneCode = 0;

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto logoNode = CSLoader::createNode("Logo.csb");
	auto logoAction = CSLoader::createTimeline("Logo.csb");
	this->addChild(logoNode);
	Vec2 screenSize = Director::getInstance()->getVisibleSize();
	logoNode->setScale(1.2f);
	logoNode->setPosition(screenSize / 2);
	logoNode->runAction(logoAction);
	logoAction->gotoFrameAndPlay(0, false);
	logoAction->setLastFrameCallFunc([](){
		Director::getInstance()->replaceScene(BeginScene::createScene());
	});
	return true;
}

Scene* BeginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BeginScene::create();
	scene->addChild(layer);
	return scene;
}

bool BeginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event){
		Director::getInstance()->replaceScene(TeachScene::createScene());
		return true;
	};
	touchListener->onTouchMoved = [](Touch* touch, Event* event){
	};
	touchListener->onTouchEnded = [](Touch* touch, Event* event){
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto winSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("beginback.png");
	sprite->setPosition(winSize / 2);
	this->addChild(sprite);
	float curScale = winSize.width / sprite->getContentSize().width;
	sprite->setScale(curScale);

	auto text = Sprite::create("beginText.png");
	text->setPosition(Vec2(winSize.width / 2, 64));
	text->setScale(curScale);
	this->addChild(text);
	text->runAction(RepeatForever::create(
		Spawn::create(
			Sequence::create(
				ScaleTo::create(1.0f, 1.2f*curScale),
				ScaleTo::create(1.0f, curScale),
				NULL),
			Sequence::create(
				FadeTo::create(1.0f, 64),
				FadeTo::create(1.0f, 128),
				NULL),
			NULL)));
	return true;

	/* bug here not act 
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event){
		Director::getInstance()->replaceScene(TeachScene::createScene());
		return true;
	};
	touchListener->onTouchMoved = [](Touch* touch, Event* event){
	};
	touchListener->onTouchEnded = [](Touch* touch, Event* event){
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite);*/
}

Scene* TeachScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TeachScene::create();
    scene->addChild(layer);
    return scene;
}

bool TeachScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	_currentLevel = TeachLevel::create();
	this->addChild(_currentLevel);
	EventListenerCustom* sceneListener = EventListenerCustom::create("changeScene", [=](EventCustom* arg){
		BetweenScene::SceneCode = (int)(arg->getUserData());
		Director::getInstance()->replaceScene(BetweenScene::createScene());
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sceneListener, this);
    return true;
}

Scene* SpringScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SpringScene::create();
	scene->addChild(layer);
	return scene;
}

bool SpringScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_currentLevel = SpringLevel::create();
	this->addChild(_currentLevel);
	EventListenerCustom* sceneListener = EventListenerCustom::create("changeScene", [=](EventCustom* arg){
		BetweenScene::SceneCode = (int)(arg->getUserData());
		Director::getInstance()->replaceScene(BetweenScene::createScene());
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sceneListener, this);
	return true;
}

Scene* WinterScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WinterScene::create();
	scene->addChild(layer);
	return scene;
}

bool WinterScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_currentLevel = WinterLevel::create();
	this->addChild(_currentLevel);
	EventListenerCustom* sceneListener = EventListenerCustom::create("changeScene", [=](EventCustom* arg){
		BetweenScene::SceneCode = (int)(arg->getUserData());
		Director::getInstance()->replaceScene(BetweenScene::createScene());
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sceneListener, this);
	return true;
}

Scene* BetweenScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BetweenScene::create();
	scene->addChild(layer);
	return scene;
}

bool BetweenScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->runAction(Sequence::create(
		DelayTime::create(0.1f),
		CallFunc::create([=](){
		if (SceneCode == 0)
		{
			Director::getInstance()->replaceScene(TeachScene::createScene());
		}
		else if (SceneCode == 1)
		{
			Director::getInstance()->replaceScene(SpringScene::createScene());
		}
		else if (SceneCode == 2)
		{
			
		}
		else if (SceneCode == 3)
		{
		
		}
		else if (SceneCode == 4)
		{
			Director::getInstance()->replaceScene(WinterScene::createScene());
		}

	}),
		NULL));
	return true;
}