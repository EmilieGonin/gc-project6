#pragma once
#include "cocos2d.h"
#include "Eevee.h"
#include <iostream>
#include <vector>
USING_NS_CC;

class Level : public cocos2d::Scene
{
protected:
	int _xSpawn, _ySpawn;
	int _speed; //Speed : 50 (normal), 300 (fast) 550 (fastest)
	int _baseEevings, _savedEevings, _killedEevings, _currentLevel, _skillSelected;
	Vec2 _mousePosition;
	std::vector<Scene*> _myLevels;

	//Eevee & Powers
	std::vector<Eevee*> _eevings;
	std::vector<Sprite*> _powers;
	int _powersInventory[5];
	Label* _countdown;
	Label* _eevingsTotal;

	//Menu Buttons
	Sprite* _fastFor;
	Sprite* _slowFor;
	Sprite* _reset;

	//Map objects
	std::vector<TMXLayer*> _barrels;
	std::vector<Node*> _barrelsNode;
	std::vector<int> collisionType;
	std::vector<TMXLayer*> freezes;
	std::vector<TMXLayer*> electricalDoors;
	std::vector<PhysicsBody*> electricalDoorsBod;

public:
	Level();
	bool onContactBegin(PhysicsContact&);
	bool onContactSeparate(PhysicsContact&);
	void createMap(TMXTiledMap* tilemap);
	void update(float) override;
	void handleEvent(Event*);
	void spawnEevee(int);
	void createMenu(int[]);
	bool isTouched(Sprite*);
	void kill(int);
	void launchExplosion(int);
	void saved(int);

	//Setters
	void increaseSpeed();
	void decreaseSpeed();
};

