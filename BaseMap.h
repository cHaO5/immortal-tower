#ifndef _BASE_MAP_H_
#define _BASE_MAP_H_ 

#include "cocos2d.h"
#include"GameManager.h" 
USING_NS_CC;

class BaseMap : public Layer
{
public:
	virtual bool init();

	CREATE_FUNC(BaseMap);

	virtual void addMonster();
	virtual void createMonster(int type ,int i);

	virtual void addPlayer();

	virtual void addAttackListener();
	virtual bool onContactBegan(PhysicsContact & contact);
    virtual void addBlood(int x,int y);

	virtual void LayerFollowPlayer(float t);

	virtual void toNextLevel(float t);
    
};

#endif
