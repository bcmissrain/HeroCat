#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Heros/HeroNormal.h"
#include "Floors/FloorNormal.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	static cocos2d::RenderTexture* getClipSprite(cocos2d::Sprite* sprite);
    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
	void update(float delta);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onButtonClick(cocos2d::ui::TouchEventType type);
	void ResetPosition();
	void AddBianbianByPos(cocos2d::Vec2 pos);
private:
	ClickState ifClickLeft;
	ClickState ifClickRight;
	ClickState ifClickJump;
	ClickState ifClickAttack;
	Layer* floorLayer = nullptr;
	BaseHero* normalHero;
	cocos2d::Vector<BaseFloor*> floors;
	cocos2d::Vector<BaseWeapon*> weapons;
	float minX;
	float minY;
	float maxX;
	float maxY;
	int attackCounter = 0;
};

#endif // __HELLOWORLD_SCENE_H__
