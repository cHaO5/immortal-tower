#include "GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == NULL)
		instance = new GameManager();//由于instance是static每次new都是同一个，相当于创造了一个单例
	return instance;
}

