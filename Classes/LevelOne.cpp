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


    auto map = TMXTiledMap::create("Map1.tmx");
    this->addChild(map, 0, 99);
    spawnEevee();

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

void LevelOne::spawnEevee() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    visibleSize.setSize(visibleSize.width, 1500);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto edgebody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.2f, 0.1f), 3);
    auto edgenode = Node::create();
    edgenode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4+ origin.y));
    edgenode->setPhysicsBody(edgebody);
    edgebody->setCollisionBitmask(2);
    edgebody->setContactTestBitmask(true);


    visibleSize.setSize(1500, visibleSize.height);
    auto edgebody2 = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.0f, 0.1f), 3);
    auto edgenode2 = Node::create();
    edgenode2->setPosition(Point(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
    edgenode2->setPhysicsBody(edgebody2);
    edgebody2->setCollisionBitmask(3);
    edgebody2->setContactTestBitmask(true);
    

    this->addChild(edgenode);
    this->addChild(edgenode2);
        
    Sprite* eeveeSprite = nullptr;
    for (size_t i = 0; i < 7; i++)
    {
        cocos2d::log("eevee created");
        eeveeSprite = Sprite::create("sprites/0000.png");
        eeveeSprite->setScale(2, 2);
        eeveeSprite->setPosition(100 + i * 50, 100);
        Vec2 myAnchorPoint(0.5, 0.5);
        eeveeSprite->setAnchorPoint(myAnchorPoint);
        
        PhysicsBody* physicsBody = PhysicsBody::createBox(Size(eeveeSprite->getContentSize().width, eeveeSprite->getContentSize().height),
            PhysicsMaterial(0.0f, 0.0f, 0.0f));
        physicsBody->setDynamic(true);
        physicsBody->setCollisionBitmask(1);
        physicsBody->setContactTestBitmask(true);
        physicsBody->setTag(i);
        
        
        

        physicsBody->setGravityEnable(true);

        Eevee* eevee = new Eevee(eeveeSprite, i );
        this->_eevings.push_back(eevee);
        log("%d", this->_eevings.size());

        eeveeSprite->addComponent(physicsBody);
        this->addChild(eeveeSprite);
        eevee->move();
    }
    
}


void LevelOne::update(float delta) {
    for (size_t i = 0; i < this->_eevings.size(); i++)
    {
        Eevee* eevee = this->_eevings[i];
        eevee->update(delta);
    }
}

bool LevelOne::onContactBegin(PhysicsContact& contact) {
    

    //("onContacftBegin %d %d", contact.getShapeA()->getBody()->getCollisionBitmask(), contact.getShapeB()->getBody()->getCollisionBitmask());
   
    log("my size %d", this->_eevings.size());
    log("my ids %d %d", this->_eevings[0]->getId(), this->_eevings[1]->getId());
    if ((contact.getShapeA()->getBody()->getCollisionBitmask() == 1 && contact.getShapeB()->getBody()->getCollisionBitmask() == 2) || (contact.getShapeA()->getBody()->getCollisionBitmask() == 2 && contact.getShapeB()->getBody()->getCollisionBitmask() == 1)) {
        if (this->_eevings.size() == 7) {
            {
                this->_eevings[contact.getShapeB()->getBody()->getTag()]->collide();
            }
        }
    }
        if (contact.getShapeA()->getBody()->getCollisionBitmask() == contact.getShapeB()->getBody()->getCollisionBitmask()) {
            return false;
        }
        return true;
    }


bool LevelOne::onContactSeparate(PhysicsContact& contact) {
    log("onContactSeparate %d %d", contact.getShapeA()->getGroup(), contact.getShapeB()->getGroup());
    return true;
}


void LevelOne::MouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;
    int button = int(e->getMouseButton());
    Vec2 mousePosition = e->getLocationInView();

    for (size_t i = 0; i < this->_eevings.size(); i++)
    {

        Eevee* eevee = this->_eevings[i];
        if (eevee->isTouched(mousePosition)) {
            //

        }
    }
}