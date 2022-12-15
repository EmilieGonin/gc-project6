#pragma once

#include "cocos2d.h"
#include <string>
#include <iostream>
USING_NS_CC;

class MouseEvent : public Node
{
protected:
	EventListenerMouse* _listener;
	EventDispatcher* _eventDispatcher;

public:
	MouseEvent();
	~MouseEvent();
	void MouseUp(Event*);
};

