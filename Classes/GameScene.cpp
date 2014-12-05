//
//  GameScene.cpp
//  PlaneX
//
//  Created by CloudL on 14/11/23.
//
//

#include "GameScene.h"
#include "AppMacros.h"
#include "About.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    GameScene *layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    this->setTouchEnabled(true);//可触摸点击
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    //随机加载背景图片
    char buff1[16],buff2[16];
    int id = getRand(1, 5);
    sprintf(buff1, "img_bg_%d.jpg", id);
    sprintf(buff2, "img_bg_%d.jpg", id);
    auto background1 = Sprite::create(buff1);
    auto background2 = Sprite::create(buff2);
    background1->setPosition(Point(background1->getContentSize().width / 2 + origin.x,
                                   background1->getContentSize().height / 2 + origin.y));
    background2->setPosition(Point(background2->getContentSize().width / 2 + origin.x,
                                   background2->getContentSize().height / 2 + origin.y + background2->getContentSize().height));
    this->addChild(background1, 0, MAP_1_Tag);
    this->addChild(background2, 0, MAP_2_Tag);
    return true;
}

int GameScene::getRand(int start, int end)
{
//    struct timeval tv;
//    gettimeofday(&tv, NULL);
//    unsigned long int rand_seed = tv.tv_sec * 1000 + tv.tv_sec / 1000;
    srand(unsigned(time(NULL)));
    float i = CCRANDOM_0_1() * (end - start + 1) + start;
    return (int)i;
}

void GameScene::onEnterTransitionDidFinish()
{
    planeLayer = PlaneLayer::create();
    this->addChild(planeLayer);
    
    bulletSprite = BulletSprite::create();
    this->addChild(bulletSprite);
    
    enemyLayer = EnemyLayer::create();
    this->addChild(enemyLayer);
    
    //设置每帧都调用gameUpdate函数
    this->schedule(schedule_selector(GameScene::gameUpdate));
    
    //添加menu,设置回调函数
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                                 origin.y + closeItem->getContentSize().height / 2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
}

//menu回调函数
void GameScene::menuCloseCallback(cocos2d::Ref *pSender)
{
    auto scene = About::createScene();
    
    auto tr = TransitionFade::create(0.5f, scene);
    
    Director::getInstance()->replaceScene(tr);
}

//子弹和敌机碰撞检测函数
bool GameScene::bulletCollisionEnemy(cocos2d::Sprite *pBullet)
{
    //遍历所有敌机,看子弹是否和敌机的包装矩形有重叠
    for (auto& eEnemy : enemyLayer->vecEnemy) {
        EnemySprite* pEnemySprite = (EnemySprite*)eEnemy;
        //判断矩形是否有重叠
        if (pBullet->boundingBox().intersectsRect(pEnemySprite->getBoundingBox())) {
            if (1 == pEnemySprite->getLife()) {
                pEnemySprite->loseLife();
                enemyLayer->blowUpEnemy(pEnemySprite);
            } else {
                pEnemySprite->loseLife();
            }
            bulletSprite->removeBullet(pBullet);
            return true;
        }
    }
    
    return false;
}



//在每帧都进行游戏逻辑检测,检测子弹与敌机/主角与飞机是否有碰撞
void GameScene::gameUpdate(float dt)
{
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* tempMap1 = (Sprite*)this->getChildByTag(MAP_1_Tag);
    Sprite* tempMap2 = (Sprite*)this->getChildByTag(MAP_2_Tag);
    
    tempMap1->setPositionY(tempMap1->getPositionY() - 5);
    tempMap2->setPositionY(tempMap2->getPositionY() - 5);
    
    if (tempMap1->getPositionY() + tempMap1->getContentSize().height / 2 <= origin.y) {
        float offset = tempMap1->getPositionY() + tempMap1->getContentSize().height / 2 - origin.y;
        tempMap1->setPosition(Point(tempMap1->getContentSize().width / 2 + origin.x,
                                    tempMap2->getContentSize().height + origin.y
                                    + tempMap1->getContentSize().height / 2 + offset));
    }
    if (tempMap2->getPositionY() + tempMap2->getContentSize().height / 2 <= origin.y) {
        float offset = tempMap2->getPositionY() + tempMap2->getContentSize().height / 2 - origin.y;
        tempMap2->setPosition(Point(tempMap2->getContentSize().width / 2 + origin.x,
                                    tempMap1->getContentSize().height + origin.y
                                    + tempMap2->getContentSize().height / 2 + offset));
    }
    
    
    bool bMoveButt = false;
    bool bMovePlane = false;
    //检测机机碰撞
    bMovePlane = enemyCollisionPlane();
    if (bMovePlane) {
        auto scene = About::createScene();
        
        auto tr = TransitionFade::create(1.0f, scene);
        
        Director::getInstance()->replaceScene(tr);
    }
    //遍历所有子弹
    for (auto& eBullet : bulletSprite->vecBullet) {
        Sprite* pBullet = (Sprite*)eBullet;
        bMoveButt = bulletCollisionEnemy(pBullet);
        if (bMoveButt) {
            return;
        }
    }
}

bool GameScene::enemyCollisionPlane()
{
    Sprite* pPlane = (Sprite*)planeLayer->getChildByTag(AIRPLANE);
    for (auto& eEnemy : enemyLayer->vecEnemy) {
        EnemySprite* pEnemySprite = (EnemySprite*)eEnemy;
        if (pPlane->boundingBox().intersectsRect(pEnemySprite->getBoundingBox())
            && pEnemySprite->getLife() > 0) {  
            this->removeChild(pPlane);
            EnemyLayer::sharedBoss = NULL;
            this->unscheduleAllSelectors();
            return true;
        }
    }
    for (auto& eBoom : bulletSprite->vecBoom) {
        BulletSprite* pBoom = (BulletSprite*)eBoom;
        if (pBoom->boundingBox().intersectsRect(pPlane->getBoundingBox()))
        {
            this->removeChild(pPlane);
            EnemyLayer::sharedBoss = NULL;
            this->unscheduleAllSelectors();
            return true;
        }
    }
    return false;
}
