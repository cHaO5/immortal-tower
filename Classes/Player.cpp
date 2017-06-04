#include"Player.h"

bool Player::init()
{
	log("lll");
	//auto *objects = _tileMap->getObjectGroup("hero");
	//CCASSERT(NULL != objects, "'Objects' object group not found");
	//auto spawnPoint = objects->getObject("hero1");
	//CCASSERT(!spawnPoint.empty(), "SpawnPoint object not found");
	//int x = spawnPoint["x"].asInt();
	//log("%d", x);
	//int y = _tileMap->getMapSize().height*_tileMap->getTileSize().height - _tileMap->getMapSize().height - spawnPoint["y"].asInt() - 1;//这里是有问题的！！！现在没问题了
	//log("%d", y);
	int x = 3264;//获取错误太多自定义吧
	int y = 3520;
    _player->setPosition(x, y);
	_player->setAnchorPoint(Point(0.5, 0.25));
	this->addChild(_player);
	_player->setGlobalZOrder(0);
    
    _weapon = new Weapon;
    _weapon->init("weapon1");
	return true;
}

bool Player::setPlayerPosition(Point position)
{
	int x =static_cast<int>( position.x / _tileMap->getTileSize().width);
	//由于原来player坐标在（获取时经过转换）设置时以左下角为原点
	//而地图以左上角为远原点，为了在地图中取到正确的点应该要做一次转化
	//先由坐标化为点再判断屏幕坐标是是以（点）为基本元素，而地图坐标系是以方格为基本元素
	//to do it：应该做一个函数转化所有坐标这样换地图方便！要转化的就障碍物的坐标
	int y = static_cast<int>((_tileMap->getMapSize().height*_tileMap->getTileSize().height - position.y) / _tileMap->getTileSize().height);

	Point tileCoord = Point(x, y);

	int tileGid = _meta->getTileGIDAt(tileCoord);
	if (tileGid)
	{
		auto properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty())
		{
			auto collision = properties["Collidable"].asString();
			//如果遇到障碍物，不让精灵移动
			if ("true" == collision)
			{
				return false;
			}

			auto collectable = properties["Collectable"].asString();
			if ("true" == collectable)
			{
				_fruit->removeTileAt(tileCoord);				
				//auto fruitSprite = _fruit->getTileAt(tileCoord);
				_meta->removeTileAt(tileCoord);
				//fruitSprite->removeFromParent();
				_numCollected++;
				return true;
			}
			return true;
		}
		return true;
	}
	return true;

}



