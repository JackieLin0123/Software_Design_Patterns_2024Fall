// This file use Strategy Pattern
#include "GanYuanShooter.h"
#include "GameManager.h"

USING_NS_CC;

bool GanYuanShooter::init()
{
    if (!Sprite::initWithFile("Pictures/GanYuanShooter.png"))
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    this->setPosition(Vec2(visibleSize.width / 2 - 200, 75));
    this->setScale(0.32);

    initial();
    return true;
}
void GanYuanShooter::initial()
{

    setDefaultData();
    // Strategy Pattern: Added for Pattern Strategy
    this->get_position = new GanYuanShooter::GetPosition();
    firstInteract();
}
void GanYuanShooter::setDefaultData()
{

    setType(SHOOTER_TYPE);
    scope = ShooterScope;
    setPrice(ShieldPrice);
    setLethality(ShooterLethality);
    setHp(ShooterHp);
    setHealth(ShooterHp);
    setCurBlock(0);
    setDefence(ShooterDefence);
    setAlive(true);
    setIntervalTime(ShooterIntervalTime);
    setCoolTime(ShooterCoolTime);
    setFirstPose(Vec2(getPosition()));
    setweapon_Price(ShooterWeapon);
    setLastAttackTime(GetCurrentTime() / 1000.f);
    setIsBlock(false);
    setIsGround(false);
}

Rect GanYuanShooter::getCurTowerRect(Point touchP)
{
    Rect rec(0, 0, 0, 0);
    for (Rect rect : this->towerRectVec)
    {
        if (rect.containsPoint(touchP))
        {
            rec = rect;
            break;
        }
    }
    return rec;
}

void GanYuanShooter::castBigMove()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite *sprite = Sprite::create();
    this->addChild(sprite);
    sprite->setPosition(Vec2(visibleSize.width / 6.5, visibleSize.height / 3));

    std::string frameNamePrefix = "Pictures/ShooterBigMove/";
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
    lethality *= 1.2;
    lethalityBar->setPercent(lethality / 5);

    auto callFunc = CallFunc::create([&]()
                                     {
        lethality /= 1.2;
        lethalityBar->setPercent(lethality / 5); });

    this->runAction(Sequence::create(DelayTime::create(BigMoveTime), callFunc, nullptr));
}

void GanYuanShooter::reborn()
{
    GameManager *instance = GameManager::getInstance();
    auto shooter = GanYuanShooter::create();
    instance->gameScene->addChild(shooter);
    instance->ganyuanVector.pushBack(shooter);
}