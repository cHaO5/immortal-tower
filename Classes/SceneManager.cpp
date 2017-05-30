#include"SceneManager.h"
#include"MenuLayer.h"
#include"ControlLayer.h"

int m_num = 0;//凡是用到都要extern
int _numCollected = 0;
bool reduceblood = false;

//#include"PopUpLayer.h"
//#include"WinLayer.h"
//#include"Loselayer.h"

void SceneManager::createScene()
{
	startScene = Scene::create();
	//this->mode = true;
	auto  menuLayer = MenuLayer::create();
	menuLayer->tsm = this;
	startScene->addChild(menuLayer);
}

void SceneManager::toGameScene()
{
	log("hhhhhhh");
	gameScene = Scene::createWithPhysics();
    gameScene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto controlLayer = ControlLayer::createControl();
	controlLayer->tsm = this;
	log("8888");
	gameScene->addChild(controlLayer,0);

	auto sliderLayer = Layer::create();
    slider = Slider::create();
	gameScene->addChild(sliderLayer,3);
	sliderLayer->addChild(slider,4);

	Sprite*fog = Sprite::create("fog.png");
	auto winSize = Director::getInstance()->getWinSize();
	auto centerPoint = Point(winSize.width / 2, winSize.height / 2);
	fog->setPosition(centerPoint);
	sliderLayer->addChild(fog,3);

	Director::getInstance()->replaceScene(gameScene);
	log("1111");

	
}
/*
void SceneManager::toStartScene()
{
	startScene = Scene::create();
	auto  menuLayer = MenuLayer::create();
	menuLayer->tsm = this;
	startScene->addChild(menuLayer);
	Director::getInstance()->replaceScene(startScene);
}*/
/*
void SceneManager::toWinScene()
{
	winScene = Scene::create();
	auto winLayer = Winlayer::create();
	winLayer->tsm = this;
	winScene->addChild(winLayer);
	Director::getInstance()->replaceScene(winScene);
}

void SceneManager::toLoseScene()
{
	loseScene = Scene::create();
	auto loseLayer = Loselayer::create();
	loseLayer->tsm = this;
	loseScene->addChild(loseLayer);
	Director::getInstance()->replaceScene(loseScene);
}
*/

/*
void SceneManager::toSettingsScene()
{
	settingsScene = Scene::create();
	auto settingsLayer = PopUpLayer::create();
	settingsLayer->tsm = this;
	settingsScene->addChild(settingsLayer);
	Director::getInstance()->replaceScene(settingsScene);
}
*/