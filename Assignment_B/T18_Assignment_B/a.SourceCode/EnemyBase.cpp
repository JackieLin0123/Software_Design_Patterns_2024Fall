// This file use State Pattern and Decorator Pattern
#include "EnemyBase.h"
#include "GameManager.h"

EnemyBase::EnemyBase()
    : runSpeed(0), entered(false), ptr(0), mov(STILL)
{
    state = new StillState();
}

EnemyBase::~EnemyBase()
{
    delete state;
}

// State Pattern : State change
void EnemyBase::changeState(EnemyState *newState)
{
    if (state)
    {
        state->exit(this);
        delete state;
    }
    state = newState;
    if (state)
    {
        state->enter(this);
    }
}

// State Pattern : Move to the next path point
void EnemyBase::runToFollowPoint()
{
    if (state)
    {
        state->execute(this);
    }
}

/*
Builder : Remove the create function and move it to create
EnemyBase* EnemyBase::create(const std::string& filename)
{
    EnemyBase* Base = new(std::nothrow)EnemyBase;
    if (Base && Base->init(filename))
    {
        Base->autorelease();
        return Base;
    }
    CC_SAFE_DELETE(Base);
    return nullptr;
}

bool EnemyBase::init(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }
    healthBar = Bar::create(EStateType::Health, health);
    //auto position = getPosition();
    auto size = getBoundingBox().size;
    healthBar->setScaleX(0.5);
    healthBar->setScaleY(0.7);
    healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    healthBar->setPosition(Vec2(200, 450));
    addChild(healthBar);
    return true;
}*/

void EnemyBase::checkNearestGanYuan()
{
    GameManager *instance = GameManager::getInstance();
    auto gyv = instance->ganyuanVector;

    auto currMinDistant = this->scope;

    GanYuanBase *ganyuanTemp = nullptr;
    for (int i = 0; i < gyv.size(); i++)
    {
        auto enemy = gyv.at(i);
        double distance = this->getPosition().getDistance(enemy->getPosition());

        if (distance < currMinDistant)
        {
            currMinDistant = distance;
            ganyuanTemp = enemy;
        }
    }
    attacking = ganyuanTemp;
}

void EnemyBase::enemyController()
{
    if (getAlive())
    {
        checkNearestGanYuan(); // Check the nearest GanYuan
        this->attack(attacking);
        if (health <= 0)
            this->die();
    }
}

void EnemyBase::cleanDie()
{
    GameManager *instance = GameManager::getInstance();

    for (int i = 0; i < instance->bulletVector.size(); i++)
    {
        if (instance->bulletVector.at(i)->getTarget() == this)
        {
            instance->bulletVector.eraseObject(instance->bulletVector.at(i), true);
        }
    }
}

void EnemyBase::die()
{
    GameManager *instance = GameManager::getInstance();

    for (int i = 0; i < instance->occupied.size(); i++)
    {
        if (instance->occupied.at(i).equals(this->getPosition()))
        {
            instance->occupied.erase(instance->occupied.begin() + i);
        }
    }
    this->setAlive(false);

    auto es = instance->enemyVector;
    es.eraseObject(this, true);
    healthBar->setOpacity(0);
    healthBar->background->setOpacity(0);
    this->setOpacity(0);

    cleanDie();
}

bool EnemyBase::attack(Actor *target)
{
    if (!Actor::attack(target))
    {
        return false;
    }

    GameManager *instance = GameManager::getInstance();
    std::string tmpPath;
    // Choose bullet path based on enemy type
    switch (this->getType())
    {
    case ENEMY1_TYPE:
        tmpPath = ENEMY1_PATH;
        break;
    case ENEMY2_TYPE:
        tmpPath = ENEMY2_PATH;
        break;
    case ENEMY3_TYPE:
        tmpPath = ENEMY3_PATH;
        break;
    default:
        return false;
    }

    // Decorator Pattern : Create base bullet
    auto baseBullet = BaseBullet::create(tmpPath, this->getLethality(), 3000, this, target);
    if (!baseBullet)
        return false;

    Bullet *bullet = baseBullet;

    // ENEMY1 can only attack SHOOTER and MEDICAL
    if (this->getType() == ENEMY1_TYPE)
    {
        if (target->getType() == SHOOTER_TYPE ||
            target->getType() == MEDICAL_TYPE)
        {
            bullet = NormalBullet::create(baseBullet);
        }
    }
    // ENEMY2 and ENEMY3 can attack SHOOTER, MEDICAL, and SHIELD
    else if (this->getType() == ENEMY2_TYPE ||
             this->getType() == ENEMY3_TYPE)
    {
        if (target->getType() == SHOOTER_TYPE ||
            target->getType() == MEDICAL_TYPE ||
            target->getType() == SHIELD_TYPE)
        {
            bullet = NormalBullet::create(baseBullet);
        }
    }

    if (bullet == baseBullet)
    {
        CC_SAFE_DELETE(baseBullet);
        return false;
    }
    // Set bullet position and scale
    bullet->setPosition(this->getPosition());
    bullet->setScale(0.12);
    instance->gameScene->addChild(bullet);
    instance->bulletVector.pushBack(dynamic_cast<Sprite *>(bullet));

    return true;
}

bool EnemyBase::checkIsEntered(EnemyBase *ttt) const
{
    /*if (this->getCurPose().equals(this->getLastPose()) && this->getPosition().distance(this->getLastPose()) < 1.f)
    {
        return true;
    }*/
    GameManager *instance = GameManager::getInstance();

    // for (int i = 0; i < instance->enemyVector.size(); i++)
    //{
    //     if (instance->enemyVector.at(i) != NULL)
    //     {
    //         if (!instance->enemyVector.at(i)->getAlive())
    //         {
    //             return false;
    //         }
    //         if (instance->enemyVector.at(i)->getCurPose().equals(instance->enemyVector.at(i)->getLastPose())
    //             && instance->enemyVector.at(i)->getPosition().distance(instance->enemyVector.at(i)->getLastPose()) < 0.1f)
    //         {
    //             return true;
    //         }
    //     }
    // }

    if (ttt != NULL)
    {
        if (!ttt->getAlive())
        {
            return false;
        }
        if (ttt->getCurPose().equals(ttt->getLastPose()) && ttt->getPosition().distance(ttt->getLastPose()) < 0.1f)
        {
            return true;
        }
    }

    return false;
}

Actor *EnemyBase::checkBlockedGanYuan(Vec2 bp)
{
    GameManager *instance = GameManager::getInstance();
    auto ganyuanVector = instance->ganyuanVector;

    for (auto gy : ganyuanVector)
    {
        if (gy->getType() == SHIELD_TYPE)
        {
            if (gy->getPosition().equals(bp))
            {
                return gy;
            }
        }
    }
    return NULL;
}
