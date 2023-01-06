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

	//0 = None, 1 = Flareon, 2 = Vaporeon, 3 = Jolteon, 4 = Glaceon, 5 = Leafeon
	void useSkill(int);
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