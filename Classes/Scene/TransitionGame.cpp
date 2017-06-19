#include "Scene/TransitionGame.h"
#include "SimpleAudioEngine.h" 

using namespace CocosDenshion;
USING_NS_CC;

TransitionGame * TransitionGame::create(float t, Scene *scene)
{
	log("create transitionScene");
	TransitionGame * pScene = new TransitionGame();
	if (pScene && pScene->initWithDuration(t, scene))
	{
		pScene->autorelease();
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
	return NULL;
}

TransitionGame::TransitionGame()
{
	m_FinishCnt = 0;
}

TransitionGame::~TransitionGame()
{
}

void TransitionGame::onEnter()
{
	//Ҫ����ĳ���
	_inScene->setVisible(false);
	TransitionScene::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point stLeftBegin, stLeftEnd, stRightBegin, stRightEnd;

	stLeftBegin.setPoint(0, visibleSize.height / 2.0f);
	stLeftEnd.setPoint(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	stRightBegin.setPoint(visibleSize.width, visibleSize.height / 2.0f);
	stRightEnd.setPoint(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	auto pLeft = Sprite::create("Scene/loadingleft.png");
	log("1eft");
	auto pRight = Sprite::create("Scene/loadingright.png");
	log("right");

	pLeft->setAnchorPoint(Point(1, 0.5));
	pRight->setAnchorPoint(Point(0, 0.5));

	addChild(pLeft, 1);
	addChild(pRight, 1);

	pLeft->setPosition(stLeftBegin);
	pRight->setPosition(stRightBegin);

	auto pActionLeft = MoveTo::create(_duration / 3, stLeftEnd);
	auto pActionRight = MoveTo::create(_duration / 3, stRightEnd);

	auto pActionLeft2 = MoveTo::create(_duration / 3, stLeftBegin);
	auto pActionRight2 = MoveTo::create(_duration / 3, stRightBegin);

	if (UserDefault::getInstance()->getIntegerForKey("backeffect", 1) == 1)
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/GUITransitionOpen.wav");
	}

	pLeft->runAction(Sequence::create(
		pActionLeft,
		CallFuncN::create(CC_CALLBACK_0(TransitionGame::OnSencondActionFinish, this)),
		DelayTime::create(1.0f),
		pActionLeft2,
		CallFuncN::create(CC_CALLBACK_0(TransitionGame::LRFinish, this)),
		NULL));
	pRight->runAction(Sequence::create(
		pActionRight,
		DelayTime::create(1.0f),
		pActionRight2,
		NULL));
}

void TransitionGame::LRFinish(void)
{
	//���ԵĻ��ɺ�Ҫִ�г��е�Finish
	TransitionScene::finish();
}

void TransitionGame::OnSencondActionFinish(void)
{
	if (UserDefault::getInstance()->getIntegerForKey("backeffect", 1) == 1)
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/GUITransitionClose.wav");
	}
	_inScene->setVisible(true);
	_outScene->setVisible(false);
}