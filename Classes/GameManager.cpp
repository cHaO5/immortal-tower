#include "GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();//����instance��staticÿ��new����ͬһ�����൱�ڴ�����һ������
	return instance;
}

