

#include "AnimationManager.hpp"

AnimationManager* AnimationManager::instance;

AnimationManager* AnimationManager::getInstance()
{
    if (instance==NULL)
        instance=new AnimationManager;
    return instance;
}

void AnimationManager::init_bat()
{
    log("bat");
    AnimationCache::getInstance()->addAnimation(createAnimation("batD-%d.png" , 1, 4, 1.0f), "batD" );
    AnimationCache::getInstance()->addAnimation(createAnimation("batDL-%d.png", 1, 4, 1.0f), "batDL");
    AnimationCache::getInstance()->addAnimation(createAnimation("batDR-%d.png", 1, 4, 1.0f), "batDR");
    AnimationCache::getInstance()->addAnimation(createAnimation("batL-%d.png" , 1, 4, 1.0f), "batL" );
    AnimationCache::getInstance()->addAnimation(createAnimation("batR-%d.png" , 1, 4, 1.0f), "batR" );
    AnimationCache::getInstance()->addAnimation(createAnimation("batU-%d.png" , 1, 4, 1.0f), "batU" );
    AnimationCache::getInstance()->addAnimation(createAnimation("batUL-%d.png", 1, 4, 1.0f), "batUL");
    AnimationCache::getInstance()->addAnimation(createAnimation("batUR-%d.png", 1, 4, 1.0f), "batUR");
}

void AnimationManager::init_skeleton()
{
    AnimationCache::getInstance()->addAnimation(createAnimation("skeletonD-%d.png" , 1, 4, 1.0f), "skeletonD" );
    AnimationCache::getInstance()->addAnimation(createAnimation("skeletonDL-%d.png", 1, 4, 1.0f), "skeletonDL");
    AnimationCache::getInstance()->addAnimation(createAnimation("skeletonDR-%d.png", 1, 4, 1.0f), "skeletonDR");
    AnimationCache::getInstance()->addAnimation(createAnimation("skeletonL-%d.png" , 1, 4, 1.0f), "skeletonL" );
    AnimationCache::getInstance()->addAnimation(createAnimation("skeletonR-%d.png" , 1, 4, 1.0f), "skeletonR" );
    AnimationCache::getInstance()->addAnimation(createAnimation("skeletonU-%d.png" , 1, 5, 1.0f), "skeletonU" );
    AnimationCache::getInstance()->addAnimation(createAnimation("skeletonUL-%d.png", 1, 3, 1.0f), "skeletonUL");
    AnimationCache::getInstance()->addAnimation(createAnimation("skeletonUR-%d.png", 1, 3, 1.0f), "skeletonUR");
}

void AnimationManager::init_soldier()
{
    AnimationCache::getInstance()->addAnimation(createAnimation("soldierD-%d.png" , 1, 4, 1.0f), "soldierD" );
    AnimationCache::getInstance()->addAnimation(createAnimation("soldierDL-%d.png", 1, 3, 1.0f), "soldierDL");
    AnimationCache::getInstance()->addAnimation(createAnimation("soldierDR-%d.png", 1, 3, 1.0f), "soldierDR");
    AnimationCache::getInstance()->addAnimation(createAnimation("soldierL-%d.png" , 1, 3, 1.0f), "soldierL" );
    AnimationCache::getInstance()->addAnimation(createAnimation("soldierR-%d.png" , 1, 3, 1.0f), "soldierR" );
    AnimationCache::getInstance()->addAnimation(createAnimation("soldierU-%d.png" , 1, 4, 1.0f), "soldierU" );
    AnimationCache::getInstance()->addAnimation(createAnimation("soldierUL-%d.png", 1, 3, 1.0f), "soldierUL");
    AnimationCache::getInstance()->addAnimation(createAnimation("soldierUR-%d.png", 1, 3, 1.0f), "soldierUR");
}

void AnimationManager::init_boss()
{
    AnimationCache::getInstance()->addAnimation(createAnimation("boss%d.png" , 1, 3, 30.0f), "boss" );
    AnimationCache::getInstance()->addAnimation(createAnimation("flyl%d.png", 1, 6, 30.0f), "flyl");
    AnimationCache::getInstance()->addAnimation(createAnimation("flyr%d.png", 1, 6, 30.0f), "flyr");
}

