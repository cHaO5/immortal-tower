#include "Monster1.h"
#include"GameManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include<math.h>
#include<cmath>
#include<queue>
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
		GameManager::getInstance()->PlayerReduceBlood[1]++;
		this->unschedule(schedule_selector(Monster1::BoundDetect));//先停止更新再移除否则更新要出错
		auto actionRemove = RemoveSelf::create();
		Monster1_weapon->runAction(actionRemove);
	}
}

void Monster1::StartListen()
{
    log("Monater0 StartListen create");
    this->schedule(schedule_selector(Monster1::FollowMove), 1.0f);
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
    auto animation = Animation::create();
    char nameSize[20] = {0};
    Vector< SpriteFrame* > frameVec;
    if (arc > -0.3926 && arc <= 0.3926) {  //turn U
        for (int i=2;i<=6;i++)
        {
            sprintf(nameSize, "2-U-%d.png",i);
            animation->addSpriteFrameWithFile(nameSize);

        }
    } else if (arc > 0.3926 && arc <= 1.1781) {  //turn UR
        for (int i=1;i<=3;i++)
        {
            sprintf(nameSize, "2-UR-%d.png",i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    } else if (arc > 1.1781 && arc <= 1.9635) {  //turn R
        for (int i=1;i<=4;i++)
        {
            sprintf(nameSize, "2-R-%d.png",i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    } else if (arc > 1.9635 && arc <= 2.7489) {  //turn DR
        for (int i=1;i<=4;i++)
        {
            sprintf(nameSize, "2-DR-%d.png",i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    } else if (arc > 2.7489 || arc <= -2.7489) {  //turn D
        for (int i=1;i<=4;i++)
        {
            sprintf(nameSize, "2-D-%d.png",i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    } else if (arc > -1.1781 && arc <= -0.3926) {  //turn UL
        for (int i=1;i<=3;i++)
        {
            sprintf(nameSize, "2-UL-%d.png",i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    } else if (arc > -1.9635 && arc <= -1.1781) {  //turn L
        for (int i=1;i<=4;i++)
        {
            sprintf(nameSize, "2-L-%d.png",i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    } else if (arc > -2.7489 && arc <= -1.9635) {  //turn DL
        for (int i=1;i<=4;i++)
        {
            sprintf(nameSize, "2-DL-%d.png",i);
            animation->addSpriteFrameWithFile(nameSize);
        }
    }
    animation->setDelayPerUnit(1.0f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    auto animate = Animate::create(animation);
//    baseMonster = Sprite::create("2-D-1.png");
//    baseMonster->setPosition(position);
//    addChild(baseMonster);
    baseMonster->runAction(animate);

    
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
    
    std::queue<node>Que;
    while (Que.size()!=0) Que.pop();
    node cur,next,ans[30][30];
    cur.x=tempMonsterX;
    cur.y=tempMonsterY;
    GameManager::getInstance()->Level0LogicMap[cur.y][cur.x]=0;
    GameManager::getInstance()->Level0LogicMap0[cur.y][cur.x]=0;
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
    GameManager::getInstance()->Level0LogicMap0[finalY][finalX]=10;
    GameManager::getInstance()->Level0LogicMap[finalY][finalX]=1;
    finalY=30-finalY;
    auto move = MoveTo::create(0.3, Point(finalX*128,finalY*128));
    auto func = CallFuncN::create(CC_CALLBACK_1(BaseMonster::Move, this));//反复调用移动
    
    baseMonster->runAction(Sequence::create(move, func, NULL));
    auto x=baseMonster->getPosition().x / 128;
    auto y=baseMonster->getPosition().y / 128;
    log("%fgggggggggggggggggggg%f",x, y);
}

