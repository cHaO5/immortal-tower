#ifndef _LOADING_SCENE_H_
#define _LOADING_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class LoadingScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);
	void loadSouce();
	void logic(float dt);
	int numberOfLoadedRes;
};
#endif
