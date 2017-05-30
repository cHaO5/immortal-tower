#include"Mouse.h"
#include"ControlLayer.h"//为的也是那个物理的碰撞类
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
	auto eventListener = EventListenerTouchOneByOne::create();//鼠标监视
	eventListener->onTouchBegan = CC_CALLBACK_2(Mouse::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);
}

bool Mouse::onTouchBegan(Touch *touch, Event *usused_event)
{
	//1 -just an example for how to get the _plater object
	//auto node = usused_event ->getCurrentTarget();
	//2 获取了场景坐标系中触摸的坐标，然后计算了这个点相对于玩家当前位置的偏移量
	auto touchLocation = touch->getLocation();//射不准因为得到的点是以屏幕左下角为原点的，而人物坐标以地图左下角
    auto winSize = Director::getInstance()->getWinSize();

	auto offset = touchLocation+(_player->_player->getPosition()-Point(winSize.width/2, winSize.height/2)) - _player->_player->getPosition();
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	
	//log("%f,%f", );
	//log("%f,%f", visibleSize.width, visibleSize.height);
	log("%f,%f",touchLocation.x,touchLocation.y);
	log("%f,%f", _player->_player->getPosition().x, _player->_player->getPosition().y);	
	log("%f,%f", offset.x,offset.y);
	//4 在玩家所在位置创建一个飞镖，将其添加到场景中
	auto projectile = Sprite::create("Projectile2.png");
	projectile->setPosition(_player->_player->getPosition().x , _player->_player->getPosition().y );
	this->addChild(projectile);
	projectile->setGlobalZOrder(1);
	//小怪物的飞镖处理方式和人物还有点不同，小怪物是一个一个发射（能不能改成一直发射即同时发射两个呢？？+_+
	//但是人物是可以一直不停发射的，如何让schedule仿佛成为每个的一部分，那就是飞镖AI让飞镖成为独立个体
	//每个个体有自己的更新，判断，击中，移除，（小心物理引擎失效）
	/*
	int range = 100;
	auto shootAmount = offset * range;//这是攻击范围属性值
	//6 将次向量添加到飞镖的位置上去，这样就有了一个目标位置
	auto realDest = shootAmount + projectile->getPosition();*/

    //5 调用nomalize（)来将偏移量化为单位向量
	offset.normalize();
	//将碰撞属性赋值给monster
	auto projectileSize = projectile->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(projectileSize.width / 2);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
	projectile->setPhysicsBody(physicsBody);

	//weaponcontrol只是用于控制飞镖的运动加入检测有没有碰到障碍物
	auto weaponcontrol = new WeaponControl;
	projectile->addChild(weaponcontrol);
	weaponcontrol->_tileMap = _tileMap;
	weaponcontrol->_meta = _meta;//障碍传进去获取障碍
	weaponcontrol->proj = projectile;//把父节点传进去获取坐标
	weaponcontrol->direction = offset;//把方向传进去
    weaponcontrol->StartListen();
	/*
	//7 创建一个动作将飞镖在2秒内移动到目标位置，然后从场景中移除
	auto actionMove = MoveTo::create(1.0f, realDest);
	auto callFunc2 = CallFuncN::create(CC_CALLBACK_1(Mouse::DelayUnschedule, this));
	auto callFunc1 = CallFuncN::create(CC_CALLBACK_1(Mouse::IfActionRemove, this));//这两个function只有在移动过程中没有击中没有提前停止更新并移除才执行的
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