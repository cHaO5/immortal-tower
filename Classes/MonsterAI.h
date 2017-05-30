#ifndef _MONSTERAI_H_
#define _MONSTERAI_H_
#include"cocos2d.h"
#include"Monster.h"

using namespace cocos2d;

USING_NS_CC;

typedef enum
{
	Monster_down,
	Monster_right,
	Monster_up,
	Monster_left,
}MDirection;

class MonsterAI : public Node
{
public:
	void FollowRun(float dt);
	void goon(Node * pSender);
	void JudegeAttack(float dt);
	void StartListen();
	void BoundDetect(float dt);
	void DelayUnschedule(Node *pSender);
	void IfActionRemove(Node *pSender);

	Player* _player;//��ǰӢ��
	TMXTiledMap *_tileMap;//��ǰ��ͼ
	TMXLayer *_meta;
	TMXLayer *_fruit;
	Sprite* proj;

	int monsterDirection;
	float   dis;//��ǰ�����Ӣ�۵ľ���
};

#endif

