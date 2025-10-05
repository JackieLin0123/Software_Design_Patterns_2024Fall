// facade:the main control layer of the game
#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "GameLayer.h"
#include "GameManager.h"

#include <ctime>
#include <sstream>

namespace patch
{
	template <typename T>
	std::string to_string(const T &n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

USING_NS_CC_EXT;
using namespace CocosDenshion;

GameLayer::GameLayer()
	: isTouchEnable(false), spriteSheet(NULL), map(NULL), waveCounter(0), moneyL(8), moneyLabel(NULL), groupLabel(NULL), groupTotalLabel(NULL), interval(0), startTime(0), totalEnemies(0), mapType(0), star(3), gameFacade(new GameFacade(GameManager::getInstance(), this))
{
}
Scene *GameLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->startTime = GetCurrentTime() / 1000.f;
	srand((unsigned int)(time(0)));
	interval = 4.0f;

	Size winSize = Director::getInstance()->getWinSize();

	GameManager *instance = GameManager::getInstance();
	mapType = instance->levelType;
	instance->towersPosition = towers_path;
	instance->groundsPosition = grounds_path;

	shield = GanYuanShield::create();
	this->addChild(shield);
	shooter = GanYuanShooter::create();
	this->addChild(shooter);
	medical = GanYuanMedical::create();
	this->addChild(medical);

	// facade: remove origin recall

	gameFacade->initToolLayer();

	schedule(CC_SCHEDULE_SELECTOR(GameLayer::addSceneEnemy), interval);
	schedule(CC_SCHEDULE_SELECTOR(GameLayer::bulletFlying), 0.1f);
	schedule(CC_SCHEDULE_SELECTOR(GameLayer::updatemoney), 1.0f);
	scheduleUpdate();

	return true;
}

void GameLayer::addSceneEnemy(float dt)
{
	gameFacade->addSceneEnemy(dt);
}

void GameLayer::bulletFlying(float dt)
{
	gameFacade->bulletFlying(dt);
}

void GameLayer::removeBullet(Bullet *pSender)
{
	gameFacade->removeBullet(pSender);
}

void GameLayer::update(float dt)
{
	float nowTime = GetCurrentTime() / 1000.f;
	gameFacade->updateGame(startTime, nowTime, star, waveQ, moneyL, moneyLabel);
}

void GameLayer::menuBackCallback(Ref *pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("Music/button.mp3").c_str(), false);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();
	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));
}
