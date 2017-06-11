#include "Weapon/Weapon1.h"
#include"Data\GameManager.h"
#include"Data\SoundManager.h"
USING_NS_CC;
Weapon1* Weapon1::create(Vec2 offset)
{
	auto Sprite = new Weapon1();
	Sprite->direction = offset;
	if (Sprite && Sprite->init()) {
		Sprite->autorelease();
		return Sprite;
	}
	CC_SAFE_DELETE(Sprite);

	return NULL;
}
bool Weapon1::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	baseweapon = Sprite::create(GameManager::getInstance()->Weapon_texture[GameManager::getInstance()->currentWeaponType]);
	baseweapon->setPosition(GameManager::getInstance()->currentPlayer->getPosition().x, GameManager::getInstance()->currentPlayer->getPosition().y);
	addChild(baseweapon,0);

	//����ײ���Ը�ֵ��monster
	auto projectileSize = baseweapon->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(projectileSize.width / 2);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
	baseweapon->setPhysicsBody(physicsBody);

	StartListen(range,direction);

	return true;
}