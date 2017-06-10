#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Layer
{
public:
	CREATE_FUNC(GameScene);
	virtual bool init();
	static Scene * createScene();

};

#endif