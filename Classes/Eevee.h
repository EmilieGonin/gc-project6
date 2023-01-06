#pragma once
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;

//Skills
//0 = None, 1 = Flareon, 2 = Vaporeon, 3 = Jolteon, 4 = Glaceon, 5 = Leafeon

class Eevee : public Sprite
{
protected:
	Vector<SpriteFrame*> _frames;
	Sprite* _sprite;
	Animation* _animation;
	Animate* _animate;
	int _direction, _skill, _id, _pas, _formerPas;

public:
	Eevee(Sprite*, int);
	Vector<SpriteFrame*> getAnimation(const char* format, int count);
	void move();
	void setDirectionSprite();
	void collide();
	void update(float, int);
	bool isTouched(Vec2);
	Label* explosion(int);

	//Getters
	Sprite* getSprite();
	Animate* getAnimate();
	int getFormerPas();
	int getId();
	int getPas();
	int getSkill();

	//Setters
	void setSkill(int);
	void setPas(int);
};