#include "Level.h"

void Level::update(float delta) {
    for (size_t i = 0; i < this->_eevings.size(); i++)
    {
        Eevee* eevee = this->_eevings[i];
        eevee->update(delta, _speed);
    }

    if (_powers.size() && _skillSelected) {
        for (size_t i = 0; i < _powers.size(); i++)
        {
            if (i == _skillSelected - 1) {
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

            if (isTouched(eevee->getSprite()) && _skillSelected) {
                if (_powersInventory[_skillSelected - 1]) {
                    eevee->setSkill(_skillSelected);
                    _powersInventory[_skillSelected - 1]--;
                    _skillSelected = 0;
                }
                else {
                    cocos2d::log("power not available");
                }
            }
        }
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
        eeveeSprite->setPosition(550, 950);
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

void Level::createMenu() {

    std::string path = "interface/";
    std::string myPowers[5] = { "pyro","feuille","givre","aqua","volt" };


    Sprite* menu = Sprite::create("interface/interface.png");
    menu->setScale(1, 1);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setPosition(0, 0);
    this->addChild(menu);


    Sprite* power = nullptr;
    for(int i = 0; i < 5 ; i++)
    {


        power = Sprite::create(path + myPowers[i] + ".png");
        power->setScale(1, 1);
        power->setAnchorPoint(Vec2::ZERO);
        power->setPosition(450 +i * 100, 50);
        this->addChild(power,5);
        _powers.push_back(power);
    }
 
    _reset = Sprite::create("interface/reset.png");
    _reset->setScale(0.35, 0.35);
    _reset->setAnchorPoint(Vec2::ZERO);
    _reset->setPosition(1250, 50);
    this->addChild(_reset,5);

    _fastFor = Sprite::create("interface/reset.png");
    _fastFor->setScale(0.35, 0.35);
    _fastFor->setAnchorPoint(Vec2::ZERO);
    _fastFor->setPosition(1350, 50);
    this->addChild(_fastFor,5);

    _slowFor = Sprite::create("interface/reset.png");
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
        box->setCollisionBitmask(8);
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
        box->setCollisionBitmask(1);
        box->setContactTestBitmask(true);

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
        box->setCollisionBitmask(1);
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

    TMXObjectGroup* collisions_BAR4 = tilemap->getObjectGroup("collision_BARREL_4");
    ValueVector& rectangle_array_BAR4 = collisions_BAR4->getObjects();
    for (cocos2d::Value& rectangle_box_BAR4 : rectangle_array_BAR4) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR4.asValueMap();

        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setCollisionBitmask(1);
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
        box->setCollisionBitmask(1);
        box->setContactTestBitmask(true);

        node->setPhysicsBody(box);

        //box->setGroup(-1);


        node->setPositionX(rectangle_box_properties["x"].asInt() + rectangle_box_properties["width"].asInt() / 2);
        node->setPositionY(rectangle_box_properties["y"].asInt() + rectangle_box_properties["height"].asInt() / 2);

        box->setGravityEnable(false);
        box->setDynamic(false);

        this->addChild(node, 20);
    }

    TMXObjectGroup* collisions_WIN = tilemap->getObjectGroup("WIN");
    ValueVector& rectangle_array_WIN = collisions_WIN->getObjects();
    for (cocos2d::Value& rectangle_box_WIN : rectangle_array_WIN) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_WIN.asValueMap();

        Node* node = Node::create();
        PhysicsBody* box = PhysicsBody::createEdgeBox(Size(rectangle_box_properties["width"].asInt(), rectangle_box_properties["height"].asInt()));
        box->setCollisionBitmask(2);
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