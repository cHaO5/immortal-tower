#include"Weapon/BaseWeapon.h"
#include"Data/GameManager.h"

bool BaseWeapon::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void BaseWeapon::StartListen(int range, Vec2 direction)
{
	_range = range;
	_direction = direction;

	auto shootAmount = direction * _range;//这是攻击范围属性值
	log("%d", _range);								 //6 将次向量添加到飞镖的位置上去，这样就有了一个目标位置
	auto realDest = shootAmount +  baseweapon->getPosition();//可能会有bug

	auto actionMove = MoveTo::create(2.0f, realDest);
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(BaseWeapon::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(BaseWeapon::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行的

	this->schedule(schedule_selector(BaseWeapon::toObstacleDetect, 0.1f));

	//7 创建一个动作将飞镖在2秒内移动到目标位置，然后从场景中移除	
	baseweapon->runAction(Sequence::create(actionMove, callFunc2, callFunc1, nullptr));

	return;
}

void BaseWeapon::toObstacleDetect(float dt)
{
	auto  position = baseweapon->getPosition() + _direction * 25;
	if (ObstacleDetect(position))
	{
		log("true");
		this->unschedule(schedule_selector(BaseWeapon::toObstacleDetect));//先停止更新再移除否则更新要出错
		auto actionRemove = RemoveSelf::create();
		baseweapon->runAction(actionRemove);
		//此时就应该要移除而不是等到remove！
	}
}

bool BaseWeapon::ObstacleDetect(Vec2 position)
{
	int x = static_cast<int>(position.x / TileSizewidth);
	//由于原来player坐标在（获取时经过转换）设置时以左下角为原点
	//而地图以左上角为远原点，为了在地图中取到正确的点应该要做一次转化
	//先由坐标化为点再判断屏幕坐标是是以（点）为基本元素，而地图坐标系是以方格为基本元素
	//to do it：应该做一个函数转化所有坐标这样换地图方便！要转化的就障碍物的坐标
	int y = static_cast<int>((MapSizeheight*TileSizeheight - position.y) / TileSizeheight);
	int* logicmap;
	switch (GameManager::getInstance()->CurrentLevel)
	{
	case(0):logicmap = logicmap0;
		break;
	case(1):logicmap = logicmap1;
		break;
	case(2):logicmap = logicmap2;
		break;
	default:
		break;
	}
	auto value = *((logicmap + MapSizewidth * y) + x);

	switch (value)
	{
	case(1):
		return true;
	default:
		return false;
	}
}

void BaseWeapon::DelayUnschedule(Node * pSender)
{
	if (baseweapon != NULL)
	{
		this->unschedule(schedule_selector(BaseWeapon::toObstacleDetect));
	}
}

void BaseWeapon::IfActionRemove(Node * pSender)
{
	if (baseweapon != NULL)
	{
		auto actionRemove = RemoveSelf::create();
		baseweapon->runAction(actionRemove);
	}
}

