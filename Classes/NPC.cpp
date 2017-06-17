#include "NPC.h"

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
    
    StartListen();
    
    return true;
}

void NPC::StartListen()
{
    this->schedule(schedule_selector(NPC::PlayerDetect), 0.01f);
}

void NPC::PlayerDetect(float dt)
{
    if (GameManager::getInstance()->currentPlayer->getBoundingBox().intersectsRect(npc->getBoundingBox()))
    {
        this->unschedule(schedule_selector(NPC::PlayerDetect));
        //Scene::dialog(GameManager::getInstance()->CurrentLevel);
    }
}

