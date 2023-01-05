#pragma once

#include <iostream>
#include <vector>

#include "cocos2d.h"
#include "Eevee.h"

USING_NS_CC;


class Level : public cocos2d::Scene
{
protected:
	std::vector<Eevee*> _eevings;
	std::vector<Label*> _labels;
	int _powers[4];

	//Speed : 50 (normal), 300 (fast) 550 (fastest)
	int _speed = 50;

public:
	void createMap(TMXTiledMap* tilemap);
	void update(float) override;
	//void MouseUp(cocos2d::Event* event);

	//Setters
	void increaseSpeed();
	void decreaseSpeed();
};

