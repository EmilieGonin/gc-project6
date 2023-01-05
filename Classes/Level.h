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
	int _powersInventory[5];
	std::vector<Sprite*> _powers;
	Sprite* _fastFor;
	Sprite* _slowFor;
	Sprite* _reset;
	std::vector<Scene*> _myLevels;
	//Speed : 50 (normal), 300 (fast) 550 (fastest)
	int _speed = 50;
	int _skillSelected;
	Vec2 _mousePosition;

public:
	void createMap(TMXTiledMap* tilemap);
	void update(float) override;
	void handleEvent(Event*);
	void spawnEevee(int);
	void createMenu(int[]);
	void getAllLevels();
	bool isTouched(Sprite*);
	//void MouseUp(cocos2d::Event* event);

	//Setters
	void increaseSpeed();
	void decreaseSpeed();
};

