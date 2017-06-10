#ifndef _PLAYER2_H_
#define _PLAYER2_H_

#include"Player/BasePlayer.h"
#include"Data/GameManager.h"
#include "cocos2d.h"

USING_NS_CC;

class Player2 : public BasePlayer
{
public:
	CREATE_FUNC(Player2);
	virtual bool init();
};

#endif

