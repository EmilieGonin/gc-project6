#include "LevelOne.h"
#include "functions.h"
USING_NS_CC;

Scene* LevelOne::createScene() {
    Scene* scene = LevelOne::createWithPhysics();
    scene = LevelOne::create();
    scene->getPhysicsWorld()->setGravity(Vect(0, -200));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    //powers inventory
    _powers[0] = 2;

    auto _tilemap = TMXTiledMap::create("TuTo.tmx");
    this->addChild(_tilemap);
    createMap(_tilemap);

    /*_tilemap = new TMXTiledMap();
    _tilemap->initWithTMXFile("Map1.tmx");
    _background = _tilemap->getLayer("background");
    _collidable = _tilemap->getLayer("collidable");
    _collidable->setVisible(false);
    _collision = _tilemap->getObjectGroup("collision");
    
    this->addChild(_tilemap);*/

    

    spawnEevee(10);

    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LevelOne::onContactBegin, this);
    //contactListener->onContactSeparate = CC_CALLBACK_1(LevelOne::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);
    
    Sprite* menu = Sprite::create("interface/interface.png");
    menu->setScale(1,1);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setPosition(0, 0);

    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(LevelOne::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
 
    this->scheduleUpdate();

    return true;    
}

bool LevelOne::onContactBegin(PhysicsContact& contact) {
    

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


bool LevelOne::onContactSeparate(PhysicsContact& contact) {
    log("onContactSeparate %d %d", contact.getShapeA()->getGroup(), contact.getShapeB()->getGroup());

    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 3) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 3 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {
        this->_eevings[contact.getShapeB()->getBody()->getTag()]->setPas(this->_eevings[contact.getShapeB()->getBody()->getTag()]->getFormerPas());
       
    }
    return true;
}


void LevelOne::MouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;
    int button = int(e->getMouseButton());
    Vec2 mousePosition = e->getLocationInView();
    int skill = 2; //Temp skill, need to get it dynamically

    for (size_t i = 0; i < this->_eevings.size(); i++)
    {
        Eevee* eevee = this->_eevings[i];
        if (eevee->isTouched(mousePosition)) {
            increaseSpeed(); //debug only
        }

        if (eevee->isTouched(mousePosition) && skill) {
            if (_powers[skill - 1]) {
                eevee->setSkill(skill);
                _powers[skill - 1]--;
            }
            else {
                cocos2d::log("power not available");
            }
        }
    }
}