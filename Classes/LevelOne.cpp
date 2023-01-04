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


    Sprite* menu = Sprite::create("interface/interface.png");
    menu->setScale(1,1);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setPosition(0, 0);

    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(LevelOne::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    spawnEevee();
    this->scheduleUpdate();

    return true;    
}

void LevelOne::spawnEevee() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto edgebody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.0f, 0.2f, 0.1f), 3);
    auto edgenode = Node::create();
    edgenode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgenode->setPhysicsBody(edgebody);
    this->addChild(edgenode);
        
    Sprite* eeveeSprite = nullptr;
    for (size_t i = 0; i < 3; i++)
    {
        cocos2d::log("eevee created");
        eeveeSprite = Sprite::create("sprites/0000.png");
        eeveeSprite->setScale(2, 2);
        eeveeSprite->setPosition(100, 100);
        Vec2 myAnchorPoint(0.5, 0.5);
        eeveeSprite->setAnchorPoint(myAnchorPoint);
        
        PhysicsBody* physicsBody = PhysicsBody::createCircle(eeveeSprite->getContentSize().height / 2);
        physicsBody->setDynamic(true);
        physicsBody->setGravityEnable(true);

        Eevee* eevee = new Eevee(eeveeSprite, i + 1);
        this->_eevings.push_back(eevee);

        eeveeSprite->addComponent(physicsBody);
        this->addChild(eeveeSprite);
        eevee->move();
    }
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