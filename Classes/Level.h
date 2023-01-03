#pragma once

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "Eevee.h"

class Level : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Level);
    void update(float) override;
    void MouseUp(cocos2d::Event* event);

protected:
    Eevee* _eevee;
    int pas = 50;
};