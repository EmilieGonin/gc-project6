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
    collisionType.clear();
    collisionType.push_back(2);
    collisionType.push_back(2);
    collisionType.push_back(3);
    collisionType.push_back(3);
    collisionType.push_back(2);
    collisionType.push_back(2);


    _xSpawn = 400;
    _ySpawn = 1000;



    auto _tilemap = TMXTiledMap::create("EevingsMap1.tmx");
    this->addChild(_tilemap);
    createMap(_tilemap);
    int inventory[5] = { 2, 2, 2, 2, 2};
    createMenu(inventory);

    _baseEevings = 1;
    spawnEevee(_baseEevings);

    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Level::onContactBegin, this);
    //contactListener->onContactSeparate = CC_CALLBACK_1(Level::onContactSeparate, this);
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



void LevelTwo::MouseUp(Event* event) {
    handleEvent(event);
}
