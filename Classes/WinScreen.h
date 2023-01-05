#pragma once

#include "Level.h"

class WinScreen : public Level
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(WinScreen);
    void MouseUp(cocos2d::Event* event);

protected:
    
    Label* timeSpentText;
    Sprite* _menuScreen;
    Sprite* _restart;
    Sprite* _next;
};