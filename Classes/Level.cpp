#include "Level.h"
#include "WinScreen.h"


void Level::update(float delta) {
    if(this->_eevings.size())
    {
        Eevee* eevee = this->_eevings[i];
        eevee->update(delta, _speed);

        if (_countdown && _countdown->getString() == "0") {
            launchExplosion(i);
        }
        for (size_t i = 0; i < this->_eevings.size(); i++)
        {
            Eevee* eevee = this->_eevings[i];
            eevee->update(delta, _speed);
        }
    }
    else {
        this->_eevings.clear();
        auto director = Director::getInstance();
        auto scene = WinScreen::createScene(_savedEevings, _baseEevings);
        director->replaceScene(scene);
    }


    if (_powers.size()) {
        Label* counter = nullptr;

        for (size_t i = 0; i < _powers.size(); i++)
        {
            if (_skillSelected && (i == _skillSelected - 1)) {
                _powers[i]->setColor(Color3B::RED);
            }
            else {
                _powers[i]->setColor(Color3B::WHITE);
            }
        }
    }
}

void Level::handleEvent(Event* event) {
    EventMouse* e = (EventMouse*)event;
    _mousePosition = e->getLocationInView();

    if (_powers.size()) {
        for (size_t i = 0; i < _powers.size(); i++)
        {
            Sprite* power = _powers[i];

            if (isTouched(power)) {
                _skillSelected = i + 1;
            }
        }
    }

    if (_eevings.size()) {
        for (size_t i = 0; i < _eevings.size(); i++)
        {
            Eevee* eevee = _eevings[i];

            if (isTouched(eevee->getSprite()) && _skillSelected && !eevee->getSkill()) {
                if (_powersInventory[_skillSelected - 1]) {
                    eevee->setSkill(_skillSelected);
                    _powersInventory[_skillSelected - 1]--;
                    _powers[_skillSelected - 1]->removeAllChildren();
                    Label* counter = Label::createWithTTF(std::to_string(_powersInventory[_skillSelected - 1]), "fonts/Hansip.otf", 25);
                    _powers[_skillSelected - 1]->addChild(counter);
                    if (_skillSelected == 1) { //Flareon
                        _countdown = eevee->explosion(i);
                    }
                    else if (_skillSelected == 5) { //Leafeon
                        
                        /*JumpBy* jump = JumpBy::create(0.5, Point(-200 * eevee->getPas(), 0), 50, 1);
                        eevee->getSprite()->runAction(jump);*/
                        eevee->getSprite()->getPhysicsBody()->applyImpulse( Vect(-50 * eevee->getPas(), 200) );
                    }
                    _skillSelected = 0;
                }
                else {
                    cocos2d::log("power not available");
                }
            }
            else if (isTouched(eevee->getSprite())) {
                kill(i);
            }
        }
    }

    if (_fastFor && isTouched(_fastFor)) {
        increaseSpeed();
    }

    if (_slowFor && isTouched(_slowFor)) {
        decreaseSpeed();
    }
}

bool Level::isTouched(Sprite* sprite) {
    Rect bounds = sprite->getBoundingBox();

    if (bounds.containsPoint(_mousePosition)) {
        return true;
    }
    else {
        return false;
    }
}

void Level::increaseSpeed() {
    if (_speed != 550) {
        _speed = _speed + 250;
    }
}
void Level::decreaseSpeed() {
    if (_speed != 50) {
        _speed = _speed - 250;
    }
}

void Level::kill(int eeveeId) {
    Eevee* eevee = _eevings[eeveeId];
    Sprite* sprite = eevee->getSprite();
    ParticleFlower* particle = ParticleFlower::create();
    particle->setPosition(sprite->getPosition());
    particle->setDuration(0.1);
    _eevings.erase(_eevings.begin() + eeveeId);
    this->addChild(particle);
    this->removeChild(sprite);
    _killedEevings += 1;
    delete eevee;
    for (int i = 0; i < _eevings.size(); i++) {
        log("HI");
        _eevings[i]->getSprite()->getPhysicsBody()->setTag(i);
    };
}

void Level::saved(int eeveeId) {
    Eevee* eevee = _eevings[eeveeId];
    Sprite* sprite = eevee->getSprite();
    ParticleFlower* particle = ParticleFlower::create();
    particle->setPosition(sprite->getPosition());
    particle->setDuration(0.1);
    _eevings.erase(_eevings.begin() + eeveeId);
    this->addChild(particle);
    this->removeChild(sprite);
    
    _savedEevings += 1;
    delete eevee;
}

