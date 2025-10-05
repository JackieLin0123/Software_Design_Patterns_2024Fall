// This file use Lazy Initialization Pattern
#pragma once

#ifndef _HARDMAP1SCENE_H__
#define __HARDMAP1SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"

class HardMap1 : public GameLayer
{
public:
    static cocos2d::Scene *createScene();
    static cocos2d::TMXTiledMap *createMap();

    virtual bool init();
    // Lazy Initialization Pattern: createScene() and createMap() are static methods that return the scene and map respectively.
    CREATE_FUNC(HardMap1);

    TMXObjectGroup *aroad = {};
    TMXObjectGroup *broad = {};
    TMXObjectGroup *croad = {};
    TMXObjectGroup *droad = {};
    std::vector<Vec2> aroad_path = {};
    std::vector<Vec2> broad_path = {};
    std::vector<Vec2> croad_path = {};
    std::vector<Vec2> droad_path = {};
};

#endif // _HARDMAP1SCENE_H__
