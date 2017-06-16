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

	auto shootAmount = _direction * _range;
	auto realDest = shootAmount +  GameManager::getInstance()->currentPlayer->getPosition();//可能会有bug

	auto actionMove = MoveTo::create(2.0f, realDest);
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(BaseWeapon::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(BaseWeapon::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行的

	this->schedule(schedule_selector(BaseWeapon::toObstacleDetect), 0.01f);

	//7 创建一个动作将飞镖在2秒内移动到目标位置，然后从场景中移除	
	baseweapon->runAction(Sequence::create(actionMove, callFunc2, callFunc1, nullptr));

	return;
}

void BaseWeapon::toObstacleDetect(float dt)
{
	auto  position = baseweapon->getPosition() + _direction * 10;
	log("%f,%f", baseweapon->getPosition().x, baseweapon->getPosition().y);
	if (ObstacleDetect(position))
	{
		log("true");
		this->unschedule(schedule_selector(BaseWeapon::toObstacleDetect));//先停止更新再移除否则更新要出错
		this->removeFromParentAndCleanup(true);
		//auto actionRemove = RemoveSelf::create();
		//baseweapon->runAction(actionRemove);
		//此时就应该要移除而不是等到remove！
	}
}

bool BaseWeapon::ObstacleDetect(Vec2 position)
{
	int x = static_cast<int>(position.x / GameManager::getInstance()->TileSizewidth);
	//由于原来player坐标在（获取时经过转换）设置时以左下角为原点
	//而地图以左上角为远原点，为了在地图中取到正确的点应该要做一次转化
	//先由坐标化为点再判断屏幕坐标是是以（点）为基本元素，而地图坐标系是以方格为基本元素
	//to do it：应该做一个函数转化所有坐标这样换地图方便！要转化的就障碍物的坐标
	int y = static_cast<int>((GameManager::getInstance()->MapSizeheight *  GameManager::getInstance()->TileSizeheight - position.y) / GameManager::getInstance()->TileSizeheight);
	int* logicmap;
	switch (GameManager::getInstance()->CurrentLevel)
	{
	case(0):logicmap = GameManager::getInstance()->Level0LogicMap[0];
		break;
	case(1):logicmap = GameManager::getInstance()->Level1LogicMap[0];
		break;
	case(2):logicmap = GameManager::getInstance()->Level2LogicMap[0];
		break;
	default:
		break;
	}
	auto value = *((logicmap + GameManager::getInstance()->MapSizewidth*y) + x);
	log("%d,%d", *logicmap,value);
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
		this->removeFromParentAndCleanup(true);
		//auto actionRemove = RemoveSelf::create();
		//baseweapon->runAction(actionRemove);
	}
}

