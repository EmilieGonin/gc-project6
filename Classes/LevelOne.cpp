#include "LevelOne.h"
#include "functions.h"
USING_NS_CC;



Scene* LevelOne::createScene() {
    Scene* scene = Scene::create();
    LevelOne* layer = LevelOne::create();
    scene->addChild(layer);

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
    if ( !Scene::init() )
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


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    spawnEevee();
    this->scheduleUpdate();

    return true;    
}

void LevelOne::spawnEevee() {
    Sprite* eeveeSprite = nullptr;
    for (size_t i = 0; i < 3; i++)
    {
        cocos2d::log("eevee created");
        eeveeSprite = Sprite::create("sprites/character.png");
        eeveeSprite->setScale(2, 2);
        eeveeSprite->setPosition(100, 100);
        Vec2 myAnchorPoint(0.5, 0.5);
        eeveeSprite->setAnchorPoint(myAnchorPoint);

        Eevee* eevee = new Eevee(eeveeSprite, i + 1);
        this->_eevings.push_back(eevee);

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

void LevelOne::MouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;
    int button = int(e->getMouseButton());
    Vec2 mousePosition = e->getLocationInView();

    for (size_t i = 0; i < this->_eevings.size(); i++)
    {
        Rect eeveeBounds = _eevings[i]->getSprite()->getBoundingBox();

        if (eeveeBounds.containsPoint(mousePosition)) {
            cocos2d::log("eevee touched :");
            cocos2d::log(std::to_string(this->_eevings[i]->getId()).c_str());
        }
    }
}