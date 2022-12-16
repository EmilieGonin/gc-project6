#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Eevee
{
protected:
	Vector<SpriteFrame*> _frames;
	Sprite* _sprite;

	Animation* _animation;
	Animate* _animate;

	int _direction;
	
public:
	Eevee();
	~Eevee();
	Vector<SpriteFrame*> getAnimation(const char* format, int count);
	void move();
	void setDirectionSprite();
	void collide();

	Sprite* getSprite();
	Animate* getAnimate();
		

};