void AnimationManager::init_player1Attacked()
{
    AnimationCache::getInstance()->addAnimation(createAnimation("player1D.png"  ,"player1attackedD.png" , 0.3f), "player1attackedD"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player1DL.png" ,"player1attackedDL.png", 0.3f), "player1attackedDL" );
    AnimationCache::getInstance()->addAnimation(createAnimation("player1DR.png" ,"player1attackedDR.png", 0.3f), "player1attackedDR" );
    AnimationCache::getInstance()->addAnimation(createAnimation("player1L.png"  ,"player1attackedL.png" , 0.3f), "player1attackedL"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player1R.png"  ,"player1attackedR.png" , 0.3f), "player1attackedR"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player1U.png"  ,"player1attackedU.png" , 0.3f), "player1attackedU"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player1UL.png" ,"player1attackedUL.png", 0.3f), "player1attackedUL" );
    AnimationCache::getInstance()->addAnimation(createAnimation("player1UR.png" ,"player1attackedUR.png", 0.3f), "player1attackedUR" );
}

void AnimationManager::init_player2Attacked()
{
    AnimationCache::getInstance()->addAnimation(createAnimation("player2D.png"  ,"player2attackedD.png" , 0.3f), "player2attackedD"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player2DL.png" ,"player2attackedDL.png", 0.3f), "player2attackedDL" );
    AnimationCache::getInstance()->addAnimation(createAnimation("player2DR.png" ,"player2attackedDR.png", 0.3f), "player2attackedDR" );
    AnimationCache::getInstance()->addAnimation(createAnimation("player2L.png"  ,"player2attackedL.png" , 0.3f), "player2attackedL"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player2R.png"  ,"player2attackedR.png" , 0.3f), "player2attackedR"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player2U.png"  ,"player2attackedU.png" , 0.3f), "player2attackedU"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player2UL.png" ,"player2attackedUL.png", 0.3f), "player2attackedUL" );
    AnimationCache::getInstance()->addAnimation(createAnimation("player2UR.png" ,"player2attackedUR.png", 0.3f), "player2attackedUR" );
}

void AnimationManager::init_player3Attacked()
{
    AnimationCache::getInstance()->addAnimation(createAnimation("player3D.png"  ,"player3attackedD.png" , 0.3f), "player3attackedD"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player3DL.png" ,"player3attackedDL.png", 0.3f), "player3attackedDL" );
    AnimationCache::getInstance()->addAnimation(createAnimation("player3DR.png" ,"player3attackedDR.png", 0.3f), "player3attackedDR" );
    AnimationCache::getInstance()->addAnimation(createAnimation("player3L.png"  ,"player3attackedL.png" , 0.3f), "player3attackedL"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player3R.png"  ,"player3attackedR.png" , 0.3f), "player3attackedR"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player3U.png"  ,"player3attackedU.png" , 0.3f), "player3attackedU"  );
    AnimationCache::getInstance()->addAnimation(createAnimation("player3UL.png" ,"player3attackedUL.png", 0.3f), "player3attackedUL" );
    AnimationCache::getInstance()->addAnimation(createAnimation("player3UR.png" ,"player3attackedUR.png", 0.3f), "player3attackedUR" );
}

void AnimationManager::init_boss_appear()
{
    AnimationCache::getInstance()->addAnimation(createAnimation("boss_appear%d.png" , 1, 10, 0.1f,0.1f), "bossappear" );
}


Animation* AnimationManager::createAnimation(const char* prefixName, int start,int end, float delay)
{
    Vector<SpriteFrame*> animFrames;
    //log("Animation");

    for (int i = start; i <= end; i++)
    {
        log("%s",prefixName);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(prefixName,i));
        if(frame!=nullptr)
        {
            animFrames.pushBack(frame);
        }
    }
    for (int i = end-1; i >=start; i--)
    {
        log("%s",prefixName);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(prefixName,i));
        if(frame!=nullptr)
        {
            animFrames.pushBack(frame);
        }
    }
    Animation* animation=Animation::createWithSpriteFrames(animFrames);
    animation->setLoops(-1);
    animation->setDelayPerUnit(delay);
    return animation;
}

Animation* AnimationManager::createAnimation(const char* prefixName, int start,int end, float delay, float flag)
{
    Vector<SpriteFrame*> animFrames;
    //log("Animation");
    
    for (int i = start; i <= end; i++)
    {
        log("%s",prefixName);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(prefixName,i));
        if(frame!=nullptr)
        {
            animFrames.pushBack(frame);
        }
    }
    for (int i = end-1; i >=start; i--)
    {
        log("%s",prefixName);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(prefixName,i));
        if(frame!=nullptr)
        {
            animFrames.pushBack(frame);
        }
    }
    Animation* animation=Animation::createWithSpriteFrames(animFrames);
    animation->setLoops(1);
    animation->setDelayPerUnit(delay);

    return animation;
}


Animation* AnimationManager::createAnimation(const char* prefixName1, const char* prefixName2, float delay)
{
    Vector<SpriteFrame*> animFrames;
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(prefixName2);
    if(frame!=nullptr) animFrames.pushBack(frame);
    frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(prefixName1);
    if(frame!=nullptr) animFrames.pushBack(frame);
    
    Animation* animation=Animation::createWithSpriteFrames(animFrames);
    animation->setLoops(1);
    animation->setDelayPerUnit(delay);
    return animation;
}
