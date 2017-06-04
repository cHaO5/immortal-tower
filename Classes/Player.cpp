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
	//int y = _tileMap->getMapSize().height*_tileMap->getTileSize().height - _tileMap->getMapSize().height - spawnPoint["y"].asInt() - 1;//������������ģ���������û������
	//log("%d", y);
	int x = 3264;//��ȡ����̫���Զ����
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
	//����ԭ��player�����ڣ���ȡʱ����ת��������ʱ�����½�Ϊԭ��
	//����ͼ�����Ͻ�ΪԶԭ�㣬Ϊ���ڵ�ͼ��ȡ����ȷ�ĵ�Ӧ��Ҫ��һ��ת��
	//�������껯Ϊ�����ж���Ļ���������ԣ��㣩Ϊ����Ԫ�أ�����ͼ����ϵ���Է���Ϊ����Ԫ��
	//to do it��Ӧ����һ������ת������������������ͼ���㣡Ҫת���ľ��ϰ��������
	int y = static_cast<int>((_tileMap->getMapSize().height*_tileMap->getTileSize().height - position.y) / _tileMap->getTileSize().height);

	Point tileCoord = Point(x, y);

	int tileGid = _meta->getTileGIDAt(tileCoord);
	if (tileGid)
	{
		auto properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty())
		{
			auto collision = properties["Collidable"].asString();
			//��������ϰ�����þ����ƶ�
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



