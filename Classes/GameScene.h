//
//  GameScene.h
//  PlaneX
//
//  Created by CloudL on 14/11/23.
//
//

#ifndef __PlaneX__GameScene__
#define __PlaneX__GameScene__

#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletSprite.h"
#include "EnemyLayer.h"
USING_NS_CC;

#define MAP_1_Tag 1
#define MAP_2_Tag 2


class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();    
    virtual bool init();    
    CREATE_FUNC(GameScene);
    //在onEnter执行完成之后调用此函数
    virtual void onEnterTransitionDidFinish();
    
    //根据每帧来更新游戏
    void gameUpdate(float dt);
    //子弹碰撞检测
    bool bulletCollisionEnemy(Sprite* pBullet);
    //飞机碰撞检测
    bool enemyCollisionPlane();
    //menu回调函数
    void menuCloseCallback(cocos2d::Ref* pSender);
    
private:
    PlaneLayer* planeLayer;
    BulletSprite* bulletSprite;
    EnemyLayer* enemyLayer;
    //获取从start到end的随机数
    int getRand(int start,int end);
};



#endif /* defined(__PlaneX__GameScene__) */
