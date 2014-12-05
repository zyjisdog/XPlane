//
//  EnemySprite.h
//  PlaneX
//
//  Created by CloudL on 14/11/23.
//
//

#ifndef __PlaneX__EnemySprite__
#define __PlaneX__EnemySprite__

#include "cocos2d.h"
#include "EnemyInfo.h"
USING_NS_CC;

class EnemySprite : public Node
{
public:
    EnemySprite();//构造函数
    ~EnemySprite();//析构函数
    
    virtual bool init();//初始化函数
    CREATE_FUNC(EnemySprite);//create函数宏定义,系统已实现
    
    void setEnemyByType(EnemyType enType);//设置敌人种类
    Sprite* getSprite();//取得已创建的敌人
    int getLife();//获得生命值
    void loseLife();//失去生命值(被子弹击中)
    Rect getBoundingBox();//取得敌人的外包装矩形
    Point getcurPoint();//取得敌人位置
private:
    Sprite *pEnemySprite;
    int nLife;
};


#endif /* defined(__PlaneX__EnemySprite__) */
