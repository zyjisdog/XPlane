//
//  PigSprite.cpp
//  PlaneX
//
//  Created by CloudL on 14/11/24.
//
//

#include "PigSprite.h"
#include "PlaneLayer.h"

PigSprite::PigSprite(){}
PigSprite::~PigSprite(){}

bool PigSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    spritePig = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
                                              ->getSpriteFrameByName("hero_01.png"));
    this->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(spritePig);
    //缩放
    this->setScale(0.6);
    //创建小猪飞行动画
    f_createAnimate(6, 8);
    //时间调度函数,使每一帧都调用f_followPlane函数来保持小猪在飞机周围
    this->schedule(schedule_selector(PigSprite::f_followPlane));
    return true;
}

//获取飞机的位置信息,使小猪始终在飞机周围
//函数要判断是否达到边界,以更新小猪在飞机左边还是右边
void PigSprite::f_followPlane(float dt)
{
    auto winSize = Director::getInstance()->getWinSize();
    auto planePos = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
    if (planePos.x + 60 + spritePig->getContentSize().width < winSize.width) {
        this->setPosition(Point(planePos.x + 60 +spritePig->getContentSize().width / 2,planePos.y));
    } else {
        this->setPosition(Point(planePos.x - 60 -spritePig->getContentSize().width / 2,planePos.y));
    }
}

//创建小猪飞行的动画,count为帧动画的数量,fps为每帧间隔时间
//RepeatForever创建无限重复动画,让spritePig来执行这个动画
void PigSprite::f_createAnimate(int count, int fps)
{
    char buff[16];
    Animation* pAnimation = Animation::create();
    pAnimation->setDelayPerUnit(1.0 / fps);
    for (int id = 1; id <= count; id++) {
        sprintf(buff, "hero_0%d.png",id);
        pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(buff));
    }
    spritePig->runAction(RepeatForever::create(Animate::create(pAnimation)));
}

