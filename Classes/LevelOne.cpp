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

    this->_eevee = new Eevee;


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

 
    this->_eevee->move();
    this->addChild(this->_eevee->getSprite(), 0);
    this->addChild(menu, 0);

    this->scheduleUpdate();

    return true;    
}   

void LevelOne::update(float delta) {

    auto position = _eevee->getSprite()->getPosition();
    position.x -= this->pas * delta;
    if (position.x < this->_eevee->getSprite()->getContentSize().width * 0.5 || position.x > Director::getInstance()->getWinSize().width - (_eevee->getSprite()->getBoundingBox().size.width) + this->_eevee->getSprite()->getContentSize().width * 0.5)
    {
        OutputDebugStringA("je collide");
        _eevee->collide();
        this->pas *= -1;
    }
    _eevee->getSprite()->setPosition(position);
}

void LevelOne::MouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;
    int button = int(e->getMouseButton());


    Rect eeveeBounds = _eevee->getSprite()->getBoundingBox();
    Vec2 mousePosition = e->getLocationInView();

    if (eeveeBounds.containsPoint(mousePosition)) {
        cocos2d::log("eevee touched");
        if (_eevee->getSkill()) {
            cocos2d::log("skill selected");
        }
    }
}