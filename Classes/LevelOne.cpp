#include "LevelOne.h"

Scene* LevelOne::createScene() {
    Scene* scene = LevelOne::createWithPhysics();
    scene = LevelOne::create();
    scene->getPhysicsWorld()->setGravity(Vect(0, -750));
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LevelOneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LevelOne::init()
{
    _currentLevel = 0;
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    if (_eevings.size() != 0) {
        _eevings.clear();
    }

    collisionType.clear();
    collisionType.push_back(1);
    collisionType.push_back(1);
    collisionType.push_back(1);
    collisionType.push_back(3);
    collisionType.push_back(2);

    _xSpawn = 550;
    _ySpawn = 950;

    auto _tilemap = TMXTiledMap::create("TuTo.tmx");
    this->addChild(_tilemap);
    createMap(_tilemap);
    int inventory[5] = { 2, 0, 0, 0, 1 };
    createMenu(inventory);

    _baseEevings = 5;
    _eevings.clear();
    spawnEevee(_baseEevings);

    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LevelOne::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(LevelOne::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);
    
    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(LevelOne::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
 
    this->scheduleUpdate();

    return true;    
}

void LevelOne::MouseUp(Event* event) {
    handleEvent(event);
}