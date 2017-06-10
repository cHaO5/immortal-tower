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
	log("player0:%d", this->getTag());
	log("add player");
	GameManager::getInstance()->currentPlayer = Player;

	attackMonster();
    Move();

	return true;
}