#ifndef _COLLECTION0_H_
#define _COLLECTION0_H_

#include"Collection/BaseCollection.h"
#include "cocos2d.h"

USING_NS_CC;

class Collection0 : public BaseCollection
{
public:
	static Collection0 * create(Vec2 MonsterPoint);
	virtual bool init();
private:
	Vec2 monsterPoint;
};

#endif
