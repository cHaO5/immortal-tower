#ifndef Hrocker_hpp
#define Hrocker_hpp

#include <stdio.h>
using namespace cocos2d;
//用于标识摇杆与摇杆的背景
typedef enum{
    tag_rocker,
    tag_rockerBG,
}tagForHRocker;
//用于标识摇杆方向
typedef enum{
    rocker_stay,
    rocker_right,
    rocker_up,
    rocker_left,
    rocker_down,
}tagDirecton;
class HRocker:public Layer
{
public:
    HRocker(void);
    ~HRocker(void);
    //创建摇杆
    static HRocker* createHRocker(const char *rockerImageName,const char *rockerBGImageName,Point position);
    //启动摇杆
    void startRocker(bool _isStopOther);
    //停止摇杆
    void stopRocker();
    //判断控制杆方向，用来判断精灵上、下、左、右运动
    int rocketDirection;
    bool rocketRun;
    float rocketangle;
    CREATE_FUNC(HRocker);
private:
    //自定义初始化函数
    void rockerInit(const char* rockerImageName,const char* rockerBGImageName,Point position);
    //是否可操作摇杆
    bool isCanMove;
    //获取当前摇杆与用户触屏点的角度
    float getRad(Point pos1,Point pos2);
    //摇杆背景的坐标
    Point rockerBGPosition;
    //摇杆背景的半径
    float rockerBGR;
    //触屏事件
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
};
#endif /* Hrocker_hpp */
