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

void GameOverLayer::GameFinished()
{
    CCDirector::sharedDirector()->replaceScene(ArmorHome::scene());
}

void GameOverLayer::basicSetup()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	//nodes
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");
	//_batchNodes = CCSpriteBatchNode::create("Sprites.pvr.ccz");
	//this->addChild(_batchNodes);
	//_particleNodes = CCDictionary::create();
	//_particleNodes->setObject(CCParticleBatchNode::create("bullet.png"),"bullet");
	//_particleNodes->setObject(CCParticleBatchNode::create("explosion1.png"),"explosion1");
	//_particleNodes->setObject(CCParticleBatchNode::create("explosion2.png"),"explosion2");
	//_particleNodes->setObject(CCParticleBatchNode::create("aoe1.png"),"aoe1");
	//_particleNodes->setObject(CCParticleBatchNode::create("aoe2.png"),"aoe2");
	//_particleNodes->setObject(CCParticleBatchNode::create("coldline1.png"),"coldline1");
	//_particleNodes->setObject(CCParticleBatchNode::create("coldline2.png"),"coldline2");
	//CCDictElement* object = NULL;
	//CCDICT_FOREACH(_particleNodes,object)
	//{
	//	this->addChild((CCParticleBatchNode*)object->getObject());
	//}


   //// Sounds
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Latin_Industries.mp3");
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("bigHit.wav");
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("boom.wav");
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew.wav");
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew2.wav");
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("smallHit.wav");
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("attack.wav");
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("defend.wav");
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("spawn.wav");

	//other UI
	CCSprite *background = CCSprite::create("background.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background,-1);

}