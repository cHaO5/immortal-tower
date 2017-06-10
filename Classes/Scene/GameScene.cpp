#include "Scene/GameScene.h"
#include "Map/level1.h"
#include "Map/Level2.h"
#include "Map/Level0.h"
#include "Layer/PlayerStateMenu.h"
#include "Data/GameManager.h"

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameScene::init()
{
	auto playerStateMenu = PlayerStateMenu::create();
    playerStateMenu->initGameOption();
	addChild(playerStateMenu ,1);//加到scene上

	auto game = Level0::create(); 
	GameManager::getInstance()->CurrentLevel= 0;
	addChild(game,0);//加到scene上
	return true;
}