#pragma once

#include "cocos2d.h"
#include "Monster.h"
NS_CC_BEGIN
class HelloWorldLayer;
class PhoenixMonster:public Monster
{
public:
	static PhoenixMonster* create(int team);
	bool init(int team);

};

NS_CC_END