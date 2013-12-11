#include "Constant.h"
#include "QuirkMonster.h"
#include "ZapMonster.h"
#include "MunchMonster.h"
#include "DragonMonster.h"
#include "PhoenixMonster.h"
#include "CCLayerParent.h"

USING_NS_CC;

const char* slideratlas[] = {"slide_sel.png","slide_sel_darkred.png","slide_sel_lightblue.png","slide_sel_green.png",
							"slide_sel_orange.png","slide_sel_purple.png","slide_sel_pink.png"};
const char* sliderintro[] = {"HitPoint","maxVelocity","maxAcceleration","Damage","FireRate","Price","FoodCap"};
const char* atlas[] = {"quirk1.png","zap1.png","munch1.png","dragon1.png","phoenix1.png"};
const char* atlas_sel[] = {"quirk_sel.png","zap_sel.png","munch_sel.png","dragon_sel.png","phoenix_sel.png"};
bool selection[] = {false,false,false,false,false};
//CCMenuItemSprite* buttons[5];
Deck decks[5] = {
	{
		"quirk1.png",
		"quirk_sel.png",
		false,
		"quirk",
		"smallHit.wav",
		5,
		NULL,
		menu_selector(CCLayerParent::quirkButtonTapped),
		{
			5,
			100,
			100,
			1.25f,
			0.5f,
			true,
			false,
			false,
			2
		}
	},
	{
		"zap1.png",
		"zap_sel.png",
		false,
		"zap",
		"pew.wav",
			10,
		NULL,
		menu_selector(CCLayerParent::zapButtonTapped),
		{
			10,
			50,
			50,
			5.0f,
			1.5f,
			true,
			false,
			false,
			2
		}
	},
	{
		"munch1.png",
		"munch_sel.png",
		false,
		"munch",
		"bigHit.wav",
			15,
		NULL,
		menu_selector(CCLayerParent::munchButtonTapped),
		{
			50,
			25,
			25,
			10.0f,
			2.0f,
			true,
			false,
			true,
			4
		}
	},
	{
		"dragon1.png",
		"dragon_sel.png",
		false,
		"dragon",
		"bigHit.wav",
			15,
		NULL,
		menu_selector(CCLayerParent::dragonButtonTapped),
		{
			50,
			60,
			30,
			10.0f,
			2.0f,
			true,
			false,
			false,
			4
		}
	},
	{
		"phoenix1.png",
		"phoenix_sel.png",
		false,
		"phoenix",
		"bigHit.wav",
			15,
		NULL,
		menu_selector(CCLayerParent::phoenixButtonTapped),
		{
			50,
			70,
			30,
			10.0f,
			2.0f,
			true,
			false,
			false,
			4
		}
	}
};


