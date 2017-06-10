#include "Weapon/Weapon0.h"
#include"Data\GameManager.h"
#include"Data\SoundManager.h"
USING_NS_CC;
Weapon0* Weapon0::create(Vec2 offset)
{
	auto Sprite = new Weapon0();
	Sprite->direction = offset;
	if (Sprite && Sprite->init()) {
		Sprite->autorelease();
		return Sprite;
	}
	CC_SAFE_DELETE(Sprite);

	return NULL;
}
bool Weapon0::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	baseweapon = Sprite::create(GameManager::getInstance()->Weapon_texture[GameManager::getInstance()->currentWeaponType]);	
	baseweapon->setPosition(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
	addChild(baseweapon,2);

	//����ײ���Ը�ֵ��monster
	auto projectileSize = baseweapon->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(projectileSize.width / 2);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)GameManager::PhysicsCategory::Projectile);
	physicsBody->setCollisionBitmask((int)GameManager::PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)GameManager::PhysicsCategory::Monster);
	baseweapon->setPhysicsBody(physicsBody);

	StartListen(range,direction);

	return true;
}