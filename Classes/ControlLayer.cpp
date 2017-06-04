#include"ControlLayer.h"

ControlLayer* ControlLayer::createControl()
{
	log("jjjj");
	ControlLayer* controlLayer=ControlLayer::create(); 

	return controlLayer;
}

bool ControlLayer::init()
{
	log("iiii");
	//log("%d", this->getTag());

	auto winSize = Director::getInstance()->getWinSize();

	_tileMap = TMXTiledMap::create("_tilemap.tmx");

	this->addChild(_tileMap);
	_tileMap->getLayer("floor")->setGlobalZOrder(-1);
	_tileMap->getLayer("wall_1")->setGlobalZOrder(0);
    _tileMap->getLayer("wall_2")->setGlobalZOrder(2);
	//_tileMap->getLayer("collections")->setGlobalZOrder(2);
	_tileMap->getLayer("meta")->setGlobalZOrder(3);

	//获取地图中不能行走的区域（墙等障碍物）
	_meta = _tileMap->getLayer("meta");
	//隐藏不能行走的区域
	_meta->setVisible(false);
	//获取地图上的东西
	_fruit = _tileMap->getLayer("collections");

	player = new Player(_tileMap,_meta,_fruit);
	player->init();
	this->addChild(player);
	player->setGlobalZOrder(0);
	//log("%f,%f", player->_player->getAnchorPoint().x, player->_player->getAnchorPoint().y);
	//再使用跟随函数之前先更新一遍，不然会跳转
	int x = player->_player->getPosition().x;
	int y = player->_player->getPosition().y;
	auto centerPoint = Point(winSize.width / 2, winSize.height / 2);
	auto actualPoint = Point(x, y);
	auto viewPoint = centerPoint - actualPoint;
	this->setPosition(viewPoint);

    winlayer =new WinLayer;
	winlayer->_player = player;
	winlayer->init();
	this->addChild(winlayer);

	monster = new Monster;
	monster->_player = player;
	monster->_tileMap = _tileMap;
	monster->_meta =_meta;
	monster->_fruit = _fruit;
	monster->setGlobalZOrder(1);
	monster->init();
	this->addChild(monster);

	keyBoard = KeyBoard::create();
	keyBoard->_player = player;
	keyBoard->_tileMap = _tileMap;
	log("mmm");
	keyBoard->startKB();//player=????
	log("ppp");
	this->addChild(keyBoard);

	mouse = new Mouse;
	mouse->_player = player;
	mouse->_tileMap = _tileMap;
	mouse->_meta = _meta;
	mouse->init();
	mouse->startM();
	this->addChild(mouse);

	//用于清除碰撞后的飞镖与Monster
	//安装了一个监听器使得HelloWorld::onContactBegan可以接收事件，并把监听器添加到了EventDispatcher中，只要两个Bitmask（刚才定义的属性）使得互相可以碰撞的物体碰撞，EventDispatcher 就会去调用 onContactBegan.
	auto contactListener = EventListenerPhysicsContact::create();//但是一个射击多个就可能要出问题因为重复remove
	contactListener->onContactBegin = CC_CALLBACK_1(ControlLayer::onContactBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}
//处理碰撞——移除碰撞的二者
bool ControlLayer::onContactBegan(PhysicsContact &contact)//PhysicsContact传递了碰撞的信息
{
	log("123456");
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != NULL)
	{
		nodeA->removeFromParent();
	}
	//A是？bug就是经常一群聚在一起的时候射击就会异常因为removefromscene已经移除了一次
	//但是为什么还会运行成功？？？这个是在碰撞时就清除，那个是在不发生碰撞时清除，如果发生了碰撞就已经清除了，
	//那removefromscene会不会发生错误？？？
	if (nodeB != NULL)
	{
	    nodeB->removeFromParent();
	}
	return true;
}


