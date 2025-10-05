// This file use Lazy Initialization Pattern
#include "NormalMap1Scene.h"

USING_NS_CC;

Scene *NormalMap1::createScene()
{
    GameManager *instance = GameManager::getInstance();
    instance->levelType = NORMAL_MAP1;
    instance->gameScene = Scene::create();
    auto layer = NormalMap1::create();
    instance->gameScene->addChild(layer);

    return instance->gameScene;
}
TMXTiledMap *NormalMap1::createMap()
{
    static TMXTiledMap *map = nullptr;
    if (map == nullptr)
    {
        map = TMXTiledMap::create("normalmap1.tmx");
        map->retain();
    }
    return map;
}
// Lazy Initialization Pattern: Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in  NormalMapScene1.cpp\n");
}

// Lazy Initialization Pattern: "init" you need to initialize your instance
bool NormalMap1::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    map = createMap();

    bgLayer = map->getLayer("normalmap1");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    Size winSize = Director::getInstance()->getWinSize();
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));

    road = map->getObjectGroup("road");
    towers = map->getObjectGroup("towers");
    grounds = map->getObjectGroup("grounds");
    this->addChild(map, 0);

    GameManager *instance = GameManager::getInstance();

    ValueVector rvalues = road->getObjects();
    for (Value value : rvalues)
    {
        ValueMap valueMap = value.asValueMap();
        road_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2)); // ��·���㱣�浽·����
    }

    instance->roadsPosition.push_back(road_path);

    ValueVector tvalues = towers->getObjects();
    for (Value value : tvalues)
    {
        ValueMap valueMap = value.asValueMap();
        towers_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2)); // ��·���㱣�浽·����
    }

    ValueVector gvalues = grounds->getObjects();
    for (Value value : gvalues)
    {
        ValueMap valueMap = value.asValueMap();
        grounds_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2)); // ��·���㱣�浽·����
    }

    GameLayer::init();

    // Sprite* enemy_ground = Sprite::create("Pictures/enemy_ground.png");
    // enemy_ground->setScale(0.125);
    // enemy_ground->setPosition(road_path[0]);
    // this->addChild(enemy_ground);
    //

    // Vector<FiniteTimeAction*> actions;

    // for (int i = 1; i < (int)road_path.size(); i++)
    //{
    //     /*Vec2 offset = road_path[i-1] - road_path[i ];
    //     int lenth = offset.getLength();*/
    //
    //     float lenth = (road_path[i - 1] - road_path[i]).getLength();
    //     MoveTo* moveTo = MoveTo::create(lenth / 100, road_path[i]);
    //     actions.pushBack(moveTo);

    //}

    // Sequence* seqAct = Sequence::create(actions);
    // enemy_ground->runAction(seqAct);

    return true;
}
