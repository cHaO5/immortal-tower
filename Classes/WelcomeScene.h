#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
	//生成背景图
	void initBackGround();
	//生成Logo图
	void initLogo();
	//生成start按钮
	void initButton_start();
	//生成&播放Logo动画
	void initLogoAnimation();
	//生成&播放start按键动画
	void initButton_startAnimation();

	void initSoundButton();

private:
	Size visibleSize;
	//游戏logo图位置
	Point point_Logo;
	//logo
	Sprite *sprite_Logo;
	//用sprite自定义start按键
	Sprite *button_Start;

	void onEnterTransitionDidFinish();
};

#endif
