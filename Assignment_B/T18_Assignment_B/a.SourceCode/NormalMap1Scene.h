// This file use Lazy Initialization Pattern
#pragma once

#ifndef _NORMALMAP1SCENE_H__
#define __NORMALMAP1SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "Const.h"

class NormalMap1 : public GameLayer
{
public:
    static cocos2d::Scene *createScene();
    static cocos2d::TMXTiledMap *createMap();
    // Lazy Initialization Pattern: createScene() and createMap() are static methods that return the scene and map respectively.
    virtual bool init();

    CREATE_FUNC(NormalMap1);

    TMXObjectGroup *road = {};
    std::vector<Vec2> road_path = {};
};

#endif // _NORMALMAP1SCENE_H__
