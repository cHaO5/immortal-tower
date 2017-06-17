#include "Data/GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();//由于instance是static每次new都是同一个，相当于创造了一个单例
	return instance;
}
/**/
void GameManager::setInstance(int tag)
{
	SLOTNUM = tag;

	sprintf(SLOTX_ISEXIT, "Slot%d", tag);
}

void GameManager::initCurrrent(int type)
{
	currentPlayerState_life = Player_life[type];
	currentPlayerState_speed = Player_speed[type];
}