void Level::launchExplosion(int eeveeId) {
    Sprite* sprite = _eevings[eeveeId]->getSprite();

    /*PhysicsBody* physicsBody = PhysicsBody::createBox(Size(eeveeSprite->getContentSize().width / 2, eeveeSprite->getContentSize().height / 2),
        PhysicsMaterial(0.0f, 0.0f, 0.0f));*/

    ParticleExplosion* explosion = ParticleExplosion::create();
    explosion->setPosition(sprite->getPosition());
    explosion->setDuration(0.1);
    //explosion->setSpeed(50);
    //explosion->setContentSize(sprite->getContentSize() * 2);
    this->addChild(explosion);
    Rect explosionBounds = explosion->getBoundingBox();

    //Size radius = sprite->getContentSize().width / 2, eeveeSprite->getContentSize().height / 2)

    //Rect bounds = sprite->getBoundingBox();
    //Rect bigBounds = Rect(sprite->getPosition(), bounds.size * 2);

    /*ParticleFire* fire = nullptr;
    for (size_t i = 0; i < 1; i++)
    {
        fire = ParticleFire::create();
        fire->setDuration(0.1);
        this->addChild(fire);
    }*/

    kill(eeveeId);
}

void Level::spawnEevee(int number) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    visibleSize.setSize(visibleSize.width, 1500);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto edgebody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.2f, 0.1f), 3);
    auto edgenode = Node::create();
    edgenode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgenode->setPhysicsBody(edgebody);
    edgebody->setCollisionBitmask(8);
    edgebody->setContactTestBitmask(true);
    this->addChild(edgenode);

    Sprite* eeveeSprite = nullptr;
    for (size_t i = 0; i < number; i++)
    {
        cocos2d::log("eevee created");
        eeveeSprite = Sprite::create("sprites/0000.png");
        eeveeSprite->setScale(2, 2);
        eeveeSprite->setPosition(_xSpawn, _ySpawn);
        Vec2 myAnchorPoint(0.5, 0.5);
        eeveeSprite->setAnchorPoint(myAnchorPoint);

        PhysicsBody* physicsBody = PhysicsBody::createBox(Size(eeveeSprite->getContentSize().width / 2, eeveeSprite->getContentSize().height / 2),
            PhysicsMaterial(0.0f, 0.0f, 0.0f));
        physicsBody->setDynamic(true);
        physicsBody->setCollisionBitmask(1);
        physicsBody->setContactTestBitmask(true);
        physicsBody->setTag(i);
        physicsBody->setRotationEnable(false);
        physicsBody->setGravityEnable(false);

        Eevee* eevee = new Eevee(eeveeSprite, i);
        this->_eevings.push_back(eevee);
        log("%d", this->_eevings.size());

        eeveeSprite->addComponent(physicsBody);
        this->addChild(eeveeSprite);
        eevee->move();

        Hide* hide = Hide::create();
        Show* show = Show::create();
        //MoveBy* move = MoveBy::create(1, Vec2(0,-100));
        DelayTime* delay = DelayTime::create(i);
        CallFunc* callback = CallFunc::create([eevee, physicsBody]() {
            physicsBody->setGravityEnable(true);
            });
        Sequence* sequence = Sequence::create(hide, delay, show, callback, NULL);
        eeveeSprite->runAction(sequence);
    }

}

