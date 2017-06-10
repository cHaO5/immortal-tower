#ifndef _LEVEL_0_H_
#define _LEVEL_0_H_

#include "Map/BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level0 : public BaseMap
{
public:
	//static Level0* createGame();
	virtual bool init();
	CREATE_FUNC(Level0);
private:
	Sprite *floor;//�ϰ���
	Sprite *wall;//�ϰ���
	Sprite *barrier;//�ϰ���

};

#endif
