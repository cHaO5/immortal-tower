#include "Monster/Monster2.h"
#include"Data/GameManager.h"

USING_NS_CC;

Monster2* Monster2::createMonster(Vec2 Position)
{
	auto Sprite = new Monster2();
	Sprite->position = Position;
	if (Sprite && Sprite->init()) {
		Sprite->autorelease();
		return Sprite;
	}
	CC_SAFE_DELETE(Sprite);

	return NULL;
}

bool Monster2::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	log("Monster2 create");
	baseMonster = Sprite::create(GameManager::getInstance()->Monster_texture[0][2]);
	baseMonster->setAnchorPoint(Point(0.5, 0.25));

	auto monsterSize = baseMonster->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width, monsterSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
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

void Monster2::Attack(float dt)//不同怪的攻击方式不同在这里重写攻击方式
{
	log("Monater0 attack create");
	//4在monster所在位置创建一个飞镖，将其添加到场景中
	auto monsterattack = Sprite::create("Projectile2.png");
	monsterattack->setPosition(baseMonster->getPosition());
	addChild(monsterattack);
	Monster2_weapon = monsterattack;
	this->schedule(schedule_selector(Monster2::BoundDetect), 0.01f);
	log("before weapon move");
	auto actionMove = MoveTo::create(1.0f, GameManager::getInstance()->currentPlayer->getPosition());
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Monster2::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(Monster2::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行
	monsterattack->runAction(Sequence::create(actionMove, callFunc2, callFunc1, nullptr));

}
void Monster2::DelayUnschedule(Node *pSender)
{
	if (Monster2_weapon != NULL)
	{
		log("successful111");
		this->unschedule(schedule_selector(Monster2::BoundDetect));
	}

}

void Monster2::IfActionRemove(Node *pSender)
{
	if (Monster2_weapon != NULL)
	{
		auto actionRemove = RemoveSelf::create();
		Monster2_weapon->runAction(actionRemove);
	}
}

void Monster2::BoundDetect(float dt)
{

	if (GameManager::getInstance()->currentPlayer->getBoundingBox().intersectsRect(Monster2_weapon->getBoundingBox()))
	{
		GameManager::getInstance()->PlayerReduceBlood[2]++;
		this->unschedule(schedule_selector(Monster2::BoundDetect));//先停止更新再移除否则更新要出错
		auto actionRemove = RemoveSelf::create();
		Monster2_weapon->runAction(actionRemove);
	}
}
