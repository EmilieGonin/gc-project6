#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Eevee : public Sprite
{
protected:
	Vector<SpriteFrame*> _frames;
	Sprite* _sprite;

	Animation* _animation;
	Animate* _animate;

	int _direction, _skill, _id, _pas;

public:
	Eevee(Sprite*, int);
	~Eevee();
	Vector<SpriteFrame*> getAnimation(const char* format, int count);
	void move();
	void setDirectionSprite();
	void collide();
	void update(float);
	bool isTouched(Vec2);

	//0 = None, 1 = Flareon, 2 = Jolteon, 3 = Vaporeon
	void useSkill(int);

	//Getters
	Sprite* getSprite();
	Animate* getAnimate();
	int getId();
};