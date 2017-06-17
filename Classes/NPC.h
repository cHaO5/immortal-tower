#ifndef _NPC_H_
#define _NPC_H_
#include"cocos2d.h"
#include"GameManager.h"
USING_NS_CC;

class NPC: public Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(NPC);
    Sprite* npc ;//会被子类的覆盖到function里面
    
    virtual void StartListen();
    virtual void PlayerDetect(float dt);
};

#endif
