//Facade: Responsible for managing the user interface of the game, including money display, buttons, etc.
#include "UIManager.h"

UIManager::UIManager(GameManager* gameManager, cocos2d::Layer* parentLayer)
    : instance(gameManager), parentLayer(parentLayer) {
    toolLayer = cocos2d::Layer::create();
    parentLayer->addChild(toolLayer, 10);
}

void UIManager::initToolLayer() {

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/battle.mp3");
	auto audio_battle = SimpleAudioEngine::getInstance();
	if (!audio_battle->isBackgroundMusicPlaying()) {
		audio_battle->playBackgroundMusic("Music/battle.mp3", true);
	}

    auto size = cocos2d::Director::getInstance()->getWinSize();
    int moneyL = 8;
    instance->setMoney(moneyL);
    auto moneyText = std::to_string(moneyL);
    auto moneyLabel = cocos2d::Label::createWithSystemFont(moneyText, "fonts/arial.ttf", 50);
    moneyLabel->setColor(cocos2d::Color3B(255, 215, 0));
    moneyLabel->setAnchorPoint(cocos2d::Point(1, 1));
    moneyLabel->setPosition(cocos2d::Point(size.width - 20, size.height));
    toolLayer->addChild(moneyLabel);

    auto sprite_money = cocos2d::Sprite::create("Pictures/money.png");
    sprite_money->setAnchorPoint(cocos2d::Point(1, 1));
    sprite_money->setScale(2);
    sprite_money->setPosition(cocos2d::Point(size.width - 100, size.height));
    toolLayer->addChild(sprite_money);

    auto star3 = cocos2d::Sprite::create("Pictures/star3.png");
    star3->setScale(0.5);
    star3->setAnchorPoint(cocos2d::Point(0.5f, 1));
    star3->setPosition(cocos2d::Point(size.width / 2, size.height));
    star3->setTag(333);
    toolLayer->addChild(star3);

    auto back = cocos2d::ui::Button::create("Pictures/pause.png", "Pictures/pause.png", "");
    back->setScale(2);
    back->setAnchorPoint(cocos2d::Vec2(0, 1));
    back->setPosition(cocos2d::Vec2(0, size.height));
    back->setPressedActionEnabled(true);
    toolLayer->addChild(back);
    back->addTouchEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            // Handle back button press
        }
    });
}

void UIManager::updateMoney(int& moneyL, cocos2d::Label* moneyLabel) {
    if (moneyL - instance->getMoney() == 1) {
        moneyL += 1;
        instance->setMoney(moneyL);
    } else {
        moneyL = instance->getMoney() + 1;
    }
    auto moneyText = std::to_string(moneyL);
    moneyLabel->setString(moneyText);
} 