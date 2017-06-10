#ifndef _BASE_MAP_H_
#define _BASE_MAP_H_ 

#include "cocos2d.h"
#include"Data/GameManager.h"
USING_NS_CC;

class BaseMap : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(BaseMap);

	//virtual void addMonster();
	//virtual void createMonster(int level,int type);
	virtual void addPlayer();
	virtual void LayerFollowPlayer(float t);
private:
	int* level0_MonsterMap = GameManager::getInstance()->level0_MonsterMap;
	int* level1_MonsterMap = GameManager::getInstance()->level1_MonsterMap;
	int* level2_MonsterMap = GameManager::getInstance()->level2_MonsterMap;
	int level0_MonsterMapSize = GameManager::getInstance()->level_MonsterMapSize[0];
	int level1_MonsterMapSize = GameManager::getInstance()->level_MonsterMapSize[1];
	int level2_MonsterMapSize = GameManager::getInstance()->level_MonsterMapSize[2];
};

#endif
