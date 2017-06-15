#include "PlayerStateMenu.h"
#include "GameOption.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "Victory.h"
#include "Failure.h"
#include "SimpleAudioEngine.h"

bool PlayerStateMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	fog = Sprite::create("fog.png");
	fog->setAnchorPoint(Point(0, 0));
	fog->setPosition(Point(0,0));
	addChild(fog,0);
	
	//instance = GameManager::getInstance();

	LifeSlider = Slider::create();
	LifeSlider->setAnchorPoint(Point(0, 0));
	LifeSlider->setPosition(Point(600, Director::getInstance()->getWinSize().height - 30 + 100));
	addChild(LifeSlider,1);

	pause = Sprite::createWithSpriteFrameName("hud_buttons_0001.png");
	pause->setAnchorPoint(Point(1, 1));
	pause->setPosition(Point(Director::getInstance()->getWinSize().width - 20, Director::getInstance()->getWinSize().height - 20 + 100));
	addChild(pause,2);

	auto pause_listener = EventListenerTouchOneByOne::create();
	pause_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{
			SoundManager::playClickEffect();
			return true;
		}
		return false;
	};
	pause_listener->onTouchEnded = [&](Touch* touch, Event* event) 
	{
		addGameOption();
	};
	pause_listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pause_listener, pause);

	this->schedule(schedule_selector(PlayerStateMenu::DetectFailure), 0.01f);
	this->schedule(schedule_selector(PlayerStateMenu::DetectVictory), 0.01f);

	return true;
}

void PlayerStateMenu::DetectFailure(float t)
{
	if (!GameManager::getInstance()->currentPlayerState_life)
	{
		log("failure");
		//停止计时器
		this->unschedule(schedule_selector(PlayerStateMenu::DetectFailure));
		//显示胜利画面
		auto failure = Failure::create();
		addChild(failure);
		failure->setGlobalZOrder(999);//无效不知道为什么
	}
}


void PlayerStateMenu::DetectVictory(float t)
{
	if (GameManager::getInstance()->MonsterClearFlag&&GameManager::getInstance()->CurrentLevel == 2)
	{
		GameManager::getInstance()->VictoryFlag = true;
	}
	if (GameManager::getInstance()->VictoryFlag)
	{
		log("success");
		//停止计时器
		this->unschedule(schedule_selector(PlayerStateMenu::DetectVictory));
		//显示胜利画面
		auto victory = Victory::create();
		victory->setGlobalZOrder(999);//无效不知道为什么
		addChild(victory, 6);

	}
}

void PlayerStateMenu::initGameOption()
{
	gameOption = GameOption::create();
	gameOption->level = 1;//getLevel();
	gameOption->difficult = 1;//getDifficult();
	gameOption->setPosition(Point(0,
		Director::getInstance()->getVisibleSize().height));
	addChild(gameOption, 99);
}

void PlayerStateMenu::addGameOption()
{
    //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	auto color = LayerColor::create(Color4B(0, 0, 0, 60), Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
	color->setTag(501);
	addChild(color);
	auto gameOptionListener = EventListenerTouchOneByOne::create();
	gameOptionListener->onTouchBegan = [&](Touch* touch, Event* event) {
		return true;
	};
	gameOptionListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(gameOptionListener, color);
	gameOption->runAction(
		Sequence::create(MoveBy::create(0.2f, Point(0, -Director::getInstance()->getVisibleSize().height)),
			CallFuncN::create(CC_CALLBACK_0(PlayerStateMenu::pauseGame, this)), NULL));
}

void PlayerStateMenu::removeGameOption()
{
	Director::getInstance()->resume();
	gameOption->runAction(MoveBy::create(0.2f, Point(0, Director::getInstance()->getVisibleSize().height)));
	removeChildByTag(501);
}

void PlayerStateMenu::pauseGame()
{
	Director::getInstance()->pause();
}

void PlayerStateMenu::onEnterTransitionDidFinish()
{
	LifeSlider->runAction(MoveBy::create(0.2f, Point(0, -100)));
	pause->runAction(MoveBy::create(0.2f, Point(0, -100)));

}
