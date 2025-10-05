// This file use Null Object Pattern
#pragma once
#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <iostream>
#include <string>
#include <time.h>
#include "cocos2d.h"
#include "Bar.h"
#include "Const.h"

USING_NS_CC;

// Null Object Pattern: Actor class
class Actor : public cocos2d::Sprite
{
public:
	virtual void die() = 0;
	virtual bool attack(Actor *target) = 0;
	virtual void takeDamage(INT32 damage) = 0;
	virtual bool init() = 0;
	virtual Vec2 getPosition() const = 0;
	virtual float getDefence() const = 0;
	virtual void setDefence(float defence) = 0;
	virtual ~Actor() {}
};

// Null Object Pattern: RealActor class
class RealActor : public Actor
{
protected:
	Bar *lethalityBar;
	Bar *healthBar;
	Bar *defenceBar;
	CC_SYNTHESIZE(int, type, Type);

	CC_SYNTHESIZE(int, road, Road);

	CC_SYNTHESIZE(int, scope, Scope);

	CC_SYNTHESIZE(int, lethality, Lethality);

	CC_SYNTHESIZE(float, hp, Hp);

	CC_SYNTHESIZE(float, health, Health);

	CC_SYNTHESIZE(float, defence, Defence);

	CC_SYNTHESIZE(bool, alive, Alive);

	CC_SYNTHESIZE(float, intervalTime, IntervalTime);

	CC_SYNTHESIZE(float, lastAttackTime, LastAttackTime);

	CC_SYNTHESIZE(bool, isBlock, IsBlock);

	CC_SYNTHESIZE(int, block, Block);

	CC_SYNTHESIZE(int, curBlock, CurBlock);

	CC_SYNTHESIZE(bool, isGround, IsGround);

	CC_SYNTHESIZE(Actor *, attacking, Attacking);

public:
	virtual void die() override;

	virtual bool attack(Actor *target) override;

	virtual void takeDamage(INT32 damage) override;

	virtual bool init() override;

	virtual Vec2 getPosition() const override;

	virtual void setPosition(const Vec2 &position) override;

	virtual float getDefence() const override;

	virtual void setDefence(float defence) override;

	static RealActor *create();
};

// Null Object Pattern: NullActor class
class NullActor : public Actor
{
public:
	static NullActor *getInstance();

	virtual void die() override {}
	virtual bool attack(Actor *target) override { return false; }
	virtual void takeDamage(INT32 damage) override {}
	virtual bool init() override { return true; }
	virtual Vec2 getPosition() const override { return Vec2::ZERO; }
	virtual void setPosition(const Vec2 &position) override {}
	virtual float getDefence() const override { return 0.0f; }
	virtual void setDefence(float defence) override {}

private:
	static NullActor *instance;
	NullActor() {} // private constructor
};

#endif // !_ACTOR_H_