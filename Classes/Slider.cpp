#include"Slider.h"



bool Slider::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bloodBg = Sprite::create("bloodbg.png");
	bloodBg->setPosition(visibleSize.width / 2, visibleSize.height - bloodBg->getContentSize().height / 2);
	this->addChild(bloodBg,3);
	blood = ProgressTimer::create(Sprite::create("blood.png"));//
	blood->setPosition(visibleSize.width / 2 + 2, visibleSize.height - bloodBg->getContentSize().height / 2 - 2);
	blood->setType(ProgressTimer::Type::BAR);
	blood->setPercentage(100.0f);//initiate
	blood->setBarChangeRate(Vec2(1, 0));
	blood->setMidpoint(Vec2(0, 1));
	this->addChild(blood, 3);//这些深度都不是随便弄的
	this->schedule(schedule_selector(Slider::schedleUpdate), 0.1f);
    this->schedule(schedule_selector(Slider::ReduceBlood), 0.1f);
	return true;
}

void Slider::schedleUpdate(float dt)
{
	auto call = CallFuncN::create(CC_CALLBACK_1(Slider::bloodCallBack, this));
	this->runAction(call);
}

void Slider::bloodCallBack(Ref* pSender)
{
	if (m_curNum == 100)
	{
		return;
	}
	if (m_num < _numCollected)
	{
		m_curNum += 10;
		blood->setPercentage(m_curNum);
		m_num = _numCollected;
	}
	return;
}
/**/
void Slider::ReduceBlood(float dt)
{
	//log("reduceblood");
	if (m_curNum == 0)
	{
		return;
	}
	if (reduceblood)
	{
		//log("reduceblood is true");
		m_curNum -= 10;
		blood->setPercentage(m_curNum);
		reduceblood = false;
	}
}