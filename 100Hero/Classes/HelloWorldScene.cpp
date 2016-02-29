#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"

#include "Levels/SpringLevel.h"
#include "Levels/TeachLevel.h"


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
	_currentLevel = TeachLevel::create();//SpringLevel::create();
	this->addChild(_currentLevel);

    return true;
}

void HelloWorld::update(float delta)
{
	_currentLevel->update(delta);
}
