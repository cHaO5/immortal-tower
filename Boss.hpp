
#ifndef Boss_hpp
#define Boss_hpp

#include <stdio.h>
#include"BaseMonster.h"
#include "cocos2d.h"
class Boss : public BaseMonster
{
public:
    static Boss * createMonster(Vec2 Position);
    virtual bool init();
    
    virtual void StartListen();
    virtual void FollowMove(float dt);
    virtual void Move(Node *pSender);
    virtual void Attack(float dt);
    virtual void DelayUnschedule(Node * pSender);
    virtual void IfActionRemove(Node * pSender);
    virtual void BoundDetect(float dt);
    
    int type = 3;
private:
    Vec2 position;
    Node* boss_weapon;
    
};

#endif /* Boss_hpp */
