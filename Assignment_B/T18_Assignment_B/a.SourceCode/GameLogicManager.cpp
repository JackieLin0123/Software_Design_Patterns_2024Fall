// facade:Responsible for handling the logic of the game, including wave management, outcome judgment, etc.
#include "GameLogicManager.h"

GameLogicManager::GameLogicManager(GameManager *gameManager) : instance(gameManager) {}

void GameLogicManager::initWave(int mapType)
{
    switch (mapType)
    {
    case NORMAL_MAP1:
        instance->waveVector.pushBack(Wave::createWave(5.f, {{5, AROAD}}));
        instance->waveVector.pushBack(Wave::createWave(10.f, {{6, AROAD}}));
        instance->waveVector.pushBack(Wave::createWave(15.f, {{4, AROAD}}));
        break;
    case NORMAL_MAP2:
        instance->waveVector.pushBack(Wave::createWave(10.f, {{rand() % 2 + 5, AROAD}, {rand() % 2 + 5, AROAD}, {rand() % 2 + 5, AROAD}}));
        instance->waveVector.pushBack(Wave::createWave(20.f, {{rand() % 2 + 5, AROAD}, {rand() % 2 + 5, AROAD}, {rand() % 2 + 5, AROAD}}));
        instance->waveVector.pushBack(Wave::createWave(30.f, {{4, AROAD}, {5, AROAD}, {6, AROAD}}));
        break;
    case NORMAL_MAP3:
        instance->waveVector.pushBack(Wave::createWave(10.f, {{rand() % 2 + 5, AROAD}, {rand() % 2 + 5, AROAD}, {rand() % 2 + 5, AROAD}}));
        instance->waveVector.pushBack(Wave::createWave(20.f, {{rand() % 2 + 5, BROAD}, {rand() % 2 + 5, BROAD}, {rand() % 2 + 5, BROAD}}));
        instance->waveVector.pushBack(Wave::createWave(30.f, {{4, AROAD}, {5, BROAD}, {6, AROAD}}));
        break;
    case HARD_MAP:
        instance->waveVector.pushBack(Wave::createWave(10.f, {{rand() % 2 + 5, AROAD}, {rand() % 2 + 5, BROAD}, {rand() % 2 + 5, CROAD}}));
        instance->waveVector.pushBack(Wave::createWave(20.f, {{rand() % 2 + 5, DROAD}, {rand() % 2 + 5, AROAD}, {rand() % 2 + 5, BROAD}}));
        instance->waveVector.pushBack(Wave::createWave(30.f, {{4, CROAD}, {5, DROAD}, {6, AROAD}}));
        break;
    }
}

void GameLogicManager::logic(float startTime, float nowTime, cocos2d::Vector<Wave *> &waveQ)
{
    Wave *groupEnemy = findEarliestWave();
    if (groupEnemy != nullptr)
    {
        if (nowTime - startTime > groupEnemy->getShowTime())
        {
            waveQ.pushBack(groupEnemy);
            instance->waveVector.eraseObject(groupEnemy);
        }
    }
}

bool GameLogicManager::allWavesSuccessful()
{
    for (int i = 0; i < instance->waveVector.size(); i++)
    {
        auto tmp = instance->waveVector.at(i);
        if (!tmp->getIsFinished())
        {
            return false;
        }
    }
    return true;
}

Wave *GameLogicManager::findEarliestWave()
{
    Wave *w = nullptr;
    if (!instance->waveVector.empty() && allWavesSuccessful())
    {
        float minShowTime = MAX_GAME_DURATION;
        for (int i = 0; i < instance->waveVector.size(); i++)
        {
            auto tmp = instance->waveVector.at(i);
            if (tmp->getShowTime() < minShowTime)
            {
                minShowTime = tmp->getShowTime();
                w = tmp;
            }
        }
    }
    return w;
}

void GameLogicManager::win(int star, cocos2d::Vector<Wave *> &waveQ)
{
    bool condition1 = instance->waveVector.empty();
    bool condition2 = star > 0;
    bool condition3 = true;
    bool condition4 = waveQ.empty();

    for (int i = 0; i < instance->enemyVector.size(); i++)
    {
        if (instance->enemyVector.at(i)->getAlive())
        {
            condition3 = false;
            break;
        }
    }

    if (condition1 && condition2 && condition3 && condition4)
    {
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        auto renderTexture = cocos2d::RenderTexture::create(visibleSize.width, visibleSize.height);
        renderTexture->begin();
        instance->gameScene->visit();
        renderTexture->end();
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.1f, Win::scene(renderTexture)));
    }
}

void GameLogicManager::lose(int &star)
{
    auto enemyVector = instance->enemyVector;
    if (!enemyVector.empty())
    {
        for (int i = 0; i < enemyVector.size(); i++)
        {
            auto enemy = enemyVector.at(i);
            if (!enemy->getAlive())
            {
                continue;
            }
            if (enemy->checkIsEntered(enemy))
            {
                bool isAlive = enemy->getAlive();
                instance->enemyVector.eraseObject(enemy);
                enemy->removeFromParent();
                if (isAlive)
                {
                    star--;
                }
                if (star <= 0)
                {
                    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
                    auto renderTexture = cocos2d::RenderTexture::create(visibleSize.width, visibleSize.height);
                    renderTexture->begin();
                    instance->gameScene->visit();
                    renderTexture->end();
                    cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.1f, Failed::scene(renderTexture)));
                }
            }
        }
    }
}