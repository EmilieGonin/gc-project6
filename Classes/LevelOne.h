#pragma once

#include "cocos2d.h"
#include "Level.h"

class LevelOne : public Level
{
public:
    virtual bool init();
    CREATE_FUNC(LevelOne);
};
