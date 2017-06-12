#include "Scene/WelcomeScene.h"
#include "Scene/TransitionGame.h"
#include "Data/SoundManager.h"
#include "SimpleAudioEngine.h" 
#include"Scene/GameMenuScene.h"

using namespace CocosDenshion;

Scene* WelcomeScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WelcomeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool WelcomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//设计分辨率可视区域大小 
	visibleSize = Director::getInstance()->getVisibleSize();

	//生成背景图
	initBackGround();
	//生成logo
	initLogo();
	//生成button_start
	initButton_start();
	initSoundButton();

	return true;
}

//新建序列动画
void WelcomeScene::onEnterTransitionDidFinish()
{
	auto Sequence = Sequence::create(ScaleTo::create(0.5f, 1.5f, 1.5f),
		ScaleTo::create(0.2f, 1.0f, 1.0f),
		CallFuncN::create(CC_CALLBACK_0(WelcomeScene::initButton_startAnimation, this)),
		NULL);
	sprite_Logo->runAction(Sequence);
}

void WelcomeScene::initBackGround()
{
	//从SpriteFrameCache中加载图片
	auto sprite_background = Sprite::create("Resources/welcome_bg.png");
	sprite_background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	//添加背景，Zorder设置为-1
	addChild(sprite_background, -1);
}

void WelcomeScene::initLogo()
{
	//从SpriteFrameCache中加载图片
	sprite_Logo = Sprite::create("Resources/title.png");
	//设置锚点为图片中央
	sprite_Logo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//计算Logo图应该在的位置
	point_Logo.x = visibleSize.width / 2;
	point_Logo.y = visibleSize.height - (sprite_Logo->getContentSize().height / 2);
	//设置位置,初始大小
	sprite_Logo->setScale(0.2f);
	sprite_Logo->setPosition(point_Logo);
	addChild(sprite_Logo, 9);
}

void WelcomeScene::initButton_start()
{
	//从资源中加载图片
	button_Start = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
	//设置锚点为图片中央
	button_Start->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//初始设置为不可见
	button_Start->setVisible(false);
	//设置位置
	button_Start->setPosition(point_Logo.x, point_Logo.y);
	//添加
	addChild(button_Start, 1);

	auto button_Start_listener = EventListenerTouchOneByOne::create();

	button_Start_listener->onTouchBegan = [&](Touch* touch, Event* event) 
	{

		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0 + 40, 0 + 30, size.width - 80, size.height / 3 + 15);
		if (rect.containsPoint(locationInNode) && target->isVisible())
		{
			SoundManager::playClickEffect();
			//改变Button式样达到点击效果
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0002.png"));
			return true;
		}

		return false;
	};
	button_Start_listener->onTouchEnded = [&](Touch* touch, Event* event) 
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		static_cast<Sprite*>(event->getCurrentTarget())->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0001.png"));

		button_Start->runAction(Sequence::create(
			                    DelayTime::create(0.3f),
			                    MoveTo::create(0.3f, Point(point_Logo.x, point_Logo.y)), NULL));
		button_Start->setVisible(false);
		Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameMenuScene::createScene()));
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(button_Start_listener, button_Start);
}

void WelcomeScene::initButton_startAnimation()
{
	//设置可见
	button_Start->setVisible(true);
	//执行平移动画
	button_Start->runAction(MoveTo::create(0.3f, Point(point_Logo.x, point_Logo.y - 180)));
}

void WelcomeScene::initSoundButton()
{
	auto winSize = Director::getInstance()->getWinSize();
	Sprite* backMusic;
	SoundManager::playWelcomeBackMusic();
	if (UserDefault::getInstance()->getIntegerForKey("backmusic", 1) == 1) {//0表示禁止BGM，1表示开启
		backMusic = Sprite::createWithSpriteFrameName("options_overlay_buttons_0001.png");
	}
	else {
		backMusic = Sprite::createWithSpriteFrameName("options_overlay_buttons_0002.png");
	}
	backMusic->setPosition(Point(0 + backMusic->getContentSize().width / 2 + 10, winSize.height - backMusic->getContentSize().height / 2 - 10));
	addChild(backMusic);
	auto button_backMusic_listener = EventListenerTouchOneByOne::create();
	button_backMusic_listener->onTouchBegan = [&](Touch* touch, Event* event) {

		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{
			if (UserDefault::getInstance()->getIntegerForKey("backmusic", 1) == 1) {//0表示禁止BGM，1表示开启
				UserDefault::getInstance()->setIntegerForKey("backmusic", 0);
			}
			else {
				UserDefault::getInstance()->setIntegerForKey("backmusic", 1);
			}
			target->setScale(1.1f);
			return true;
		}
		return false;
	};
	button_backMusic_listener->onTouchEnded = [&](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setScale(1.0f);
		if (UserDefault::getInstance()->getIntegerForKey("backmusic", 1) == 1) {//0表示禁止BGM，1表示开启
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0001.png"));
		}
		else {
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0002.png"));
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(button_backMusic_listener, backMusic);

	Sprite* backEffect;
	if (UserDefault::getInstance()->getIntegerForKey("backeffect", 1) == 1) {//0表示禁止BGM，1表示开启
		backEffect = Sprite::createWithSpriteFrameName("options_overlay_buttons_0003.png");
	}
	else {
		backEffect = Sprite::createWithSpriteFrameName("options_overlay_buttons_0004.png");
	}
	backEffect->setPosition(Point(backMusic->getPosition().x + backMusic->getContentSize().width, winSize.height - backEffect->getContentSize().height / 2 - 10));
	addChild(backEffect);
	auto button_backEffect_listener = EventListenerTouchOneByOne::create();
	button_backEffect_listener->onTouchBegan = [&](Touch* touch, Event* event) {

		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{
			if (UserDefault::getInstance()->getIntegerForKey("backeffect", 1) == 1) {//0表示禁止BGM，1表示开启
				UserDefault::getInstance()->setIntegerForKey("backeffect", 0);
			}
			else {
				UserDefault::getInstance()->setIntegerForKey("backeffect", 1);
			}
			target->setScale(1.1f);
			return true;
		}
		return false;
	};
	button_backEffect_listener->onTouchEnded = [&](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setScale(1.0f);
		if (UserDefault::getInstance()->getIntegerForKey("backeffect", 1) == 1) {//0表示禁止BGM，1表示开启
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0003.png"));
		}
		else {
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0004.png"));
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(button_backEffect_listener, backEffect);
}