
#include "SplashScene.h"
//#include "SimpleAudioEngine.h"
//#include "GameOverScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

//const char* atlas_sel[] = {"quirk_sel.png","zap_sel.png","munch_sel.png","dragon_sel.png","phoenix_sel.png"};
// there's no 'id' in cpp, so we recommend returning the class instance pointer
CCScene* Splash::scene(int level)
{
	CCScene *scene = CCScene::create();

	Splash *splash = Splash::create(level);

	scene->addChild(splash);

	return scene;

}
Splash* Splash::create(int level)
{
	// 'layer' is an autorelease object  
	Splash *layer =new Splash();
	if(layer && layer->init(level))
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
/*
void Splash::gameLogic(float dt)
{
	this->addMonster();
}
*/
// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool Splash::init(int level)
{
	if(! CCLayer::init())
	{
		return false;
	}
	this->level = level;
	basicSetup();
	this->setTouchEnabled(true);

	//_monstersDestroyed = 0;
	return true;
}


void Splash::basicSetup()
{
	//planes = CCArray::create();
	//planes->retain();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
     
	//nodes
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");
	_batchNodes = CCSpriteBatchNode::create("Sprites.pvr.ccz");
	this->addChild(_batchNodes);
	
	CCSprite *background = CCSprite::create("background.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background,-1);

    //int columns = 3;
    //int spaceBetween = columns +1;
    //int rows = 3;
    //int spaceBetweenRows = rows +1;
    //int spacing = winSize.width/spaceBetween;
    //int rowSpacing = winSize.height/spaceBetweenRows;


    //CCPoint point = ccp(0,winSize.height-rowSpacing);
    
    CCArray* items = CCArray::create();
    for(int i=0;i<SPRITE_NUM;i++)
    {
		CCMenuItemSprite* startButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(atlas[i]),CCSprite::createWithSpriteFrameName(atlas_sel[i]),this,menu_selector(Splash::levelButtonTapped));
		startButton->retain();
		startButton->setTag(i);
		 //      point.x = point.x + spacing;
  //      if(point.x> spacing*columns) {
  //          point.x = spacing;
  //          point.y = point.y - rowSpacing;
  //       }
  //      CCMenuItemSprite* startButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName(atlas[i]),CCSprite::createWithSpriteFrameName(atlas[i]),this,menu_selector(ArmorHome::levelButtonTapped));
  //      startButton->setPosition(point);
  //      char temp[64];
  //      sprintf(temp, "%d", i);
  //      CCSize contentSize =  startButton->getContentSize();
  //      spacing = contentSize.width;
		//rowSpacing = contentSize.height;
  //      CCLabelBMFont* quirkLabel = CCLabelBMFont::create(temp,"Courier.fnt");
  //      CCLog("label string %s",quirkLabel->getString());
  //      quirkLabel->retain();
  //      //quirkLabel->setPosition(CCPointZero);
  //      //quirkLabel->setAnchorPoint(ccp(0.5f,0.5f));
  //      quirkLabel->setPosition(ccp(contentSize.width * 0.75,contentSize.height * 0.6));
  //      startButton->addChild(quirkLabel);
  //      startButton->setTag(i);
        items->addObject(startButton);
		decks[i].selection = false;
    }
    menu = CCMenu::createWithArray(items);
	menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(ccp(MARGIN,winSize.height/2));
    this->addChild(menu);
	int yoffset = winSize.height/2 - MARGIN * (SLIDENUM/2);
	for(int i =0; i< SLIDENUM; i++)
	{
		CCLabelTTF* ttf1 = CCLabelTTF::create(sliderintro[i], "Helvetica", 12, ccp(MARGIN*2,MARGIN), kCCTextAlignmentRight );
		ttf1->setPosition(ccp(winSize.width/2 -80 - MARGIN,yoffset));
		this->addChild(ttf1);
		CCControlSlider* slider = CCControlSlider::create(CCSprite::createWithSpriteFrameName("slide.png"),CCSprite::createWithSpriteFrameName(slideratlas[i]),CCSprite::createWithSpriteFrameName("slide_center.png"));
		slider->setPosition(ccp(winSize.width/2,yoffset));
		yoffset += MARGIN;
		slider->setValue(0.9f);
	    this->addChild(slider);
	}

	//slider->setEnabled(true);
	//slider->setMaximumValue(150);

   CCMenuItemSprite *startButton =  CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(Splash::startButtonTapped));
   CCSize contentSize =  startButton->getContentSize();
   startButton->setPosition (ccp(winSize.width/2, -5*MARGIN));
 //   CCSprite* quirk = CCSprite::createWithSpriteFrameName(frameName);
	//quirk->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
 //   startButton->addChild(quirk);

    CCLabelBMFont* quirkLabel = CCLabelBMFont::create("Start","Courier.fnt");
    quirkLabel->setPosition(ccp(contentSize.width * 0.5, MARGIN*0.9));
    startButton->addChild(quirkLabel);
	menu->addChild(startButton);
	//menu_sel->setPosition(ccp(winSize.width/2,MARGIN));
	//this->addChild(menu_sel);
}

void Splash::levelButtonTapped(CCObject *object)
{
	//menu_sel->removeChild((CCMenuItemSprite*)object,true);
	CCMenuItemSprite* item = (CCMenuItemSprite*)object;
	int tag = item->getTag();
	item->setNormalImage(CCSprite::createWithSpriteFrameName(atlas_sel[tag]));
	item->setSelectedImage(CCSprite::createWithSpriteFrameName(atlas[tag]));
	decks[tag].selection = true;
	//planes->addObject(CCInteger::create(tag));
}

