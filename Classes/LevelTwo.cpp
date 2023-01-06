#include "LevelTwo.h"

Scene* LevelTwo::createScene() {
    Scene* scene = LevelTwo::createWithPhysics();
    scene = LevelTwo::create();
    scene->getPhysicsWorld()->setGravity(Vect(0, -200));
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

    if (_eevings.size() != 0) {
        _eevings.clear();
    }

     _currentLevel = 0;
    
    collisionType.clear();
    collisionType.push_back(2);
    collisionType.push_back(2);
    collisionType.push_back(3);
    collisionType.push_back(3);
    collisionType.push_back(2);
    collisionType.push_back(2);

    plasma = Sprite::create("plasma.png");
    plasma->setAnchorPoint(Vec2::ZERO);
    plasma->setScale(0.10, 0.10);
    plasma->setPosition(954, 480);

    PhysicsBody* antennaP = PhysicsBody::createBox(Size(plasma->getContentSize().width / 2, plasma->getContentSize().height / 2),
        PhysicsMaterial(0.0f, 0.0f, 0.0f));

    antennaP->setGravityEnable(false);
    antennaP->setDynamic(false);
    antennaP->setTag(1);
    antennaP->setContactTestBitmask(true);
    antennaP->setCollisionBitmask(6);
    plasma->setPhysicsBody(antennaP);

    this->addChild(plasma, 3);
    _xSpawn = 835;
    _ySpawn = 1050;

    auto _tilemap = TMXTiledMap::create("EevingsMap1.tmx");
    this->addChild(_tilemap);
    createMap(_tilemap);
    int inventory[5] = { 2, 4, 4, 4, 10};
    createMenu(inventory);

    _baseEevings = 10;
    _eevings.clear();
    spawnEevee(_baseEevings);

    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Level::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(Level::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);

    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(LevelTwo::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate();

    return true;
}

void LevelTwo::MouseUp(Event* event) {
    handleEvent(event);
}
