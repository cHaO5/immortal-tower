#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include"cocos2d.h"
#include"SceneManager.h"
#include"ControlLayer.h"
USING_NS_CC;

class MenuLayer : public Layer
{
public:
	SceneManager * tsm;
	CREATE_FUNC(MenuLayer);
	virtual bool init();
	
private:
    void createBG();
	void createButton(cocos2d::Point centerPoint);
	void start();
};

#endif
