#ifndef _WINLAYER_H_
#define _WINLAYER_H_ 

#include"cocos2d.h"
#include"Player.h"

using namespace cocos2d;


USING_NS_CC;

class WinLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(WinLayer);
	void setViewpointCenter(float dt);

	Player* _player;
};

#endif
