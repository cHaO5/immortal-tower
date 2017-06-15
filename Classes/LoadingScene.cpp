#include "LoadingScene.h"
#include "SimpleAudioEngine.h" 
#include "WelcomeScene.h"
#include"GameScene.h"
using namespace CocosDenshion;
USING_NS_CC;


Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoadingScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	numberOfLoadedRes = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto back = Sprite::create("Default@2x.png");
	back->setRotation(-90.0f);
	back->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(back);
	schedule(schedule_selector(LoadingScene::logic));
	return true;
}

void LoadingScene::loadSouce()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("savage_music_theme.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("savage_music_desert_battle.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Map_Theme_1.wav");

	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_GUIButtonCommon.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_GUIOpenTowerMenu.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("GUITransitionClose.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("GUITransitionOpen.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("Archer_Ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Artillery_Ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Mage_Ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Barrack_Ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("Sound_WaveIncoming.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_WinStars.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_LooseLife.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_NextWaveReady.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_TowerBuilding.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_TowerOpenDoor.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_TowerSell.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_TowerUpgrade.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_VictoryCheer.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("Sound_ArrowHit2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_ArrowHit3.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_ArrowRelease3.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_ArrowRelease2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_Bomb1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_MageShot.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("Sound_QuestCompleted.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_QuestFailed.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("Sound_FireballUnleash.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Sound_FireballHit.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("Archer_Taunt1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Archer_Taunt2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Barrack_Taunt1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Barrack_Taunt2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Mage_Taunt1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Mage_Taunt2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Barrack_Move.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Artillery_Taunt1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Artillery_Taunt2.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("crossbow_eagle.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("crossbow_multishot.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("crossbow_taunt_ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("axlethrower_totem_vanish.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("axlethrower_totem_weakness.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("axlethrower_totem_spirits.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("axlethrower_taunt_totem1.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("dwaarp_attack.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("dwaarp_drillIn.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("dwaarp_drillOut.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("dwaarp_lavaSmash.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("mecha_dropoil.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("mecha_spawn.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("mecha_taunt_ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("mecha_walk.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("archmage_attack.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("archmage_precharge.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("archmage_taunt_ready.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("archmage_twister.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("necromancer_attack.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("necromancer_deathknight_taunt_2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("necromancer_taunt_dknight.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("necromancer_taunt_ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("assassin_taunt_ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("Reinforcements_Event2.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("inapp_cash.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("inapp_freeze.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("inapp_hearts.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("Sound_RallyPointPlaced.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("earthquake_taunt_ready.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("boss_efreeti_clapping.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("boss_efreeti_death.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("boss_efreeti_evillaugh.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("boss_mono_chestdrum.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("boss_mono_chimps_1.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("boss_mono_chimps_2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("boss_mono_chimps_3.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("boss_mono_death.wav");

	numberOfLoadedRes++;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_a-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ingame_gui-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_a_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_a_3-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_32_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("towers-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_na_2_IPAD2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_campaign_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_iron_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gui_menu_sprite_heroic_32-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_16_na-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("map_spritesheet_16_na_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cinematics_comic1-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_desert_3-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_desert-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies_jungle_2-hd.plist");
    
    UserDefault::getInstance()->setIntegerForKey("gamemusic", 0);
    log("11111111111111111111111111");
	Scene* scene = GameScene::createScene();//解决文件太大卡顿
	numberOfLoadedRes++;
}

void LoadingScene::logic(float dt)
{
	if (numberOfLoadedRes == 0)
	{
		loadSouce();
	}
	if (numberOfLoadedRes == 2)
	{
		auto scene = WelcomeScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}
