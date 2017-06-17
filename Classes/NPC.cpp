#include "NPC.h"
#include "WelcomeScene.h"
#include "TransitionGame.h"
#include "SoundManager.h"
#include "SimpleAudioEngine.h"
#include"GameMenuScene.h"
#include "Information.h"
#include"SlotMenu.h"
#include "cocos2d.h"
using namespace CocosDenshion;

bool NPC::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    //具体坐标还要修改
    switch(GameManager::getInstance()->CurrentLevel)
    {
        case(0):npc = Sprite::create("npc/npc-1.png");
            npc->setPosition(Point(4 * 128 - 64, 6 * 128 - 64));
            break;
        case(1):npc = Sprite::create("npc/npc-2.png");
            npc->setPosition(Point(10 * 128 - 64, 10 * 128 - 64));
            break;
        case(2):npc = Sprite::create("npc/npc-3.png");
            npc->setPosition(Point(4 * 128 - 64, 6 * 128 - 64));
            break;
        default:
            break;
    }
    addChild(npc,0);
    
    initMenu_save();
    StartListen();
    setSaveMenuInVisible();
    return true;
}

void NPC::initMenu_save()
{
    menu_Save = Sprite::createWithSpriteFrameName("mainmenu_saveslot_bg.png");
    menu_Save->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //计算位置
//    point_Menu_Save.x = visibleSize.width / 2;
//    point_Menu_Save.y = point_Logo.y - sprite_Logo->getContentSize().height*1.4 / 2+110;
    point_Menu_Save.x = 4 * 128 - 64;
    point_Menu_Save.y = 6 * 128 - 64;
    log("logggggggggggggggggggggggggggg%f %f", point_Menu_Save.x, point_Menu_Save.y);
    //起始位置在屏幕外
    menu_Save->setPosition(Point(point_Menu_Save.x, point_Menu_Save.y));
    //添加
    addChild(menu_Save, 0);
    //关闭按键类型为MenuItemSprite
    button_Menu_Save_Close = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0001.png"),
                                                    Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0002.png"),
                                                    CC_CALLBACK_1(NPC::savemenuCloseCallback, this));
    //计算位置
    addContent();
    point_Button_Menu_Save_Close.x = point_Menu_Save.x;
    point_Button_Menu_Save_Close.y = point_Menu_Save.y - menu_Save->getContentSize().height / 2 + button_Menu_Save_Close->getContentSize().height + 2;
    //log("logggggggggggggggggggggggggggg%f %f", point_Button_Menu_Save_Close.x, point_Button_Menu_Save_Close.y);
    
    button_Menu_Save_Close->setPosition(Point(point_Button_Menu_Save_Close.x, point_Button_Menu_Save_Close.y - 500));
    //参见MenuItem用法
    auto menu = Menu::create(button_Menu_Save_Close, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 0);
}

void NPC::StartListen()
{
    this->schedule(schedule_selector(NPC::PlayerDetect), 1.0f);
}

void NPC::PlayerDetect(float dt)
{
    if (GameManager::getInstance()->currentPlayer->getBoundingBox().intersectsRect(npc->getBoundingBox()))
    {
        setSaveMenuVisible();
        this->unschedule(schedule_selector(NPC::PlayerDetect));
        setSaveMenuInVisible();
    }
}

void NPC::savemenuCloseCallback(cocos2d::Ref* pSender)
{
    SoundManager::playClickEffect();
    setSaveMenuInVisible();
}

void NPC::setSaveMenuInVisible()
{
    //移出屏幕外
    menu_Save->runAction(MoveBy::create(0.3f, Point(0, -500)));
    button_Menu_Save_Close->runAction(MoveBy::create(0.3f, Point(0, -500)));
}

void NPC::setSaveMenuVisible()
{
    //移到屏幕内
    menu_Save->runAction(MoveTo::create(0.3f, point_Menu_Save));
    button_Menu_Save_Close->runAction(MoveTo::create(0.3f, point_Button_Menu_Save_Close));
}

void NPC::addContent()
{
    Label *label;
    switch (GameManager::getInstance()->CurrentLevel) {
        case 0:
            label = Label::createWithTTF("I have no idea what is in the tower.","Resources/Comic_Book.ttf",42,
                                         Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
            break;
        case 1:
            label = Label::createWithTTF("Have you met you-know-who?","Resources/Comic_Book.ttf",42,
                                         Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
            break;
        case 2:
            label = Label::createWithTTF("Cross the maze, and you will find him.\nGOOD LUCK...","Resources/Comic_Book.ttf",42,
                                         Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
            break;
        default:
            break;
    }
    label->setColor(Color3B(219,205,139));
    label->setPosition(Point(menu_Save->getContentSize().width/2, menu_Save->getContentSize().height/2));
    menu_Save->addChild(label);
}
