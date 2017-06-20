

#ifndef AnimationManager_hpp
#define AnimationManager_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class AnimationManager
{
public:
    static AnimationManager* getInstance();
    void init_bat();
    void init_skeleton();
    void init_soldier();
    void init_boss();
    void init_player1Attacked();
    void init_player2Attacked();
    void init_player3Attacked();
    void init_boss_appear();
    Animation* createAnimation(const char* prefixName, int start,int end, float delay);
    Animation* createAnimation(const char* prefixName, int start,int end, float delay,float flag);
    Animation* createAnimation(const char* prefixName1, const char* prefixName2, float delay);
    
private:
    static AnimationManager * instance;
};

#endif /* AnimationManager_hpp */
