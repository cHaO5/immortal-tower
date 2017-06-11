#include "Monster/Monster0.h"
#include"Data/GameManager.h"

USING_NS_CC;

Monster0* Monster0::createMonster(Vec2 Position)
{
	auto Sprite = new Monster0();
	Sprite->position = Position;
	if (Sprite && Sprite->init()) {
		Sprite->autorelease();
		return Sprite;
	}
	CC_SAFE_DELETE(Sprite);

	return NULL;
}

bool Monster0::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	log("Monster0 create");
	baseMonster = Sprite::create(GameManager::getInstance()->Monster_texture[0][2]);

	auto monsterSize = baseMonster->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(monsterSize.width/2);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
	baseMonster->setPhysicsBody(physicsBody);

	baseMonster->setPosition(position);
	addChild(baseMonster, 0);

	StartListen();

	return true;
}

void Monster0::Attack(float dt)//不同怪的攻击方式不同在这里重写攻击方式
{
	log("Monater0 attack create");
	//4在monster所在位置创建一个飞镖，将其添加到场景中
	auto monsterattack = Sprite::create("Projectile2.png");
	monsterattack->setPosition(baseMonster->getPosition());
	addChild(monsterattack);
	Monster0_weapon = monsterattack;
	this->schedule(schedule_selector(Monster0::BoundDetect), 0.01f);
	log("before weapon move");
	auto actionMove = MoveTo::create(1.0f, GameManager::getInstance()->currentPlayer->getPosition());
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Monster0::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(Monster0::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行
	monsterattack->runAction(Sequence::create(actionMove, callFunc2, callFunc1, nullptr));

}
void Monster0::DelayUnschedule(Node *pSender)
{
	if (Monster0_weapon!= NULL)
	{
		log("successful111");
		this->unschedule(schedule_selector(Monster0::BoundDetect));
	}

}

void Monster0::IfActionRemove(Node *pSender)
{
	if (Monster0_weapon != NULL)
	{
		auto actionRemove = RemoveSelf::create();
		Monster0_weapon->runAction(actionRemove);
	}
}

void Monster0::BoundDetect(float dt)
{

	if (GameManager::getInstance()->currentPlayer->getBoundingBox().intersectsRect(Monster0_weapon->getBoundingBox()))
	{
		log("-10");
		GameManager::getInstance()->PlayerReduceBlood[0]++;
		this->unschedule(schedule_selector(Monster0::BoundDetect));//先停止更新再移除否则更新要出错
		auto actionRemove = RemoveSelf::create();
		Monster0_weapon->runAction(actionRemove);
	}
}
