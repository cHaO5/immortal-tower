#ifndef _PLAYER_H_
#define _PLAYER_H_ 
#include"cocos2d.h"

USING_NS_CC;

extern int m_num;//�����õ���Ҫextern�����ı�Ѫ����
extern int _numCollected;

class Player : public Node
{
public:
	virtual bool init();
	bool setPlayerPosition(Point position);
	TMXTiledMap *_tileMap;
	TMXLayer *_meta;
	TMXLayer *_fruit;
	Sprite *_player;

	Player(TMXTiledMap *_tileMap, TMXLayer *_meta, TMXLayer *_fruit) :
		_tileMap(_tileMap), _meta(_meta), _fruit(_fruit)
	{
		_player = Sprite::create("1_1.png");

	};
	//WinLayer* winLayer;
};

#endif
