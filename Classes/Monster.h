#ifndef _MONSTER_H_
#define _MONSTER_H_
#include"cocos2d.h"
#include"Player.h"

using namespace cocos2d;
USING_NS_CC;

class Monster : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Monster);
	void addMonster(float dt);

	Player* _player;
	TMXTiledMap *_tileMap;//µØÍ¼
	TMXLayer *_meta;
	TMXLayer *_fruit;
	int ptm;
	Vec2 monsterarray[4] = { Point(490,443),Point(490,512),Point(490,332),Point(490,224) };
};

#endif
