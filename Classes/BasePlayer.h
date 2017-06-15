#ifndef _BASE_PLAYER_H_
#define _BASE_PLAYER_H_ 
#include"cocos2d.h"

USING_NS_CC;

class BasePlayer : public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(BasePlayer);
	virtual void attackMonster();
	virtual void Move();
	Sprite* Player;

};

#endif

