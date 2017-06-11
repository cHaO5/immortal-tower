#include "Monster/Monster1.h"
#include"Data/GameManager.h"

USING_NS_CC;

Monster1* Monster1::createMonster(Vec2 Position)
{
	auto Sprite = new Monster1();
	Sprite->position = Position;
	if (Sprite && Sprite->init()) {
		Sprite->autorelease();
		return Sprite;
	}
	CC_SAFE_DELETE(Sprite);

	return NULL;
}

bool Monster1::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	log("Monster1 create");
	baseMonster = Sprite::create(GameManager::getInstance()->Monster_texture[0][2]);

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

void Monster1::Attack(float dt)//��ͬ�ֵĹ�����ʽ��ͬ��������д������ʽ
{
	log("Monater0 attack create");
	//4��monster����λ�ô���һ�����ڣ�������ӵ�������
	auto monsterattack = Sprite::create("Projectile2.png");
	monsterattack->setPosition(baseMonster->getPosition());
	addChild(monsterattack);
	Monster1_weapon = monsterattack;
	this->schedule(schedule_selector(Monster1::BoundDetect), 0.01f);
	log("before weapon move");
	auto actionMove = MoveTo::create(1.0f, GameManager::getInstance()->currentPlayer->getPosition());
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Monster1::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(Monster1::IfActionRemove, this));//������functionֻ�����ƶ�������û�л���û����ǰֹͣ���²��Ƴ���ִ��
	monsterattack->runAction(Sequence::create(actionMove, callFunc2, callFunc1, nullptr));

}
void Monster1::DelayUnschedule(Node *pSender)
{
	if (Monster1_weapon != NULL)
	{
		log("successful111");
		this->unschedule(schedule_selector(Monster1::BoundDetect));
	}

}

void Monster1::IfActionRemove(Node *pSender)
{
	if (Monster1_weapon != NULL)
	{
		auto actionRemove = RemoveSelf::create();
		Monster1_weapon->runAction(actionRemove);
	}
}

void Monster1::BoundDetect(float dt)
{

	if (GameManager::getInstance()->currentPlayer->getBoundingBox().intersectsRect(Monster1_weapon->getBoundingBox()))
	{
		GameManager::getInstance()->PlayerReduceBlood[1]++;
		this->unschedule(schedule_selector(Monster1::BoundDetect));//��ֹͣ�������Ƴ��������Ҫ����
		auto actionRemove = RemoveSelf::create();
		Monster1_weapon->runAction(actionRemove);
	}
}
