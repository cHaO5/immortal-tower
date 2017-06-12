#include "Victory.h"
#include "TransitionGame.h"
#include "GameMenuScene.h"
#include "WelcomeScene.h"
#include "GameManager.h"
#include "SoundManager.h"

USING_NS_CC;
bool Victory::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	position.x = visibleSize.width / 2;
	position.y = visibleSize.height*0.6;

	auto RestartSpriteOff = Sprite::createWithSpriteFrameName("button_restart_0001.png");
	auto RestartSpriteOn = Sprite::createWithSpriteFrameName("button_restart_0002.png");

	RestartMenuItem = MenuItemSprite::create(RestartSpriteOff, RestartSpriteOn, CC_CALLBACK_1(Victory::OnRestartTouch, this));
	RestartMenuItem->setPosition(position.x, position.y - 350);
	RestartMenuItem->setVisible(false);

	auto menu = Menu::create(RestartMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu,0);

	VictorySprite = Sprite::createWithSpriteFrameName("victoryBadges_0002.png");
	VictorySprite->setPosition(position);
	VictorySprite->setScale(0.2f);
	addChild(VictorySprite,0);

	auto Sequence = Sequence::create(CallFuncN::create(CC_CALLBACK_0(Victory::VSpriteAnimation, this)),
		                             DelayTime::create(0.5f),
		                             CallFuncN::create(CC_CALLBACK_0(Victory::RItemAnimation, this)),
		                             DelayTime::create(0.5f),
		                             NULL);
	runAction(Sequence);
	SoundManager::playQuestCompleted();

	return true;
}

void Victory::VSpriteAnimation()
{
	VictorySprite->runAction(ScaleTo::create(0.5f, 1.0f, 1.0f));
}

void Victory::RItemAnimation()
{
	RestartMenuItem->setVisible(true);
	auto move = MoveTo::create(0.5f, Point(position.x, position.y - 230));
	RestartMenuItem->runAction(move);

}

void Victory::OnRestartTouch(Ref* pSpender)
{
	GameManager::getInstance()->CurrentLevel = 0;
	GameManager::getInstance()->VictoryFlag = false;
	Director::getInstance()->replaceScene(TransitionGame::create(1.0f, WelcomeScene::createScene()));
}
