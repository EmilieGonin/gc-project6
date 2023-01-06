#pragma once
#include "Level.h"
USING_NS_CC;

class LevelOne : public Level
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LevelOne);
    void MouseUp(cocos2d::Event* event);

protected:
    TMXTiledMap* _tilemap;
    TMXLayer* _background;
    TMXObjectGroup* _collision;
};
