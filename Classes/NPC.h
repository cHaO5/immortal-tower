#ifndef _NPC_H_
#define _NPC_H_
#include"cocos2d.h"
#include"GameManager.h"
//#include "SlotMenu.h"
USING_NS_CC;

class NPC: public Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(NPC);
    Sprite* npc ;//会被子类的覆盖到function里面
    //bool initWithNum();
    
    void initMenu_save();
    virtual void StartListen();
    virtual void PlayerDetect(float dt);
    void savemenuCloseCallback(cocos2d::Ref* pSender);
    void setSaveMenuInVisible();
    void setSaveMenuVisible();
    void addContent();

    Size visibleSize;
    //游戏logo图位置
    Point point_Logo;
    //logo
    Sprite *sprite_Logo;
    //用sprite自定义start按键
    Sprite *button_Start;
    //credit
    Sprite *button_credit;
    //记录menu
    Sprite *menu_Save;
    //menu_Save起始位置
    Point point_Menu_Save;
    //menu的关闭按键
    MenuItemSprite *button_Menu_Save_Close;
    //menu的关闭按键位置
    Point point_Button_Menu_Save_Close;
};

#endif
