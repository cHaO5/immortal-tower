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

	auto eventListener = EventListenerTouchOneByOne::create();//������
	eventListener->onTouchBegan = CC_CALLBACK_2(ControlLayerAttack::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, GameManager::getInstance()->currentPlayer);

	return true;
}

bool ControlLayerAttack::onTouchBegan(Touch *touch, Event *usused_event)
{
	auto player = GameManager::getInstance()->currentPlayer;
	//��ȡ�˳�������ϵ�д��������꣬Ȼ�������������������ҵ�ǰλ�õ�ƫ����
	auto touchLocation = touch->getLocation();//�䲻׼��Ϊ�õ��ĵ�������Ļ���½�Ϊԭ��ģ������������Ե�ͼ���½�
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
		playerPos.x -= (GameManager::getInstance()->TileSizewidth/ 2) - 2;//Ҳ���Ը�Ϊgetcontentwith�߽���ж�
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
	// 0.3s�����Ŷ����ӿ�ʼ���������õ�ʱ�䣬�Ӷ��Եò�����ô��е��
	auto moveTo = MoveTo::create(0.3, Vec2(player->getPositionX() + offsetX,player->getPositionY() + offsetY));
	player->runAction(moveTo);
}

bool setPlayerPosition(Point position)
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

