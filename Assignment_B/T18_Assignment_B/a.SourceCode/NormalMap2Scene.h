// This file use Lazy Initialization Pattern
#pragma once
#ifndef _NORMALMAP2SCENE_H__
#define __NORMALMAP2SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "Const.h"

class NormalMap2 : public GameLayer
{
public:
    static cocos2d::Scene *createScene();
    static cocos2d::TMXTiledMap *createMap();
    // Lazy Initialization Pattern: createScene() and createMap() are static methods that return the scene and map respectively.
    virtual bool init();

    CREATE_FUNC(NormalMap2);

    TMXObjectGroup *aroad = {};
    TMXObjectGroup *broad = {};
    std::vector<Vec2> aroad_path = {};
    std::vector<Vec2> broad_path = {};
};

#endif // _NORMALMAP2SCENE_H__