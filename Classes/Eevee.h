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

	int _direction, _skill, _id, _pas, _formerPas;

public:
	Eevee(Sprite*, int);
	~Eevee();
	Vector<SpriteFrame*> getAnimation(const char* format, int count);
	void move();
	void setDirectionSprite();
	void collide();
	void update(float, int);
	bool isTouched(Vec2);

	//0 = None, 1 = Flareon, 2 = Glaceon, 3 = Leafeon
	void useSkill(int);

	//Getters
	Sprite* getSprite();
	Animate* getAnimate();
	int getFormerPas();
	int getId();
	int getSkill();

	//Setters
	void setSkill(int);
	void setPas(int);
};