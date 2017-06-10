#ifndef __VICTORY_H__
#define __VICTORY_H__

#include "cocos2d.h"

USING_NS_CC;

class Victory : public Layer
{
public:

	virtual bool init();
	CREATE_FUNC(Victory);
	void OnRestartTouch(Ref* pSpender);
	void VSpriteAnimation();
	void RItemAnimation();

private:
	Sprite* win_Gnome;
	Point position;
	Sprite* VictorySprite;
	MenuItemSprite* RestartMenuItem;
};

#endif // __HELLOWORLD_SCENE_H__

