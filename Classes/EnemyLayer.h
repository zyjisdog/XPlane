//
//  EnemyLayer.h
//  PlaneX
//
//  Created by CloudL on 14/11/24.
//
//

#ifndef __PlaneX__EnemyLayer__
#define __PlaneX__EnemyLayer__

#include "cocos2d.h"
#include "EnemyInfo.h"
#include "EnemySprite.h"
USING_NS_CC;

class EnemyLayer : public Layer
{
public:
    EnemyLayer();
    ~EnemyLayer();
    
    virtual bool init();
    CREATE_FUNC(EnemyLayer);
    
    void addEnemy1(float dt);//添加敌机1
    void addEnemy2(float dt);//添加敌机2
    void addEnemy3(float dt);//添加敌机3
    
    //敌机爆炸效果
    void blowUpEnemy(EnemySprite* pEnemySprite);
    //移除敌机
    void removeEnemy(Node* pNode);
    
    //设置分数
    void setScore(int nScore);
    //得到分数
    int getScore();
    //更新分数
    void updateScore(int score);
    //移除动画
    void f_removeMyAnimation(Node* pNode);
    
    //敌机容器
    Vector<EnemySprite*> vecEnemy;
    //最高得分
    static int m_score;
    //得分文字
    LabelBMFont* scoreItem;
    
    static EnemySprite* sharedBoss;
};


#endif /* defined(__PlaneX__EnemyLayer__) */
