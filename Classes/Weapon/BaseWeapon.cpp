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
	auto realDest = shootAmount +  GameManager::getInstance()->currentPlayer->getPosition();//���ܻ���bug

	auto actionMove = MoveTo::create(2.0f, realDest);
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(BaseWeapon::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(BaseWeapon::IfActionRemove, this));//������functionֻ�����ƶ�������û�л���û����ǰֹͣ���²��Ƴ���ִ�е�

	this->schedule(schedule_selector(BaseWeapon::toObstacleDetect), 0.01f);

	//7 ����һ��������������2�����ƶ���Ŀ��λ�ã�Ȼ��ӳ������Ƴ�	
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
		this->unschedule(schedule_selector(BaseWeapon::toObstacleDetect));//��ֹͣ�������Ƴ��������Ҫ����
		this->removeFromParentAndCleanup(true);
		//auto actionRemove = RemoveSelf::create();
		//baseweapon->runAction(actionRemove);
		//��ʱ��Ӧ��Ҫ�Ƴ������ǵȵ�remove��
	}
}

bool BaseWeapon::ObstacleDetect(Vec2 position)
{
	int x = static_cast<int>(position.x / GameManager::getInstance()->TileSizewidth);
	//����ԭ��player�����ڣ���ȡʱ����ת��������ʱ�����½�Ϊԭ��
	//����ͼ�����Ͻ�ΪԶԭ�㣬Ϊ���ڵ�ͼ��ȡ����ȷ�ĵ�Ӧ��Ҫ��һ��ת��
	//�������껯Ϊ�����ж���Ļ���������ԣ��㣩Ϊ����Ԫ�أ�����ͼ����ϵ���Է���Ϊ����Ԫ��
	//to do it��Ӧ����һ������ת������������������ͼ���㣡Ҫת���ľ��ϰ��������
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

