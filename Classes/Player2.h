#ifndef _PLAYER2_H_
#define _PLAYER2_H_

#include"BasePlayer.h"
#include"GameManager.h"
#include "cocos2d.h"

USING_NS_CC;

class Player2 : public BasePlayer
{
public:
	CREATE_FUNC(Player2);
	virtual bool init();
};

#endif

