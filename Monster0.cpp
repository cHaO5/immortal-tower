#include "Monster0.h"
#include "GameManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "AnimationManager.hpp"
#include"ControlLayer.h"
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
    
   
    
    baseMonster = Sprite::create("batD-1.png");
    //AnimationManager::getInstance()->init_bat();
    baseMonster->setPosition(position);
    addChild(baseMonster,0,1);
    log("PreAnimationGet");
    auto A=Animate::create(AnimationCache::getInstance()->getAnimation( "batD" ));
    log("AnimationGet");
    baseMonster->runAction(A);
    log("Monster0 createAnimation");
    
    auto monsterSize = baseMonster->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(monsterSize.width/2);
	physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
    baseMonster->setPhysicsBody(physicsBody);
	
    
	//this->addChild(baseMonster);
    /*if (action)
    {
        baseMonster->runAction(action);
        action->gotoFrameAndPlay(0);
    }*/
	StartListen();

	return true;
}

void Monster0::Attack(float dt)//不同怪的攻击方式不同在这里重写攻击方式
{
	log("Monater0 attack create");
	log("before weapon move");
	
    auto monsterattack = CSLoader::getInstance()->createNodeWithFlatBuffersFile("weapon2.csb");
    auto nodetimeline = CSLoader::createTimeline("weapon2.csb");
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
        monsterattack->setRotation(Vec2(dis.y, dis.x).getAngle() / 3.14f * 180+270);
        addChild(monsterattack,0,0);
        Monster0_weapon = monsterattack;
        this->schedule(schedule_selector(Monster0::BoundDetect), 0.01f);
        
        log("before weapon move");
        auto actionMove = MoveTo::create(0.4f, endPos);
        auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Monster0::DelayUnschedule, this));
        auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(Monster0::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行
        Vec2 startPos = Vec2(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
        Vec2 endPos = Vec2(baseMonster->getPosition().x, baseMonster->getPosition().y);
        Vec2 dis = endPos - startPos;
        auto arc=Vec2(dis.y, dis.x).getAngle();
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

        
        monsterattack->runAction(Sequence::create(actionMove, callFunc2, callFunc1, nullptr));
    }
}

void Monster0::StartListen()
{
    log("Monater0 StartListen create");
    this->schedule(schedule_selector(Monster0::FollowMove), 1.0f);
}

void Monster0::FollowMove(float dt)
{
    
    float x= GameManager::getInstance()->currentPlayer->getPosition().x - BaseMonster::baseMonster->getPosition().x;
    float y= GameManager::getInstance()->currentPlayer->getPosition().y - BaseMonster::baseMonster->getPosition().y;
    
    log("Monater0 followrun create");
    //先计算怪物和英雄的距离
    auto dis = sqrt(pow(x, 2) + pow(y, 2));
    if (dis >= 2000)//当怪物与英雄距离超2000
        return;
    if (dis <= 1000)//在怪物可视范围内，怪物开始移动
    {
        this->unschedule(schedule_selector(Monster0::FollowMove));
        auto func = CallFuncN::create(CC_CALLBACK_1(Monster0::Move, this));//让怪物移动
        baseMonster->runAction(func);
        

        if (dis <= 600)//开始攻击
        {
            log("before attack");
            this->schedule(schedule_selector(BaseMonster::Attack), 1.5f);
        }
    }
}

void Monster0::Move(Node *pSender)
{
    log("Monater0 Move create");
    Vec2 endPos = Vec2(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
    Vec2 startPos = Vec2(baseMonster->getPosition().x, baseMonster->getPosition().y);
    Vec2 dis = endPos - startPos;
    auto arc=Vec2(dis.y, dis.x).getAngle();
    //AnimationManager::getInstance()->init_bat();
    if (arc > -0.3926 && arc <= 0.3926) {  //turn U
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("batU")));
    } else if (arc > 0.3926 && arc <= 1.1781) {  //turn UR
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("batUR")));
    } else if (arc > 1.1781 && arc <= 1.9635) {  //turn R
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("batR")));
    } else if (arc > 1.9635 && arc <= 2.7489) {  //turn DR
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("batDR")));
    } else if (arc > 2.7489 || arc <= -2.7489) {  //turn D
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("batD")));
    } else if (arc > -1.1781 && arc <= -0.3926) {  //turn UL
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("batUL")));
    } else if (arc > -1.9635 && arc <= -1.1781) {  //turn L
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("batL")));
    } else if (arc > -2.7489 && arc <= -1.9635) {  //turn DL
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("batDL")));
    }
    
    auto move = MoveBy::create(1.0, Point(GameManager::getInstance()->currentPlayer->getPosition().x - baseMonster->getPosition().x >0 ? 128 : -128,
                                          GameManager::getInstance()->currentPlayer->getPosition().y - baseMonster->getPosition().y >0 ? 128 : -128));
    auto func = CallFuncN::create(CC_CALLBACK_1(BaseMonster::Move, this));//反复调用移动
    baseMonster->runAction(Sequence::create(move, func, NULL));
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
        
        Vec2 endPos = Vec2(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
        Vec2 startPos = Vec2(baseMonster->getPosition().x, baseMonster->getPosition().y);
        Vec2 dis = endPos - startPos;
        auto arc=Vec2(dis.y, dis.x).getAngle();
       
        Vector< SpriteFrame* > frameVec;
        int i=1;
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
        
        GameManager::getInstance()->PlayerReduceBlood[1]++;
        this->unschedule(schedule_selector(Monster0::BoundDetect));//先停止更新再移除否则更新要出错
		auto actionRemove = RemoveSelf::create();
		Monster0_weapon->runAction(actionRemove);
	}
    
}


