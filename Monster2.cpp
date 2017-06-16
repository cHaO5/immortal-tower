#include "Monster2.h"
#include"GameManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include<math.h>
#include<cmath>
#include<queue>

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
	baseMonster = Sprite::create("U-1.png");

	auto monsterSize = baseMonster->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width, monsterSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
	baseMonster->setPhysicsBody(physicsBody);
    baseMonster->setPosition(position);
	addChild(baseMonster, 2);

	StartListen();

	return true;
}

void Monster2::Attack(float dt)//��ͬ�ֵĹ�����ʽ��ͬ��������д������ʽ
{
	log("Monater0 attack create");
	//4��monster����λ�ô���һ�����ڣ�������ӵ�������
    float x = GameManager::getInstance()->currentPlayer->getPosition().x - baseMonster->getPosition().x;
    float y = GameManager::getInstance()->currentPlayer->getPosition().y - baseMonster->getPosition().y;
    auto dis = sqrt(pow(x, 2) + pow(y, 2));
    if (dis<512){
    Monster2_weapon = 2;
	this->schedule(schedule_selector(Monster2::BoundDetect), 0.03f);
        Vec2 endPos = Vec2(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
        Vec2 startPos = Vec2(baseMonster->getPosition().x, baseMonster->getPosition().y);
        Vec2 dis = endPos - startPos;
        auto arc=Vec2(dis.y, dis.x).getAngle();
        auto animation = Animation::create();
        char nameSize[20] = {0};
        bool flag=1;
        Vector< SpriteFrame* > frameVec;
        if (arc > -0.3926 && arc <= 0.3926) {  //turn U
            sprintf(nameSize, "U-1attacked.png");
            animation->addSpriteFrameWithFile(nameSize);
            sprintf(nameSize, "U.png");
            animation->addSpriteFrameWithFile(nameSize);
            flag=0;
        } else if (arc > 0.3926 && arc <= 1.1781) {  //turn UR
            sprintf(nameSize, "UR-1attacked.png");
            animation->addSpriteFrameWithFile(nameSize);
            sprintf(nameSize, "UR.png");
            animation->addSpriteFrameWithFile(nameSize);
            flag=0;
        } else if (arc > 1.1781 && arc <= 1.9635) {  //turn R
            sprintf(nameSize, "R-1attacked.png");
            animation->addSpriteFrameWithFile(nameSize);
            sprintf(nameSize, "R.png");
            animation->addSpriteFrameWithFile(nameSize);
            flag=0;
        } else if (arc > 1.9635 && arc <= 2.7489) {  //turn DR
            sprintf(nameSize, "DR-1attacked.png");
            animation->addSpriteFrameWithFile(nameSize);
            sprintf(nameSize, "DR.png");
            animation->addSpriteFrameWithFile(nameSize);
            flag=0;
        } else if (arc > 2.7489 || arc <= -2.7489) {  //turn D
            sprintf(nameSize, "D-1attacked.png");
            animation->addSpriteFrameWithFile(nameSize);
            sprintf(nameSize, "D.png");
            animation->addSpriteFrameWithFile(nameSize);
            flag=0;
        } else if (arc > -1.1781 && arc <= -0.3926) {  //turn UL
            sprintf(nameSize, "UL-1attacked.png");
            animation->addSpriteFrameWithFile(nameSize);
            sprintf(nameSize, "UL.png");
            animation->addSpriteFrameWithFile(nameSize);
            flag=0;
        } else if (arc > -1.9635 && arc <= -1.1781) {  //turn L
            sprintf(nameSize, "L-1attacked.png");
            animation->addSpriteFrameWithFile(nameSize);
            sprintf(nameSize, "L.png");
            animation->addSpriteFrameWithFile(nameSize);
            flag=0;
        } else if (arc > -2.7489 && arc <= -1.9635) {  //turn DL
            sprintf(nameSize, "DL-1attacked.png");
            animation->addSpriteFrameWithFile(nameSize);
            sprintf(nameSize, "DL.png");
            animation->addSpriteFrameWithFile(nameSize);
            flag=0;
        }
        if (flag==0){
            animation->setDelayPerUnit(0.1f);
            animation->setLoops(1);
            animation->setRestoreOriginalFrame(true);
            auto animate = Animate::create(animation);
            GameManager::getInstance()->currentPlayer->runAction(animate);
            /*Blink *blink = Blink::create(0.3f, 2);
             GameManager::getInstance()->currentPlayer->runAction(blink);
             GameManager::getInstance()->currentPlayer->setVisible(true);*/
        }

	log("before weapon move");
    GameManager::getInstance()->PlayerReduceBlood[2]++;
	Monster2_weapon = 1;
	//������functionֻ�����ƶ�������û�л���û����ǰֹͣ���²��Ƴ���ִ��
    }
}
void Monster2::DelayUnschedule(Node *pSender)
{
	if (Monster2_weapon ==2)
	{
		log("successful111");
		this->unschedule(schedule_selector(Monster2::BoundDetect));
	}

}

void Monster2::BoundDetect(float dt)
{
		this->unschedule(schedule_selector(Monster2::BoundDetect));//��ֹͣ�������Ƴ��������Ҫ����
		Monster2_weapon=1;
}
