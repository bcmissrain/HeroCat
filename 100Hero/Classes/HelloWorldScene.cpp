#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"

#include "Levels/TestLevel.h"
#include "Levels/TeachLevel.h"
#include "Levels/SpringLevel.h"


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
	_currentLevel = TeachLevel::create();
		//SpringLevel::create();
	this->addChild(_currentLevel);

    return true;
}

Scene* HelloWorldB::createScene()
{
	auto scene = Scene::create();

	auto layer = HelloWorldB::create();

	scene->addChild(layer);

	return scene;
}

bool HelloWorldB::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->runAction(Sequence::create(
		DelayTime::create(0.5),
		CallFunc::create([](){
		Director::getInstance()->replaceScene(HelloWorld2::createScene());
	}),
		NULL));
	return true;
}

Scene* HelloWorld2::createScene()
{
	auto scene = Scene::create();

	auto layer = HelloWorld2::create();

	scene->addChild(layer);

	return scene;
}

bool HelloWorld2::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//Director::getInstance()->replaceScene(HelloWorld::createScene());
	_currentLevel = SpringLevel::create();
	this->addChild(_currentLevel);
	return true;
}
