#include"Layer/ControlLayer.h"
#include"Data/GameManager.h"
#include"Weapon/BaseWeapon.h"
#include"Weapon/Weapon0.h"
#include"Weapon/Weapon1.h"

ControlLayerAttack* ControlLayerAttack::createAttackControl()
{
	auto layer = new ControlLayerAttack();
	if (layer && layer->initAttackControl()) 
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

	return NULL;
}

bool ControlLayerAttack::initAttackControl()
{
	if (!Layer::init())
	{
		return false;
	}

	auto eventListener = EventListenerTouchOneByOne::create();//鼠标监视
	eventListener->onTouchBegan = CC_CALLBACK_2(ControlLayerAttack::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, GameManager::getInstance()->currentPlayer);

	return true;
}

bool ControlLayerAttack::onTouchBegan(Touch *touch, Event *usused_event)
{
	auto player = GameManager::getInstance()->currentPlayer;
	//获取了场景坐标系中触摸的坐标，然后计算了这个点相对于玩家当前位置的偏移量
	auto touchLocation = touch->getLocation();//射不准因为得到的点是以屏幕左下角为原点的，而人物坐标以地图左下角
	auto winSize = Director::getInstance()->getWinSize();
	auto offset = touchLocation + (player->getPosition() - Point(winSize.width / 2, winSize.height / 2)) - player->getPosition();
	offset.normalize();

	BaseWeapon* weapon;
	switch (GameManager::getInstance()->currentWeaponType)
	{
	case(0):weapon = Weapon0::create(offset);
		    addChild(weapon);
		    break;
	case(1):weapon = Weapon1::create(offset);
			addChild(weapon);
			break;
	default:
		break;
	}
	return true;
}

ControlLayerMove* ControlLayerMove::createMoveControl()
{
	auto layer = new ControlLayerMove();
	if (layer && layer->initMoveControl())
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

	return NULL;
}

bool ControlLayerMove::initMoveControl()
{
	if (!Layer::init())
	{
		return false;
	}

	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = CC_CALLBACK_1(ControlLayerMove::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

	return true;
}
void ControlLayerMove::onKeyPressed(EventKeyboard::KeyCode keyCode)
{
	auto player = GameManager::getInstance()->currentPlayer;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		keyPressedDuration(EventKeyboard::KeyCode::KEY_UP_ARROW);
		player->setTexture(GameManager::getInstance()->Player_texture[GameManager::getInstance()->currentPlayerState_type][0]);
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		keyPressedDuration(EventKeyboard::KeyCode::KEY_LEFT_ARROW);
		player->setTexture(GameManager::getInstance()->Player_texture[GameManager::getInstance()->currentPlayerState_type][1]);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		keyPressedDuration(EventKeyboard::KeyCode::KEY_DOWN_ARROW);
		player->setTexture(GameManager::getInstance()->Player_texture[GameManager::getInstance()->currentPlayerState_type][2]);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		keyPressedDuration(EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
		player->setTexture(GameManager::getInstance()->Player_texture[GameManager::getInstance()->currentPlayerState_type][3]);
		break;
	default:break;
	}
}

void ControlLayerMove::keyPressedDuration(EventKeyboard::KeyCode code)
{
	bool setPlayerPosition(Point position);
	auto player = GameManager::getInstance()->currentPlayer;
	auto playerPos = player->getPosition();
	int offsetX = 0, offsetY = 0;
	bool ref = true;
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		offsetX = -GameManager::getInstance()->Player_speed[GameManager::getInstance()->currentPlayerState_type];
		playerPos.x -= (GameManager::getInstance()->TileSizewidth/ 2) - 2;//也可以改为getcontentwith边界点判断
		playerPos.x += offsetX;
		ref = setPlayerPosition(playerPos);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		offsetX = GameManager::getInstance()->Player_speed[GameManager::getInstance()->currentPlayerState_type];
		playerPos.x += (GameManager::getInstance()->TileSizewidth / 2) - 2;
		playerPos.x += offsetX;
		ref = setPlayerPosition(playerPos);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		offsetY = GameManager::getInstance()->Player_speed[GameManager::getInstance()->currentPlayerState_type];
		playerPos.y += (GameManager::getInstance()->TileSizeheight / 2) - 2;
		playerPos.y += offsetY;
		ref = setPlayerPosition(playerPos);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		offsetY = -GameManager::getInstance()->Player_speed[GameManager::getInstance()->currentPlayerState_type];
		playerPos.y -= (GameManager::getInstance()->TileSizeheight / 2) - 2;
		playerPos.y += offsetY;
		ref = setPlayerPosition(playerPos);
		break;
	default:
		offsetY = offsetX = 0;
		break;
	}
	if (ref == false)
	{
		offsetY = offsetX = 0;
	}
	// 0.3s代表着动作从开始到结束所用的时间，从而显得不会那么机械。
	auto moveTo = MoveTo::create(0.3, Vec2(player->getPositionX() + offsetX,player->getPositionY() + offsetY));
	player->runAction(moveTo);
}

bool setPlayerPosition(Point position)
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
	case(1):logicmap =GameManager::getInstance()->Level1LogicMap[0];
		break;
	case(2):logicmap =GameManager::getInstance()->Level2LogicMap[0];
		break;
	default:
		break;
	}
	auto value = *((logicmap + GameManager::getInstance()->MapSizewidth*y) + x);
	log("%d,%d", x, y);
	log("%d", value);
	switch (value)
	{
	case(1):
		return false;
	default:
		return true;
	}
}

