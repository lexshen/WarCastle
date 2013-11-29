#include "MunchMonster.h"

USING_NS_CC;


bool MunchMonster::init(int team)
{
  CCString * spriteFrameName = CCString::createWithFormat("munch%d.png", team);
     if (GameObject::init(spriteFrameName)) {
    	this->curHp = 50;
        this->maxHp = 50;
        this->team = team;
        this->maxVelocity = 25;
        this->maxAcceleration = 25;
        this->isMelee = true;
        this->meleeDamage = 10.0;
        this->meleeDestroySelf = false;
        this->meleeDamageRate = 2.0;
        this->meleeAoe = true;
        this->meleeSound = CCString::create("bigHit.wav");
		
		this->coins = 15;
		this->people = 4;
     	}
	 return true;
	
}


MunchMonster* MunchMonster::create(int team)
{
	MunchMonster *pRet = new MunchMonster(); \
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