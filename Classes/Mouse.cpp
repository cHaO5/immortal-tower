#include"Mouse.h"
#include"ControlLayer.h"//Ϊ��Ҳ���Ǹ��������ײ��

bool Mouse::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	return true;
}

void Mouse::startM()
{
	auto eventListener = EventListenerTouchOneByOne::create();//������
	eventListener->onTouchBegan = CC_CALLBACK_2(Mouse::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);
}

bool Mouse::onTouchBegan(Touch *touch, Event *usused_event)
{
	//1 -just an example for how to get the _plater object
	//auto node = usused_event ->getCurrentTarget();
	//2 ��ȡ�˳�������ϵ�д��������꣬Ȼ�������������������ҵ�ǰλ�õ�ƫ����
	auto touchLocation = touch->getLocation();//�䲻׼��Ϊ�õ��ĵ�������Ļ���½�Ϊԭ��ģ������������Ե�ͼ���½�
	log("%f,%f",touchLocation.x,touchLocation.y);
	//log("%f,%f", _player->_player->getPosition().x, _player->_player->getPosition().y);
	auto offset = touchLocation + (_player->_player->getPosition()-Point(240.0,160.0))- _player->_player->getPosition();
	//log("%f,%f", offset.x,offset.y);
	//4 ���������λ�ô���һ�����ڣ�������ӵ�������
	auto projectile = Sprite::create("Projectile2.png");
	projectile->setPosition(_player->_player->getPosition().x , _player->_player->getPosition().y );
	this->addChild(projectile, 2);
	//_projectiles.pushBack(projectile);

	//5 ����nomalize��)����ƫ������Ϊ��λ����
	offset.normalize();
	auto shootAmount = offset * 1000;//ʹ�������Գ�����ǰ�ֱ�������Ļ�ı߽�
									 //6 ����������ӵ����ڵ�λ����ȥ������������һ��Ŀ��λ��
	auto realDest = shootAmount + projectile->getPosition();


	//����ײ���Ը�ֵ��monster
	auto projectileSize = projectile->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(projectileSize.width / 2);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
	projectile->setPhysicsBody(physicsBody);
	//7 ����һ��������������2�����ƶ���Ŀ��λ�ã�Ȼ��ӳ������Ƴ�
	auto actionMove = MoveTo::create(2.0f, realDest);
	auto actionRemove = RemoveSelf::create();
	projectile->runAction(Sequence::create(actionMove,actionRemove,nullptr));

	return true;
}

void Mouse::stopM()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}