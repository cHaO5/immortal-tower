#include "Monster1.h"
#include"GameManager.h"

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
    

    baseMonster = Sprite::create(GameManager::getInstance()->Monster_texture[1][2]);

	
        log("%fvvv%f",GameManager::getInstance()->currentPlayer->getPosition().x,GameManager::getInstance()->currentPlayer->getPosition().y);
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


void Monster1::Attack(float dt)//不同怪的攻击方式不同在这里重写攻击方式
{
	log("Monater0 attack create");
	//4在monster所在位置创建一个飞镖，将其添加到场景中
    
    auto monsterattack = CSLoader::getInstance()->createNodeWithFlatBuffersFile("weapon1.csb");
    auto nodetimeline = CSLoader::createTimeline("weapon1.csb");
    //monsterattack->setPosition(position);
    //addChild(monsterattack);
    monsterattack->runAction( nodetimeline );
    nodetimeline->gotoFrameAndPlay(0,80,true);
    Vec2 endPos = Vec2(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
    Vec2 startPos = Vec2(baseMonster->getPosition().x, baseMonster->getPosition().y);
    Vec2 dis = endPos - startPos;
    float x= GameManager::getInstance()->currentPlayer->getPosition().x - baseMonster->getPosition().x;
    float y= GameManager::getInstance()->currentPlayer->getPosition().y - baseMonster->getPosition().y;
    auto d = sqrt(pow(x, 2) + pow(y, 2));
    if (d<500){
	monsterattack->setPosition(baseMonster->getPosition());
    monsterattack->setRotation(Vec2(dis.y, dis.x).getAngle() / 3.14f * 180+180);
	addChild(monsterattack);
	Monster1_weapon = monsterattack;
    auto pic=GameManager::getInstance()->currentPlayer->getTexture();
	this->schedule(schedule_selector(Monster1::BoundDetect), 0.01f);
    GameManager::getInstance()->currentPlayer->setTexture(pic);
	log("before weapon move");
	auto actionMove = MoveTo::create(0.4f, endPos);
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Monster1::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(Monster1::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行
	monsterattack->runAction(Sequence::create(actionMove, callFunc2, callFunc1, nullptr));
    }

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
		this->unschedule(schedule_selector(Monster1::BoundDetect));//先停止更新再移除否则更新要出错
		auto actionRemove = RemoveSelf::create();
		Monster1_weapon->runAction(actionRemove);
	}
}
