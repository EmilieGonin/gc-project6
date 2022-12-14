#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Eevee
{
protected:
	Vector<SpriteFrame*> sprite;
public:
	Eevee(Vector<SpriteFrame*>);
	~Eevee();
};