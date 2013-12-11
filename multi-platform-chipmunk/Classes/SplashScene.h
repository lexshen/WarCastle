#ifndef __Splash_H__
#define __Splash_H__

#include "cocos2d.h"
#include "Scenes.h"
#include "CCControlSlider.h"
NS_CC_BEGIN


class Splash :	public CCLayer
{
private:
	//CCArray *_monsters;
	//CCArray *_projectiles;
	//int _monstersDestroyed;
	//static Splash* splash;
	//cocos2d::CCSprite *_player;
	//cocos2d::CCSprite *_nextProjectile;
	CCSpriteBatchNode* _batchNodes;
	//CCArray* planes;
	CCMenu* menu;
	//CCMenu* menu_sel;
	int level;
public:
	static Splash* sharedSplash(); 
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int level);  
   // implement the "static node()" method manually
    //CREATE_FUNC(Splash);
	static Splash* create(int level);
	void basicSetup();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene(int level);
   
	void levelButtonTapped(CCObject *object);
	void startButtonTapped(CCObject *object);
   // void gameLogic(float dt);

    void registerWithTouchDispatcher();

    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
/*
	inline void monsterMoveEnded(CCNode *node){
		_monsters->removeObject(node);
		node->removeFromParentAndCleanup(true);
		//CCScene *gameover = GameOverLayer::scene();
		//CCDirector::sharedDirector()->replaceScene(gameover);
	}
    inline void MoveEnded(CCNode *node){
		_projectiles->removeObject(node);
		node->removeFromParentAndCleanup(true);
		
	}

 	inline void playerMoveEnded(CCNode *node){
		this->addChild(_nextProjectile);
		_projectiles->addObject(_nextProjectile);
		_nextProjectile->release();
		_nextProjectile = NULL;
		
	}
	*/
	void update(float dt);

    //void addMonster();

 };
NS_CC_END
#endif

