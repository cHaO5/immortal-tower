#ifndef _CONTROLLAYER_H_
#define _CONTROLLAYER_H_

#include"cocos2d.h"

USING_NS_CC;

class ControlLayerAttack: public Layer
{
public:
	virtual bool initAttackControl();
	bool onTouchBegan(Touch * touch, Event * usused_event);
	static ControlLayerAttack* createAttackControl();
	

};
class ControlLayerMove: public Layer
{
public:
	virtual bool initMoveControl();
	static ControlLayerMove* createMoveControl();
	bool isKeyPressed(EventKeyboard::KeyCode keyCode);
//	void onKeyPressed(EventKeyboard::KeyCode keyCode);
	void keyPressedDuration(EventKeyboard::KeyCode code);
	void updateState(float delta) ;
private:
	std::map <cocos2d::EventKeyboard::KeyCode, bool> keys;
};


#endif