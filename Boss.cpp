#include "Boss.hpp"
#include "GameManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "AnimationManager.hpp"

Boss* Boss::createMonster(Vec2 Position)
{
    auto Sprite = new Boss();
    Sprite->position = Position;
    if (Sprite && Sprite->init()) {
        Sprite->autorelease();
        return Sprite;
    }
    CC_SAFE_DELETE(Sprite);
    
    return NULL;
}




bool Boss::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    log("boss create");
    
    
    baseMonster = Sprite::create(GameManager::getInstance()->Monster_texture[3][0]);
    
    
    log("%fvvv%f",GameManager::getInstance()->currentPlayer->getPosition().x,GameManager::getInstance()->currentPlayer->getPosition().y);
    auto monsterSize = baseMonster->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width, monsterSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
    physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
    physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
    baseMonster->setPhysicsBody(physicsBody);
    
    
    baseMonster->setPosition(position);
    addChild(baseMonster);
    
    StartListen();
    return true;
}


void Boss::Attack(float dt)//不同怪的攻击方式不同在这里重写攻击方式
{
    //srand(time(NULL));
    //int i=rand()%10+1;
    srand(time(NULL));
    int p=rand()%3+1;

    auto monsterattack = CSLoader::getInstance()->createNodeWithFlatBuffersFile(StringUtils::format("weapon%d.csb",p));
    auto nodetimeline = CSLoader::createTimeline(StringUtils::format("weapon%d.csb",p));
    monsterattack->runAction( nodetimeline );
    nodetimeline->gotoFrameAndPlay(0,80,true);
    //monsterattack->setPosition(position);
    //addChild(monsterattack);
    
        
    Vec2 endPos = Vec2(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
    Vec2 startPos = Vec2(baseMonster->getPosition().x, baseMonster->getPosition().y);
    Vec2 dis = endPos - startPos;
    monsterattack->setPosition(baseMonster->getPosition());
    int angle;
    if (p==1) angle=180;
    if (p==2) angle=270;
    if (p==3) angle=270+180;
    monsterattack->setRotation(Vec2(dis.y, dis.x).getAngle() / 3.14f * 180+angle);
    addChild(monsterattack);
    boss_weapon = monsterattack;
    this->schedule(schedule_selector(Boss::BoundDetect), 0.01f);
    
    log("before weapon move");
    auto actionMove = MoveTo::create(0.4f, endPos);
    auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Boss::DelayUnschedule, this));
    auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(Boss::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行
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
void Boss::DelayUnschedule(Node *pSender)
{
    if (boss_weapon != NULL)
    {
        log("successful111");
        this->unschedule(schedule_selector(Boss::BoundDetect));
    }
    
}

void Boss::IfActionRemove(Node *pSender)
{
    if (boss_weapon != NULL)
    {
        auto actionRemove = RemoveSelf::create();
        boss_weapon->runAction(actionRemove);
    }
}

void Boss::BoundDetect(float dt)
{
    
    if (GameManager::getInstance()->currentPlayer->getBoundingBox().intersectsRect(boss_weapon->getBoundingBox()))
    {
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
        
        GameManager::getInstance()->PlayerReduceBlood[3]++;
        this->unschedule(schedule_selector(Boss::BoundDetect));//先停止更新再移除否则更新要出错
        auto actionRemove = RemoveSelf::create();
        boss_weapon->runAction(actionRemove);
    }
}

void Boss::StartListen()
{
    log("boss StartListen create");
    this->schedule(schedule_selector(Boss::FollowMove), 3.0f);
}

void Boss::FollowMove(float dt)
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
        this->unschedule(schedule_selector(Boss::FollowMove));
        auto func = CallFuncN::create(CC_CALLBACK_1(Boss::Move, this));//让怪物移动
        baseMonster->runAction(func);
        
        
        if (dis <= 600)//开始攻击
        {
            log("before attack");
            this->schedule(schedule_selector(BaseMonster::Attack), 1.5f);
        }
    }
}

void Boss::Move(Node *pSender)//此处加入ai算法
{
    //log("Monater0 Move create");
    int tempMonsterX=static_cast<int>(baseMonster->getPosition().x / GameManager::getInstance()->TileSizewidth);
    int tempMonsterY=static_cast<int>((GameManager::getInstance()->MapSizeheight *  GameManager::getInstance()->TileSizeheight - baseMonster->getPosition().y) / GameManager::getInstance()->TileSizeheight);
    int tempPlayerX=static_cast<int>(GameManager::getInstance()->currentPlayer->getPosition().x / GameManager::getInstance()->TileSizewidth);
    int finalX=tempMonsterX;
    int finalY=tempMonsterY;
    if (finalX+1<tempPlayerX) {
        if (GameManager::getInstance()->Level0LogicMap[finalX+3][finalY]!=1) {
            finalX=finalX+3;
            baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("flyr")));
        }
    }
    else if (finalX-1>tempPlayerX) {
        if (GameManager::getInstance()->Level0LogicMap[finalX-3][finalY]!=1) {
            finalX=finalX-3;
            baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("flyl")));
        }
    }
    else baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("boss")));

    
    finalY=30-finalY;
    auto move = MoveTo::create(0.8, Point(finalX*128,finalY*128));
    auto func = CallFuncN::create(CC_CALLBACK_1(BaseMonster::Move, this));//反复调用移动
    baseMonster->runAction(Sequence::create(move, func, NULL));

}

