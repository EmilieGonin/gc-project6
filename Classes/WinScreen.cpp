#include "WinScreen.h"

//Scenes
#include "LevelOne.h"
#include "LevelTwo.h"
#include "functions.h"

int savedEeveings, baseEevings, currentLevel;

Scene* WinScreen::createScene(int savedEevingss, int BaseEevingss)
{
   savedEeveings = savedEevingss;
   baseEevings = BaseEevingss;

   Scene* scene = WinScreen::create();
   return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LevelOneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool WinScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    log("%d", this->_savedEevings);
   
    _menuScreen = Sprite::create("winScreen.png");
    _menuScreen->setAnchorPoint(Vec2::ZERO);
    _menuScreen->setPosition(0, 0);
    
    _next = Sprite::create("interface/next.png");
    _next->setAnchorPoint(Vec2::ZERO);
    _next->setScale(0.85,0.85);
    _next->setPosition(750, 50);

    _restart = Sprite::create("interface/reset.png");
    _restart->setAnchorPoint(Vec2::ZERO);
    _restart->setScale(0.45,0.45);
    _restart->setPosition(650, 110);

    Label * savedEevingsText = Label::createWithTTF("Eevings saved : x "+ std::to_string(savedEeveings), "fonts/Hansip.otf", 25);
    savedEevingsText->setTextColor(Color4B::WHITE);
    savedEevingsText->setPosition(770, 700);
    savedEevingsText->setScale(2, 2);

    Label * deadEevingsText = Label::createWithTTF("Poor dead Eevings : x" + std::to_string(baseEevings - savedEeveings), "fonts/Hansip.otf", 25);
    deadEevingsText->setTextColor(Color4B::WHITE);
    deadEevingsText->setPosition(830, 550);
    deadEevingsText->setScale(2, 2);

    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(WinScreen::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->addChild(_menuScreen, 0);
    this->addChild(savedEevingsText, 0);
    this->addChild(deadEevingsText, 0);
    this->addChild(_next, 0);
    this->addChild(_restart, 0);

    return true;
}

void WinScreen::MouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;
    int button = int(e->getMouseButton());

    Vec2 mousePosition = e->getLocationInView();
    Rect menuBounds = _menuScreen->getBoundingBox();
    Rect nextBounds = _next->getBoundingBox();
    Rect restartBounds = _restart->getBoundingBox();
 
    if (nextBounds.containsPoint(mousePosition)) {
        cocos2d::log("menu touched");
        auto director = Director::getInstance();
        auto scene = LevelTwo::createScene();
        director->replaceScene(scene);
    }
    else if (restartBounds.containsPoint(mousePosition)) {
        cocos2d::log("menu touched");
        auto director = Director::getInstance();
        auto scene = LevelOne::createScene();
        director->replaceScene(scene);
    }
}