// This file use Lazy Initialization Pattern
#include "NormalMap3Scene.h"

USING_NS_CC;

Scene *NormalMap3::createScene()
{
    GameManager *instance = GameManager::getInstance();
    instance->levelType = NORMAL_MAP3;
    instance->gameScene = Scene::create();
    auto layer = NormalMap3::create();
    instance->gameScene->addChild(layer);

    return instance->gameScene;
}
TMXTiledMap *NormalMap3::createMap()
{
    static TMXTiledMap *map = nullptr;
    if (map == nullptr)
    {
        map = TMXTiledMap::create("normalmap3.tmx");
        map->retain();
    }
    return map;
}
// Lazy Initialization Pattern: Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in NormalMapScene3.cpp\n");
}

// Lazy Initialization Pattern: "init" you need to initialize your instance
bool NormalMap3::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    GameManager *instance = GameManager::getInstance();
    map = createMap();

    bgLayer = map->getLayer("normalmap3");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    Size winSize = Director::getInstance()->getWinSize();
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));

    aroad = map->getObjectGroup("aroad");
    broad = map->getObjectGroup("broad");
    towers = map->getObjectGroup("towers");
    grounds = map->getObjectGroup("grounds");
    this->addChild(map, 0);

    ValueVector ravalues = aroad->getObjects();
    for (Value value : ravalues)
    {
        ValueMap valueMap = value.asValueMap();
        aroad_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2)); // ��·���㱣�浽·����
    }
    ValueVector rbvalues = broad->getObjects();
    for (Value value : rbvalues)
    {
        ValueMap valueMap = value.asValueMap();
        broad_path.push_back(Vec2(valueMap["x"].asFloat() + valueMap["width"].asFloat() / 2, valueMap["y"].asFloat() + valueMap["height"].asFloat() / 2)); // ��·���㱣�浽·����
    }
    instance->roadsPosition.push_back(aroad_path);
    instance->roadsPosition.push_back(broad_path);

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

    // instance->towersPosition = towers_path;
    // instance->groundsPosition = grounds_path;
    // instance->setMoney(money);

    // Sprite* enemy_ground = Sprite::create("Pictures/enemy_ground.png");
    // enemy_ground->setScale(0.125);
    // enemy_ground->setPosition(aroad_path[0]);
    // this->addChild(enemy_ground);

    // Vector<FiniteTimeAction*> actions;

    // for (int i = 1; i < (int)aroad_path.size(); i++)
    //{

    //    float lenth = (aroad_path[i - 1] - aroad_path[i]).getLength();
    //    MoveTo* moveTo = MoveTo::create(lenth / 100, aroad_path[i]);
    //    actions.pushBack(moveTo);

    //}

    // Sequence* seqAct = Sequence::create(actions);
    // enemy_ground->runAction(seqAct);

    return true;
}