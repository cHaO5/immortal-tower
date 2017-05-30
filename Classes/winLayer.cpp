#include"winLayer.h"

bool WinLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	srand((unsigned int)time(nullptr));
	this->schedule(schedule_selector(WinLayer::setViewpointCenter), 0.1);
	
	return true;
}

void WinLayer::setViewpointCenter(float dt)
{
	auto follow= Follow::create(_player->_player);
	this->getParent()->runAction(follow);

}
