#include "SoundManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h" 

using namespace CocosDenshion;
USING_NS_CC;

bool SoundManager::cheakEffectState()
{
	if (UserDefault::getInstance()->getIntegerForKey("backeffect") == 1)
		return true;
	else
		return false;
}


void SoundManager::playClickEffect()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("Sound_GUIButtonCommon.wav");
}

void SoundManager::playWelcomeBackMusic()
{
    SimpleAudioEngine::getInstance()->playBackgroundMusic("savage_music_theme.wav", 1);
	if (UserDefault::getInstance()->getIntegerForKey("backmusic") == 0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playDesertBattle()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("savage_music_desert_battle.wav", 1);
    if (UserDefault::getInstance()->getIntegerForKey("backmusic") == 0) {
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
}

void SoundManager::playJungleBattle()
{
    log("1898989");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("savage_music_jungle_battle.wav", 1);
	if (UserDefault::getInstance()->getIntegerForKey("backmusic") == 0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playGameTheme1()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Map_Theme_1.wav", 1);
	if (UserDefault::getInstance()->getIntegerForKey("backmusic") == 0)
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundManager::playNextWaveReady()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("Sound_NextWaveReady.wav");
}


void SoundManager::playIncomingWave()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("Sound_WaveIncoming.wav");
}

void SoundManager::playQuestCompleted()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("Sound_QuestCompleted.wav");
}

void SoundManager::playQuestFailed()
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("Sound_QuestFailed.wav");
}

