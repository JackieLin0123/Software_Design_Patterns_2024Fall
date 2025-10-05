// This file use Builder Pattern and Facade Pattern
// facade pattern: Responsible for managing enemies in the game, including their generation, behavior, and status updates.
#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager(GameManager *gameManager) : instance(gameManager) {}

// builder : remove origin function
/*void GameLayer::addSceneEnemy(float dt)
{
    GameManager* instance = GameManager::getInstance();

    for (int i = 0; i < waveQ.size(); i++)
    {
        auto groupEnemy = waveQ.at(i);

        EnemyType et;

        if (groupEnemy == NULL)
        {
            return;
        }
        else if (!groupEnemy->enemies.empty())
        {
            et = groupEnemy->enemies.front();

            std::vector<Vec2> rd = instance->roadsPosition.at(et.road - 1);

            if (et.type == ENEMY1_TYPE) {

                //SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);


                auto enemy = Enemy1::create();
                enemy->setEntered(false);
                enemy->setLastAttackTime(this->getNowTime());
                enemy->setRoad(et.road);
                enemy->setFirstPose(rd.front());
                enemy->setLastPose(rd.back());
                enemy->setCurPose(rd.front());
                enemy->setNextPose(rd.at(1));
                enemy->setPtr(0);
                enemy->setPosition(rd.front());
                enemy->setScale(0.125);
                this->addChild(enemy, 10);
                instance->enemyVector.insert(0, enemy);

                //enemy = Enemy1::createEnemy1(pointsVector, 500);
                //groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
                this->addChild(enemy, 10);
                instance->enemyVector.pushBack(enemy);
            }
            else if (et.type == ENEMY2_TYPE) {
                //SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
                //enemy = Enemy2::createEnemy2(pointsVector, 700);
                //groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
            this->addChild(enemy, 10);
                instance->enemyVector.pushBack(enemy);

                auto enemy = Enemy2::create();
                enemy->setEntered(false);
                enemy->setLastAttackTime(this->getNowTime());
                enemy->setRoad(et.road);
                enemy->setFirstPose(rd.front());
                enemy->setLastPose(rd.back());
                enemy->setCurPose(rd.front());
                enemy->setNextPose(rd.at(1));
                enemy->setPtr(0);
                enemy->setPosition(rd.front());
                enemy->setScale(0.125);
                this->addChild(enemy, 10);
                instance->enemyVector.insert(0, enemy);

            }
            else if (et.type == ENEMY3_TYPE) {
                //enemy = Enemy3::createEnemy3(pointsVector, 900);
                //SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
                //groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
                //this->addChild(enemy, 10);
                //instance->enemyVector.pushBack(enemy);

                auto enemy = Enemy3::create();
                enemy->setEntered(false);
                enemy->setLastAttackTime(this->getNowTime());
                enemy->setRoad(et.road);
                enemy->setFirstPose(rd.front());
                enemy->setLastPose(rd.back());
                enemy->setCurPose(rd.front());
                enemy->setNextPose(rd.at(1));
                enemy->setPtr(0);
                enemy->setPosition(rd.front());
                enemy->setScale(0.125);
                this->addChild(enemy, 10);
                instance->enemyVector.insert(0, enemy);

            }

            groupEnemy->enemies.erase(groupEnemy->enemies.begin());

        }
        else
        {
            waveQ.eraseObject(groupEnemy);
        }
    }
}*/

// builder : Creating Enemy by Builder
void GameLayer::addSceneEnemy(float dt)
{
    GameManager *instance = GameManager::getInstance();

    for (int i = 0; i < waveQ.size(); i++)
    {
        auto groupEnemy = waveQ.at(i);

        if (groupEnemy == NULL || groupEnemy->enemies.empty())
        {
            waveQ.eraseObject(groupEnemy);
            continue;
        }

        auto et = groupEnemy->enemies.front();
        std::vector<Vec2> rd = instance->roadsPosition.at(et.road - 1);

        EnemyCreateBase *enemyCreator = nullptr;

        // Select the corresponding director class according to the type of enemy
        switch (et.type)
        {
        case ENEMY1_TYPE:
            enemyCreator = new AirEnemyCreate();
            break;
        case ENEMY2_TYPE:
            enemyCreator = new GroundEnemyCreate1();
            break;
        case ENEMY3_TYPE:
            enemyCreator = new GroundEnemyCreate2();
            break;
        default:
            break;
        }

        if (enemyCreator != nullptr)
        {
            EnemyDirector enemyDirector(enemyCreator);    // Use the director class to create enemies
            EnemyBase *enemy = enemyDirector.construct(); // Spawn enemies

            // Setting the initial position and status of the enemy
            enemy->setEntered(false);
            enemy->setLastAttackTime(this->getNowTime());
            enemy->setRoad(et.road);
            enemy->setFirstPose(rd.front());
            enemy->setLastPose(rd.back());
            enemy->setCurPose(rd.front());
            enemy->setNextPose(rd.at(1));
            enemy->setPtr(0);
            enemy->setPosition(rd.front());
            enemy->setScale(0.125);

            this->addChild(enemy, 10);
            instance->enemyVector.insert(0, enemy);

            groupEnemy->enemies.erase(groupEnemy->enemies.begin());
        }
        else
        {
            CC_SAFE_DELETE(enemyCreator);
        }
    }
}

void EnemyManager::runEnemies()
{
    for (auto enemy : instance->enemyVector)
    {
        enemy->runToFollowPoint();
    }
    // 处理敌人状态更新
    for (auto enemy : instance->enemyVector)
    {
        if (!enemy->getAlive())
        {
            instance->enemyVector.eraseObject(enemy);
            enemy->removeFromParent();
        }
    }
}

void EnemyManager::removeBullet(Bullet *pSender)
{
    instance->bulletVector.eraseObject(pSender, true);
    pSender->getParent()->removeChild(pSender, true);
}

void EnemyManager::bulletFlying(float dt)
{
    for (int i = 0; i < instance->bulletVector.size(); i++)
    {
        auto bullet = instance->bulletVector.at(i);
        if (bullet && bullet->getTarget() != nullptr)
        {
            bullet->calculatePosition();
            if (bullet->calculateDistance() < 20.f)
            {
                auto receiver = bullet->getTarget();
                if (receiver != nullptr)
                {
                    receiver->takeDamage(bullet->getDamage());
                }
                removeBullet(bullet);
            }
        }
        else
        {
            removeBullet(bullet);
        }
    }
}