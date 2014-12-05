//
//  PigSprite.h
//  PlaneX
//
//  Created by CloudL on 14/11/24.
//
//

#ifndef __PlaneX__PigSprite__
#define __PlaneX__PigSprite__

#include "cocos2d.h"
USING_NS_CC;

class PigSprite : public cocos2d::Sprite
{
public:
    PigSprite();
    ~PigSprite();
    
    //精灵初始化
    virtual bool init();
    //create函数宏
    CREATE_FUNC(PigSprite);
    
    //创建动画
    void f_createAnimate(int count,int fps);
    
    //跟随飞机
    void f_followPlane(float dt);
private:
    Sprite *spritePig;
};

#endif /* defined(__PlaneX__PigSprite__) */
