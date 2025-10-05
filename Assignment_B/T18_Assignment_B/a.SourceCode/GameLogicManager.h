// facade: Responsible for handling the logic of the game, including wave management, outcome judgment, etc.
#ifndef _GAME_LOGIC_MANAGER_H_
#define _GAME_LOGIC_MANAGER_H_

#include "cocos2d.h"
#include "GameManager.h"
#include "Wave.h"
#include "WinScene.h"
#include "FailedScene.h"

class GameLogicManager
{
public:
    GameLogicManager(GameManager *gameManager);
    void initWave(int mapType);
    void logic(float startTime, float nowTime, cocos2d::Vector<Wave *> &waveQ);
    bool allWavesSuccessful();
    Wave *findEarliestWave();
    void win(int star, cocos2d::Vector<Wave *> &waveQ);
    void lose(int &star);

private:
    GameManager *instance;
};

#endif /* _GAME_LOGIC_MANAGER_H_ */