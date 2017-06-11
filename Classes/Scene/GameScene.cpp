#include "Scene/GameScene.h"
#include"Map/BaseMap.h"
#include "Map/level1.h"
#include "Map/Level2.h"
#include "Map/Level0.h"
#include "Layer/PlayerStateMenu.h"
#include "Data/GameManager.h"

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene -> getPhysicsWorld()->setGravity(Vec2(0, 0));
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
	BaseMap* game;

	switch (GameManager::getInstance()->CurrentLevel)
	{
	case(0):game = Level0::create(); 
	        addChild(game,0);//加到scene上
	        return true;
		    break;
	case(1):game = Level1::create();
		    addChild(game, 0);//加到scene上
		    return true;
		    break;
	case(2):game = Level2::create();
			addChild(game, 0);//加到scene上
			return true;
			break;
	default:break;
	}
	return true;
}

