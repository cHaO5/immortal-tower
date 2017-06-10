#ifndef _PLAYER0_H_
#define _PLAYER0_H_

#include"Player/BasePlayer.h"
#include"Data/GameManager.h"
#include "cocos2d.h"

USING_NS_CC;

class Player0 : public BasePlayer
{
public:
	CREATE_FUNC(Player0);
	virtual bool init();
	
};

#endif
