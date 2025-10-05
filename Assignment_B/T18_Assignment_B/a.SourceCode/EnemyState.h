// This file use State Pattern
#pragma once
#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class EnemyBase;

// State Pattern: Abstract State Interface
class EnemyState
{
protected:
    // State Pattern: Reference to context
    EnemyBase *enemy;

public:
    // State Pattern: Constructor with context reference
    EnemyState(EnemyBase *enemy) : enemy(enemy) {}
    virtual ~EnemyState() {}

    // State Pattern: Core state behavior methods
    virtual void enter() = 0;
    virtual void execute() = 0;
    virtual void exit() = 0;

protected:
    // State Pattern: Common helper methods for concrete states
    std::vector<Vec2> getRoadPositions();
    Vec2 getNextPathPoint();
    bool hasNextPoint();
    bool isBlockedByGanYuan(const Vec2 &position);
    float calculateMoveDuration(const Vec2 &from, const Vec2 &to);

    // State Pattern: State transition methods
    void transitToStillState();
    void transitToRunningState();
    void transitToAttackingState();
};

// State Pattern: Concrete State Classes
class StillState : public EnemyState
{
public:
    // State Pattern: Constructor passing context to base class
    StillState(EnemyBase *enemy) : EnemyState(enemy) {}

    // State Pattern: Implementation of state-specific behavior
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};

// State Pattern: Concrete Running State
class RunningState : public EnemyState
{
public:
    RunningState(EnemyBase *enemy) : EnemyState(enemy) {}
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};

// State Pattern: Concrete Attacking State
class AttackingState : public EnemyState
{
public:
    AttackingState(EnemyBase *enemy) : EnemyState(enemy) {}
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};