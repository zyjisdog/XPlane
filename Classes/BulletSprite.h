//
//  BulletSprite.h 批次渲染版本
//  PlaneX
//
//  Created by CloudL on 14/11/24.
//
//

#ifndef __PlaneX__BulletSprite__
#define __PlaneX__BulletSprite__

#include "cocos2d.h"
USING_NS_CC;

class BulletSprite : public cocos2d::Layer
{
public:
    BulletSprite();
    ~BulletSprite();    
    
    virtual bool init();
    CREATE_FUNC(BulletSprite);
    
    //创建子弹运行动画
    Animation* f_createAnimate(int count,int fps);
    //移除屏幕外的子弹或者碰撞后的子弹
    void removeBullet(Node* pNode);
    void removeBoom(Node* pNode);
    //发射子弹,在其中进行子弹的渲染和子弹的飞行动作
    void shootBullet(float dt);
    void bossShootBullet(float dt);
    
    //子弹容器
    Vector<Sprite*> vecBullet;
    Vector<Sprite*> vecBoom;
    //批次渲染
    SpriteBatchNode* bulletBatchNode;
    SpriteBatchNode* boomBatchNode;
};

#endif /* defined(__PlaneX__BulletSprite__) */
