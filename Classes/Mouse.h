#ifndef _MOUSE_H_
#define _MOUSE_H_

#include"cocos2d.h"
#include"Player.h"
#include "Weapon.h"
USING_NS_CC;

class Mouse :public Layer
{
public:
	//CREATE_FUNC(Mouse);
	virtual bool init();
	void startM();
	void stopM();
	bool onTouchBegan(Touch *touch, Event * unused_event);

	Player* _player;
	TMXTiledMap *_tileMap;//µ±Ç°µØÍ¼
	TMXLayer *_meta;

};

#endif

