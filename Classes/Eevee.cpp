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
    _pas = 0;
    _formerPas = 1;
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

    if (_skill == 1) { //Flareon
        _sprite->setColor(Color3B::RED);
    }
    else if (_skill == 2) { //Vaporeon
        _sprite->setColor(Color3B::BLUE);
    }
    else if (_skill == 3) { //Jolteon
        _sprite->setColor(Color3B::YELLOW);
    }
    else if (_skill == 4) { //Glaceon
        _sprite->setColor(Color3B::MAGENTA);
    }
    else if (_skill == 5) { //Leafeon
        _sprite->setColor(Color3B::GREEN);
    }
    else {
        _sprite->setColor(Color3B::WHITE);
    }
}

void Eevee::useSkill(int skill) {
    //
}

Label* Eevee::explosion(int eeveeId) {
    Label* countdown = Label::createWithTTF("5", "fonts/Hansip.otf", 22);
    countdown->setPosition(10, 30);
    countdown->setTag(1);
    DelayTime* delay = DelayTime::create(1);
    RemoveSelf* remove = RemoveSelf::create();
    CallFunc* callback = CallFunc::create([countdown]() {
        int count = atoi((countdown->getString()).c_str()) - 1;
    countdown->setString(std::to_string(count));
        });
    Sequence* sequence = Sequence::create(delay, callback, delay, callback, delay, callback, delay, callback, delay, callback, nullptr);
    _sprite->addChild(countdown);
    countdown->runAction(sequence);
    return countdown;
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

     /*   log("je collide my tag %d %d", b->getTag(), getId());*/
            if (this->_sprite->getScaleX() == 2)
            {
                this->_sprite->setScaleX(-2);      
                _pas *= -1;
                _formerPas = _pas;
            }
            else
            {
                this->_sprite->setScaleX(2); 
                _pas *= -1;
                _formerPas = _pas;
            }
}

//Getters
Sprite* Eevee::getSprite() { return this->_sprite; }
Animate* Eevee::getAnimate() { return _animate; }
int Eevee::getId() { return _id; }
int Eevee::getFormerPas() { return _formerPas; }

int Eevee::getPas() { return _pas; }

int Eevee::getSkill() { return _skill; }


//Setters
void Eevee::setSkill(int skill) { _skill = skill; }
void Eevee::setPas(int pas) {
    _pas = pas;
}