#include "Scene/GameMenuScene.h"
#include "Scene/TransitionGame.h"
#include "Scene/WelcomeScene.h"
#include "Data/GameManager.h"
#include "Data/SoundManager.h"
#include"Layer/GameMenu.h"

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
