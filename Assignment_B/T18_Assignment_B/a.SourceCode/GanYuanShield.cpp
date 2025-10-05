// This file use Strategy Pattern
#include "GanYuanShield.h"
#include "GameManager.h"

USING_NS_CC;

bool GanYuanShield::init()
{
    if (!GanYuanBase::init("Pictures/snake.png"))
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->setPosition(Vec2(visibleSize.width / 2, 75));
    this->setScale(0.3);
    initial();
    return true;
}

GanYuanShield *GanYuanShield::create()
{
    GanYuanShield *shield = new GanYuanShield();
    if (shield && shield->init())
    {
        shield->autorelease(); //
        return shield;
    }
    CC_SAFE_DELETE(shield);
    return nullptr;
}

void GanYuanShield::setDefaultData()
{

    setType(SHIELD_TYPE);
    setPrice(ShieldPrice);
    scope = ShieldScope;
    setLethality(ShieldLethality);
    setHp(ShieldHp);
    setHealth(ShieldHp);
    setBlock(ShieldBlock);
    setCurBlock(0);
    setDefence(ShieldDefence);
    setAlive(true);
    setIntervalTime(ShieldIntervalTime);
    setCoolTime(ShieldCoolTime);
    setFirstPose(Vec2(getPosition()));
    setweapon_Price(ShieldWeapon);
    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(true);
}

void GanYuanShield::initial()
{
    setDefaultData();
    // Strategy Pattern: Added for Pattern Strategy
    this->get_position = new GanYuanShield::GetPosition();
    firstInteract();
}

void GanYuanShield::castBigMove()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite *sprite = Sprite::create();
    this->addChild(sprite);
    sprite->setPosition(Vec2(visibleSize.width / 6.5, visibleSize.height / 3));

    std::string frameNamePrefix = "Pictures/snakeBigMove/";
    int numFrames = 9;

    Vector<SpriteFrame *> frames;
    for (int i = 1; i <= numFrames; i++)
    {
        std::string frameFileName = frameNamePrefix + std::to_string(i) + ".png";
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(frameFileName);
        if (texture)
        {
            Size frameSize = texture->getContentSize();
            Rect frameRect = Rect(0, 0, frameSize.width, frameSize.height);
            SpriteFrame *frame = SpriteFrame::createWithTexture(texture, frameRect);
            frames.pushBack(frame);
        }
    }
    int opacity = this->getOpacity();
    if (!frames.empty())
    {
        Animation *animation = Animation::createWithSpriteFrames(frames, 0.1f);
        Animate *animate = Animate::create(animation);
        RepeatForever *repeat = RepeatForever::create(animate);
        this->setOpacity(0);
        sprite->runAction(repeat);
    }

    DelayTime *delay = DelayTime::create(3.0f);
    CallFunc *stopAnimation = CallFunc::create([=]()
                                               {
        sprite->stopAllActions();
        sprite->removeFromParent();
        this->setOpacity(opacity); });

    Sequence *sequence = Sequence::create(delay, stopAnimation, nullptr);
    this->runAction(sequence);
    // 开大招的数值
    defence *= 1.5;
    defenceBar->setPercent(defence * 200);

    auto callFunc = CallFunc::create([&]()
                                     {
        defence /= 1.5;
        defenceBar->setPercent(defence * 200); });

    this->runAction(Sequence::create(DelayTime::create(BigMoveTime), callFunc, nullptr));
}

void GanYuanShield::reborn()
{
    GameManager *instance = GameManager::getInstance();
    auto shield = GanYuanShield::create();
    instance->gameScene->addChild(shield);
    instance->ganyuanVector.pushBack(shield);
}