#include "Map/level1.h"
#include"Data\GameManager.h"
#include"Data\SoundManager.h"
USING_NS_CC;

bool Level1::init()
{
	if (!Layer::init())
	{
		return false;
	}
	floor = Sprite::create(GameManager::getInstance()->levelMap[1][0]);
	floor->setAnchorPoint(Point(0, 0));
	floor->setPosition(Point(0, 0));
	addChild(floor, 0);
	wall = Sprite::create(GameManager::getInstance()->levelMap[1][1]);
	wall->setAnchorPoint(Point(0, 0));
	wall->setPosition(Point(0, 0));
	addChild(wall, 0);
	barrier = Sprite::create(GameManager::getInstance()->levelMap[1][2]);
	barrier->setAnchorPoint(Point(0, 0));
	barrier->setPosition(Point(0, 0));
	addChild(barrier, 5);//应该是在level0这个父节点中，而不是map这个父节点中

	//addMonster();
	addPlayer();
	//DetectVictory();
	//DetectFailure();
	this->schedule(schedule_selector(BaseMap::LayerFollowPlayer), 0.01f);

	SoundManager::playDesertBattle();
	return true;
}