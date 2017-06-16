#include "Collection/Collection0.h"
#include"Data/GameManager.h"

USING_NS_CC;
Collection0* Collection0::create(Vec2 MonsterPoint)
{
	auto Sprite = new Collection0();
	Sprite->monsterPoint = MonsterPoint;
	if (Sprite && Sprite->init())
	{
		Sprite->autorelease();
		return Sprite;
	}
	CC_SAFE_DELETE(Sprite);

	return NULL;
}
bool Collection0::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	basecollection = Sprite::create("Collection/collection0.png");	
	basecollection->setPosition(monsterPoint);
	addChild(basecollection,0);

	StartListen();

	return true;
}