#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Constant.h"
NS_CC_BEGIN

class HelloWorldLayer;

class Monster:public GameObject
{
public:
	Deck* deck;
	Monster();
	Monster(Deck* deck);
  CCPoint velocity;
  CCPoint acceleration;
  float maxVelocity;
  float maxAcceleration;

  bool isRanged;
  float rangedRange;
  float rangedDamage;
  float rangedDamageRate;
  float rangedLastDamageTime;
  CCString* rangedSound;

  bool isMelee;
  float meleeDamage;
  bool meleeDestroySelf;
  float meleeDamageRate;
  float meleeLastDamageTime;
  bool meleeAoe;
  CCString* meleeSound;



};

NS_CC_END