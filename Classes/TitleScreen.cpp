#include "TitleScreen.h"

#include "WinScreen.h"
#include "functions.h"
USING_NS_CC;

Scene* TitleScreen::createScene()
{
    Scene* scene = TitleScreen::create();
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
    if (!Scene::init())
    {
        return false;
    }

    this->start = Label::createWithTTF("Start", "fonts/Hansip.otf", 25);
    start->setTextColor(Color4B::WHITE);
    start->setPosition(100, 200);
    //_labels.push_back(start);
    this->quit = Label::createWithTTF("Quit", "fonts/Hansip.otf", 25);
    quit->setTextColor(Color4B::WHITE);
    quit->setPosition(100, 135);
    //_labels.push_back(quit);

    _menuScreen = Sprite::create("menuScreen.png");
  
    _menuScreen->setAnchorPoint(Vec2(0,0));
    _menuScreen->setPosition(0, 0);

    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(TitleScreen::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->addChild(_menuScreen, 0);
    this->addChild(start, 1);
    this->addChild(quit, 1);

    return true;
}

void TitleScreen::MouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;
    int button = int(e->getMouseButton());
  
    Vec2 mousePosition = e->getLocationInView();
    Rect menuBounds = _menuScreen->getBoundingBox();
    Rect startBounds = this->start->getBoundingBox();
    Rect quitBounds = this->quit->getBoundingBox();
   
    if (startBounds.containsPoint(mousePosition)) {
        cocos2d::log("menu touched");
        auto director = Director::getInstance();
        auto scene = WinScreen::createScene();
        director->replaceScene(scene);
    }
    if (quitBounds.containsPoint(mousePosition)) {
   
        auto director = Director::getInstance();
        director->end();
    }
}