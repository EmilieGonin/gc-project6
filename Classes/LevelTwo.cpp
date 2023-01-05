#include "LevelTwo.h"

Scene* LevelTwo::createScene() {
    Scene* scene = LevelTwo::createWithPhysics();
    scene = LevelTwo::create();
    scene->getPhysicsWorld()->setGravity(Vect(0, -200));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LevelOneScene.cpp\n");
}

bool LevelTwo::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    //powers inventory
    _powersInventory[0] = 2;

    auto _tilemap = TMXTiledMap::create("EevingsMap1.tmx");
    this->addChild(_tilemap);
    createMap(_tilemap);
    createMenu();

    _baseEevings = 10;
    spawnEevee(_baseEevings);

    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LevelTwo::onContactBegin, this);
    //contactListener->onContactSeparate = CC_CALLBACK_1(LevelOne::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);

    Sprite* menu = Sprite::create("interface/interface.png");
    menu->setScale(1, 1);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setPosition(0, 0);

    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(LevelTwo::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate();

    return true;
}

bool LevelTwo::onContactBegin(PhysicsContact& contact) {


    //("onContacftBegin %d %d", contact.getShapeA()->getBody()->getCollisionBitmask(), contact.getShapeB()->getBody()->getCollisionBitmask());

    //log("my size %d", this->_eevings.size());
    //log("my ids %d %d", this->_eevings[0]->getId(), this->_eevings[1]->getId());
    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 2) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 2 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {


        this->_eevings[contact.getShapeB()->getBody()->getTag()]->collide();
    }

    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 3) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 3 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {

        this->_eevings[contact.getShapeB()->getBody()->getTag()]->setPas(1);

    }
    if (contact.getShapeA()->getBody()->getCollisionBitmask() == contact.getShapeB()->getBody()->getCollisionBitmask()) {
        return false;
    }
    return true;
}

bool LevelTwo::onContactSeparate(PhysicsContact& contact) {
    log("onContactSeparate %d %d", contact.getShapeA()->getGroup(), contact.getShapeB()->getGroup());

    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 3) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 3 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {
        this->_eevings[contact.getShapeB()->getBody()->getTag()]->setPas(this->_eevings[contact.getShapeB()->getBody()->getTag()]->getFormerPas());

    }
    return true;
}


void LevelTwo::MouseUp(Event* event) {
    handleEvent(event);
}
