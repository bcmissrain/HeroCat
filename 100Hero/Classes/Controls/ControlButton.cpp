#include "ControlButton.h"
USING_NS_CC;

void ControlButton::onEnter()
{
	Sprite::onEnter();
	//auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->onTouchBegan = ControlButton::ccTouchBegan;
	//touchListener->onTouchMoved = ControlButton::ccTouchMove;
	//touchListener->onTouchEnded = ControlButton::ccTouchEnded;
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void ControlButton::onExit()
{
	Sprite::onExit();
}