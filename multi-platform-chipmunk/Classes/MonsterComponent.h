#pragma once
#include "cocos2d.h"
#include "Component.h"
#include "Monster.h"
#include "QuirkMonster.h"
#include "ZapMonster.h"
#include "MunchMonster.h"
#include "DragonMonster.h"
#include "PhoenixMonster.h"
NS_CC_BEGIN

typedef enum {
    MonsterTypeQuirk,
    MonsterTypeZap,
    MonsterTypeMunch,
    MonsterTypeDragon,
    MonsterTypePhoenix,
} MonsterType;

class MonsterComponent: public Component
{
public:
	MonsterType monsterType;
	Monster* monster;
	MonsterComponent(MonsterType monsterType,int team);
	~MonsterComponent();
	CCString* ClassName();
	static MonsterComponent* create(MonsterType monsterType,int team);
};
NS_CC_END
