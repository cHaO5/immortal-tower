#include"KeyBoard.h"

bool KeyBoard::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}

Player* KeyBoard::startKB()
{
	log("ddd");
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = CC_CALLBACK_1(KeyBoard::onKeyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_1(KeyBoard::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

	return _player;
}

void KeyBoard::onKeyPressed(EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		keyPressedDuration(EventKeyboard::KeyCode::KEY_UP_ARROW);
		_player->_player->setTexture("1_4.png");
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		keyPressedDuration(EventKeyboard::KeyCode::KEY_LEFT_ARROW);
		_player->_player->setTexture("1_3.png");
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		keyPressedDuration(EventKeyboard::KeyCode::KEY_DOWN_ARROW);
		_player->_player->setTexture("1_1.png");
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		keyPressedDuration(EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
		_player->_player->setTexture("1_2.png");
		break;
	default:break;
	}
}

void KeyBoard::keyPressedDuration(EventKeyboard::KeyCode code)
{
	auto playerPos = _player->_player->getPosition();
	int offsetX = 0, offsetY = 0;
	bool ref = true;
	switch (code)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		offsetX = -_tileMap->getTileSize().width;
		playerPos.x += offsetX;
		playerPos.x -= (_tileMap->getTileSize().width / 2)- 2;
		ref = this->_player->setPlayerPosition(playerPos);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		offsetX = _tileMap->getTileSize().width;
        playerPos.x += (_tileMap->getTileSize().width / 2) - 2;
		playerPos.x += offsetX;
		ref = this->_player->setPlayerPosition(playerPos);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		offsetY = _tileMap->getTileSize().height;
		playerPos.y += (_tileMap->getTileSize().height / 2) - 2;
		playerPos.y += offsetY;
		ref = this->_player->setPlayerPosition(playerPos);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		offsetY = -_tileMap->getTileSize().height;
		playerPos.y -= (_tileMap->getTileSize().height / 2) - 2;
		playerPos.y += offsetY;
		ref = this->_player->setPlayerPosition(playerPos);
		break;
	default:
		offsetY = offsetX = 0;
		break;
	}
	//playerPos.x += offsetX;
	//playerPos.y += offsetY;
	//bool ref = true;
	//ref = this->_player->setPlayerPosition(playerPos);
	if (ref == false)
	{
		offsetY = offsetX = 0;
	}
	// 0.3s代表着动作从开始到结束所用的时间，从而显得不会那么机械。
	auto moveTo = MoveTo::create(0.3, Vec2(_player->_player->getPositionX() + offsetX, _player->_player->getPositionY() + offsetY));
	_player->_player->runAction(moveTo);
}

void KeyBoard::onKeyReleased(EventKeyboard::KeyCode keyCode)
{

}

void KeyBoard::stopKB()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}