void Level::createMenu(int powers[]) {

    std::string path = "interface/";
    std::string myPowers[5] = { "pyro","aqua","volt","givre","feuille" };


    Sprite* menu = Sprite::create("interface/interface.png");
    menu->setScale(1, 1);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setPosition(0, 0);
    this->addChild(menu);


    Sprite* power = nullptr;
    Label* counter = nullptr;
    for(int i = 0; i < myPowers->size() + 1; i++)
    {
        //create level inventory
        _powersInventory[i] = powers[i];

        power = Sprite::create(path + myPowers[i] + ".png");
        power->setScale(1, 1);
        power->setAnchorPoint(Vec2::ZERO);
        power->setPosition(450 +i * 100, 50);

        counter = Label::createWithTTF(std::to_string(_powersInventory[i]), "fonts/Hansip.otf", 25);
        power->addChild(counter);

        this->addChild(power,5);
        _powers.push_back(power);
    }
 
    _reset = Sprite::create("interface/reset.png");
    _reset->setScale(0.35, 0.35);
    _reset->setAnchorPoint(Vec2::ZERO);
    _reset->setPosition(1250, 50);
    this->addChild(_reset,5);

    _fastFor = Sprite::create("interface/fastFor.png");
    _fastFor->setScale(0.35, 0.35);
    _fastFor->setAnchorPoint(Vec2::ZERO);
    _fastFor->setPosition(1350, 50);
    this->addChild(_fastFor,5);

    _slowFor = Sprite::create("interface/slowFor.png");
    _slowFor->setScale(0.35, 0.35);
    _slowFor->setAnchorPoint(Vec2::ZERO);
    _slowFor->setPosition(1450, 50);
    this->addChild(_slowFor,5);

}
void Level::createMap(TMXTiledMap* tilemap) {

    TMXObjectGroup* collisions_SOL = tilemap->getObjectGroup("collision_SOL");
    ValueVector& rectangle_array_SOL = collisions_SOL->getObjects();
    for (cocos2d::Value& rectangle_box_SOL : rectangle_array_SOL) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_SOL.asValueMap();

        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setCollisionBitmask(3);
        box->setContactTestBitmask(true);

        node->setPhysicsBody(box);

        //box->setGroup(-1);


        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node, 20);
    }

    TMXObjectGroup* collisions_MUR = tilemap->getObjectGroup("collision_MUR");
    ValueVector& rectangle_array_MUR = collisions_MUR->getObjects();
    for (cocos2d::Value& rectangle_box_MUR : rectangle_array_MUR) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_MUR.asValueMap();

        Node* node = Node::create();

        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        
        box->setContactTestBitmask(true);
        box->setCollisionBitmask(2);
        node->setPhysicsBody(box);

        //box->setGroup(-1);


        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node, 20);
    }

    TMXObjectGroup* collisions_BAR1 = tilemap->getObjectGroup("collision_BARREL_1");
    ValueVector& rectangle_array_BAR1 = collisions_BAR1->getObjects();
    for (cocos2d::Value& rectangle_box_BAR1 : rectangle_array_BAR1) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR1.asValueMap();

        Node* node = Node::create();


        // !!!!!!!!!!!!!!!!!!!!!!!!!!

        barrels.push_back(tilemap->getLayer("BARREL_1"));
        myBarrelsNode.push_back(node);
        // !!!!!!!!!!!!!!!!!!!!!!!!!!


        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setContactTestBitmask(true);
        box->setCollisionBitmask(collisionType[0]);
       

        node->setPhysicsBody(box);

        //box->setGroup(-1);


        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node, 20);
    }

    TMXObjectGroup* collisions_BAR2 = tilemap->getObjectGroup("collision_BARREL_2");
    ValueVector& rectangle_array_BAR2 = collisions_BAR2->getObjects();
    for (cocos2d::Value& rectangle_box_BAR2 : rectangle_array_BAR2) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR2.asValueMap();

        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setCollisionBitmask(collisionType[1]);
        box->setContactTestBitmask(true);

        node->setPhysicsBody(box);

        //box->setGroup(-1);


        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node, 20);
    }

    TMXObjectGroup* collisions_BAR3 = tilemap->getObjectGroup("collision_BARREL_3");
    ValueVector& rectangle_array_BAR3 = collisions_BAR3->getObjects();
    for (cocos2d::Value& rectangle_box_BAR3 : rectangle_array_BAR3) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR3.asValueMap();

        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setCollisionBitmask(collisionType[2]);
        box->setContactTestBitmask(true);
     
        node->setPhysicsBody(box);

        //box->setGroup(-1);


        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node, 20);
    }

    TMXObjectGroup* collisions_BAR4 = tilemap->getObjectGroup("collision_BARREL_4");
    ValueVector& rectangle_array_BAR4 = collisions_BAR4->getObjects();
    for (cocos2d::Value& rectangle_box_BAR4 : rectangle_array_BAR4) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR4.asValueMap();

        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setCollisionBitmask(collisionType[3]);
        box->setContactTestBitmask(true);

        node->setPhysicsBody(box);

        //box->setGroup(-1);


        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node, 20);
    }

    TMXObjectGroup* collisions_BAR5 = tilemap->getObjectGroup("collision_BARREL_5");
    ValueVector& rectangle_array_BAR5 = collisions_BAR5->getObjects();
    for (cocos2d::Value& rectangle_box_BAR5 : rectangle_array_BAR5) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR5.asValueMap();

        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setCollisionBitmask(collisionType[4]);
        box->setContactTestBitmask(true);

        node->setPhysicsBody(box);
            //box->setGroup(-1);


        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node, 20);
    }

    TMXObjectGroup* collisions_BAR6 = tilemap->getObjectGroup("collision_BARREL_6");
    if (tilemap->getObjectGroup("collision_BARREL_6") != NULL)
    {
        ValueVector& rectangle_array_BAR6 = collisions_BAR6->getObjects();
        for (cocos2d::Value& rectangle_box_BAR6 : rectangle_array_BAR6) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR6.asValueMap();

            Node* node = Node::create();
            PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
            box->setCollisionBitmask(collisionType[5]);
            box->setContactTestBitmask(true);

            node->setPhysicsBody(box);

            //box->setGroup(-1);


            node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
            node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

            box->setGravityEnable(false);
            box->setDynamic(false);

            this->addChild(node, 20);
        }
    }

    TMXObjectGroup* collisions_WIN = tilemap->getObjectGroup("WIN");
    ValueVector& rectangle_array_WIN = collisions_WIN->getObjects();
    for (cocos2d::Value& rectangle_box_WIN : rectangle_array_WIN) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_WIN.asValueMap();

        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setCollisionBitmask(7);
        box->setContactTestBitmask(true);

        node->setPhysicsBody(box);

        //box->setGroup(-1);


        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node, 20);
    }

    TMXObjectGroup* collisions_FREEZE_1 = tilemap->getObjectGroup("collision_FREEZE_1");
    if (tilemap->getObjectGroup("collision_FREEZE_1") != NULL)
    {
        freezes.push_back(tilemap->getLayer("FREEZE_1"));
        tilemap->getLayer("FREEZE_1")->setVisible(false);
        ValueVector& rectangle_array_FREEZE_1 = collisions_FREEZE_1->getObjects();

        for (cocos2d::Value& rectangle_box_FREEZE_1 : rectangle_array_FREEZE_1) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_FREEZE_1.asValueMap();

            Node* node = Node::create();
            PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
            box->setCollisionBitmask(5);
            box->setContactTestBitmask(true);
            box->setTag(0);
            node->setPhysicsBody(box);

            //box->setGroup(-1);


            node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
            node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

            box->setGravityEnable(false);
            box->setDynamic(false);

            this->addChild(node, 20);
        }
    }

    TMXObjectGroup* collisions_FREEZE_2 = tilemap->getObjectGroup("collision_FREEZE_2");
    if(tilemap->getObjectGroup("collision_FREEZE_2") != NULL)
    {
        freezes.push_back(tilemap->getLayer("FREEZE_2"));
        tilemap->getLayer("FREEZE_2")->setVisible(false);
        ValueVector& rectangle_array_FREEZE_2 = collisions_FREEZE_2->getObjects();
        for (cocos2d::Value& rectangle_box_FREEZE_2 : rectangle_array_FREEZE_2) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_FREEZE_2.asValueMap();

            Node* node = Node::create();
            PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
            box->setCollisionBitmask(5);
            box->setContactTestBitmask(true);
            box->setTag(1);
            node->setPhysicsBody(box);

            //box->setGroup(-1);


            node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
            node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

            box->setGravityEnable(false);
            box->setDynamic(false);

            this->addChild(node, 20);
        }
    }

    TMXObjectGroup* collisions_FREEZE_3 = tilemap->getObjectGroup("collision_FREEZE_3");
    if(tilemap->getObjectGroup("collision_FREEZE_3") != NULL)
    {
        freezes.push_back(tilemap->getLayer("FREEZE_3"));
        tilemap->getLayer("FREEZE_3")->setVisible(false);
        ValueVector& rectangle_array_FREEZE_3 = collisions_FREEZE_3->getObjects();
        for (cocos2d::Value& rectangle_box_FREEZE_3 : rectangle_array_FREEZE_3) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_FREEZE_3.asValueMap();
                    Node* node = Node::create();
            PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
            box->setCollisionBitmask(5);
            box->setContactTestBitmask(true);
            box->setTag(2);
            node->setPhysicsBody(box);

            //box->setGroup(-1);


            node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
            node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

            box->setGravityEnable(false);
            box->setDynamic(false);

            this->addChild(node, 20);
  
        }
    }

    TMXObjectGroup* WATER = tilemap->getObjectGroup("WATER");
    if(tilemap->getObjectGroup("WATER") != NULL)
    {
        ValueVector& rectangle_array_WATER = WATER->getObjects();
        for (cocos2d::Value& rectangle_box_WATER : rectangle_array_WATER) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_WATER.asValueMap();

            Node* node = Node::create();
            PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
            box->setCollisionBitmask(4);
            box->setContactTestBitmask(true);

            node->setPhysicsBody(box);

            //box->setGroup(-1);


            node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
            node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

            box->setGravityEnable(false);
            box->setDynamic(false);

            this->addChild(node, 20);
        }
    }

    TMXObjectGroup* VOLT = tilemap->getObjectGroup("collision_JOLTEON");
    if (tilemap->getObjectGroup("collision_JOLTEON") != NULL)
    {
        electricalDoors.push_back(tilemap->getLayer("JOLTEON"));
        ValueVector& rectangle_array_VOLT = VOLT->getObjects();
        for (cocos2d::Value& rectangle_box_VOLT : rectangle_array_VOLT) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_VOLT.asValueMap();

            Node* node = Node::create();
            PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
            box->setCollisionBitmask(3);
            box->setContactTestBitmask(true);
            electricalDoorsBod.push_back(box);
            node->setPhysicsBody(box);

            //box->setGroup(-1);


            node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
            node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

            box->setGravityEnable(false);
            box->setDynamic(false);

            this->addChild(node, 20);
        }
    }

}

