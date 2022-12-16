#include "Eevee.h"
#include <iostream>
Eevee::Eevee() {
	

    // 0 - 3 going left 4 - 6 going right

    SpriteFrameCache* spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("sprites/character.plist");

    this->_sprite = Sprite::create("sprites/character.png");
    this->_sprite->setScale(2, 2);
    this->_sprite->setPosition(20, 20);
    Vec2 myAnchorPoint(0.5, 0.5);
    this->_sprite->setAnchorPoint(myAnchorPoint);

    this->_direction = 0;

    this->_frames = getAnimation("%04d.png", 3);
    this->_animation = Animation::createWithSpriteFrames(this->_frames, 0.2f);
    this->_animate = Animate::create(this->_animation);


   


};
Eevee::~Eevee() {};


Vector<SpriteFrame*> Eevee::getAnimation(const char* format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for (int i = this->_direction; i < this->_direction + 3; i++)
    {
        sprintf(str, format, i);

        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

void Eevee::move() {

    this->_sprite->runAction(RepeatForever::create(this->_animate));
}

void Eevee::setDirectionSprite() {

    Vector<SpriteFrame*> frames = getAnimation("%04d.png", this->_direction);
    this->_animation = Animation::createWithSpriteFrames(frames, 0.2f);
    this->_animate = Animate::create(this->_animation);

 }

void Eevee::collide() {
    if(this->_sprite->getScaleX() == 2)
    {

        OutputDebugStringA(std::to_string(this->_direction).c_str());
        this->_sprite->setScaleX(-2);
    }
    else
    {
        this->_sprite->setScaleX(2);
    }

}

Sprite* Eevee::getSprite() { return this->_sprite; }
Animate* Eevee::getAnimate() { return this->_animate; }