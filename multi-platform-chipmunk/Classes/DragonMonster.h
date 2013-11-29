#pragma once

#include "cocos2d.h"
#include "Monster.h"
NS_CC_BEGIN
class HelloWorldLayer;
class DragonMonster:public Monster
{
public:
	static DragonMonster* create(int team);
	bool init(int team);

};

NS_CC_END