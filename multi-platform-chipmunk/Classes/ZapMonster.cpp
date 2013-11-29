#include "ZapMonster.h"

USING_NS_CC;

bool ZapMonster::init(int team)
{

	CCString* spriteFrameName = CCString::createWithFormat("zap%d.png", team);
     if (GameObject::init(spriteFrameName)) {
         curHp = 10;
         maxHp = 10;
         team = team;
         maxVelocity = 50;
         maxAcceleration = 50;
         isRanged = true;
         rangedRange = 100;
         rangedDamageRate = 1.5;
         rangedDamage = 5;
         rangedSound = CCString::create("pew.wav");

		this->coins = 20;
		this->people = 3;
    }
	 return true;
}


ZapMonster* ZapMonster::create(int team)
{
	ZapMonster *pRet = new ZapMonster(); \
	if (pRet&& pRet->init(team) ) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
}