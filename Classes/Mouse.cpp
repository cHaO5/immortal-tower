#include"Mouse.h"
#include"ControlLayer.h"//Ϊ��Ҳ���Ǹ��������ײ��
#include"WeaponControl.h"

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
    auto winSize = Director::getInstance()->getWinSize();

	auto offset = touchLocation+(_player->_player->getPosition()-Point(winSize.width/2, winSize.height/2)) - _player->_player->getPosition();
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	
	//log("%f,%f", );
	//log("%f,%f", visibleSize.width, visibleSize.height);
	log("%f,%f",touchLocation.x,touchLocation.y);
	log("%f,%f", _player->_player->getPosition().x, _player->_player->getPosition().y);	
	log("%f,%f", offset.x,offset.y);
	//4 ���������λ�ô���һ�����ڣ�������ӵ�������
	auto projectile = Sprite::create("Projectile2.png");
	projectile->setPosition(_player->_player->getPosition().x , _player->_player->getPosition().y );
	this->addChild(projectile);
	projectile->setGlobalZOrder(1);
	//С����ķ��ڴ���ʽ�����ﻹ�е㲻ͬ��С������һ��һ�����䣨�ܲ��ܸĳ�һֱ���伴ͬʱ���������أ���+_+
	//���������ǿ���һֱ��ͣ����ģ������schedule�·��Ϊÿ����һ���֣��Ǿ��Ƿ���AI�÷��ڳ�Ϊ��������
	//ÿ���������Լ��ĸ��£��жϣ����У��Ƴ�����С����������ʧЧ��
	/*
	int range = 100;
	auto shootAmount = offset * range;//���ǹ�����Χ����ֵ
	//6 ����������ӵ����ڵ�λ����ȥ������������һ��Ŀ��λ��
	auto realDest = shootAmount + projectile->getPosition();*/

    //5 ����nomalize��)����ƫ������Ϊ��λ����
	offset.normalize();
	//����ײ���Ը�ֵ��monster
	auto projectileSize = projectile->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(projectileSize.width / 2);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
	projectile->setPhysicsBody(physicsBody);

	//weaponcontrolֻ�����ڿ��Ʒ��ڵ��˶���������û�������ϰ���
	auto weaponcontrol = new WeaponControl;
	projectile->addChild(weaponcontrol);
	weaponcontrol->_tileMap = _tileMap;
	weaponcontrol->_meta = _meta;//�ϰ�����ȥ��ȡ�ϰ�
	weaponcontrol->proj = projectile;//�Ѹ��ڵ㴫��ȥ��ȡ����
	weaponcontrol->direction = offset;//�ѷ��򴫽�ȥ
    weaponcontrol->StartListen();
	/*
	//7 ����һ��������������2�����ƶ���Ŀ��λ�ã�Ȼ��ӳ������Ƴ�
	auto actionMove = MoveTo::create(1.0f, realDest);
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Mouse::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(Mouse::IfActionRemove, this));//������functionֻ�����ƶ�������û�л���û����ǰֹͣ���²��Ƴ���ִ�е�
	projectile->runAction(Sequence::create(actionMove,callFunc2,callFunc1, nullptr));
*/
	//auto actionRemove = RemoveSelf::create();
	//projectile->runAction(Sequence::create(actionMove,actionRemove,nullptr));

	return true;
}

void Mouse::stopM()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}