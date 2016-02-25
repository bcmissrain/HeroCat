#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Heros/HuluCat.h"
#include "Floors/FloorNormal.h"
#include "Levels/BaseLevel.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	static cocos2d::RenderTexture* getClipSprite(cocos2d::Sprite* sprite);
    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
	void update(float delta);
private:
	BaseLevel* _currentLevel;
};

#endif // __HELLOWORLD_SCENE_H__
