#include "About.h"
#include "AppMacros.h"
#include "HelloWorldScene.h"
#include "Chinese.h"
USING_NS_CC;


Scene* About::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	About *layer = About::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool About::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"SpookyPeas.png",
		"Pea.png",
		CC_CALLBACK_1(About::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height*0.2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

    CCDictionary* strings = CCDictionary::createWithContentsOfFile("Chinese.plist");
    const CCString* zuozhe = ((CCString*)strings->objectForKey("zuozhe"));
	auto label1 = LabelTTF::create(zuozhe->getCString()/*ChineseWord("zuozhe") + ":" + zhangyunjin->getCString()
    ChineseWord("zhangyunjin")*/, "fonts\\Marker Felt.ttf", TITLE_FONT_SIZE);

	// position the label on the center of the screen
	label1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label1->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label1, 1);

	// add "About" splash screen" 创建一个精灵
    const CCString* xuehao = ((CCString*)strings->objectForKey("xuehao"));
	auto label2 = LabelTTF::create(xuehao->getCString()/*ChineseWord("xuehao") + ":2012226010020"*/, "fonts\\Marker Felt.ttf", TITLE_FONT_SIZE);

	// position the sprite on the center of the screen 设置精灵的位置
	label2->setPosition(Vec2(visibleSize / 2) + origin);

	// add the sprite as a child to this layer 把精灵添加到layer
	this->addChild(label2);

	return true;
}

void About::menuCloseCallback(Ref* sender)
{
	//场景切换到游戏场景
	auto scene = HelloWorld::createScene();

	//增加场景特效
	auto tr = TransitionFade::create(0.5, scene);
	//场景切换
	Director::getInstance()->replaceScene(tr);
}

