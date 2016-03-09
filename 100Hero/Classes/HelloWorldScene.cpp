#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "Levels/TestLevel.h"
#include "Levels/TeachLevel.h"
#include "Levels/SpringLevel.h"
#include "Levels/WinterLevel.h"

USING_NS_CC;
int BetweenScene::SceneCode = 0;

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