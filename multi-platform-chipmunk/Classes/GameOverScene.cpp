#include "GameOverScene.h"

USING_NS_CC;

CCScene* GameOverLayer::scene()
{
	// 'scene' is an autorelease object    
	CCScene *scene = CCScene::create();
	
	GameOverLayer* layer = GameOverLayer::create();	
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}
/*
GameOverLayer* GameOverLayer::create(BOOL won,int level)
{
	// 'layer' is an autorelease object  
	GameOverLayer *layer =new GameOverLayer();
	if(layer && layer->initWithWon(won, level))
	{
		layer->autorelease();
		return layer;
	}
	else
	{
		delete layer;
		layer = NULL;
		return NULL;
	}
}

// on "init" you need to initialize your instance
bool GameOverLayer::initWithWon(BOOL won,int level)
{
	//////////////////////////////   
	// 1. super init first    
	if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
	{
		return false;
	}
	CCString message;
	if(won)
		message="You WON!";
	else
		message="You LOSE :(";

    CCPoint winSize = CCDirector::sharedDirector()->getWinSize(); 
	CCLabelTTF *label = CCLabelTTF::create(message.getCString(),"Arial",32.0f);
	label->setColor(ccc3(0,0,0));
	label->setPosition(CCPointMake(winSize.x/2, winSize.y/2));
	this->addChild(label);

	this->runAction(CCSequence::create(
		CCDelayTime::create(3.0f),
		CCCallFunc::create(this,callfunc_selector(GameOverLayer::GameFinished)),
		NULL));
	_level = level;
	return true;
}
*/
void GameOverLayer::GameFinished()
{
    CCDirector::sharedDirector()->replaceScene(ArmorHome::scene());
}