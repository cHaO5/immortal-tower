#ifndef _WEAPON0_H_
#define _WEAPON0_H_

#include"BaseWeapon.h"
#include "cocos2d.h"

USING_NS_CC;

class Weapon0 : public BaseWeapon
{
public:
	static Weapon0 * create(Vec2 offset);
	virtual bool init();

	int type = 0;

private:
	Vec2 direction;
	int range = GameManager::getInstance()->Weapon_range[0];
};

#endif
