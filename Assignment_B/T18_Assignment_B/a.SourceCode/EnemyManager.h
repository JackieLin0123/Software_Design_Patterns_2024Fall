// This file use Builder Pattern and Facade Pattern
// facade pattern: Responsible for managing enemies in the game, including their generation, behavior, and status updates.
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "cocos2d.h"
#include "GameManager.h"
#include "Bullet.h"

class EnemyManager
{
public:
    EnemyManager(GameManager *gameManager);
    void addSceneEnemy(float dt);
    void runEnemies();
    void removeBullet(Bullet *pSender);
    void bulletFlying(float dt);

private:
    GameManager *instance;
};

#endif /* _ENEMY_MANAGER_H_ */