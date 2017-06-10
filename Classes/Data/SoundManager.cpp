#include "SoundManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h" 

using namespace CocosDenshion;
USING_NS_CC;

bool SoundManager::cheakEffectState()
{
	if (UserDefault::getInstance()->getIntegerForKey("backeffect", 1) == 1)
		return true;
	else
		return false;
}


void SoundManager::playClickEffect()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_GUIButtonCommon.wav");
}

void SoundManager::playWelcomeBackMusic()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/savage_music_theme.wav");
	if (UserDefault::getInstance()->getIntegerForKey("backmusic", 1) == 0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playDesertBattle()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/savage_music_desert_battle.wav");
	if (UserDefault::getInstance()->getIntegerForKey("backmusic", 1) == 0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playJungleBattle()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/savage_music_jungle_battle.wav");
	if (UserDefault::getInstance()->getIntegerForKey("backmusic", 1) == 0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playGameTheme1()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Map_Theme_1.wav");
	if (UserDefault::getInstance()->getIntegerForKey("backmusic", 1) == 0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playNextWaveReady()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_NextWaveReady.wav");
}


void SoundManager::playIncomingWave()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_WaveIncoming.wav");
}

void SoundManager::playQuestCompleted()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_QuestCompleted.wav");
}

void SoundManager::playQuestFailed()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/Sound_QuestFailed.wav");
}

