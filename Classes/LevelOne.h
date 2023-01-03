
#pragma once

#include "cocos2d.h"
#include "Eevee.h"

class LevelOne : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(LevelOne);
    void update(float) override;
    void MouseUp(cocos2d::Event* event);

protected:
    Eevee* _eevee;
    //Sprite* _menuScreen;
    int pas = 50;
};
