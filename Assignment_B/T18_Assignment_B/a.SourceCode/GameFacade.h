// Facade pattern:Encapsulates calls to EnemyManager, GameLogicManager, and UIManager, providing a unified interface for GameLayer to use.

#ifndef _GAME_FACADE_H_
#define _GAME_FACADE_H_

#include "GameManager.h"
#include "EnemyManager.h"
#include "GameLogicManager.h"
#include "UIManager.h"

class GameFacade
{
public:
    GameFacade(GameManager *gameManager, cocos2d::Layer *parentLayer);

    void initToolLayer();

    void addSceneEnemy(float dt);

    void bulletFlying(float dt);

    void removeBullet(Bullet *pSender);

    void runEnemies();

    void updateMoney(int &moneyL, cocos2d::Label *moneyLabel);

    void processGameLogic(float startTime, float nowTime, cocos2d::Vector<Wave *> &waveQ);

    void checkWin(int &star, cocos2d::Vector<Wave *> &waveQ);

    void checkLose(int &star);

    void updateGame(float startTime, float nowTime, int &star, cocos2d::Vector<Wave *> &waveQ, int &moneyL, cocos2d::Label *moneyLabel);

private:
    EnemyManager *enemyManager;
    GameLogicManager *gameLogicManager;
    UIManager *uiManager;
};

#endif /* _GAME_FACADE_H_ */