#ifndef __CONTROL_BUTTON__
#define __CONTROL_BUTTON__
#include "cocos2d.h"
#include "../Base/BaseDefine.h"

class ControlButton:public cocos2d::Sprite
{
public:
	ControlButton(){}
	~ControlButton(){}
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){};
	virtual void ccTouchMove(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){};
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event){};
};

#endif