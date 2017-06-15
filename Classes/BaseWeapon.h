#ifndef _BASE_WEAPON_H_
#define _BASE_WEAPON_H_ 
#include"cocos2d.h"
#include"GameManager.h"
USING_NS_CC;

class BaseWeapon: public Sprite
{
public:

	virtual bool init();
	CREATE_FUNC(BaseWeapon);
	Sprite* baseweapon ;//会被子类的覆盖到function里面

	virtual void StartListen(int range,Vec2 direction);
	virtual void toObstacleDetect(float dt);
	virtual bool ObstacleDetect(Vec2 position);
	virtual void DelayUnschedule(Node *pSender);
	virtual void IfActionRemove(Node *pSender);
private:
	Vec2 _direction;
	int _range;

	float TileSizewidth = GameManager::getInstance()->TileSizewidth;
	float TileSizeheight = GameManager::getInstance()->TileSizeheight;
	int MapSizeheight = GameManager::getInstance()->MapSizeheight;
	int MapSizewidth = GameManager::getInstance()->MapSizewidth;
};

#endif

