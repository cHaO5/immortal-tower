#include "cocos2d.h"

using namespace cocos2d;
USING_NS_CC;

extern int m_num;//�����õ���Ҫextern�����ı�Ѫ����
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