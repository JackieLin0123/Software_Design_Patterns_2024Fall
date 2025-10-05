// This file use Strategy Pattern
#ifndef _GAN_YUAN_SHIELD_H_
#define _GAN_YUAN_SHIELD_H_

#include "GanYuanBase.h"
#include "Const.h"
#include "Bar.h"
class GanYuanBase;

class GanYuanShield : public GanYuanBase
{
    // Strategy Pattern: Added for Pattern Strategy
public:
    class GetPositionShield : public GanYuanBase::GetPosition
    {
    public:
        virtual std::vector<Vec2> &get(GameManager *instance)
        {
            return instance->towersPosition[i];
        }
    };

public:
    CC_SYNTHESIZE(int, block, Block);
    CC_SYNTHESIZE(int, curBlock, CurBlock);

    CC_SYNTHESIZE(Animation *, attackAnimation, AttackAnimation);
    CC_SYNTHESIZE(Animation *, bigMoveAnimation, BigMoveAnimation);

    bool init();
    static GanYuanShield *create();
    virtual void setDefaultData();
    virtual void positionLegal(bool &state, Vec2 &p);
    virtual void initial();
    void castBigMove();
    Sprite *ganyuanShield;
    virtual void reborn();
};

#endif /* defined(_GAN_YUAN_SHIELD_H_) */