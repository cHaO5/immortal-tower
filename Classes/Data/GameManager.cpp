#include "Data/GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();//����instance��staticÿ��new����ͬһ�����൱�ڴ�����һ������
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

