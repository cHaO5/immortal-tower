#include "Monster1.h"
#include"GameManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include<math.h>
#include<cmath>
#include<queue>
#include"ControlLayer.h"
USING_NS_CC;

struct node
{
    int x,y,step;
};

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
	addChild(baseMonster, 0,2);

    
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
    monsterattack->setPosition(baseMonster->getPosition());
    monsterattack->setRotation(Vec2(dis.y, dis.x).getAngle() / 3.14f * 180+180);
    addChild(monsterattack,0,0);
    Monster1_weapon = monsterattack;
    this->schedule(schedule_selector(Monster1::BoundDetect), 0.01f);
        
    log("before weapon move");
    auto actionMove = MoveTo::create(0.4f, endPos);
    auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Monster1::DelayUnschedule, this));
    auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(Monster1::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行
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
		this->unschedule(schedule_selector(Monster1::BoundDetect));//先停止更新再移除否则更新要出错
		auto actionRemove = RemoveSelf::create();
		Monster1_weapon->runAction(actionRemove);
	}
}

void Monster1::StartListen()
{
    log("Monater0 StartListen create");
    this->schedule(schedule_selector(Monster1::FollowMove), 0.5f);
}

void Monster1::FollowMove(float dt)
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
        this->unschedule(schedule_selector(Monster1::FollowMove));
        auto func = CallFuncN::create(CC_CALLBACK_1(Monster1::Move, this));//让怪物移动
        baseMonster->runAction(func);
        
        
        if (dis <= 600)//开始攻击
        {
            log("before attack");
            this->schedule(schedule_selector(BaseMonster::Attack), 1.5f);
        }
    }
}

