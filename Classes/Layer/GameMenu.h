#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#include "cocos2d.h"
USING_NS_CC;

class GameMenu : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameMenu);
	void onEnterTransitionDidFinish();
	MenuItemSprite *player0, *player1, *player2;
	bool isFirst;
};

#endif
