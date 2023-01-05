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
    _pas = 1;
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

void Eevee::update(float delta, int speed) {
    Vec2 position = _sprite->getPosition();
    position.x -= _pas * speed * delta;
    _sprite->setPosition(position);

    if (_skill == 1) {
        _sprite->setColor(Color3B::RED);
    }
    else if (_skill == 2) {
        _sprite->setColor(Color3B::BLUE);
    }
    else if (_skill == 3) {
        _sprite->setColor(Color3B::GREEN);
    }
    else {
        _sprite->setColor(Color3B::WHITE);
    }
}

void Eevee::useSkill(int skill) {
    //
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
    if (this->_sprite->getScaleX() == 2)
    {
        this->_sprite->setScaleX(-2);
        _pas *= -1;
    }
    else
    {
        this->_sprite->setScaleX(2);
        _pas *= -1;
    }
}

//Getters
Sprite* Eevee::getSprite() { return this->_sprite; }
Animate* Eevee::getAnimate() { return _animate; }
int Eevee::getId() { return _id; };

//Setters
void Eevee::setSkill(int skill) { _skill = skill; }