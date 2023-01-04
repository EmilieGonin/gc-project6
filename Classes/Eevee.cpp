#include "Eevee.h"
#include <iostream>
Eevee::Eevee(Sprite* sprite, int id) {
    // 0 - 3 going left 4 - 6 going right

    SpriteFrameCache* spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("sprites/character.plist");

    _sprite = sprite;
    _direction = 0;
    _frames = getAnimation("%04d.png", 3);
    _animation = Animation::createWithSpriteFrames(this->_frames, 0.2f);
    _animate = Animate::create(this->_animation);
    _skill = 0;
    _id = id;
    _pas = 50;
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

void Eevee::update(float delta) {
    Vec2 position = _sprite->getPosition();
    position.x -= _pas * delta;

    if (position.x < _sprite->getContentSize().width * 0.5 || position.x > Director::getInstance()->getWinSize().width - (_sprite->getBoundingBox().size.width) + _sprite->getContentSize().width * 0.5)
    {
        cocos2d::log(("eevee collided :" + std::to_string(_id)).c_str());
        this->collide();
        _pas *= -1;
    }

    _sprite->setPosition(position);
}

bool Eevee::isTouched(Vec2 position) {
    Rect eeveeBounds = _sprite->getBoundingBox();

    if (eeveeBounds.containsPoint(position)) {
        cocos2d::log(("eevee touched : " + std::to_string(_id)).c_str());
        return true;
    }
    else {
        return false;
    }
}

void Eevee::collide() {
    cocos2d::log("get scale x :");
    cocos2d::log(std::to_string(this->_sprite->getScaleX()).c_str());

    if(this->_sprite->getScaleX() == 2)
    {
        this->_sprite->setScaleX(-2);
    }
    else
    {
        this->_sprite->setScaleX(2);
    }

}

Sprite* Eevee::getSprite() { return this->_sprite; }
Animate* Eevee::getAnimate() { return _animate; }
int Eevee::getSkill() { return _skill; };
int Eevee::getId() { return _id; };