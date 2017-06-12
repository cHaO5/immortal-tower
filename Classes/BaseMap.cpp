#include "BaseMap.h"
#include "GameManager.h"
#include "SoundManager.h"
#include"BasePlayer.h"
#include"Player0.h"
#include"Player1.h"
#include"Player2.h"
#include"BaseMonster.h"
#include"Monster0.h"
#include"Monster1.h"
#include"Monster2.h"
#include"GameScene.h"

USING_NS_CC;

bool BaseMap::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}
/**/
void BaseMap::addAttackListener()
{
	//用于清除碰撞后的飞镖与Monster
	//安装了一个监听器使得HelloWorld::onContactBegan可以接收事件，并把监听器添加到了EventDispatcher中，只要两个Bitmask（刚才定义的属性）使得互相可以碰撞的物体碰撞，EventDispatcher 就会去调用 onContactBegan.
	auto contactListener = EventListenerPhysicsContact::create();//但是一个射击多个就可能要出问题因为重复remove
	contactListener->onContactBegin = CC_CALLBACK_1(BaseMap::onContactBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

//处理碰撞——移除碰撞的二者
bool BaseMap::onContactBegan(PhysicsContact &contact)//PhysicsContact传递了碰撞的信息
{
	log("onContactBegan");
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != NULL)
	{
        auto monsterx=nodeA->getPosition().x;
        auto monstery=nodeA->getPosition().y;
        log("removeA");
        nodeA->getParent()->removeFromParentAndCleanup(true);
        Sprite* fruit = Sprite::create("fruit_temp.png");
        fruit->setPosition(monsterx,monstery);
        this->addChild(fruit);
    }
	if (nodeB != NULL)
	{
		log("removeB");
		nodeB->getParent()->removeFromParentAndCleanup(true);
	}
	return true;
}

void BaseMap::LayerFollowPlayer(float t)//需要不停刷新的函数
{
	auto follow = Follow::create(GameManager::getInstance()->currentPlayer);
	this->runAction(follow);
}

void BaseMap::toNextLevel(float t)
{
	if (GameManager::getInstance()->MonsterClearFlag
		&& (GameManager::getInstance()->currentPlayer->getPosition().x >= GameManager::getInstance()->Level_EndPosition[GameManager::getInstance()->CurrentLevel][0])
		&& (GameManager::getInstance()->currentPlayer->getPosition().x <= GameManager::getInstance()->Level_EndPosition[GameManager::getInstance()->CurrentLevel][1])
		&& (GameManager::getInstance()->currentPlayer->getPosition().y >= GameManager::getInstance()->Level_EndPosition[GameManager::getInstance()->CurrentLevel][2])
		&& (GameManager::getInstance()->currentPlayer->getPosition().y <= GameManager::getInstance()->Level_EndPosition[GameManager::getInstance()->CurrentLevel][3]))
	{
		log("transition Scene success");
	    GameManager::getInstance()->CurrentLevel++;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene()));
		
	}
}


void BaseMap::addMonster()
{
	log("addMonster");
	int level = GameManager::getInstance()->CurrentLevel;
	int* MonsterCreateMap;
	switch (level)
	{
	  case(0):MonsterCreateMap = GameManager::getInstance()->level0_MonsterMap;
	        for (int i = 0; i <GameManager::getInstance()->level_MonsterMapSize[0]; i++)
	       {
				log("add_0");
				auto type = MonsterCreateMap[i];
				createMonster(type,i);
	       }
		   break;
	  case(1):MonsterCreateMap = GameManager::getInstance()->level1_MonsterMap;
		    for (int i = 0; i < GameManager::getInstance()->level_MonsterMapSize[1]; i++)
		    {
				log("add_1");
			    auto type = MonsterCreateMap[i];
			    createMonster(type,i);
		    }
		   break;
	  case(2):MonsterCreateMap = GameManager::getInstance()->level2_MonsterMap;
		  for (int i = 0; i < GameManager::getInstance()->level_MonsterMapSize[2]; i++)
		  {
			  log("add_2");
			  auto type = MonsterCreateMap[i];
			  createMonster(type,i);
		  }
		  break;
	default:break;
	}
}

void BaseMap::createMonster(int type ,int i)
{
	BaseMonster* monster;
	switch(type)
	{
	case(0):monster = Monster0::createMonster(GameManager::getInstance()->ValidPosition_level0[i]);
		    addChild(monster,3);
		    break;
	case(1):monster = Monster1::createMonster(GameManager::getInstance()->ValidPosition_level1[i]);//Monster1
			addChild(monster,3);
			break;
	case(2):monster = Monster2::createMonster(GameManager::getInstance()->ValidPosition_level2[i]);//Monster2
			addChild(monster,3);
			break;
	default:
			break;
     }
	log("%d", i);
}


void BaseMap::addPlayer()
{
	BasePlayer* player;
	switch (GameManager::getInstance()->currentPlayerState_type)
	{
		case(0):player = Player0::create();//在create中记得返回player的指针到GM
	            addChild(player,3);
				log("addPlayer :%d", this->getTag());
				log("add player0");
			    break;
		case(1):player = Player1::create();
			    addChild(player,3);
				log("add player1");
			    break;
		case(2):player = Player2::create();
			    addChild(player,3 );
				log("add player2");
			    break;
		default:break;
	}

}

