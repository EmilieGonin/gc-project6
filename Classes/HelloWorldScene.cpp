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

#include "HelloWorldScene.h"
#include <iostream>
#include "Eevee.h"
#include "functions.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    Scene* scene = Scene::create();
    HelloWorld* layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }


    auto map = TMXTiledMap::create("Map1.tmx");
    this->addChild(map, 0, 99);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("eevee chill", "fonts/Marker Felt.ttf", 24);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 0);

    // load the Sprite Sheet
    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("sprites/character.plist");

    this->eevee = Sprite::create("sprites/character.png")   ;
    this->eevee->setScale(3, 3);
    this->eevee->setAnchorPoint(Vec2::ZERO);
   
    Vector<SpriteFrame*> frames = getAnimation("%04d.png", 3);

    Animation* animation = Animation::createWithSpriteFrames(frames, 0.2f);
    Animate* animate = Animate::create(animation);
    this->eevee->runAction(RepeatForever::create(animate));

    this->addChild(this->eevee, 0);
 

   
    this->scheduleUpdate();
    return true;
}   

Vector<SpriteFrame*> HelloWorld::getAnimation(const char* format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for (int i = 0; i < count; i++)
    {
        sprintf(str, format, i);

        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}


    void HelloWorld::menuCloseCallback(Ref* pSender)
    {
        //Close the cocos2d-x game scene and quit the application
        Director::getInstance()->end();

        /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

        //EventCustom customEndEvent("game_scene_close_event");
        //_eventDispatcher->dispatchEvent(&customEndEvent);


    }

    void HelloWorld::update(float delta) {

        auto position = this->eevee->getPosition();
        position.x -= this->pas * delta;
        if (position.x < 0  || position.x > Director::getInstance()->getWinSize().width - (this->eevee->getBoundingBox().size.width))
        {
            this->pas = this->pas * -1;
        }
        this->eevee->setPosition(position);
    }