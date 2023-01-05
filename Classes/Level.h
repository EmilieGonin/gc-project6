#pragma once

#include <iostream>
#include <vector>

#include "cocos2d.h"
#include "Eevee.h"

class Level : public cocos2d::Scene
{
public:
	void update(float) override;
	//void MouseUp(cocos2d::Event* event);

protected:
	int _savedEevings, _baseEevings;
	std::vector<Eevee*> _eevings;
	std::vector<Label*> _labels;
};

