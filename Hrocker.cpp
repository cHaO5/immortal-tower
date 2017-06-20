#include "Hrocker.hpp"
#include "GameScene.h"
#include "GameManager.h"
const double PI=3.1415;
HRocker::HRocker(void)
{
    rocketRun=false;
}
HRocker::~HRocker(void)
{
}
//创建摇杆(摇杆的操作题图片资源名，摇杆背景图片资源名，起始坐标)
HRocker* HRocker::createHRocker(const char *rockerImageName,const char *rockerBGImageName,Point position)
{
    HRocker *layer = HRocker::create();
    if (layer)
    {
        layer->rockerInit(rockerImageName,rockerBGImageName,position);
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}
//自定义初始化函数
void HRocker::rockerInit(const char* rockerImageName,const char* rockerBGImageName,Point position)
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    Sprite *spRockerBG = Sprite::create(rockerBGImageName);
    spRockerBG->setPosition(position);
    spRockerBG->setVisible(false);
    addChild(spRockerBG,0,tag_rockerBG);
    Sprite *spRocker = Sprite::create(rockerImageName);
    spRocker->setPosition(position);
    spRocker->setVisible(false);
    addChild(spRocker,1,tag_rocker);
    rockerBGPosition = position;
    rockerBGR = spRockerBG->getContentSize().width*0.5;//
    rocketDirection=-1;//表示摇杆方向不变
}
//启动摇杆(显示摇杆、监听摇杆触屏事件)
void HRocker::startRocker(bool _isStopOther)
{
    Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
    log("Hrockerbegin");
    rocker->setVisible(true);
    Sprite *rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
    rockerBG->setVisible(true);
    
}
//停止摇杆(隐藏摇杆，取消摇杆的触屏监听)
void HRocker::stopRocker()
{
    Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
    rocker->setVisible(false);
    Sprite * rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
    rockerBG->setVisible(false);
}
//获取当前摇杆与用户触屏点的角度
float HRocker::getRad(Point pos1,Point pos2)
{
    float px1 = pos1.x;
    float py1 = pos1.y;
    float px2 = pos2.x;
    float py2 = pos2.y;
    //得到两点x的距离
    float x = px2 - px1;
    //得到两点y的距离
    float y = py1 - py2;
    //算出斜边长度
    float xie = sqrt(pow(x,2) + pow(y,2));
    //得到这个角度的余弦值(通过三角函数中的店里：角度余弦值=斜边/斜边)
    float cosAngle = x / xie;
    //通过反余弦定理获取到期角度的弧度
    float rad = acos(cosAngle);
    //注意：当触屏的位置Y坐标<摇杆的Y坐标，我们要去反值-0~-180
    if (py2 < py1)
    {
        rad = -rad;
    }
    return rad;
}
Point getAngelePosition(float r,float angle){
    return Vec2(r*cos(angle),r*sin(angle));
}
//抬起事件
bool HRocker::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    Point point = pTouch->getLocation();
    Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
    if (rocker->boundingBox().containsPoint(point))
        isCanMove = true;
    rocketRun=true;
    return true;
}

void HRocker::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    if (!isCanMove)
    {
        return;
    }
    auto player=GameManager::getInstance()->currentPlayer;
    Point point = pTouch->getLocation();
    Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
    //得到摇杆与触屏点所形成的角度
    float angle = getRad(rockerBGPosition,point);
    //判断两个圆的圆心距是否大于摇杆背景的半径
    if (sqrt(pow((rockerBGPosition.x - point.x),2) + pow((rockerBGPosition.y - point.y),2)) >= rockerBGR)
    {
        //保证内部小圆运动的长度限制
        rocker->setPosition(ccpAdd(getAngelePosition(rockerBGR,angle),Vec2(rockerBGPosition.x,rockerBGPosition.y)));
    }
    else
        rocker->setPosition(point);
    //判断方向
    auto offsetX=0,offsetY=0;
    auto playerPos=player->getPosition();
    bool setPlayerPosition(Point position);
    rocketRun=true;
    log("%f\n", angle);
    if (rocketRun==true){
    if(angle>=-PI/4&&angle<PI/4)//right
    {
        offsetX = GameManager::getInstance()->Player_speed[GameManager::getInstance()->currentPlayerState_type];
        playerPos.x += (GameManager::getInstance()->TileSizewidth / 2) - 2;
        playerPos.x += offsetX;
        rocketRun=false;
    }
    else if(angle>=PI/4&&angle<3*PI/4)//up
    {
        offsetY = GameManager::getInstance()->Player_speed[GameManager::getInstance()->currentPlayerState_type];
        playerPos.y += (GameManager::getInstance()->TileSizeheight / 2) - 2;
        playerPos.y += offsetY;
        rocketRun=false;
    }
    else if((angle>=3*PI/4&&angle<=PI)||(angle>=-PI&&angle<-3*PI/4))//left
    {
        offsetX = -GameManager::getInstance()->Player_speed[GameManager::getInstance()->currentPlayerState_type];
        playerPos.x -= (GameManager::getInstance()->TileSizewidth/ 2) - 2;//也可以改为getcontentwith边界点判断
        playerPos.x += offsetX;
        rocketRun=false;
    }
    else if(angle>=-3*PI/4&&angle<-PI/4)//down
    {
        offsetY = -GameManager::getInstance()->Player_speed[GameManager::getInstance()->currentPlayerState_type];
        playerPos.y -= (GameManager::getInstance()->TileSizeheight / 2) - 2;
        playerPos.y += offsetY;
        rocketRun=false;
    }
        int x = static_cast<int>(playerPos.x / GameManager::getInstance()->TileSizewidth);
        int y = static_cast<int>((GameManager::getInstance()->MapSizeheight *  GameManager::getInstance()->TileSizeheight - playerPos.y) / GameManager::getInstance()->TileSizeheight);
        int* logicmap;
        switch (GameManager::getInstance()->CurrentLevel)
        {
            case(0):logicmap = GameManager::getInstance()->Level0LogicMap[0];
                break;
            case(1):logicmap =GameManager::getInstance()->Level1LogicMap[0];
                break;
            case(2):logicmap =GameManager::getInstance()->Level2LogicMap[0];
                break;
            default:
                break;
        }
        auto value = *((logicmap + GameManager::getInstance()->MapSizewidth*y) + x);

        if (value==1)
        {
            offsetY = offsetX = 0;
        }
        
    if (offsetX>0)player->setTexture(GameManager::getInstance()->Player_texture[GameManager::getInstance()->currentPlayerState_type][3]);//R
    if (offsetX<0)player->setTexture(GameManager::getInstance()->Player_texture[GameManager::getInstance()->currentPlayerState_type][1]);//L
    if (offsetY>0)player->setTexture(GameManager::getInstance()->Player_texture[GameManager::getInstance()->currentPlayerState_type][2]);//D
    if (offsetY<0)player->setTexture(GameManager::getInstance()->Player_texture[GameManager::getInstance()->currentPlayerState_type][0]);//U
    
        
    auto moveTo = MoveTo::create(10.0, Vec2(player->getPositionX() + offsetX,player->getPositionY() + offsetY));
    player->runAction(moveTo);
    rocketangle=angle;
    }
}

//离开事件
void HRocker::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (!isCanMove)
    {
        return;
    }
    Sprite *rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
    Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
    rocker->stopAllActions();
    rocker->runAction(MoveTo::create(0.08f,rockerBG->getPosition()));
    isCanMove = false;
    rocketDirection=rocker_stay;
}
