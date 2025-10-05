// This file use Decorator Pattern and Null Object Pattern
#include "Bullet.h"
#include "Actor.h"
#include "GameManager.h"
#include "math.h"

#define PI 3.1415926

// Decorator Pattern: basic bullet creation
BaseBullet *BaseBullet::create(const std::string &filename, float damage, float velo, Actor *from, Actor *target)
{
	BaseBullet *bullet = new (std::nothrow) BaseBullet;
	if (bullet && bullet->init(filename, damage, velo, from, target))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

// Decorator Pattern: basic bullet initialization
bool BaseBullet::init(const std::string &filename, float damage, float velo, Actor *from, Actor *target)
{
	if (!Sprite::init())
	{
		return false;
	}

	setTexture(filename);
	setPosition(from->getPosition());
	setScale(0.5);

	this->setDamage(damage);
	this->setVelo(velo);
	this->setFrom(from);
	// Null Object Pattern: Use the empty object mode to process target
	this->setTarget(target ? target : NullActor::getInstance());

	return true;
}

// Decorator Pattern: basic bullet position calculation
void BaseBullet::calculatePosition()
{
	// Null Object Pattern: Remove null check
	auto delta = target->getPosition() - this->getPosition();
	auto distance = delta.length();
	auto dx = delta.x;
	auto dy = delta.y;

	auto rotateRadians = delta.getAngle();
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);

	setRotation(rotateDegrees);
	setPosition(getPosition() + Vec2(dx / distance * velo / FRAMES_PER_SECOND,
									 dy / distance * velo / FRAMES_PER_SECOND));
}

// basic bullet distance calculation
float BaseBullet::calculateDistance() const
{
	// Null Object Pattern: Remove null check
	auto delta = target->getPosition() - this->getPosition();
	return delta.getLength();
}

// Decorator Pattern: basic bullet effect application
void BaseBullet::applyEffect()
{
	// Null Object Pattern: Remove null check
	target->takeDamage(damage);
}

// Decorator Pattern: Normal bullet decorator creation
NormalBullet *NormalBullet::create(Bullet *bullet)
{
	auto normalBullet = new (std::nothrow) NormalBullet(bullet);
	if (normalBullet)
	{
		normalBullet->autorelease();
		return normalBullet;
	}
	CC_SAFE_DELETE(normalBullet);
	return nullptr;
}

// Normal bullet decorator effect application
void NormalBullet::applyEffect()
{
	BulletDecorator::applyEffect();
}

// Decorator Pattern: Healing bullet decorator creation
HealingBullet *HealingBullet::create(Bullet *bullet)
{
	auto healingBullet = new (std::nothrow) HealingBullet(bullet);
	if (healingBullet)
	{
		healingBullet->autorelease();
		return healingBullet;
	}
	CC_SAFE_DELETE(healingBullet);
	return nullptr;
}

// Decorator Pattern: Healing bullet decorator effect application
void HealingBullet::applyEffect()
{
	if (target)
	{
		target->takeDamage(-damage);
	}
}

// Decorator Pattern: Penetrate bullet decorator creation
PenetrateBullet *PenetrateBullet::create(Bullet *bullet)
{
	auto penetrateBullet = new (std::nothrow) PenetrateBullet(bullet);
	if (penetrateBullet)
	{
		penetrateBullet->autorelease();
		return penetrateBullet;
	}
	CC_SAFE_DELETE(penetrateBullet);
	return nullptr;
}

// Decorator Pattern: Penetrate bullet decorator effect application
void PenetrateBullet::applyEffect()
{
	if (target)
	{
		float originalDefense = target->getDefence();
		target->setDefence(0);
		target->takeDamage(damage);
		target->setDefence(originalDefense);
	}
}

// Decorator Pattern: Slow bullet decorator creation
SlowBullet *SlowBullet::create(Bullet *bullet)
{
	auto slowBullet = new (std::nothrow) SlowBullet(bullet);
	if (slowBullet)
	{
		slowBullet->autorelease();
		return slowBullet;
	}
	CC_SAFE_DELETE(slowBullet);
	return nullptr;
}

// Decorator Pattern: Slow bullet decorator effect application
void SlowBullet::applyEffect()
{
	if (target)
	{
		// Less damage than a regular bullet
		target->takeDamage(damage * 0.5f);
		if (auto enemy = dynamic_cast<EnemyBase *>(target))
		{
			// Slow down the enemy
			enemy->setRunSpeed(enemy->getRunSpeed() * 0.7f);
			// Reset the enemy's speed after 3 seconds
			enemy->scheduleOnce([enemy](float)
								{ enemy->setRunSpeed(enemy->getOriginalRunSpeed()); }, 3.0f, "reset_speed_key");
		}
	}
}

// Decorator Pattern: Melee bullet decorator creation
MeleeBullet *MeleeBullet::create(Bullet *bullet)
{
	auto meleeBullet = new (std::nothrow) MeleeBullet(bullet);
	if (meleeBullet)
	{
		meleeBullet->autorelease();
		return meleeBullet;
	}
	CC_SAFE_DELETE(meleeBullet);
	return nullptr;
}

// Decorator Pattern: Melee bullet decorator effect application
void MeleeBullet::applyEffect()
{
	if (target)
	{
		target->takeDamage(damage * 1.5f);
	}
}
