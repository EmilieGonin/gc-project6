/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "LevelOne.h"
#include <iostream>
#include <string>
#include "Eevee.h"
#include "functions.h"
USING_NS_CC;

Scene* LevelOne::createScene()
{
    Scene* scene = Scene::create();
    LevelOne* layer = LevelOne::create();
    scene->addChild(layer);
    
    return scene;

}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LevelOneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LevelOne::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }                

    this->_eevee = new Eevee;


    auto map = TMXTiledMap::create("Map1.tmx");
    this->addChild(map, 0, 99);


    Sprite* menu = Sprite::create("interface/interface.png");
    menu->setScale(1,1);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setPosition(0, 0);

    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(LevelOne::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

   
    this->_eevee->move();
    this->addChild(this->_eevee->getSprite(), 0);
    this->addChild(menu, 0);

 
    this->scheduleUpdate();
    return true;    
}   

    void LevelOne::update(float delta) {

        auto position = _eevee->getSprite()->getPosition();
        position.x -= this->pas * delta;
        if (position.x < this->_eevee->getSprite()->getContentSize().width * 0.5 || position.x > Director::getInstance()->getWinSize().width - (_eevee->getSprite()->getBoundingBox().size.width) + this->_eevee->getSprite()->getContentSize().width * 0.5)
        {
            OutputDebugStringA("je collide");
            _eevee->collide();
            this->pas *= -1;
        }
        _eevee->getSprite()->setPosition(position);
    }

    void LevelOne::MouseUp(Event* event) {
        EventMouse* e = (EventMouse*)event;
        int button = int(e->getMouseButton());
        //cocos2d::log("Mouse button pressed");
        //cocos2d::log(std::to_string(button).c_str());

        Rect eeveeBounds = _eevee->getSprite()->getBoundingBox();
        Vec2 mousePosition = e->getLocationInView();

        if (eeveeBounds.containsPoint(mousePosition)) {
            cocos2d::log("eevee touched");
            if (_eevee->getSkill()) {
                cocos2d::log("skill selected");
            }
        }

        //Change scene
        /*auto director = Director::getInstance();
        auto scene = LevelOne::createScene();
        director->replaceScene(scene);*/
    }