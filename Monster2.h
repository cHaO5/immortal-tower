#ifndef _MONSTER2_H_
#define _MONSTER2_H_

#include"BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Monster2 : public BaseMonster
{
public:
	static Monster2 * createMonster(Vec2 Position);
	virtual bool init();

	virtual void Attack(float dt);
    virtual void DelayUnschedule(Node * pSender);
    virtual void BoundDetect(float dt);

	int type = 2;
private:
	Vec2 position;
    int Monster2_weapon;

};

#endif
