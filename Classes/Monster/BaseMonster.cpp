#include"Monster/BaseMonster.h"
#include"Data/GameManager.h"
#include<math.h>

bool BaseMonster::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void BaseMonster::StartListen()
{
	log("Monater0 StartListen create");
	this->schedule(schedule_selector(BaseMonster::FollowMove), 1.0f);
}

void BaseMonster::FollowMove(float dt)
{
	float x = GameManager::getInstance()->currentPlayer->getPosition().x - baseMonster->getPosition().x;
	float y = GameManager::getInstance()->currentPlayer->getPosition().y - baseMonster->getPosition().y;
	log("Monater0 followrun create");
	//先计算怪物和英雄的距离
	auto dis = sqrt(pow(x, 2) + pow(y, 2));

	if (dis >= 2000)//当怪物与英雄距离超2000
		return;
	if (dis <= 1000)//在怪物可视范围内，怪物开始移动
	{
		this->unschedule(schedule_selector(BaseMonster::FollowMove));
		auto func = CallFuncN::create(CC_CALLBACK_1(BaseMonster::Move, this));//让怪物移动
		baseMonster->runAction(func);

		if (dis <= 600)//开始攻击
		{
			log("before attack");
			this->schedule(schedule_selector(BaseMonster::Attack), 1.5f);
		}
	}
}

void BaseMonster::Move(Node *pSender)//此处加入ai算法
{
	//log("Monater0 Move create");
	auto move = MoveBy::create(1.0, Point(GameManager::getInstance()->currentPlayer->getPosition().x - baseMonster->getPosition().x >0 ? 128 : -128,
		                                  GameManager::getInstance()->currentPlayer->getPosition().y - baseMonster->getPosition().y >0 ? 128 : -128));

	auto func = CallFuncN::create(CC_CALLBACK_1(BaseMonster::Move, this));//反复调用移动
	baseMonster->runAction(Sequence::create(move, func, NULL));
}

void BaseMonster::Attack(float dt)//子类重写该function
{
	log("Monater0 baseclass attack create");
}
