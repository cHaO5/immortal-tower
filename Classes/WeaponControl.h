#ifndef _WEAPONCONTROL_H_
#define _WEAPONCONTROL_H_

#include"cocos2d.h"

USING_NS_CC;

class WeaponControl :public Node
{
public:
	void StartListen();
	void toObstacleDetect(float dt);
	bool ObstacleDetect(Vec2 position);
	void DelayUnschedule(Node *pSender);
	void IfActionRemove(Node *pSender);


	TMXTiledMap *_tileMap;//µ±Ç°µØÍ¼
	TMXLayer *_meta;
	Sprite* proj;
	Vec2 direction;
};

#endif
