#include"Sprite/Slider.h"
#include"Data/GameManager.h"

Slider* Slider::createSlider()
{
	auto slider = new Slider;

	if (slider && slider->init())
	{
		slider->autorelease();
		return slider;
	}
	CC_SAFE_DELETE(slider);
	return NULL;
}

bool Slider::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto bloodBg = Sprite::create("Resources/bloodbg.png");
	addChild(bloodBg);
	
	blood = ProgressTimer::create(Sprite::create("Resources/blood.png"));
	blood->setPosition(bloodBg->getPosition().x+2, bloodBg->getPosition().y - 1); //
	blood->setType(ProgressTimer::Type::BAR);
	blood->setPercentage(100.0f);//initiate
	blood->setBarChangeRate(Vec2(1, 0));
	blood->setMidpoint(Vec2(0, 1));
	addChild(blood);
	
	this->schedule(schedule_selector(Slider::bloodCallBack),0.1f);
	return true;
}

void Slider::bloodCallBack(float dt)
{
	IncreaseBlood();
	MonsterZeroDamage();
	MonsterOneDamage();
	MonsterTwoDamage();
}

void Slider::IncreaseBlood()
{
	if (0 < GameManager::getInstance()->PlayerIncreaseBlood)
	{
		GameManager::getInstance()->currentPlayerState_life += 10 * GameManager::getInstance()->PlayerIncreaseBlood;
		if (GameManager::getInstance()->currentPlayerState_life >= GameManager::getInstance()->Player_life[GameManager::getInstance()->currentPlayerState_type])
	    {
			blood->setPercentage(100);
	    }
		else
		{
			blood->setPercentage(GameManager::getInstance()->currentPlayerState_life/ GameManager::getInstance()->Player_life[GameManager::getInstance()->currentPlayerState_type]);

		}
		GameManager::getInstance()->PlayerIncreaseBlood = 0;
	}
}

void Slider::MonsterZeroDamage()
{
	if (0 < GameManager::getInstance()->PlayerReduceBlood[0])
	{
		GameManager::getInstance()->currentPlayerState_life -= GameManager::getInstance()->Monster_damage[0] * GameManager::getInstance()->PlayerReduceBlood[0];
		if (GameManager::getInstance()->currentPlayerState_life >= 0)
		{
			blood->setPercentage(GameManager::getInstance()->currentPlayerState_life/ GameManager::getInstance()->Player_life[GameManager::getInstance()->currentPlayerState_type]);
		}
		else
		{
			blood->setPercentage(0);
		}
		GameManager::getInstance()->PlayerReduceBlood[0] = 0;
	}
}

void Slider::MonsterOneDamage()
{
	if (0 < GameManager::getInstance()->PlayerReduceBlood[1])
	{
		GameManager::getInstance()->currentPlayerState_life -= GameManager::getInstance()->Monster_damage[1] * GameManager::getInstance()->PlayerReduceBlood[1];
		if (GameManager::getInstance()->currentPlayerState_life >= 0)
		{
			blood->setPercentage(GameManager::getInstance()->currentPlayerState_life / GameManager::getInstance()->Player_life[GameManager::getInstance()->currentPlayerState_type]);
		}
		else
		{
			blood->setPercentage(0);
		}
		GameManager::getInstance()->PlayerReduceBlood[1] = 0;
	}
}

void Slider::MonsterTwoDamage()
{
	if (0 < GameManager::getInstance()->PlayerReduceBlood[2])
	{
		GameManager::getInstance()->currentPlayerState_life -= GameManager::getInstance()->Monster_damage[2] * GameManager::getInstance()->PlayerReduceBlood[2];
		if (GameManager::getInstance()->currentPlayerState_life >= 0)
		{
			blood->setPercentage(GameManager::getInstance()->currentPlayerState_life / GameManager::getInstance()->Player_life[GameManager::getInstance()->currentPlayerState_type]);
		}
		else
		{
			blood->setPercentage(0);
		}
		GameManager::getInstance()->PlayerReduceBlood[2] = 0;
	}
}