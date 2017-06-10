#ifndef __GAMEMENUSCENE_H__
#define __GAMEMENUSCENE_H__

#include "cocos2d.h"
#include "Data/GameManager.h"

USING_NS_CC;
class GameMenuScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameMenuScene);
	Sprite* bgSprite;

};

#endif