bool Level::onContactBegin(PhysicsContact& contact) {
    if(contact.getShapeA() != NULL && contact.getShapeB() != NULL)
    {
        PhysicsBody* a = contact.getShapeA()->getBody();
        PhysicsBody* b = contact.getShapeB()->getBody();
        if (this->_eevings.size() == _baseEevings - _killedEevings - _savedEevings)
        {
            
            //("onContacftBegin %d %d", a->getCollisionBitmask(), b->getCollisionBitmask());

            //log("my size %d", this->_eevings.size());
            //log("my ids %d %d", this->_eevings[0]->getId(), this->_eevings[1]->getId());
            if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 2) || (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 1)) {

                //  collide avec mur
                log("je collide avec wall %d ", this->_eevings[b->getTag()]->getPas());
                this->_eevings[b->getTag()]->collide();
            }

            else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 3) || (a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 1)) {
                //pour relancer la marche après une chute
                log("je collide avec sol");
                this->_eevings[b->getTag()]->setPas(this->_eevings[b->getTag()]->getFormerPas());

                if (this->_eevings[b->getTag()]->getSkill() == 5)
                {
                    this->_eevings[b->getTag()]->setSkill(0);
                }
                return true;


            }


            //EEVEE POWERS

            else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 4) || (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 1)) {

                if (this->_eevings[b->getTag()]->getSkill() == 2) {
                    return true;
                }
                else {
                    log("die");
                    kill(b->getTag());
                }
            }

            else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 5) || (a->getCollisionBitmask() == 5 && b->getCollisionBitmask() == 1)) {

                if (this->_eevings[b->getTag()]->getSkill() == 4) {

                    Vec2 myPosition = this->_eevings[b->getTag()]->getSprite()->getPosition();

                    this->_eevings[b->getTag()]->getSprite()->setPosition(myPosition);
                    freezes[a->getTag()]->setVisible(true);
                    a->setCollisionBitmask(3);
                    a->setGroup(5);


                }
                else {
                    return false;
                }
                // if eevee glaceon -> enable collision
            }

            else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 6) || (a->getCollisionBitmask() == 6 && b->getCollisionBitmask() == 1)) {

                if (this->_eevings[b->getTag()]->getSkill() == 3) {
                    electricalDoors[a->getTag() - 1]->setVisible(false);
                    electricalDoorsBod[a->getTag() - 1]->setCollisionBitmask(1);
                }
                return false;
            }
            else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 7) || (a->getCollisionBitmask() == 7 && b->getCollisionBitmask() == 1)) {
                //dgdgd
            }

            else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 8) || (a->getCollisionBitmask() == 8 && b->getCollisionBitmask() == 1)) {

                kill(b->getTag());
            }
            else if (a->getCollisionBitmask() == b->getCollisionBitmask()) {
                //pour transpercer
                return false;
            }
            return true;
        }
    }
}



bool Level::onContactSeparate(PhysicsContact& contact) {

    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
  
   // log("onContactSeparate %d %d", contact.getShapeA()->getGroup(), contact.getShapeB()->getGroup());
    if(this->_eevings.size())
    {
  
        if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 4) || (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 1)) {
            log("je reset skill 1");
            this->_eevings[b->getTag()]->setSkill(0);
        }

        else if ((a->getCollisionBitmask() == 1 && b->getGroup() == 5) || (a->getGroup() == 5 && b->getCollisionBitmask() == 1)) {
            log("je reset skill 2");
            this->_eevings[b->getTag()]->setSkill(0);
        }
        else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 6) || (a->getCollisionBitmask() == 6 && b->getCollisionBitmask() == 1)) {
            log("je reset skill 3");
            this->_eevings[b->getTag()]->setSkill(0);
        }
        else if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 7) || (a->getCollisionBitmask() == 7 && b->getCollisionBitmask() == 1)) {
            log("je reset skill 4");
            this->_eevings[b->getTag()]->setSkill(0);
        }
    }

    return true;
}