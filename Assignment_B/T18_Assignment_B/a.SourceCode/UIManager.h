// Facade: Responsible for managing the user interface of the game, including money display, buttons, etc.
#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include "cocos2d.h"
#include "GameManager.h"

class UIManager
{
public:
    UIManager(GameManager *gameManager, cocos2d::Layer *parentLayer);
    void initToolLayer();
    void updateMoney(int &moneyL, cocos2d::Label *moneyLabel);

private:
    GameManager *instance;
    cocos2d::Layer *toolLayer;
    cocos2d::Layer *parentLayer;
};

#endif /* _UI_MANAGER_H_ */