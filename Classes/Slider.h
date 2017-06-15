#include "cocos2d.h"

using namespace cocos2d;
USING_NS_CC;

class Slider : public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(Slider);
private:
	ProgressTimer* blood = NULL;

	void bloodCallBack(float dt);//���ܸ��˲����Ժ����bug
	void IncreaseBlood();
	void MonsterZeroDamage();
	void MonsterOneDamage();
	void MonsterTwoDamage();

};