#ifndef _MONSTER1_H_
#define _MONSTER1_H_

#include"BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Monster1 : public BaseMonster
{
public:
	static Monster1 * createMonster(Vec2 Position);
	virtual bool init();

	virtual void Attack(float dt);
	virtual void DelayUnschedule(Node * pSender);
	virtual void IfActionRemove(Node * pSender);
	virtual void BoundDetect(float dt);

	int type = 1;
private:
	Vec2 position;
	Sprite* Monster1_weapon;

};

#endif
