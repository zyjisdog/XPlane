//
//  PlaneLayer.h
//  PlaneX
//
//  Created by CloudL on 14/11/24.
//
//

#ifndef __PlaneX__PlaneLayer__
#define __PlaneX__PlaneLayer__

#include "cocos2d.h"
#include "PigSprite.h"
USING_NS_CC;

enum Enum_Plane
{
    AIRPLANE = 1,
};

class PlaneLayer : public cocos2d::Layer
{
public:
    //创建场景
    static cocos2d::Scene* createScene();
    //init初始化函数
    virtual bool init();
    //menu回调函数
    void menuCloseCallback(cocos2d::Ref* pSender);
    //create静态函数,其中调用init方法
    static PlaneLayer* create();
    
    //跟随的小猪精灵
    PigSprite *mp_pig;
    //全局单例标志
    static PlaneLayer* sharedPlane;
    //创建飞机精灵
    void f_createSprite();
    
    //点击开始时间响应函数
    bool onTouchBegan(Touch* touch,Event* pEvent);
    //点击移动事件响应函数
    void onTouchMoved(Touch* touch,Event* pEvent);
};

#endif /* defined(__PlaneX__PlaneLayer__) */
