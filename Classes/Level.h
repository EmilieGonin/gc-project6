#pragma once

#include <iostream>
#include <vector>

#include "cocos2d.h"
#include "Eevee.h"

USING_NS_CC;


class Level : public cocos2d::Scene
{
protected:
	int _savedEevings, _baseEevings;
	int _currentLevel = 0;
	std::vector<Eevee*> _eevings;
	std::vector<Label*> _labels;
	int _powers[5];
	std::vector<Sprite*> _myPowers;
	Sprite* _fastFor;
	Sprite* _slowFor;
	Sprite* _reset;
	std::vector<Scene*> _myLevels;
	//Speed : 50 (normal), 300 (fast) 550 (fastest)
	int _speed = 50;

public:
	void createMap(TMXTiledMap* tilemap);
	void update(float) override;
	void spawnEevee(int);
	void createMenu();
	void getAllLevels();
	//void MouseUp(cocos2d::Event* event);

	//Setters
	void increaseSpeed();
	void decreaseSpeed();
};

