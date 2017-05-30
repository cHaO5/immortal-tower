#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include"cocos2d.h"
#include"Slider.h"

USING_NS_CC;


class SceneManager
{
public:
	Scene * startScene;
	Scene * gameScene;
	Slider* slider;
	
	//Scene * settingsScene;
	//Scene* winScene;
	//Scene* loseScene;
	//bool mode;

	void createScene();
	void toGameScene();
	//void toStartScene();
	//void toSettingsScene();
	//void toWinScene();
	//void toLoseScene();

};

#endif