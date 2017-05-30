#include"Mouse.h"
#include"ControlLayer.h"//为的也是那个物理的碰撞类

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
	log("%f,%f",touchLocation.x,touchLocation.y);
	//log("%f,%f", _player->_player->getPosition().x, _player->_player->getPosition().y);
	auto offset = touchLocation + (_player->_player->getPosition()-Point(240.0,160.0))- _player->_player->getPosition();
	//log("%f,%f", offset.x,offset.y);
	//4 在玩家所在位置创建一个飞镖，将其添加到场景中
	auto projectile = Sprite::create("Projectile2.png");
	projectile->setPosition(_player->_player->getPosition().x , _player->_player->getPosition().y );
	this->addChild(projectile, 2);
	//_projectiles.pushBack(projectile);

	//5 调用nomalize（)来将偏移量化为单位向量
	offset.normalize();
	auto shootAmount = offset * 1000;//使长度足以超过当前分辨率下屏幕的边界
									 //6 将次向量添加到飞镖的位置上去，这样就有了一个目标位置
	auto realDest = shootAmount + projectile->getPosition();


	//将碰撞属性赋值给monster
	auto projectileSize = projectile->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(projectileSize.width / 2);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
	projectile->setPhysicsBody(physicsBody);
	//7 创建一个动作将飞镖在2秒内移动到目标位置，然后从场景中移除
	auto actionMove = MoveTo::create(2.0f, realDest);
	auto actionRemove = RemoveSelf::create();
	projectile->runAction(Sequence::create(actionMove,actionRemove,nullptr));

	return true;
}

void Mouse::stopM()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}