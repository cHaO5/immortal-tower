#include"BaseMonster.h"
#include"GameManager.h"
#include<math.h>
#include<cmath>
#include<queue>

struct node
{
    int x,y,step;
};

bool BaseMonster::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}



void BaseMonster::StartListen()
{
	log("Monater StartListen create");
	this->schedule(schedule_selector(BaseMonster::FollowMove), 0.3f);
}

void BaseMonster::FollowMove(float dt)
{

    float x = GameManager::getInstance()->currentPlayer->getPosition().x - baseMonster->getPosition().x;
	float y = GameManager::getInstance()->currentPlayer->getPosition().y - baseMonster->getPosition().y;
	log("Monater followrun create");
	//�ȼ�������Ӣ�۵ľ���
	auto dis = sqrt(pow(x, 2) + pow(y, 2));

	
	//�ڹ�����ӷ�Χ�ڣ����￪ʼ�ƶ�
	{
		this->unschedule(schedule_selector(BaseMonster::FollowMove));
		auto func = CallFuncN::create(CC_CALLBACK_1(BaseMonster::Move, this));//�ù����ƶ�
		baseMonster->runAction(func);

		if (dis <= 500)//��ʼ����
		{
			log("before attack");
			this->schedule(schedule_selector(BaseMonster::Attack), 1.5f);
		}
	}
}




void BaseMonster::Move(Node *pSender)//�˴�����ai�㷨
{
	log("Monater 1111111111 Move create");
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
            while(x!=tempMonsterX || y!=tempMonsterY)//ͨ�����ݵĹ��̵õ����߹���·��
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
                ans[next.x][next.y].x=cur.x;//��¼��һ����
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
	auto func = CallFuncN::create(CC_CALLBACK_1(BaseMonster::Move, this));//���������ƶ�
    
	baseMonster->runAction(Sequence::create(move, func, NULL));
    auto x=baseMonster->getPosition().x / 128;
    auto y=baseMonster->getPosition().y / 128;
    log("%fgggggggggggggggggggg%f",x, y);
}

void BaseMonster::Attack(float dt)//������д��function
{
	log("Monater0 baseclass attack create");
}
