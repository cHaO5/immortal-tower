#include "Map/BaseMap.h"
#include "Data/GameManager.h"
#include "Data/SoundManager.h"
#include"Player/BasePlayer.h"
#include"Player/Player0.h"
#include"Player/Player1.h"
#include"Player/Player2.h"
#include"Monster/Monster0.h"
#include"Monster/Monster1.h"
#include"Monster/Monster2.h"
USING_NS_CC;

bool BaseMap::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void BaseMap::LayerFollowPlayer(float t)//需要不停刷新的函数
{
	auto follow = Follow::create(GameManager::getInstance()->currentPlayer);
	this->runAction(follow);
}
/*
void BaseMap::addMonster()
{
	int level = GameManager::getInstance()->CurrentLevel;
	switch (level)
	{
	  case(0):auto MonsterCreate = level0_MonsterMap;
	        for (int i = 0; i <level0_MonsterMapSize; i++)
	       {
				auto type = MonsterCreate[i];
				createMonster(level,type);
	       }
		   break;
	  case(1):auto MonsterCreate = level1_MonsterMap;
		    for (int i = 0; i <level1_MonsterMapSize; i++)
		    {
			    auto type = MonsterCreate[i];
			    createMonster(level, type);
		    }
		   break;
	  case(2):auto MonsterCreate = level2_MonsterMap;
		  for (int i = 0; i < level2_MonsterMapSize; i++)
		  {
			  auto type = MonsterCreate[i];
			  createMonster(level, type);
		  }
		  break;
	default:break;
	}
}

void BaseMap::createMonster(int level,int type)
{
	for (int i = 0; i < GameManager::getInstance()->ValidPosition_levelSize[level]; i++)
	{
		switch(type)
		{
		case(0):auto monster = Monster0::createMonster(GameManager::getInstance()->ValidPosition_level0[i]);
		        addChild(monster,1);
		        break;
		case(1):auto monster = Monster1::createMonster(GameManager::getInstance()->ValidPosition_level1[i]);
				addChild(monster,1);
				break;
		case(2):auto monster = Monster2::createMonster(GameManager::getInstance()->ValidPosition_level2[i]);
				addChild(monster,1);
				break;
		default:
			break;
		}
	}
}
*/
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
