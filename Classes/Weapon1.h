#ifndef _WEAPON1_H_
#define _WEAPON1_H_

#include"BaseWeapon.h"
#include "cocos2d.h"

USING_NS_CC;

class Weapon1 : public BaseWeapon
{
public:
	static Weapon1 * create(Vec2 offset);
	virtual bool init();

	int type = 1;
private:
	Vec2 direction;
	int range = GameManager::getInstance()->Weapon_range[1];
};

#endif
