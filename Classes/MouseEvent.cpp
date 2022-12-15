#include "MouseEvent.h"

MouseEvent::MouseEvent() {
	_listener = EventListenerMouse::create();
	EventMouse* event = _listener->onMouseUp;
	_listener->onMouseUp = CC_CALLBACK_1(MouseEvent::MouseUp, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

MouseEvent::~MouseEvent() {}

void MouseEvent::MouseUp(Event* event) {
	EventMouse* e = (EventMouse*)event;
	std::string str = "Mouse Up detected, Key: ";
	str += std::to_string((int)e->getMouseButton());
}