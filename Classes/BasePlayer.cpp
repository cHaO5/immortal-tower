#include"BasePlayer.h"
#include"ControlLayer.h"
#include"GameManager.h"

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

