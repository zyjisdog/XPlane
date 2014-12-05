//
//  BulletSprite.cpp
//  PlaneX
//
//  Created by CloudL on 14/11/24.
//
//

#include "BulletSprite.h"
#include "PlaneLayer.h"
#include "EnemyLayer.h"


BulletSprite::BulletSprite(){}
BulletSprite::~BulletSprite(){}

bool BulletSprite::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!Layer::init());
        Texture2D* texture = TextureCache::sharedTextureCache()->textureForKey("bullet.png");
        //创建BatchNode节点
        bulletBatchNode = SpriteBatchNode::createWithTexture(texture);
        boomBatchNode = SpriteBatchNode::createWithTexture(texture);
        this->addChild(bulletBatchNode);
        this->addChild(boomBatchNode);
        //每0.2s发射一次子弹
        this->schedule(schedule_selector(BulletSprite::shootBullet), 0.2f);
        this->schedule(schedule_selector(BulletSprite::bossShootBullet), 1.0f);
        bRet = true;
    } while (0);
    return bRet;
}

void BulletSprite::shootBullet(float dt)
{
    auto winSize = Director::getInstance()->getWinSize();
    auto PlanePos = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
    //从缓存中创建子弹
    auto spriteBullet = Sprite::createWithSpriteFrameName("bullet_1.png");
    //将创建好的子弹添加到BatchNode中进行批次渲染
    bulletBatchNode->addChild(spriteBullet);
    //将创建好的子弹添加到容器
    vecBullet.pushBack(spriteBullet);
    Point bulletPos = (Point(PlanePos.x,PlanePos.y + PlaneLayer::sharedPlane
                             ->getChildByTag(AIRPLANE)->getContentSize().height / 2 + 20));
    spriteBullet->setPosition(bulletPos);
    spriteBullet->setScale(0.4f);
    
    //上下范围
    float flyLen =winSize.height - PlanePos.y;
    //子弹运行速度,可以自己控制,每秒走的像素
    float flyVelocity = 320 / 1;
    //实际飞行时间
    float realFlyDuration = flyLen / flyVelocity;
    
    //子弹运行的距离和时间,从飞机处开始运行到屏幕顶端
    auto actionMove = MoveTo::create(realFlyDuration, Point(bulletPos.x,winSize.height));
    //子弹执行完动作后进行函数回调,调用移除函数
    auto actionDone = CallFuncN::create(CC_CALLBACK_1(BulletSprite::removeBullet, this));
    
    Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
    spriteBullet->runAction(sequence);
}

void BulletSprite::bossShootBullet(float dt)
{
    if (EnemyLayer::sharedBoss != NULL ) {
        auto winSize = Director::getInstance()->getWinSize();
        auto origin = Director::getInstance()->getVisibleOrigin();
        auto BossPos = EnemyLayer::sharedBoss->getPosition();
        //从缓存中创建子弹
        auto spriteBoom = Sprite::createWithSpriteFrameName("bullet_1.png");
        //将创建好的子弹添加到BatchNode中进行批次渲染
        boomBatchNode->addChild(spriteBoom);
        //将创建好的子弹添加到容器
        vecBoom.pushBack(spriteBoom);
        Point boomPos = (Point(BossPos.x,BossPos.y - EnemyLayer::sharedBoss
                                 ->getSprite()->getContentSize().height / 2 + 20));
        spriteBoom->setPosition(boomPos);
        spriteBoom->setRotation(180.0f);
        spriteBoom->setScale(0.4f);
        
        //上下范围
        float flyLen = BossPos.y - origin.y;
        //子弹运行速度,可以自己控制,每秒走的像素
        float flyVelocity = 320 / 1;
        //实际飞行时间
        float realFlyDuration = (flyLen / flyVelocity) / 2;
        
        //子弹运行的距离和时间,从飞机处开始运行到屏幕顶端
        auto actionMove = MoveTo::create(realFlyDuration, Point(boomPos.x,origin.y));
        //子弹执行完动作后进行函数回调,调用移除函数
        auto actionDone = CallFuncN::create(CC_CALLBACK_1(BulletSprite::removeBoom, this));
        
        Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
        spriteBoom->runAction(sequence);
    }
        
}

//移除子弹,将子弹从容器中移除,同时也从SpriteBatchNode中移除
void BulletSprite::removeBullet(Node* pNode)
{
    if (NULL == pNode) {
        return;
    }
    Sprite* bullet = (Sprite*) pNode;
    this->bulletBatchNode->removeChild(bullet, true);
    vecBullet.eraseObject(bullet);
}

//移除子弹,将子弹从容器中移除,同时也从SpriteBatchNode中移除
void BulletSprite::removeBoom(Node* pNode)
{
    if (NULL == pNode) {
        return;
    }
    Sprite* boom = (Sprite*) pNode;
    this->boomBatchNode->removeChild(boom, true);
    vecBoom.eraseObject(boom);
}

//从缓存中获取子弹动画图片后创建子弹动画
Animation* BulletSprite::f_createAnimate(int count, int fps)
{
    char buff[16];
    Animation *pAnimation = Animation::create();
    pAnimation->setDelayPerUnit(1.0 / fps);
    for (int id = 1; id < count; id++) {
        sprintf(buff, "bullet_%d.png", id);
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()
                                   ->getSpriteFrameByName(buff));
    }
    return pAnimation;
}
