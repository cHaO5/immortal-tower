#include "GameMenu.h"
#include "GameManager.h"
#include "SoundManager.h"
#include"TransitionGame.h"
#include"GameScene.h"
#include "SimpleAudioEngine.h"

bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	isFirst = true;
	auto winSize = Director::getInstance()->getWinSize();

	player0 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("heroroom_bigPortraits_0002.png"),
		Sprite::createWithSpriteFrameName("heroroom_bigPortraits_0002.png"));
	player1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("heroroom_bigPortraits_0008.png"),
		Sprite::createWithSpriteFrameName("heroroom_bigPortraits_0008.png"));
	player2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("heroroom_bigPortraits_0010.png"),
		Sprite::createWithSpriteFrameName("heroroom_bigPortraits_0010.png"));



	player0->setCallback([&](Ref *pSender) 
	{
		SoundManager::playClickEffect();
		GameManager::getInstance()->currentPlayerState_type = 0;
        
        UserDefault::getInstance()->setIntegerForKey("gamemusic", 2);
        
        Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameScene::createScene()));
	});

	player1->setCallback([&](Ref *pSender) 
	{
		SoundManager::playClickEffect();
		GameManager::getInstance()->currentPlayerState_type = 1;
        
        UserDefault::getInstance()->setIntegerForKey("gamemusic", 2);
        
        Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameScene::createScene()));
	});
	player2->setCallback([&](Ref *pSender)
	{
		SoundManager::playClickEffect();
		GameManager::getInstance()->currentPlayerState_type = 2;
        
        UserDefault::getInstance()->setIntegerForKey("gamemusic", 2);
        
        Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameScene::createScene()));
	});

	player0->setPosition(Point(winSize.width - player0->getContentSize().width / 2-180, player0->getContentSize().height / 2 - 340));
	player1->setPosition(Point(player0->getPosition().x - 300, player0->getContentSize().height / 2 - 340));
	player2->setPosition(Point(player1->getPosition().x - 300, player1->getContentSize().height / 2 - 340));

	auto menu = Menu::create(player0, player1, player2, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
    
	return true;
}

void GameMenu::onEnterTransitionDidFinish()
{
	//auto instance = GameManager::getInstance();
	if (isFirst) 
	{
		player0->runAction(MoveBy::create(0.3f, Point(0, 490)));
		player2->runAction(MoveBy::create(0.3f, Point(0, 490)));
		player1->runAction(MoveBy::create(0.3f, Point(0, 490)));
		isFirst = false;
	}
}
