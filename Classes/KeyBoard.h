#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include"cocos2d.h"
#include"Player.h"
//#include"winLayer.h"

USING_NS_CC;

class KeyBoard : public cocos2d::Layer
{
public:
	CREATE_FUNC(KeyBoard);
	virtual bool init();
	void keyPressedDuration(EventKeyboard::KeyCode code);
	Player* startKB();
	void stopKB();
    Player* _player;
	//WinLayer* winLayer;
	TMXTiledMap *_tileMap;
private:
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode);
	
};

#endif
