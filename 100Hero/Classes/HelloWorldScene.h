#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Heros/HuluCat.h"
#include "Floors/FloorNormal.h"
#include "Levels/BaseLevel.h"

class TeachScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	static cocos2d::RenderTexture* getClipSprite(cocos2d::Sprite* sprite);
    virtual bool init();
    
    CREATE_FUNC(TeachScene);
private:
	BaseLevel* _currentLevel;
};

class SpringScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SpringScene);
private:
	BaseLevel* _currentLevel;
};

class WinterScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WinterScene);
private:
	BaseLevel* _currentLevel;
};

class BetweenScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BetweenScene);

public:
	static int SceneCode;
};

#endif // __HELLOWORLD_SCENE_H__
