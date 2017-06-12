#ifndef _PLAYER_STATE_MENU_H_
#define _PLAYER_STATE_MENU_H_

#include "cocos2d.h"
#include "GameManager.h"
#include "GameOption.h"
#include "Slider.h"

USING_NS_CC;

class PlayerStateMenu : public Layer
{
public:
	virtual bool init();
	void onEnterTransitionDidFinish();
	CREATE_FUNC(PlayerStateMenu);

	void DetectVictory(float t);
	void DetectFailure(float t);

	Slider* LifeSlider;
	Sprite* pause;
	Sprite* fog;

	//GameManager* instance;
    void pauseGame();

	GameOption *gameOption;
	void addGameOption();
	void initGameOption();
	void removeGameOption();
};
#endif
