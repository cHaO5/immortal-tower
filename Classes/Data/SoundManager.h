#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

class SoundManager
{
public:
	static void playClickEffect();
	static void playIncomingWave();
	static void playNextWaveReady();

	//¹Ø¿¨½áÊø
	static void playQuestCompleted();
	static void playQuestFailed();

public:
	static void playWelcomeBackMusic();
	static void playJungleBattle();
	static void playDesertBattle();
	static void playGameTheme1();
private:
	static bool cheakEffectState();
};

#endif