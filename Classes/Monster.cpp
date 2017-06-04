#include"Monster.h"
#include"MonsterAI.h"
#include"ControlLayer.h"//为的是那个物理的类

bool Monster::init()
{
	ptm = 0;
	log("%f,%f", monsterarray[ptm].x, monsterarray[ptm].y);
	log("yyyyy");
	//srand((unsigned int)time(nullptr));//自动生成怪物?
    this->schedule(schedule_selector(Monster::addMonster), 5);//改成了5就不出错了？？？！


	return true;
}


void Monster::addMonster(float dt)
{
	
	//初始化敌人精灵
	auto enemySprite = Sprite::create("panghu.png");

	//1 为Monster添加了碰撞属性
	auto monsterSize = enemySprite->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width, monsterSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//2 属性设置为Dynamic，这样就能让我们3通过我们刚定义的MoveTo来控制移动//
	physicsBody->setDynamic(true);
	//3
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
	//4
	enemySprite->setPhysicsBody(physicsBody);

	float x;
	float y;

	if (ptm < 4)
	{
	    x = monsterarray[ptm].x;
		y = monsterarray[ptm].y;
		ptm++;
	}
	else
	{
		return;
	}
	enemySprite->setPosition(Point(x, y));
	enemySprite->setAnchorPoint(Point(0, 0));
	_tileMap->addChild(enemySprite);
	enemySprite->setGlobalZOrder(1);

	auto monsterai =new MonsterAI;//控制monster的行为
	monsterai->_player =_player;
	monsterai->_tileMap = _tileMap;
	monsterai->_meta = _meta;
	monsterai->_fruit = _fruit;
	monsterai->proj = NULL;
	enemySprite->addChild(monsterai);
	monsterai->StartListen();

	return;
}
