// This file use Decorator Pattern and Null Object Pattern
#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"
#include <string>

USING_NS_CC;

class Actor;

// Decorator Pattern : Component , define the common interface of bullet
class Bullet : public Sprite
{
public:
	virtual bool init(const std::string &filename, float damage, float velo, Actor *from, Actor *target) = 0;
	virtual void calculatePosition() = 0;
	virtual float calculateDistance() const = 0;
	virtual void applyEffect() = 0;

	CC_SYNTHESIZE(float, damage, Damage);
	CC_SYNTHESIZE(float, velo, Velo);
	CC_SYNTHESIZE(Actor *, from, From);
	CC_SYNTHESIZE(Actor *, target, Target);
};

// Decorator Pattern : Concrete Component - Base bullet realization
class BaseBullet : public Bullet
{
public:
	static BaseBullet *create(const std::string &filename, float damage, float velo, Actor *from, Actor *target);
	virtual bool init(const std::string &filename, float damage, float velo, Actor *from, Actor *target) override;
	virtual void calculatePosition() override;
	virtual float calculateDistance() const override;
	virtual void applyEffect() override;
};

// Decorator Pattern : Base Decorator
class BulletDecorator : public Bullet
{
protected:
	Bullet *m_bullet;

public:
	BulletDecorator(Bullet *bullet) : m_bullet(bullet) {}
	// Decorator initialization delegate
	virtual bool init(const std::string &filename, float damage, float velo, Actor *from, Actor *target) override
	{
		return m_bullet->init(filename, damage, velo, from, target);
	}
	// Decorator position delegate
	virtual void calculatePosition() override
	{
		m_bullet->calculatePosition();
	}
	// Decorator distance delegate
	virtual float calculateDistance() const override
	{
		return m_bullet->calculateDistance();
	}
	// Decorator effect delegate
	virtual void applyEffect() override
	{
		m_bullet->applyEffect();
	}
};

// Decorator Pattern : Concrete Decorators - Normal bullet decorator
class NormalBullet : public BulletDecorator
{
public:
	static NormalBullet *create(Bullet *bullet);
	virtual void applyEffect() override;
};

// Decorator Pattern : Concrete Decorators - Healing bullet decorator
class HealingBullet : public BulletDecorator
{
public:
	static HealingBullet *create(Bullet *bullet);
	virtual void applyEffect() override;
};

// Decorator Pattern : Concrete Decorators - Penetrate bullet decorator
class PenetrateBullet : public BulletDecorator
{
public:
	static PenetrateBullet *create(Bullet *bullet);
	virtual void applyEffect() override;
};

// Decorator Pattern : Concrete Decorators - Slow bullet decorator
class SlowBullet : public BulletDecorator
{
public:
	static SlowBullet *create(Bullet *bullet);
	virtual void applyEffect() override;
};

// Decorator Pattern : Concrete Decorators - Melee bullet decorator
class MeleeBullet : public BulletDecorator
{
public:
	static MeleeBullet *create(Bullet *bullet);
	virtual void applyEffect() override;
};

#endif // !_BULLET_H_