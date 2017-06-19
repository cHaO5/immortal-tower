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
	baseMonster = Sprite::create(GameManager::getInstance()->Monster_texture[1][2]);
	auto monsterSize = baseMonster->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width, monsterSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
	baseMonster->setPhysicsBody(physicsBody);
    baseMonster->setPosition(position);
	addChild(baseMonster, 0,3);

	StartListen();

	return true;
}

void Monster2::Attack(float dt)//不同怪的攻击方式不同在这里重写攻击方式
{
	log("Monater0 attack create");
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
        Vector< SpriteFrame* > frameVec;
        int i=1;
        if (arc > -0.3926 && arc <= 0.3926) {  //turn U
            GameManager::getInstance()->currentPlayer->setTexture(StringUtils::format("player%dD.png",i));
        } else if (arc > 0.3926 && arc <= 1.1781) {  //turn UR
            GameManager::getInstance()->currentPlayer->setTexture(StringUtils::format("player%dDL.png",i));
        } else if (arc > 1.1781 && arc <= 1.9635) {  //turn R
            GameManager::getInstance()->currentPlayer->setTexture(StringUtils::format("player%dL.png",i));
        } else if (arc > 1.9635 && arc <= 2.7489) {  //turn DR
            GameManager::getInstance()->currentPlayer->setTexture(StringUtils::format("player%dUL.png",i));
        } else if (arc > 2.7489 || arc <= -2.7489) {  //turn D
            GameManager::getInstance()->currentPlayer->setTexture(StringUtils::format("player%dU.png",i));
        } else if (arc > -1.1781 && arc <= -0.3926) {  //turn UL
            GameManager::getInstance()->currentPlayer->setTexture(StringUtils::format("player%dDR.png",i));
        } else if (arc > -1.9635 && arc <= -1.1781) {  //turn L
            GameManager::getInstance()->currentPlayer->setTexture(StringUtils::format("player%dR.png",i));
        } else if (arc > -2.7489 && arc <= -1.9635) {  //turn DL
            GameManager::getInstance()->currentPlayer->setTexture(StringUtils::format("player%dUR.png",i));
        }
        

        
    GameManager::getInstance()->PlayerReduceBlood[2]++;
	Monster2_weapon = 1;
	//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行
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
    this->unschedule(schedule_selector(Monster2::BoundDetect));//先停止更新再移除否则更新要出错
    Monster2_weapon=1;
    int i=1;
    Vec2 endPos = Vec2(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
    Vec2 startPos = Vec2(baseMonster->getPosition().x, baseMonster->getPosition().y);
    Vec2 dis = endPos - startPos;
    auto arc=Vec2(dis.y, dis.x).getAngle();
    Vector< SpriteFrame* > frameVec;
    if (arc > -0.3926 && arc <= 0.3926) {  //turn U
        GameManager::getInstance()->currentPlayer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("player%dattackedD",i))));
    } else if (arc > 0.3926 && arc <= 1.1781) {  //turn UR
        GameManager::getInstance()->currentPlayer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("player%dattackedDL",i))));
    } else if (arc > 1.1781 && arc <= 1.9635) {  //turn R
        GameManager::getInstance()->currentPlayer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("player%dattackedL",i))));
    } else if (arc > 1.9635 && arc <= 2.7489) {  //turn DR
        GameManager::getInstance()->currentPlayer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("player%dattackedUL",i))));
    } else if (arc > 2.7489 || arc <= -2.7489) {  //turn D
        GameManager::getInstance()->currentPlayer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("player%dattackedU",i))));
    } else if (arc > -1.1781 && arc <= -0.3926) {  //turn UL
        GameManager::getInstance()->currentPlayer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("player%dattackedDR",i))));
    } else if (arc > -1.9635 && arc <= -1.1781) {  //turn L
        GameManager::getInstance()->currentPlayer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("player%dattackedR",i))));
    } else if (arc > -2.7489 && arc <= -1.9635) {  //turn DL
        GameManager::getInstance()->currentPlayer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("player%dattackedUR",i))));
    }
}
