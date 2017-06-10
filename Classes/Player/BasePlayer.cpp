#include"Player/BasePlayer.h"
#include"Layer/ControlLayer.h"
#include"Data/GameManager.h"

bool BasePlayer::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void BasePlayer::attackMonster()
{
	auto attackControl = ControlLayerAttack::createAttackControl();
	addChild(attackControl);
}

void BasePlayer::Move()
{
	auto moveControl = ControlLayerMove::createMoveControl();
	addChild(moveControl);
}

