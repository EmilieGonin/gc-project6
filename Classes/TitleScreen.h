#pragma once
#include "Level.h"
USING_NS_CC;

class TitleScreen : public Level
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TitleScreen);
    void MouseUp(cocos2d::Event* event);
    
protected:
    Label* start;
    Label* quit;
    Sprite* _menuScreen;
};