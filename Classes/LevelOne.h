
#pragma once
#include "Level.h"

class LevelOne : public Level
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(LevelOne);
    void spawnEevee();
    void MouseUp(cocos2d::Event* event);

protected:
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; }
    cocos2d::PhysicsWorld* sceneWorld;
    //Sprite* _menuScreen;
};
