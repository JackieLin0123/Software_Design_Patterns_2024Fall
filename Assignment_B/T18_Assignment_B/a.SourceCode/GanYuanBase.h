// This file use Strategy Pattern and Decorator Pattern
#ifndef _GAN_YUAN_BASE_H_
#define _GAN_YUAN_BASE_H_

#include <iostream>
#include <string>
#include <time.h>
#include "cocos2d.h"
#include "EnemyBase.h"
#include "Const.h"
#include "Bar.h"
#include "Actor.h"
#include "Bullet.h"
USING_NS_CC;
class GanYuanBase : public RealActor
{
    // Strategy Pattern: Added for Pattern Strategy
public:
    class GetPosition
    {
    public:
        virtual std::vector<Vec2> &get(GameManager *);
    };

public:
    GanYuanBase();
    EventListenerTouchOneByOne *listener1;
    virtual bool init(const std::string &filename);

    static GanYuanBase *create(const std::string &filename);

    CC_SYNTHESIZE(Vec2, firstPose, FirstPose);
    CC_SYNTHESIZE(Vec2, pose, Pose);
    CC_SYNTHESIZE(int, price, Price);
    CC_SYNTHESIZE(float, coolTime, CoolTime);
    CC_SYNTHESIZE(int, weapon_price, weapon_Price);

    // EnemyBase* nearestEnemy;

    virtual void setDefaultData() {};
    virtual void ganYuanController();
    virtual void firstInteract();
    virtual void selectCallback(Ref *sender);
    virtual void moveToPosition();
    virtual void positionLegal(bool &state, Vec2 &p);
    virtual void weaponCallback(Ref *sender);
    virtual void castBigMove() {};
    virtual void die();
    virtual bool attack(Actor *target);
    virtual void reborn() {};
    virtual void cleanDie();

    MenuItemImage *m_selectMenu;
    Menu *m_menuSelect;
    MenuItemImage *weapon;

    void checkBlock();

    void checkNearestEnemy();

    void checkInjuredGanYuan();

    void sortInjuredGanYuan();

    // Strategy Pattern: Added for Pattern Strategy
    GetPosition *get_position;
};
#endif /* defined(_GAN_YUAN_BASE_H_) */
