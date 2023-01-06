#pragma once
#include "Level.h"
USING_NS_CC;

class LevelTwo : public Level
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LevelTwo);
    void MouseUp(cocos2d::Event* event);

protected:
    TMXTiledMap* _tilemap;
    TMXLayer* _background;
    TMXObjectGroup* _collision;
    Sprite* plasma;
};