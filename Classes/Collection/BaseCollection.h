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
	Sprite* basecollection ;//�ᱻ����ĸ��ǵ�function����

	virtual void StartListen();
	virtual void PlayerDetect(float dt);
};

#endif

