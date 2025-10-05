// Facade:the main control layer of the game
#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "GameFacade.h"

class GameLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    void update(float dt) override;

    void menuBackCallback(cocos2d::Ref *pSender);

    void addSceneEnemy(float dt);

    void bulletFlying(float dt);

    void runEnemies();

    void updateMoney(float dt);

    CREATE_FUNC(GameLayer);

private:
    bool isTouchEnable;
    cocos2d::Sprite *spriteSheet;
    cocos2d::TMXTiledMap *map;
    int waveCounter;
    int moneyL;
    cocos2d::Label *moneyLabel;
    cocos2d::Label *groupLabel;
    cocos2d::Label *groupTotalLabel;
    float interval;
    float startTime;
    int totalEnemies;
    int mapType;
    int star;

    GameFacade *gameFacade;

    GanYuanShield *shield;
    GanYuanShooter *shooter;
    GanYuanMedical *medical;
};

#endif // __GAMELAYER_H__