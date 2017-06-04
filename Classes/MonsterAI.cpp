#include"MonsterAI.h"
#include<math.h>

extern bool reduceblood;

//启动监听
void MonsterAI::StartListen()
{
	//monsterDirection = -1;
	this->schedule(schedule_selector(MonsterAI::FollowRun), 2.0f);
}

void MonsterAI::FollowRun(float dt)
{	
	float x = _player->_player->getPosition().x - this->getParent()->getPosition().x;
	float y = _player->_player->getPosition().y - this->getParent()->getPosition().y ;

	//先计算怪物和英雄的距离
	dis = sqrt(pow(x, 2) + pow(y, 2));

	if (dis >= 2000)//当怪物与英雄距离超2000
		return;
	if (dis <= 1000)//在怪物可视范围内，怪物开始移动
	{
		this->unschedule(schedule_selector(MonsterAI::FollowRun));
	    auto func = CallFuncN::create(CC_CALLBACK_1(MonsterAI::goon,this));//让怪物移动
		this->getParent()->runAction(Sequence::create(func, NULL));

		if (dis <= 600)//开始攻击攻击已经没问题了
		{
			this->schedule(schedule_selector(MonsterAI::JudegeAttack), 2.5f);
		}
	}
}

void MonsterAI::goon(Node *pSender)//此处加入ai算法//默认先向下走，如果遇到障碍就向右不行就向上，再不行就向左（类似于一个默认键盘）然后完成一个类似于player的对障碍的判断
{
	auto s = (Sprite*)pSender;//this->getParent();
	auto move = MoveBy::create(1.0, Point(_player->_player->getPosition().x - s->getPosition().x>0 ? 10 : -10,
		                                  _player->_player->getPosition().y - s->getPosition().y>0 ? 10 : -10));
	
	auto func = CallFuncN::create(CC_CALLBACK_1(MonsterAI::goon, this));//反复调用移动
	s->runAction(Sequence::create(move, func, NULL));
}

void MonsterAI::JudegeAttack(float dt)
{
	log("success");
	//4 在monster所在位置创建一个飞镖，将其添加到场景中
	auto projectile = Sprite::create("Projectile2.png");

	projectile->setPosition(Point(this->getParent()->getPosition().x, this->getParent()->getPosition().y));
	log("%f,%f", projectile->getPosition().x, projectile->getPosition().y);

    this->getParent()->getParent()->addChild(projectile);//为什么总是在hero后面¬_¬
	projectile->setGlobalZOrder(1);
	//不能生成一次就只查一次啊，要从生成那刻开始不停地更
	//新状态直到被销毁那就应该在这里有个计时器，但是什么计时器可以支持有参数地函数更新呢

    proj = projectile;

	this->schedule(schedule_selector(MonsterAI::BoundDetect), 0.1f);

	auto actionMove = MoveTo::create(2.0f,_player->_player->getPosition());
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(MonsterAI::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(MonsterAI::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行的

	projectile->runAction(Sequence::create(actionMove,callFunc2,callFunc1, nullptr));
	
}

void MonsterAI::DelayUnschedule(Node *pSender)
{
	if (proj != NULL)
	{
	   log("successful111");
       this->unschedule(schedule_selector(MonsterAI::BoundDetect));
	}

}

void MonsterAI::IfActionRemove(Node *pSender)
{
	if (proj!= NULL)
	{
		auto actionRemove = RemoveSelf::create();
		proj->runAction(actionRemove);
	}
}

//想让他不是每次更新都重新传一次这样s的值就不是对应projecttile的值了
//这个更新只对于一个怪物而言的即每个怪物一个proj作为中间传值的量，关键在于飞镖是2.0秒产生一个的，为了让两个projecttile
//的值不互相影响在下一个产生之前即在2s内必须完成飞镖的创建运动且在这个过程中监控是否打到了player
void MonsterAI::BoundDetect(float dt)
{
	log("hhh");
	
	//log("playergetBoundBox");
	//log("%f,%f", _player->_player->getPosition().x, _player->_player->getPosition().y);
	//log("%f,%f", _player->_player->getContentSize().width, _player->_player->getContentSize().height);
	//log("%f,%f,%f,%f", _player->_player->getBoundingBox().getMinX(), _player->_player->getBoundingBox().getMaxX(), _player->_player->getBoundingBox().getMinY(), _player->_player->getBoundingBox().getMaxY());

   // log("monstergetBoundBox");
    //log("%f,%f", proj->getPosition().x, proj->getPosition().y);
	//log("%f,%f", proj->getContentSize().width, proj->getContentSize().height);
	//log("%f,%f,%f,%f",proj->getBoundingBox().getMinX(), proj->getBoundingBox().getMaxX(), proj->getBoundingBox().getMinY(), proj->getBoundingBox().getMaxY());
	
	if (_player->_player->getBoundingBox().intersectsRect(this->proj->getBoundingBox()))
	{
		log("true");
		reduceblood = true;
		this->unschedule(schedule_selector(MonsterAI::BoundDetect));//先停止更新再移除否则更新要出错
		auto actionRemove = RemoveSelf::create();
		proj->runAction(actionRemove);

		//此时就应该要移除而不是等到remove！！！！！！！！！！
	}
}
