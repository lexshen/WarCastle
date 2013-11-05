#include "HumanPlayer.h"

USING_NS_CC;

bool HumanPlayer::create(HelloWorld *layer)
{
	if(Player::create(CCString::create("castle1_def.png"),layer)){
		team =1 ;
	}
	return true;
}

void HumanPlayer::setAttacking(bool attacking)
{
    //[super setAttacking:attacking];
    if (attacking) {
        setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("castle1_atk.png"));
    } else {
        setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("castle1_def.png"));
    }
}
