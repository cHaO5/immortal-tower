#ifndef _CONTROLLAYER_H_
#define _CONTROLLAYER_H_

#include"cocos2d.h"
#include"SceneManager.h"
#include"Player.h"
#include"Monster.h"
#include"KeyBoard.h"
#include"Mouse.h"
#include"winLayer.h"

USING_NS_CC;

 enum class PhysicsCategory
{
	None = 0,
	Monster = (1 << 0),//1
	Projectile = (1 << 1),//2
	All = PhysicsCategory::Monster | PhysicsCategory::Projectile//3
};

class ControlLayer : public Layer
{
public:
	SceneManager* tsm;

	static ControlLayer* createControl();
	CREATE_FUNC(ControlLayer);
	virtual bool init();
	bool onContactBegan(PhysicsContact &contact);

    Player* player;
	TMXTiledMap *_tileMap;//��ͼ
private:
	Monster* monster;
	TMXLayer *_background;
	TMXLayer *_meta;//�ϰ���
	TMXLayer *_fruit;//����
	KeyBoard* keyBoard;
	Mouse* mouse;
	WinLayer* winlayer;
};

#endif
