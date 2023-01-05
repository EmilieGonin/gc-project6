#include "Level.h"

void Level::update(float delta) {
    for (size_t i = 0; i < this->_eevings.size(); i++)
    {
        Eevee* eevee = this->_eevings[i];
        eevee->update(delta, _speed);
    }
}

void Level::increaseSpeed() {
    if (_speed != 100) {
        _speed = _speed + 25;
    }
}
void Level::decreaseSpeed() {
    if (_speed != 0) {
        _speed = _speed - 25;
    }
}

//void Level::MouseUp(Event* event) {
//    EventMouse* e = (EventMouse*)event;
//    //int button = int(e->getMouseButton());
//    Vec2 mousePosition = e->getLocationInView();
//
//    if (_eevings.size()) {
//        for (size_t i = 0; i < _eevings.size(); i++)
//        {
//            Eevee* eevee = _eevings[i];
//            if (eevee->isTouched(mousePosition)) {
//                //
//            }
//        }
//    }
//
//    if (_labels.size()) {
//        for (size_t i = 0; i < _labels.size(); i++)
//        {
//            Label* label = _labels[i];
//            Rect labelBounds = _labels[i]->getBoundingBox();
//        }
//    }
//
//    Rect menuBounds = _menuScreen->getBoundingBox();
//
//    /*if (startBounds.containsPoint(mousePosition)) {
//        cocos2d::log("menu touched");
//        auto director = Director::getInstance();
//        auto scene = LevelOne::createScene();
//        director->replaceScene(scene);
//    }
//    if (quitBounds.containsPoint(mousePosition)) {
//
//        auto director = Director::getInstance();
//        director->end();
//    }*/
//
//
//}
