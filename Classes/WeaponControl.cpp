#include"WeaponControl.h"

void WeaponControl::StartListen()
{
	//5 ����nomalize��)����ƫ������Ϊ��λ����
	int range = 1000;
	auto shootAmount = direction * range;//���ǹ�����Χ����ֵ
	 //6 ����������ӵ����ڵ�λ����ȥ������������һ��Ŀ��λ��
	auto realDest = shootAmount + proj->getPosition();

    auto actionMove = MoveTo::create(2.0f, realDest);
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(WeaponControl::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(WeaponControl::IfActionRemove, this));//������functionֻ�����ƶ�������û�л���û����ǰֹͣ���²��Ƴ���ִ�е�
	
	this->schedule(schedule_selector(WeaponControl::toObstacleDetect), 0.1f);

	//7 ����һ��������������2�����ƶ���Ŀ��λ�ã�Ȼ��ӳ������Ƴ�	
	proj->runAction(Sequence::create(actionMove, callFunc2, callFunc1, nullptr));

	return;
}
void WeaponControl::toObstacleDetect(float dt)
{
	log("now now now");

	auto  position = proj->getPosition() + direction* 25;

	log("%f,%f", proj->getPosition().x, proj->getPosition().y);
	log("%f,%f", direction.x, direction.y);
	log("%f,%f", position.x, position.y);

	if (ObstacleDetect(position))
	{
		log("true!!!!!!");
		this->unschedule(schedule_selector(WeaponControl::toObstacleDetect));//��ֹͣ�������Ƴ��������Ҫ����
		auto actionRemove = RemoveSelf::create();
		proj->runAction(actionRemove);
		//��ʱ��Ӧ��Ҫ�Ƴ������ǵȵ�remove��������������������
	}
}

bool WeaponControl::ObstacleDetect(Vec2 position)
{
	log("%f,%f", position.x, position.y);
	int x = static_cast<int>(position.x /_tileMap->getTileSize().width);
	int y = static_cast<int>((_tileMap->getMapSize().height*_tileMap->getTileSize().height - position.y) / _tileMap->getTileSize().height);
	Point tileCoord = Point(x, y);

	int tileGid = _meta->getTileGIDAt(tileCoord);
	if (tileGid)
	{
		auto properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty())
		{
			auto collision = properties["Collidable"].asString();
			//��������ϰ���
			if ("true" == collision)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

void  WeaponControl::DelayUnschedule(Node *pSender)
{
	if (proj != NULL)
	{
		log("successful111");
		this->unschedule(schedule_selector(WeaponControl::toObstacleDetect));
	}

}

void WeaponControl::IfActionRemove(Node *pSender)
{
	if (proj != NULL)
	{
		auto actionRemove = RemoveSelf::create();
		proj->runAction(actionRemove);
	}
}
