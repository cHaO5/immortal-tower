#include "GameMenuScene.h"
#include "TransitionGame.h"
#include "WelcomeScene.h"
#include "GameManager.h"
#include "SoundManager.h"
#include"GameMenu.h"

USING_NS_CC;

Scene* GameMenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameMenuScene::create();

	auto menuLayer = GameMenu::create();

	scene->addChild(layer);
	scene->addChild(menuLayer);

	return scene;
}

bool GameMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//instance = GameManager::getInstance();

	bgSprite = Sprite::createWithSpriteFrameName("MapBackground.png");
	bgSprite->setAnchorPoint(Vec2::ZERO);
	bgSprite->setPosition(Vec2::ZERO);
	addChild(bgSprite);

	return true;
}
