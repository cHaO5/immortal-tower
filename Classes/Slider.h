#include "cocos2d.h"

using namespace cocos2d;
USING_NS_CC;

extern int m_num;//凡是用到都要extern用来改变血量条
extern int _numCollected;
extern bool reduceblood;

class Slider : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(Slider);

private:
	int m_curNum;
	ProgressTimer* blood;
	void bloodCallBack(Ref* pSender);
	void ReduceBlood(float dt);
	void schedleUpdate(float dt);
	Slider() :m_curNum(100), blood(NULL) {};
};