#ifndef _PLAYER_H_
#define _PLAYER_H_ 
#include"cocos2d.h"
#include "Weapon.h"

USING_NS_CC;

extern int m_num;//凡是用到都要extern用来改变血量条
extern int _numCollected;


////////////////////////////////////////////////////这个东西放哪里，重构的时候注意调整一下
typedef enum {
    DAMAGE = 1,
    SPEED = 2,
    RANGE = 3
}PICKUP;

class Player : public Node
{
public:
	virtual bool init();
	bool setPlayerPosition(Point position);
	TMXTiledMap *_tileMap;
	TMXLayer *_meta;
	TMXLayer *_fruit;
	Sprite *_player;
    
    Weapon *_weapon;
    
    Player(TMXTiledMap *_tileMap, TMXLayer *_meta, TMXLayer *_fruit) :
		_tileMap(_tileMap), _meta(_meta), _fruit(_fruit)
	{
		_player = Sprite::create("D.png");
	};
};

#endif
