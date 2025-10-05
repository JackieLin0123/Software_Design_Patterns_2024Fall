// This file use State Pattern
#include "EnemyState.h"

// State Pattern : Concrete StillState
class StillState : public EnemyState
{
public:
    StillState(EnemyBase *enemy) : EnemyState(enemy) {}
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};

// State Pattern : Concrete RunningState
class RunningState : public EnemyState
{
public:
    RunningState(EnemyBase *enemy) : EnemyState(enemy) {}
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};

// State Pattern : Concrete AttackingState
class AttackingState : public EnemyState
{
public:
    AttackingState(EnemyBase *enemy) : EnemyState(enemy) {}
    virtual void enter() override;
    virtual void execute() override;
    virtual void exit() override;
};