void Splash::startButtonTapped(CCObject *object)
{
	 switch(level){
            
        case 1:
            CCDirector::sharedDirector()->replaceScene(TutorialQuirk::scene());break;
        case 2:
            CCDirector::sharedDirector()->replaceScene(TutorialZap::scene());break;
        case 3:
            CCDirector::sharedDirector()->replaceScene(TutorialMunch::scene());break;
        case 4:
            CCDirector::sharedDirector()->replaceScene(TutorialQuirkZap::scene());break;
        case 5:
            CCDirector::sharedDirector()->replaceScene(TutorialZapMunch::scene());break;
        case 6:
            CCDirector::sharedDirector()->replaceScene(TutorialMunchQuirk::scene());break;
        default:
            CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());break;

    }
}


//static Splash* Splash::sharedSplash()
//{
//	//splash = Splash::s
//
//}
/*
void Splash::addMonster()
{
	CCSprite *monster = CCSprite::create("monster.png");
	monster->setTag(1);
	_monsters->addObject(monster);
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = monster->getTextureRect().size.height;
	int maxY = winSize.height- minY;
	int range = maxY-minY;
	int acturalY = minY+ (rand()%maxY);
	monster->setPosition(ccp(winSize.width+monster->getContentSize().width,acturalY));
	this->addChild(monster);

	int minDuration = 2.0f;
	int maxDuration = 4.0f;
	int rangeDuration = maxDuration- minDuration;
	int acturalDuration = minDuration + (rand() % maxDuration);

	CCMoveTo *actionMove = CCMoveTo::create(acturalDuration,ccp(-monster->getContentSize().width,acturalY));
	CCCallFuncN *actionMoveDone = CCCallFuncN::create(this,callfuncN_selector(Splash::monsterMoveEnded));
	monster->runAction(CCSequence::create(actionMove,actionMoveDone,NULL));
	
 }
 */


void Splash::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool Splash::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void Splash::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	/*
	//if(_nextProjectile!=NULL) return;
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("pew-pew-lei.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(fullPath.c_str());

	CCPoint position = this->convertTouchToNodeSpace(pTouch);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	_nextProjectile = CCSprite::create("projectile2.png");
	_nextProjectile->retain();
	_nextProjectile ->setTag(2);
	//_projectiles->addObject(_nextProjectile );
	
	_nextProjectile ->setPosition(ccp(20,winSize.height/2));
	
	float bearVelocity = winSize.width / 1.0;
	CCPoint moveDifference = ccpSub(position,_nextProjectile->getPosition());
	if(moveDifference.x<0) return;
	//this->addChild(_nextProjectile);
	
	int realX = winSize.width + _nextProjectile ->getContentSize().width/2;
	float ratio = (float)moveDifference.y/moveDifference.x;
	int realY = (realX * ratio) + _nextProjectile ->getPosition().y;

	CCPoint realDest = ccp(realX,realY);
	CCPoint realDistance = ccpSub(realDest,_nextProjectile ->getPosition());
	
	float distanceToMove = ccpLength(realDistance);
	float moveDuration = distanceToMove / bearVelocity;

	float angleRadius = atanf(realDistance.y/realDistance.x);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadius);
	float cocosDegrees = - angleDegrees;
	float rotateDegreesPerSecond = 180 / 0.5f;
	float degreesDiff = _player->getRotation() - cocosDegrees;
	float rotateDuration = fabs(degreesDiff / rotateDegreesPerSecond);

	_player->runAction(CCSequence::create(CCRotateTo::create(rotateDuration,cocosDegrees),
		CCCallFuncN::create(this,callfuncN_selector(Splash::playerMoveEnded)),
		NULL));
	_player->setRotation(cocosDegrees);
	_nextProjectile ->runAction(CCSequence::create(CCMoveTo::create(moveDuration,realDest),
		CCCallFuncN::create(this,callfuncN_selector(Splash::MoveEnded)),
		NULL));
		*/
}

void Splash::update(float dt)
{
	/*
	CCArray *projectileToDelete = CCArray::create();
	CCObject *pit=NULL;
	CCARRAY_FOREACH(_projectiles,pit)
	{
		CCArray *monstersToDelete = CCArray::create();
		CCObject* mit = NULL;
		CCARRAY_FOREACH(_monsters,mit)
		{
			if(dynamic_cast<CCSprite*>(pit)->boundingBox().intersectsRect(dynamic_cast<CCSprite*>(mit)->boundingBox()))
			{
				monstersToDelete ->addObject(mit);
			}
		}

		CCARRAY_FOREACH(monstersToDelete, mit)
		{
			_monsters->removeObject(mit);
			this->removeChild(dynamic_cast<CCSprite*>(mit),true);
			_monstersDestroyed++;
			if(_monstersDestroyed>30)
			{
				CCScene *gameover = GameOverLayer::scene();
				CCDirector::sharedDirector()->replaceScene(gameover);
			}
		}

		if(monstersToDelete->count())
			projectileToDelete->addObject(dynamic_cast<CCSprite*>(pit));

		monstersToDelete->release();
		
		CCARRAY_FOREACH(projectileToDelete,pit)
		{
			_projectiles->removeObject(pit);
			this->removeChild(dynamic_cast<CCSprite*>(pit),true);

		}
	}
	projectileToDelete->release();
	*/
}
