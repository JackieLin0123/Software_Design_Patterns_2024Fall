// This file use Null Object Pattern
#include "EnemyCreateBase.h"

void EnemyCreateBase::new_enemy()
{
    e = new EnemyBase();
}

void EnemyCreateBase::general_init()
{
    e->setAlive(true);
    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsGround(true);

    // Initialize health bar
    healthBar = Bar::create(EStateType::Health, e->getHealth()); // code encapsulation enhancement
    auto size = e->getBoundingBox().size;
    healthBar->setScaleX(0.5);
    healthBar->setScaleY(0.7);
    healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    healthBar->setPosition(Vec2(200, 450));
    e->addChild(healthBar);
}

void EnemyCreateBase::after_init()
{
    e->autorelease();
}

EnemyBase *EnemyCreateBase::get_result()
{
    return e;
}

bool AirEnemyCreate::type_init()
{
    if (!e->Sprite::initWithFile("Pictures/enemy_air.png"))
    {
        return false;
    }

    e->setType(ENEMY1_TYPE);
    e->scope = Enemy1Scope;
    e->setLethality(Enemy1Lethality);       // Killing power
    e->setHp(Enemy1Hp);                     // Max health
    e->setHealth(Enemy1Hp);                 // Current health
    e->setDefence(Enemy1Defence);           // Defence
    e->setRunSpeed(Enemy1RunSpeed);         // Movement speed
    e->setIntervalTime(ShieldIntervalTime); // Attack interval time
    return true;
}

bool GroundEnemyCreate1::type_init()
{
    if (!e->Sprite::initWithFile("Pictures/enemy_ground1.png"))
    {
        return false;
    }

    e->setType(ENEMY2_TYPE);
    e->scope = Enemy2Scope;
    e->setLethality(Enemy2Lethality);
    e->setHp(Enemy2Hp);
    e->setHealth(Enemy2Hp);
    e->setDefence(Enemy2Defence);
    e->setIntervalTime(Enemy2IntervalTime);
    e->setRunSpeed(Enemy2RunSpeed);
    e->setIsBlock(false);
    return true;
}

bool GroundEnemyCreate2::type_init()
{
    if (!e->Sprite::initWithFile("Pictures/enemy_ground2.png"))
    {
        return false;
    }

    e->setType(ENEMY3_TYPE);
    e->scope = Enemy3Scope;
    e->setLethality(Enemy3Lethality);
    e->setHp(Enemy3Hp);
    e->setHealth(Enemy3Hp);
    e->setDefence(Enemy3Defence);
    e->setIntervalTime(Enemy3IntervalTime);
    e->setRunSpeed(Enemy3RunSpeed);
    e->setIsBlock(false);
    return true;
}

EnemyDirector::EnemyDirector(EnemyCreateBase *enemyCreate) : enemyCreate(enemyCreate) {}

EnemyBase *EnemyDirector::construct()
{
    enemyCreate->new_enemy();
    enemyCreate->type_init();
    enemyCreate->general_init();
    enemyCreate->after_init();
    return enemyCreate->get_result();
}