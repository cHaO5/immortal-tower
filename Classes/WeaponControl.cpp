#include"WeaponControl.h"

void WeaponControl::StartListen()
{
	//5 调用nomalize（)来将偏移量化为单位向量
	int range = 1000;
	auto shootAmount = direction * range;//这是攻击范围属性值
	 //6 将次向量添加到飞镖的位置上去，这样就有了一个目标位置
	auto realDest = shootAmount + proj->getPosition();

    auto actionMove = MoveTo::create(2.0f, realDest);
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(WeaponControl::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(WeaponControl::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行的
	
	this->schedule(schedule_selector(WeaponControl::toObstacleDetect), 0.1f);

	//7 创建一个动作将飞镖在2秒内移动到目标位置，然后从场景中移除	
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
		this->unschedule(schedule_selector(WeaponControl::toObstacleDetect));//先停止更新再移除否则更新要出错
		auto actionRemove = RemoveSelf::create();
		proj->runAction(actionRemove);
		//此时就应该要移除而不是等到remove！！！！！！！！！！
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
			//如果遇到障碍物
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
