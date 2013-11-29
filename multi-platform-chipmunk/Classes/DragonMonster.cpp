#include "DragonMonster.h"
USING_NS_CC;
bool DragonMonster::init(int team)
{
	CCString * spriteFrameName = CCString::createWithFormat("dragon%d.png", team);
    if (GameObject::init(spriteFrameName)) {
        this->curHp = 5;
        this->maxHp = 5;
        this->team = team;
        this->maxVelocity = 100;
        this->maxAcceleration = 100;
        this->isMelee = true;
        this->meleeDamage = 1.25;
        this->meleeDestroySelf = false;
        this->meleeDamageRate = 0.5;
        this->meleeAoe = false;
        this->meleeSound = CCString::create("smallHit.wav");

		this->coins = 10;
		this->people = 2;
    }
	return true;

}



DragonMonster* DragonMonster::create(int team)
{
	DragonMonster *pRet = new DragonMonster(); \
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