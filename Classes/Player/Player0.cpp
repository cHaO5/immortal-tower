#include "Player/Player0.h"
#include"Data/GameManager.h"
USING_NS_CC;
bool Player0::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	Player = Sprite::create(GameManager::getInstance()->Player_texture[0][2]);
	Player->setPosition(GameManager::getInstance()->Level0_StartPosition);
	Player->setAnchorPoint(Point(0.5, 0.25));
	addChild(Player);

	GameManager::getInstance()->currentPlayer = Player;
	GameManager::getInstance()->currentPlayerState_life = GameManager::getInstance()->Player_life[0];
	GameManager::getInstance()->currentPlayerState_speed = GameManager::getInstance()->Player_speed[0];

	attackMonster();
    Move();

	return true;
}