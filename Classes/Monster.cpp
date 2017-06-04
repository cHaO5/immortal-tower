#include"Monster.h"
#include"MonsterAI.h"
#include"ControlLayer.h"//Ϊ�����Ǹ��������

bool Monster::init()
{
	ptm = 0;
	log("%f,%f", monsterarray[ptm].x, monsterarray[ptm].y);
	log("yyyyy");
	//srand((unsigned int)time(nullptr));//�Զ����ɹ���?
    this->schedule(schedule_selector(Monster::addMonster), 5);//�ĳ���5�Ͳ������ˣ�������


	return true;
}


void Monster::addMonster(float dt)
{
	
	//��ʼ�����˾���
	auto enemySprite = Sprite::create("panghu.png");

	//1 ΪMonster�������ײ����
	auto monsterSize = enemySprite->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width, monsterSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//2 ��������ΪDynamic����������������3ͨ�����Ǹն����MoveTo�������ƶ�//
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

	auto monsterai =new MonsterAI;//����monster����Ϊ
	monsterai->_player =_player;
	monsterai->_tileMap = _tileMap;
	monsterai->_meta = _meta;
	monsterai->_fruit = _fruit;
	monsterai->proj = NULL;
	enemySprite->addChild(monsterai);
	monsterai->StartListen();

	return;
}
