#pragma once
#include "Level.h"
#include "functions.h"

USING_NS_CC;

class LevelTwo : public Level
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(LevelTwo);


    void MouseUp(cocos2d::Event* event);


protected:
    TMXTiledMap* _tilemap;
    TMXLayer* _background;
    TMXObjectGroup* _collision;
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; }
    cocos2d::PhysicsWorld* sceneWorld;
    //Sprite* _menuScreen;
};