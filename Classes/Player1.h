#ifndef _PLAYER1_H_
#define _PLAYER1_H_

#include"BasePlayer.h"
#include"GameManager.h"
#include "cocos2d.h"

USING_NS_CC;

class Player1 : public BasePlayer
{
public:
	CREATE_FUNC(Player1);
	virtual bool init();
};

#endif
