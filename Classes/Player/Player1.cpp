#include "Player/Player1.h"

USING_NS_CC;
bool Player1::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	Player = Sprite::create(GameManager::getInstance()->Player_texture[1][2]);
	Player->setPosition(GameManager::getInstance()->Level0_StartPosition);
	Player->setAnchorPoint(Point(0.5, 0.25));
	addChild(Player);


	GameManager::getInstance()->currentPlayer = Player;
	GameManager::getInstance()->currentPlayerState_speed = GameManager::getInstance()->Player_speed[1];

	attackMonster();
	Move();

	return true;
}