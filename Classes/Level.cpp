#include "Level.h"

void Level::update(float delta) {
    for (size_t i = 0; i < this->_eevings.size(); i++)
    {
        Eevee* eevee = this->_eevings[i];
        eevee->update(delta, _speed);
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

    TMXObjectGroup* collisions_BAR1 = tilemap->getObjectGroup("collision_BARREL_1");
    ValueVector& rectangle_array_BAR1 = collisions_BAR1->getObjects();
    for (cocos2d::Value& rectangle_box_BAR1 : rectangle_array_BAR1) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR1.asValueMap();

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

    TMXObjectGroup* collisions_BAR2 = tilemap->getObjectGroup("collision_BARREL_2");
    ValueVector& rectangle_array_BAR2 = collisions_BAR2->getObjects();
    for (cocos2d::Value& rectangle_box_BAR2 : rectangle_array_BAR2) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR2.asValueMap();

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

    TMXObjectGroup* collisions_BAR3 = tilemap->getObjectGroup("collision_BARREL_3");
    ValueVector& rectangle_array_BAR3 = collisions_BAR3->getObjects();
    for (cocos2d::Value& rectangle_box_BAR3 : rectangle_array_BAR3) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR3.asValueMap();

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

    TMXObjectGroup* collisions_BAR4 = tilemap->getObjectGroup("collision_BARREL_4");
    ValueVector& rectangle_array_BAR4 = collisions_BAR4->getObjects();
    for (cocos2d::Value& rectangle_box_BAR4 : rectangle_array_BAR4) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR4.asValueMap();

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

    TMXObjectGroup* collisions_BAR5 = tilemap->getObjectGroup("collision_BARREL_5");
    ValueVector& rectangle_array_BAR5 = collisions_BAR5->getObjects();
    for (cocos2d::Value& rectangle_box_BAR5 : rectangle_array_BAR5) {
        cocos2d::ValueMap rectangle_box_properties = rectangle_box_BAR5.asValueMap();

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