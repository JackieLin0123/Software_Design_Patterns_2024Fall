// This file use Null Object Pattern
#ifndef ENEMY_CREATE_BASE_H
#define ENEMY_CREATE_BASE_H

#include "Enemy.h"
#include "GameManager.h"

USING_NS_CC;

class EnemyCreateBase
{
private:
    EnemyBase *e;

public:
    EnemyCreateBase();

    // Step 1: Create a new object
    virtual void new_enemy();

    // Step 2: Type-specific initialization (to be implemented by subclasses)
    virtual bool type_init() = 0;

    // Step 3: Common initialization
    virtual void general_init();

    // Step 4: After initialization (memory management)
    virtual void after_init();

    // Get the resulting enemy object
    virtual EnemyBase *get_result();
};

class AirEnemyCreate : public EnemyCreateBase
{
public:
    virtual bool type_init() override;
};

class GroundEnemyCreate1 : public EnemyCreateBase
{
public:
    virtual bool type_init() override;
};

class GroundEnemyCreate2 : public EnemyCreateBase
{
public:
    virtual bool type_init() override;
};

class EnemyDirector
{
private:
    EnemyCreateBase *enemyCreate;

public:
    EnemyDirector(EnemyCreateBase *enemyCreate);

    EnemyBase *construct();
};
#endif // ENEMY_CREATE_BASE_H
