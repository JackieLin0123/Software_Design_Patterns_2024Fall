// This file use Null Object Pattern and Singleton Pattern
#include "Actor.h"

NullActor *NullActor::instance = nullptr;

// Null Object Pattern: NullActor class
NullActor *NullActor::getInstance()
{
	if (instance == nullptr)
	{
		instance = new NullActor();
	}
	return instance;
}

// Null Object Pattern: RealActor class
RealActor *RealActor::create()
{
	RealActor *sprite = new (std::nothrow) RealActor();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool RealActor::init()
{
	if (Sprite::init())
	{
		return true;
	}
	return false;
}

void RealActor::takeDamage(INT32 damage)
{
	float actualDefence = damage < 0 ? 1 - defence : 1;

	INT32 actualDamage = static_cast<INT32>(actualDefence * damage * -1);

	int a = getHealth() - actualDamage <= 0 ? 0 : getHealth() - actualDamage >= getHp() ? getHp()
																						: getHealth() - actualDamage;
	this->setHealth(getHealth() + actualDamage <= 0 ? 0 : getHealth() + actualDamage >= getHp() ? getHp()
																								: getHealth() + actualDamage);
	if (this->healthBar != NULL)
		healthBar->ifRecover(actualDamage);

	if (getHealth() <= 0)
	{
		die();
	}
}

// Null Object Pattern: RealActor class
bool RealActor::attack(Actor *target)
{
	auto nowTime = GetCurrentTime() / 1000.f;

	if (nowTime - getLastAttackTime() <= getIntervalTime() || target == nullptr)
	{
		return false;
	}

	setLastAttackTime(nowTime);
	return true;
}

void RealActor::die()
{
	this->setAlive(false);
}

Vec2 RealActor::getPosition() const
{
	return Sprite::getPosition();
}

float RealActor::getDefence() const
{
	return defence;
}

void RealActor::setDefence(float defence)
{
	this->defence = defence;
}
