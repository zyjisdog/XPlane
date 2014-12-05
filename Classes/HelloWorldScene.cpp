#include "HelloWorldScene.h"
#include "Chinese.h"
#include "AppMacros.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto newItem = MenuItemImage::create(
                                           "new_1.png",
                                           "new_2.png",
                                           CC_CALLBACK_1(HelloWorld::menuNewCallback, this));
    newItem->setScale(0.25f);
    newItem->setPosition(origin.x + visibleSize.width / 2,origin.y + visibleSize.height*0.2);
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                                 origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(newItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCDictionary* strings = CCDictionary::createWithContentsOfFile("Chinese.plist");
    const CCString* feijidazhan = ((CCString*)strings->objectForKey("feijidazhan"));
    auto label = LabelTTF::create(feijidazhan->getCString()/*ChineseWord("feijidazhan")*/,"fonts\\Marker Felt.ttf", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize / 2) + origin);

    // add the sprite as a child to this layer
    this->addChild(sprite);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuNewCallback(cocos2d::Ref *pSender)
{
    auto scene = GameScene::createScene();
    
    auto tr = TransitionFade::create(0.5, scene);
    
    Director::getInstance()->replaceScene(tr);
}
