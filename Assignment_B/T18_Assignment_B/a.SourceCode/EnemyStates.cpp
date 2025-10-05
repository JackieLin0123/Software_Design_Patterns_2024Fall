// This file use State Pattern
#include "EnemyStates.h"
#include "EnemyBase.h"
#include "GameManager.h"

// State Pattern: StillState behavior implementation
void StillState::execute()
{
    if (!hasNextPoint())
    {
        return;
    }

    Vec2 nextPoint = getNextPathPoint();

    // State Pattern: Check condition for state transition
    if (isBlockedByGanYuan(nextPoint))
    {
        transitToAttackingState();
        return;
    }

    // State Pattern: Perform state-specific action and transition
    float duration = calculateMoveDuration(enemy->getCurrentPosition(), nextPoint);
    enemy->moveToPosition(nextPoint, duration);
    transitToRunningState();
}

// State Pattern: RunningState behavior implementation
void RunningState::execute()
{
    Vec2 nextPoint = getNextPathPoint();

    // State Pattern: Check condition for state transition
    if (enemy->isAtPosition(nextPoint))
    {
        enemy->setCurPose(nextPoint);
        enemy->setPtr(enemy->getPtr() + 1);

        auto positions = getRoadPositions();
        if (!positions.at(enemy->getPtr()).equals(enemy->getLastPose()))
        {
            enemy->setNextPose(positions.at(enemy->getPtr() + 1));
        }

        // State Pattern: Transition to next state
        transitToStillState();
    }
}

// State Pattern: AttackingState behavior implementation
void AttackingState::execute()
{
    if (enemy->getType() == ENEMY3_TYPE || enemy->getType() == ENEMY2_TYPE)
    {
        Vec2 nextPoint = getNextPathPoint();
        Actor *target = enemy->checkBlockedGanYuan(nextPoint);

        // State Pattern: Perform state-specific action or transition
        if (target && target->getAlive())
        {
            enemy->setAttacking(target);
            enemy->attack(target);
        }
        else
        {
            transitToStillState();
        }
    }
}