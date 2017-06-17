#include"Collection/BaseCollection.h"
#include"Data/GameManager.h"

bool BaseCollection::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void BaseCollection::StartListen()
{
	this->schedule(schedule_selector(BaseCollection::PlayerDetect), 0.05f);
}

void BaseCollection::PlayerDetect(float dt)
{
	if (GameManager::getInstance()->currentPlayer->getBoundingBox().intersectsRect(basecollection->getBoundingBox()))
	{
		this->unschedule(schedule_selector(BaseCollection::PlayerDetect));
		GameManager::getInstance()->PlayerIncreaseBlood++;
		this->removeFromParentAndCleanup(true);
	}
}