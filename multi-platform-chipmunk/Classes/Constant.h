//
//  Created by Ray Wenderlich on 10/24/12.
//  Copyright (c) 2012 Razeware LLC. All rights reserved.
//
#pragma once
#include <stdlib.h>
#include "cocos2d.h"
//#import <QuartzCore/CABase.h>
NS_CC_BEGIN
#define CCRANDOM_X_Y(__X__, __Y__) (((__Y__) - (__X__)) * (rand() / (float)RAND_MAX) + (__X__))

#define OPPOSITE_TEAM(__TEAM__)  (__TEAM__==1?2:1   )
//#define SOUND
//typedef unsigned int UINT;
//typedef bool BOOL;
//#define GetTickCount() CACurrentMediaTime() * 1000
//extern CCMenuItemSprite* buttons[];

#define SLIDENUM 7
#define SPRITE_NUM 5
typedef struct FightProperty{
	float HitPoint;
	int maxVelocity;
	int maxAcceleration;
	float Damage;
	float FireRate;
	bool melee;
	bool range;
	bool aoe;
	int FoodCap;
} Fight;

typedef struct DamageProperty{
	bool destroySelf;
	float lastDamageTime;
	//bool notBullet;
} Damage;

typedef struct DeckProperty{
	const char* atlas;
	const char* atlas_sel;
	bool selection;
	const char* name;
	const char* sound;
	int price;
	cocos2d::CCMenuItemSprite* button;
	cocos2d::SEL_MenuHandler handler;
	Fight fight;
} Deck;


NS_CC_END

extern const char* slideratlas[];
extern const char* sliderintro[];
extern const char* atlas_sel[];
extern const char* atlas[];
extern bool selection[];
extern cocos2d::Deck decks[];
