#include"MenuLayer.h"

bool MenuLayer::init()
{
	if (!Layer::init()) 
	{
		return false;
	}

	//create background
	createBG();

	return true;
}

void MenuLayer::createBG() 
{
	auto winSize = Director::getInstance()->getWinSize();
	auto centerPoint = Point(winSize.width / 2, winSize.height / 2);

	//BG
	Sprite* spriteBg = Sprite::create("MainBG.png");
	spriteBg->setPosition(centerPoint);
	this->addChild(spriteBg);

	//create button
	createButton(centerPoint);
}


void MenuLayer::createButton(cocos2d::Point centerPoint)
{
	//Start mutton
	MenuItemImage* menuItem = MenuItemImage::create("start_n.png","start_s.png",CC_CALLBACK_0(MenuLayer::start, this));
	
	Menu* menu = Menu::create(menuItem, NULL);

	menu->setPosition(centerPoint);

	this->addChild(menu);
}

void MenuLayer::start() 
{
	log("game is start !");
	tsm->toGameScene();
	//Scene* playScene = TransitionFade::create(1,PlayScene::createScene());
	//Director::getInstance()->replaceScene(playScene);
}