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
	//���ɱ���ͼ
	void initBackGround();
	//����Logoͼ
	void initLogo();
	//����start��ť
	void initButton_start();
	//����&����Logo����
	void initLogoAnimation();
	//����&����start��������
	void initButton_startAnimation();

	void initSoundButton();

private:
	Size visibleSize;
	//��Ϸlogoͼλ��
	Point point_Logo;
	//logo
	Sprite *sprite_Logo;
	//��sprite�Զ���start����
	Sprite *button_Start;

	void onEnterTransitionDidFinish();
};

#endif
