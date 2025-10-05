// This file use State Pattern and Decorator Pattern
#pragma once
#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

#include <iostream>
#include <string>
#include <time.h>
#include "cocos2d.h"
#include "GanYuanBase.h"
#include "Const.h"
#include "Bar.h"
#include "Actor.h"
#include "Bullet.h"

USING_NS_CC;

class EnemyState;

class EnemyBase : public RealActor
{
private:
    // State Pattern: Reference to current state
    EnemyState *state;

public:
    EnemyBase();

    // builder pattern: remove create logic
    // virtual bool init(const std::string& filename);

    // static EnemyBase* create(const std::string& filename);

    // State Pattern: Method to change states
    void changeState(EnemyState *newState);

    // State Pattern: Main method that delegates to state behavior
    void runToFollowPoint();

    // State Pattern: Helper methods for states to use
    Vec2 getCurrentPosition() const { return getPosition(); }
    Vec2 getNextPosition(int index) const;
    float getDistance(const Vec2 &pos1, const Vec2 &pos2) const;
    void moveToPosition(const Vec2 &target, float duration);
    bool isAtPosition(const Vec2 &pos) const;

    CC_SYNTHESIZE(bool, entered, Entered);

    CC_SYNTHESIZE(Vec2, firstPose, FirstPose);

    CC_SYNTHESIZE(Vec2, lastPose, LastPose);

    CC_SYNTHESIZE(Vec2, curPose, CurPose);

    CC_SYNTHESIZE(int, ptr, Ptr);

    CC_SYNTHESIZE(Vec2, nextPose, NextPose);

    CC_SYNTHESIZE(float, runSpeed, RunSpeed);

    CC_SYNTHESIZE(State, mov, Mov);

    virtual void enemyController();

    virtual Actor *checkBlockedGanYuan(Vec2 bp);

    void checkNearestGanYuan();

    virtual bool checkIsEntered(EnemyBase *ttt) const;

    virtual bool attack(Actor *target);

    virtual void die();

    void cleanDie();
};

#endif /* defined(_ENEMY_BASE_H_) */ //