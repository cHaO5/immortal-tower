#include "GameScene.h"
#include"BaseMap.h"
#include "level1.h"
#include "Level2.h"
#include "Level0.h"
#include "PlayerStateMenu.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"

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
    log("22222222222222333333333333");
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    auto path = FileUtils::getInstance()->getWritablePath();
    cout << path << endl;
    //GameManager::getInstance()->loadGame();
    //GameManager::getInstance()->reLoadGame(0);
    //GameManager::getInstance()->saveData(0);
    
    auto playerStateMenu = PlayerStateMenu::create();
    playerStateMenu->initGameOption();
    addChild(playerStateMenu ,1);//加到scene上
    BaseMap* game;
    
    switch (GameManager::getInstance()->CurrentLevel)
    {
        case(0):game = Level0::create();
            //GameManager::getInstance()->initWIthJsonFile("archive.json");
            //GameManager::getInstance()->reloadGame();
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

