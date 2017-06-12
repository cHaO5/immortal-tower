#ifndef _LEVEL_2_H_
#define _LEVEL_2_H_

#include "BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level2 : public BaseMap
{
public:

	virtual bool init();
	CREATE_FUNC(Level2);
private:
	Sprite *floor;//’œ∞≠ŒÔ
	Sprite *wall;//’œ∞≠ŒÔ
	Sprite *barrier;//’œ∞≠ŒÔ
};

#endif
