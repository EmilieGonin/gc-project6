#include "TitleScreen.h"
#include "LevelOne.h"
#include "functions.h"
USING_NS_CC;

Scene* TitleScreen::createScene()
{
    Scene* scene = Scene::create();
    TitleScreen* layer = TitleScreen::create();
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
bool TitleScreen::init()
{
    //////////////////////////////
    // 1. super init first
      //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }


    _menuScreen = Sprite::create("menuScreen.png");
    _menuScreen->setScale(0.65, 0.65);
    _menuScreen->setAnchorPoint(Vec2::ZERO);
    _menuScreen->setPosition(0, 0);

    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(TitleScreen::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->addChild(_menuScreen, 0);

    return true;
}

void TitleScreen::MouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;
    int button = int(e->getMouseButton());
  
    Vec2 mousePosition = e->getLocationInView();
    Rect menuBounds = _menuScreen->getBoundingBox();
   
    if (menuBounds.containsPoint(mousePosition)) {
        cocos2d::log("menu touched");
        auto director = Director::getInstance();
        auto scene = LevelOne::createScene();
        director->replaceScene(scene);
    }

  
}