// This file use Strategy Pattern and Decorator Pattern
#include "GanYuanBase.h"
#include "GameManager.h"
GanYuanBase::GanYuanBase()
{
	alive = false;
};
GanYuanBase *GanYuanBase::create(const std::string &filename)
{
	GanYuanBase *Base = new (std::nothrow) GanYuanBase;
	if (Base && Base->init(filename))
	{
		Base->autorelease();
		return Base;
	}
	CC_SAFE_DELETE(Base);
	return nullptr;
}

bool GanYuanBase::init(const std::string &filename)
{
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}
	return true;
}
static void problemLoading(const char *filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Menu.cpp\n");
}

void GanYuanBase::firstInteract()
{
	auto selectmenu = MenuItemImage::create("Pictures/select.jpg", "Pictures/select.jpg", CC_CALLBACK_1(GanYuanBase::selectCallback, this));
	auto menu_select = Menu::create(selectmenu, NULL, NULL);
	if (menu_select == nullptr || menu_select->getContentSize().width <= 0 || menu_select->getContentSize().height <= 0)
	{
		problemLoading("'select'");
	}
	else
	{
		menu_select->setPosition(Vec2(-500, 0));
		menu_select->setScale(0.3);
		menu_select->setOpacity(200);
		this->addChild(menu_select);
	}
	m_selectMenu = selectmenu;
	m_menuSelect = menu_select;
}
void GanYuanBase::selectCallback(Ref *sender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	GameManager *managerInstance = GameManager::getInstance();
	if (managerInstance->getMoney() > price)
	{
		this->removeChild(m_selectMenu, true);
		this->removeChild(m_menuSelect, true);
		moveToPosition();
	}
	else
	{
		Label *label = Label::createWithTTF("MONEY NOT ENOUGH!", "fonts/arial.ttf", 200);
		label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		label->setColor(Color3B::RED);
		this->addChild(label);

		DelayTime *delay = DelayTime::create(1.0f);
		CallFunc *removeLabel = CallFunc::create([label]()
												 { label->removeFromParent(); });

		label->runAction(Sequence::create(delay, removeLabel, nullptr));
	}
}
void GanYuanBase::moveToPosition()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch *touch, Event *event)
	{
		auto target = static_cast<Sprite *>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
		{
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);
			return true;
		}
		return false;
	};
	listener1->onTouchMoved = [](Touch *touch, Event *event)
	{
		auto target = static_cast<Sprite *>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
	};
	listener1->onTouchEnded = [=](Touch *touch, Event *event)
	{
		auto target = static_cast<Sprite *>(event->getCurrentTarget());
		log("sprite onTouchesEnded..");
		target->setOpacity(255);
		bool state = false;
		Vec2 p;
		positionLegal(state, p);
		if (!state)
		{

			Label *label = Label::createWithTTF("Position ILLEGAL!", "fonts/arial.ttf", 200);
			label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
			;
			label->setColor(Color3B::RED);
			this->addChild(label);

			DelayTime *delay = DelayTime::create(1.0f);
			CallFunc *removeLabel = CallFunc::create([label]()
													 { label->removeFromParent(); });

			label->runAction(Sequence::create(delay, removeLabel, nullptr));
			this->setPosition(firstPose);
		}
		else
		{
			// this->setPose(getPosition());
			// this->setPose(p);
			GameManager *instance = GameManager::getInstance();
			this->setPosition(p);
			instance->occupied.push_back(p);
			alive = true;
			instance->ganyuanVector.pushBack(this);
			instance->setMoney(instance->getMoney() - price);
			lethalityBar = Bar::create(EStateType::Lethality, lethality);
			lethalityBar->setMaxState(500);
			if (lethality <= 0)
			{
				lethalityBar->setPercent((-lethality) / 5);
			}
			else
				lethalityBar->setPercent(lethality / 5);
			healthBar = Bar::create(EStateType::Health, health);
			defenceBar = Bar::create(EStateType::Defence, defence);
			defenceBar->setMaxState(500);
			defenceBar->setPercent(defence * 200);
			auto position = getPosition();
			auto size = getBoundingBox().size;
			lethalityBar->setScaleX(0.5);
			lethalityBar->setScaleY(0.7);
			lethalityBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			lethalityBar->setPosition(Vec2(200, 450 + 35));
			addChild(lethalityBar);
			healthBar->setScaleX(0.5);
			healthBar->setScaleY(0.7);
			healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			healthBar->setPosition(Vec2(200, 450 + 70));
			addChild(healthBar);
			defenceBar->setScaleX(0.5);
			defenceBar->setScaleY(0.7);
			defenceBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			defenceBar->setPosition(Vec2(200, 450));
			addChild(defenceBar);

			weapon = MenuItemImage::create("Pictures/weapon_n.png", "Pictures/weapon_y.png", CC_CALLBACK_1(GanYuanBase::weaponCallback, this));
			auto menu_weapon = Menu::create(weapon, NULL, NULL);
			menu_weapon->setPosition(Vec2(-20, 100));
			menu_weapon->setOpacity(200);
			menu_weapon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			this->addChild(menu_weapon);
		}
	};
	listener1->setEnabled(1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

// Strategy Pattern: Added for Pattern Strategy
void GanYuanBase::positionLegal(bool &state, Vec2 &p)
{
	GameManager *instance = GameManager::getInstance();
	auto pos = this->get_position->get(instance);
	for (int i = 0; i < pos.size(); i++)
	{
		//(road_path[i - 1] - road_path[i]).getLength()
		if ((this->getPosition()).distance(pos[i]) < 50.f)
		{
			state = true;
			p = pos[i];
			listener1->setEnabled(0);
			return;
		}
	}
	return;
}
void GanYuanBase::weaponCallback(Ref *sender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	GameManager *instance = GameManager::getInstance();
	if (instance->getMoney() > weapon_price)
	{
		instance->setMoney(instance->getMoney() - weapon_price);
		castBigMove();
	}
	else
	{
		Label *label = Label::createWithTTF("MONEY NOT ENOUGH!", "fonts/arial.ttf", 200);
		label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		label->setColor(Color3B::RED);
		this->addChild(label);

		DelayTime *delay = DelayTime::create(1.0f);
		CallFunc *removeLabel = CallFunc::create([label]()
												 { label->removeFromParent(); });
		label->runAction(Sequence::create(delay, removeLabel, nullptr));
	}
}

void GanYuanBase::checkNearestEnemy()
{
	GameManager *instance = GameManager::getInstance();
	auto enemyVector = instance->enemyVector;

	auto currMinDistant = this->scope;

	EnemyBase *enemyTemp = nullptr;
	for (int i = 0; i < enemyVector.size(); i++)
	{
		auto enemy = enemyVector.at(i);
		double distance = this->getPosition().getDistance(enemy->getPosition());

		if (distance < currMinDistant)
		{
			currMinDistant = distance;
			enemyTemp = enemy;
		}
	}
	attacking = enemyTemp;
}

bool GanYuanBase::attack(Actor *target)
{
	if (!Actor::attack(target))
	{
		return false;
	}

	GameManager *instance = GameManager::getInstance();
	std::string tmpPath;
	// Choose bullet path based on ganyuan type
	switch (this->getType())
	{
	case SHIELD_TYPE:
		tmpPath = SHIELD_PATH;
		break;
	case SHOOTER_TYPE:
		tmpPath = SHOOTER_PATH;
		break;
	case MEDICAL_TYPE:
		tmpPath = MEDICAL_PATH;
		break;
	default:
		return false;
	}

	// Decorator Pattern : Create base bullet
	auto baseBullet = BaseBullet::create(tmpPath, this->getLethality(), 3000, this, target);
	if (!baseBullet)
		return false;

	Bullet *bullet = baseBullet;

	// Create different bullets based on ganyuan type
	switch (this->getType())
	{
		// SHOOTER can attack ENEMY1, ENEMY2, and ENEMY3
	case SHOOTER_TYPE:
		if (target->getType() == ENEMY1_TYPE ||
			target->getType() == ENEMY2_TYPE ||
			target->getType() == ENEMY3_TYPE)
		{
			// Randomly choose bullet type
			int bulletType = rand() % 3;
			switch (bulletType)
			{
			case 0:
				// Decorator Pattern : Concrete Decorators - Normal bullet decorator
				bullet = NormalBullet::create(baseBullet);
				break;
			case 1:
				// Decorator Pattern : Concrete Decorators - Penetrate bullet decorator
				bullet = PenetrateBullet::create(baseBullet);
				break;
			case 2:
				// Decorator Pattern : Concrete Decorators - Slow bullet decorator
				bullet = SlowBullet::create(baseBullet);
				break;
			}
		}
		break;
		// MEDICAL can heal SHIELD, MEDICAL, and SHOOTER
	case MEDICAL_TYPE:
		if (target->getType() == SHIELD_TYPE ||
			target->getType() == MEDICAL_TYPE ||
			target->getType() == SHOOTER_TYPE)
		{
			// Decorator Pattern : Concrete Decorators - Healing bullet decorator
			bullet = HealingBullet::create(baseBullet);
		}
		break;
		// SHIELD can attack ENEMY2 and ENEMY3
	case SHIELD_TYPE:
		if (target->getType() == ENEMY2_TYPE ||
			target->getType() == ENEMY3_TYPE)
		{
			// Decorator Pattern : Concrete Decorators - Melee bullet decorator
			bullet = MeleeBullet::create(baseBullet);
		}
		break;
	}

	if (bullet == baseBullet)
	{
		CC_SAFE_DELETE(baseBullet);
		return false;
	}
	// Set bullet position and scale
	bullet->setPosition(this->getPosition());
	bullet->setScale(0.12);
	instance->gameScene->addChild(bullet);
	instance->bulletVector.pushBack(dynamic_cast<Sprite *>(bullet));

	return true;
}

void GanYuanBase::cleanDie()
{
	GameManager *instance = GameManager::getInstance();

	for (int i = 0; i < instance->bulletVector.size(); i++)
	{
		if (instance->bulletVector.at(i)->getTarget() == this)
		{
			instance->bulletVector.eraseObject(instance->bulletVector.at(i), true);
		}
	}
}

void GanYuanBase::die()
{
	GameManager *instance = GameManager::getInstance();
	for (int i = 0; i < instance->occupied.size(); i++)
	{
		if (instance->occupied.at(i).equals(this->getPosition()))
		{
			instance->occupied.erase(instance->occupied.begin() + i);
		}
	}
	this->setAlive(false);

	auto ganyaunVector = instance->ganyuanVector;
	ganyaunVector.eraseObject(this, true);
	lethalityBar->setOpacity(0);
	lethalityBar->background->setOpacity(0);
	healthBar->setOpacity(0);
	healthBar->background->setOpacity(0);
	defenceBar->setOpacity(0);
	defenceBar->background->setOpacity(0);
	weapon->setOpacity(0);
	this->setOpacity(0);

	cleanDie();

	auto callFunc = CallFunc::create([&]()
									 {
		this->reborn();
		this->getParent()->removeChild(this, true); });

	this->runAction(Sequence::create(DelayTime::create(coolTime), callFunc, nullptr));
}
void GanYuanBase::ganYuanController()
{
	if (getAlive())
	{
		checkNearestEnemy(); // �ж��������
		attack(attacking);
		if (health <= 0)
			die();
	}
}
void GanYuanBase::checkInjuredGanYuan()
{
	GameManager *instance = GameManager::getInstance();

	auto ganyaunVector = instance->ganyuanVector;

	if (!ganyaunVector.empty())
	{
		for (int i = 0; i < ganyaunVector.size(); i++)
		{
			auto ganyuan = ganyaunVector.at(i);

			if (ganyuan->getHealth() < hp * 1.0 && ganyuan->getHealth() > 0)
			{
				instance->injuredganyuan.pushBack(ganyuan);
			}
		}
	}
}

void qSort(Vector<GanYuanBase *> array, int low, int high)
{
	int i = low;
	int j = high;
	if (i >= j)
	{
		return;
	}

	int temp = array.at(low)->getHealth();
	while (i != j)
	{
		while (array.at(j)->getHealth() >= temp && i < j)
		{
			j--;
		}
		while (array.at(i)->getHealth() <= temp && i < j)
		{
			i++;
		}
		if (i < j)
		{
			// swap(array[i], array[j]);
			array.swap(i, j);
		}
	}

	array.swap(low, i);
	qSort(array, low, i - 1);
	qSort(array, i + 1, high);
}

void GanYuanBase::sortInjuredGanYuan()
{
	GameManager *instance = GameManager::getInstance();

	qSort(instance->injuredganyuan, 0, instance->injuredganyuan.size() - 1);
}
