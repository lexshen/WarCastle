#pragma once
#include "cocos2d.h"
#include "Player.h"

NS_CC_BEGIN

class HelloWorld;

class AIPlayer:public Player
{
public:

bool create(HelloWorld *layer);
void setAttacking(bool attacking);
};

NS_CC_END