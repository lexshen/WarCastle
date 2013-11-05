#ifndef __GAMEOVERSCENE_H__
#define __GAMEOVERSCENE_H__
#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayerColor
{
public:
	    // there's no 'id' in cpp, so we recommend returning the class instance pointer 
	static cocos2d::CCScene* scene(BOOL won);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone    
    //  virtual bool init();
	static GameOverLayer* create(BOOL won);
	
	bool initWithWon(BOOL won);  
    
	//CREATE_FUNC(GameOverLayer);

	void GameFinished();
};

#endif