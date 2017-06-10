#ifndef _WEAPONCONTROL_H_
#define _WEAPONCONTROL_H_

#include"cocos2d.h"
#include "Weapon.h"

USING_NS_CC;

//typedef enum {
//    RANGE = 2,
//    DAMAGE = 1,
//    SPEED = 5
//}Weapon1;
//
//typedef enum {
//    RANGE = 3,
//    DAMAGE = 2,
//    SPEED = 10
//}Weapon2;

class WeaponControl :public Node
{
public:
	void StartListen(Weapon *weapon);
	void toObstacleDetect(float dt);
	bool ObstacleDetect(Vec2 position);
	void DelayUnschedule(Node *pSender);
	void IfActionRemove(Node *pSender);


	TMXTiledMap *_tileMap;//µ±Ç°µØÍ¼
	TMXLayer *_meta;
	Sprite* proj;
	Vec2 direction;
    //std::string _weapon;
};

#endif
