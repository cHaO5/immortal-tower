#ifndef _MONSTER0_H_
#define _MONSTER0_H_

#include"BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Monster0 : public BaseMonster
{
public:
	static Monster0 * createMonster(Vec2 Position);
	virtual bool init();
    
    virtual void StartListen();
    virtual void FollowMove(float dt);
    virtual void Move(Node *pSender);
    virtual void Attack(float dt);
	virtual void DelayUnschedule(Node * pSender);
	virtual void IfActionRemove(Node * pSender);
	virtual void BoundDetect(float dt);

    int type = 0;
private:
	Vec2 position;
	Node* Monster0_weapon;

};

#endif
