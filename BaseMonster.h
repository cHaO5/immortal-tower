#ifndef _BASE_MONSTER_H_
#define _BASE_MONSTER_H_ 
#include"cocos2d.h"

USING_NS_CC;

class BaseMonster : public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(BaseMonster);

	virtual void StartListen();
	virtual void FollowMove(float dt);
	virtual void Move(Node *pSender);
	virtual void Attack(float dt);

    
	Sprite* baseMonster;

};

#endif


