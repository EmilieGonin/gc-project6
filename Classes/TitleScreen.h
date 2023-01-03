#pragma once

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "Eevee.h"

class TitleScreen : public cocos2d::Scene
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
    int pas = 50;
};