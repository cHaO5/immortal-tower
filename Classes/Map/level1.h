#ifndef _LEVEL_1_H_
#define _LEVEL_1_H_

#include "Map/BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level1 : public BaseMap
{
public:
	virtual bool init();
	CREATE_FUNC(Level1);
private:
	Sprite *floor;//�ϰ���
	Sprite *wall;//�ϰ���
	Sprite *barrier;//�ϰ���
};

#endif
