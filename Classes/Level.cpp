#include "Level.h"

void Level::update(float delta) {
    for (size_t i = 0; i < this->_eevings.size(); i++)
    {
        Eevee* eevee = this->_eevings[i];
        eevee->update(delta, _speed);
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
                    if (_skillSelected == 5) {
                        
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
    delete eevee;
}

void Level::spawnEevee(int number) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    visibleSize.setSize(visibleSize.width, 1500);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto edgebody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.2f, 0.1f), 3);
    auto edgenode = Node::create();
    edgenode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgenode->setPhysicsBody(edgebody);
    edgebody->setCollisionBitmask(2);
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
        ValueVector& rectangle_array_FREEZE_1 = collisions_FREEZE_1->getObjects();

        for (cocos2d::Value& rectangle_box_FREEZE_1 : rectangle_array_FREEZE_1) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_FREEZE_1.asValueMap();

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
    }

    TMXObjectGroup* collisions_FREEZE_2 = tilemap->getObjectGroup("collision_FREEZE_2");
    if(tilemap->getObjectGroup("collision_FREEZE_2") != NULL)
    {
        ValueVector& rectangle_array_FREEZE_2 = collisions_FREEZE_2->getObjects();
        for (cocos2d::Value& rectangle_box_FREEZE_2 : rectangle_array_FREEZE_2) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_FREEZE_2.asValueMap();

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
    }

    TMXObjectGroup* collisions_FREEZE_3 = tilemap->getObjectGroup("collision_FREEZE_3");
    if(tilemap->getObjectGroup("collision_FREEZE_3") != NULL)
    {
        ValueVector& rectangle_array_FREEZE_3 = collisions_FREEZE_3->getObjects();
        for (cocos2d::Value& rectangle_box_FREEZE_3 : rectangle_array_FREEZE_3) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_FREEZE_3.asValueMap();
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
    }

    TMXObjectGroup* WATER = tilemap->getObjectGroup("WATER");
    if(tilemap->getObjectGroup("WATER") != NULL)
    {
        ValueVector& rectangle_array_WATER = WATER->getObjects();
        for (cocos2d::Value& rectangle_box_WATER : rectangle_array_WATER) {
            cocos2d::ValueMap rectangle_box_properties = rectangle_box_WATER.asValueMap();

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
    }


}

bool Level::onContactBegin(PhysicsContact& contact) {


    //("onContacftBegin %d %d", contact.getShapeA()->getBody()->getCollisionBitmask(), contact.getShapeB()->getBody()->getCollisionBitmask());

    //log("my size %d", this->_eevings.size());
    //log("my ids %d %d", this->_eevings[0]->getId(), this->_eevings[1]->getId());
    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 2) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 2 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        //  collide avec mur
        log("je collide avec wall %d ", this->_eevings[contact.getShapeB()->getBody()->getTag()]->getPas());
        this->_eevings[contact.getShapeB()->getBody()->getTag()]->collide();
    }

    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 3) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 3 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {
        //pour relancer la marche après une chute
     
            this->_eevings[contact.getShapeB()->getBody()->getTag()]->setPas(this->_eevings[contact.getShapeB()->getBody()->getTag()]->getFormerPas());

            this->_eevings[contact.getShapeB()->getBody()->getTag()]->setSkill(0);
        
    }


    //EEVEE POWERS

    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 4) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 4 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        //  collide avec water pour swim
        // if eevee swimmeaon -> walk else die
    }
    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 5) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 5 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        //  collide avec "water but ice power
        // if eevee glaceon -> enable collision
    }
    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 6) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 6 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        //  collide avec lever volteon
        // if eevee == volteon -> activate lever
    }
    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 7) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 7 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        //  collide avec door 
        //code pour detruire eevee et pour augmenter _savedEevings
    }



    if (contact.getShapeA()->getBody()->getCollisionBitmask() == contact.getShapeB()->getBody()->getCollisionBitmask()) {
        //pour transpercer
        return false;
    }
    return true;
}


bool Level::onContactSeparate(PhysicsContact& contact) {
   // log("onContactSeparate %d %d", contact.getShapeA()->getGroup(), contact.getShapeB()->getGroup());

    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 3) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 3 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {
        this->_eevings[contact.getShapeB()->getBody()->getTag()]->setPas(0);

        //stop moving wehn falling
    }

    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 4) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 4 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        this->_eevings[contact.getShapeB()->getBody()->getTag()]->setSkill(0);
    }
    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 5) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 5 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        this->_eevings[contact.getShapeB()->getBody()->getTag()]->setSkill(0);
    }
    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 6) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 6 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        this->_eevings[contact.getShapeB()->getBody()->getTag()]->setSkill(0);
    }
    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 7) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 7 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        this->_eevings[contact.getShapeB()->getBody()->getTag()]->setSkill(0);
    }

    return true;
}