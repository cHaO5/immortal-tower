#include "Layer/Failure.h"
#include "Scene/TransitionGame.h"
#include "Scene/WelcomeScene.h"
#include "Scene/GameScene.h"
#include "Data/SoundManager.h"

USING_NS_CC;

bool Failure::init()
{
	if (!Layer::init()) {
		return false;
	}
	//initOption();
	auto size = Director::getInstance()->getVisibleSize(); //��ȡ��Ļ��С 
	
	initOption();
	initMap();
	option->runAction(Sequence::create(MoveBy::create(0.2f, Point(0, -500)),
		                               NULL));
									   
	SoundManager::playQuestFailed();
	return true;
}

void ::Failure::initOption()
{
	option = Sprite::create();
	auto chain_left = Sprite::createWithSpriteFrameName("options_chain.png");
	chain_left->setAnchorPoint(Point(1, 0));
	chain_left->setPosition(Point(-190, 200));
	option->addChild(chain_left);

	auto chain_right = Sprite::createWithSpriteFrameName("options_chain.png");
	chain_right->setAnchorPoint(Point(0, 0));
	chain_right->setPosition(Point(190, 200));
	option->addChild(chain_right);
	for (int j = -40; j <= 40; j++)
	{
		auto mid_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			              ->getSpriteFrameByName("options_tileMid_center.png"));
		mid_center->setPosition(Point(8.5*j, -56));
		option->addChild(mid_center);
	}
	for (int j = -40; j <= 40; j++)
	{
		auto mid_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			              ->getSpriteFrameByName("options_tileMid_center.png"));
		mid_center->setPosition(Point(8.5*j, +56));
		option->addChild(mid_center);
	}
	for (int j = -7; j <= 7; j++)
	{
		auto top_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			              ->getSpriteFrameByName("options_tileTop_center.png"));
		top_center->setPosition(Point(32 * j, +161));
		option->addChild(top_center);
	}

	for (int j = -7; j <= 7; j++)
	{
		auto top_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			              ->getSpriteFrameByName("options_tileTop_center.png"));
		top_center->setPosition(Point(32 * j, -161));
		top_center->setFlippedY(true);
		option->addChild(top_center);
	}
	auto mid_left1 = Sprite::createWithSpriteFrameName("options_tileMid_left.png");
	mid_left1->setPosition(Point(-369, -56));
	option->addChild(mid_left1);
	auto mid_left2 = Sprite::createWithSpriteFrameName("options_tileMid_left.png");
	mid_left2->setPosition(Point(-369, 56));
	option->addChild(mid_left2);
	auto mid_right1 = Sprite::createWithSpriteFrameName("options_tileMid_right.png");
	mid_right1->setPosition(Point(369, -56));
	option->addChild(mid_right1);
	auto mid_right2 = Sprite::createWithSpriteFrameName("options_tileMid_right.png");
	mid_right2->setPosition(Point(369, 56));
	option->addChild(mid_right2);


	auto top_left1 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_left1->setPosition(Point(-347, 161));
	option->addChild(top_left1);

	auto top_left2 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_left2->setFlippedY(true);
	top_left2->setPosition(Point(-347, -161));
	option->addChild(top_left2);

	auto top_right1 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_right1->setPosition(Point(347, -161));
	top_right1->setFlippedX(true);
	top_right1->setFlippedY(true);
	option->addChild(top_right1);

	auto top_right2 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_right2->setPosition(Point(347, 161));
	top_right2->setFlippedX(true);
	option->addChild(top_right2);

	auto top_left_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	top_left_deco->setPosition(Point(220, 161));
	option->addChild(top_left_deco);

	auto down_left_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	down_left_deco->setFlippedY(true);
	down_left_deco->setPosition(Point(220, -161));
	option->addChild(down_left_deco);

	auto top_right_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	top_right_deco->setFlippedX(true);
	top_right_deco->setPosition(Point(-220, 161));
	option->addChild(top_right_deco);

	auto down_right_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	down_right_deco->setFlippedX(true);
	down_right_deco->setFlippedY(true);
	down_right_deco->setPosition(Point(-220, -161));
	option->addChild(down_right_deco);

	auto top_left_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	top_left_cut->setPosition(Point(-266, 161));
	option->addChild(top_left_cut);

	auto down_left_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	down_left_cut->setFlippedY(true);
	down_left_cut->setPosition(Point(-266, -161));
	option->addChild(down_left_cut);

	auto top_right_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	top_right_cut->setFlippedX(true);
	top_right_cut->setPosition(Point(266, 161));
	option->addChild(top_right_cut);

	auto down_right_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	down_right_cut->setFlippedX(true);
	down_right_cut->setFlippedY(true);
	down_right_cut->setPosition(Point(266, -161));
	option->addChild(down_right_cut);

	option->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2 + 20 + 500));
	addChild(option);
}

void Failure::initMap()
{
	auto size = Director::getInstance()->getVisibleSize();
	//------------��һ�� ----------------------------------------------------------------------------------------//

	auto str = " GAME OVER!";

	//��ɫ�������������
	auto downLabel = Label::createWithTTF(str, "Resources/ObelixPro.ttf", 60);
	downLabel->setPosition(Point(0, 60));
	downLabel->setColor(Color3B(255, 255, 255));
	option->addChild(downLabel, 2);


	auto restart = Sprite::createWithSpriteFrameName("options_buttons_0003.png");
	restart->setPosition(Point(-145, -100));
	restart->setTag(0);

	auto exit = Sprite::createWithSpriteFrameName("options_buttons_0001.png");
	exit->setPosition(Point(145, -100));
	exit->setTag(1);

	option->addChild(restart);
	option->addChild(exit);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Failure::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Failure::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, restart);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), exit);
}

void Failure::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setScale(1.0f);
	switch (target->getTag())
	{
	case(0)://���¿�ʼ
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameScene::createScene()));
		break;
	case(1)://�˳�
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionGame::create(1.0f, WelcomeScene::createScene()));
		break;
	default:
		break;
	}
}

void Failure::pauseGame()
{
	Director::getInstance()->pause();
}

bool Failure::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{
		SoundManager::playClickEffect();
		target->setScale(0.9f);
		return true;
	}
	return false;
}