void Monster1::Move(Node *pSender)//此处加入ai算法
{
    //log("Monater0 Move create");
    Vec2 endPos = Vec2(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
    Vec2 startPos = Vec2(baseMonster->getPosition().x, baseMonster->getPosition().y);
    Vec2 dis = endPos - startPos;
    auto arc=Vec2(dis.y, dis.x).getAngle();
    if (arc > -0.3926 && arc <= 0.3926) {  //turn U
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("skeletonU")));
    } else if (arc > 0.3926 && arc <= 1.1781) {  //turn UR
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("skeletonUR")));
    } else if (arc > 1.1781 && arc <= 1.9635) {  //turn R
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("skeletonR")));
    } else if (arc > 1.9635 && arc <= 2.7489) {  //turn DR
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("skeletonDR")));
    } else if (arc > 2.7489 || arc <= -2.7489) {  //turn D
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("skeletonD")));
    } else if (arc > -1.1781 && arc <= -0.3926) {  //turn UL
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("skeletonUL")));
    } else if (arc > -1.9635 && arc <= -1.1781) {  //turn L
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("skeletonL")));
    } else if (arc > -2.7489 && arc <= -1.9635) {  //turn DL
        baseMonster->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("skeletonDL")));
    }


    
    int Map[30][30];
    for (int i=0;i<30;i++)
        for (int j=0;j<30;j++)
            Map[i][j]=GameManager::getInstance()->Level0LogicMap0[i][j];
    int dx[4]={-1, 1, 0, 0};
    int dy[4]={ 0, 0, 1,-1};
    
    
    int tempMonsterX=static_cast<int>(baseMonster->getPosition().x / GameManager::getInstance()->TileSizewidth);
    int tempMonsterY=static_cast<int>((GameManager::getInstance()->MapSizeheight *  GameManager::getInstance()->TileSizeheight - baseMonster->getPosition().y) / GameManager::getInstance()->TileSizeheight);
    int tempPlayerX=static_cast<int>(GameManager::getInstance()->currentPlayer->getPosition().x / GameManager::getInstance()->TileSizewidth);
    int tempPlayerY=static_cast<int>((GameManager::getInstance()->MapSizeheight *  GameManager::getInstance()->TileSizeheight - GameManager::getInstance()->currentPlayer->getPosition().y) / GameManager::getInstance()->TileSizeheight);
    float x= GameManager::getInstance()->currentPlayer->getPosition().x - baseMonster->getPosition().x;
    float y= GameManager::getInstance()->currentPlayer->getPosition().y - baseMonster->getPosition().y;
    std::queue<node>Que;
    while (Que.size()!=0) Que.pop();
    node cur,next,ans[30][30];
    cur.x=tempMonsterX;
    cur.y=tempMonsterY;
    auto initx=cur.x;
    auto inity=cur.y;
    cur.step=0;
    log("%dggg%d",cur.x,cur.y);
    Que.push(cur);
    int finalX=tempMonsterX,finalY=tempMonsterY;
    while(!Que.empty())
    {
        cur=Que.front();
        Que.pop();
        if(cur.x==tempPlayerX && cur.y==tempPlayerY)
        {
            node put[100];
            for (int i=0;i<100;i++)
            {
                put[i].x=0;
                put[i].y=0;
                put[i].step=0;
            }
            int k=1,a,b;
            int x=tempPlayerX;
            int y=tempPlayerY;
            while(x!=tempMonsterX || y!=tempMonsterY)//通过回溯的过程得到我走过的路径
            {
                a=x;
                b=y;
                put[k].x=ans[x][y].x;
                put[k++].y=ans[x][y].y;
                
                x=ans[a][b].x;
                y=ans[a][b].y;
            }
            if (k<=2) {
                if (GameManager::getInstance()->Level0LogicMap0[tempMonsterX+1][tempMonsterY+0]==0)
                {
                    finalX=tempMonsterX+1;
                    finalY=tempMonsterY+0;
                }
                else if (GameManager::getInstance()->Level0LogicMap0[tempMonsterX+0][tempMonsterY+1]==0)
                {
                    finalX=tempMonsterX+0;
                    finalY=tempMonsterY+1;
                }
                else if (GameManager::getInstance()->Level0LogicMap0[tempMonsterX-1][tempPlayerY+0]==0)
                {
                    finalX=tempMonsterX-1;
                    finalY=tempMonsterY+0;
                }
                else if (GameManager::getInstance()->Level0LogicMap0[tempMonsterX+0][tempMonsterY-1]==0)
                {
                    finalX=tempMonsterX+0;
                    finalY=tempMonsterY-1;
                }
                
                
            }
            else{
                finalX=put[k-2].x;
                finalY=put[k-2].y;
            }
            for (int i=k-1;i>=1;i--) log("%dpppp%d\n",put[i].x,put[i].y);
            break;
        }
        
        for(int i=0;i<4;i++)
        {
            next.x=cur.x+dx[i];
            next.y=cur.y+dy[i];
            
            if(next.x>=0 && next.x<30 && next.y>=0 && next.y<30 && Map[next.y][next.x]==0)
            {
                Map[next.y][next.x]=1;
                next.step=cur.step+1;
                ans[next.x][next.y].x=cur.x;//记录上一个点
                ans[next.x][next.y].y=cur.y;
                Que.push(next);
            }
        }
    }
    log("%dggggggg%d",finalX,finalY);
    
    log("%dggggggggggg%d",tempPlayerX,tempPlayerY);
    
    //finalX++; finalY++;
    GameManager::getInstance()->Level0LogicMap[inity][initx]=0;
    GameManager::getInstance()->Level0LogicMap0[inity][initx]=0;
    GameManager::getInstance()->Level0LogicMap0[finalY][finalX]=10;
    GameManager::getInstance()->Level0LogicMap[finalY][finalX]=1;
    finalY=30-finalY;
    auto move = MoveTo::create(0.5f, Point(finalX*128,finalY*128));
    auto func = CallFuncN::create(CC_CALLBACK_1(BaseMonster::Move, this));//反复调用移动
    baseMonster->runAction(Sequence::create(move, func, NULL));
    log("%fgggggggggggggggggggg%f",x, y);
}

