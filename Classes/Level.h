#pragma once

#include <iostream>
#include <vector>

#include "cocos2d.h"
#include "Eevee.h"

USING_NS_CC;


class Level : public cocos2d::Scene
{
protected:
	int _xSpawn, _ySpawn;
	int _baseEevings = 0;
	int  _savedEevings = 0;
	int  _killedEevings = 0;
	int _currentLevel = 0;
	std::vector<Eevee*> _eevings;
	std::vector<Label*> _labels;
	int _powersInventory[5];
	std::vector<Sprite*> _powers;
	Sprite* _fastFor;
	Sprite* _slowFor;
	Sprite* _reset;
	std::vector<Scene*> _myLevels;
	std::vector<int> collisionType;
	//Speed : 50 (normal), 300 (fast) 550 (fastest)
	int _speed = 50;
	int _skillSelected;
	Vec2 _mousePosition;
	Label* _countdown;
	std::vector<TMXLayer*> _barrels;
	std::vector<Node*> _barrelsNode;

public:

	bool onContactBegin(PhysicsContact&);
	bool onContactSeparate(PhysicsContact&);

	std::vector<TMXLayer*> freezes;
	std::vector<TMXLayer*> electricalDoors;
	std::vector<PhysicsBody*> electricalDoorsBod;


	void createMap(TMXTiledMap* tilemap);
	void update(float) override;
	void handleEvent(Event*);
	void spawnEevee(int);
	void createMenu(int[]);
	void getAllLevels();
	bool isTouched(Sprite*);
	void kill(int);
	void launchExplosion(int);
	void saved(int);
	//void MouseUp(cocos2d::Event* event);

	//Setters
	void increaseSpeed();
	void decreaseSpeed();
};

