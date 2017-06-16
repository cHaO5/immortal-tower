#ifndef _BASE_COLLECTION_H_
#define _BASE_COLLECTION_H_ 
#include"cocos2d.h"
#include"Data/GameManager.h"
USING_NS_CC;

class BaseCollection: public Sprite
{
public:

	virtual bool init();
	CREATE_FUNC(BaseCollection);
	Sprite* basecollection ;//会被子类的覆盖到function里面

	virtual void StartListen();
	virtual void PlayerDetect(float dt);
};

#endif

