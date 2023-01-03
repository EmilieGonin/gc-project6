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

	int _direction, _skill, _id, _pas;

public:
	Eevee(Sprite*, int);
	~Eevee();
	Vector<SpriteFrame*> getAnimation(const char* format, int count);
	void move();
	void setDirectionSprite();
	void collide();
	void update(float);

	Sprite* getSprite();
	Animate* getAnimate();

	enum class Skill {
		NONE = 0,
		FLAREON = 1,
		JOLTEON = 2,
		VAPOREON = 3
	};

	//Getters
	int getSkill();
	int getId();
};