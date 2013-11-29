#pragma once

#include "cocos2d.h"
#include "Monster.h"
NS_CC_BEGIN
class HelloWorldLayer;
class QuirkMonster:public Monster
{
public:
	static QuirkMonster* create(int team);
	bool init(int team);

};

NS_CC_END