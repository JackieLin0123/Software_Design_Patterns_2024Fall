// Facade pattern: Encapsulates calls to EnemyManager, GameLogicManager, and UIManager, providing a unified interface for GameLayer to use.
#include "GameFacade.h"

GameFacade::GameFacade(GameManager *gameManager, cocos2d::Layer *parentLayer)
{
    enemyManager = new EnemyManager(gameManager);
    gameLogicManager = new GameLogicManager(gameManager);
    uiManager = new UIManager(gameManager, parentLayer);
}

void GameFacade::initToolLayer()
{
    uiManager->initToolLayer();
}

void GameFacade::addSceneEnemy(float dt)
{
    enemyManager->addSceneEnemy(dt);
}

void GameFacade::bulletFlying(float dt)
{
    enemyManager->bulletFlying(dt);
}

void GameFacade::runEnemies()
{
    enemyManager->runEnemies();
}

void GameFacade::removeBullet(Bullet *pSender)
{
    enemyManager->removeBullet(pSender);
}

void GameFacade::updateMoney(int &moneyL, cocos2d::Label *moneyLabel)
{
    uiManager->updateMoney(moneyL, moneyLabel);
}

void GameFacade::processGameLogic(float startTime, float nowTime, cocos2d::Vector<Wave *> &waveQ)
{
    gameLogicManager->logic(startTime, nowTime, waveQ);
}

void GameFacade::checkWin(int &star, cocos2d::Vector<Wave *> &waveQ)
{
    gameLogicManager->win(star, waveQ);
}

void GameFacade::checkLose(int &star)
{
    gameLogicManager->lose(star);
}

void GameFacade::updateGame(float startTime, float nowTime, int &star, cocos2d::Vector<Wave *> &waveQ, int &moneyL, cocos2d::Label *moneyLabel)
{
    processGameLogic(startTime, nowTime, waveQ);
    updateMoney(moneyL, moneyLabel);
    runEnemies();
    checkLose(star);
    checkWin(star, waveQ);
}