#include "ArmorHomeScene.h"
#include "HelloWorldScene.h"
#include "Constant.h"
#include "SimpleAudioEngine.h"
#include "EntityManager.h"
#include "HealthSystem.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "GunComponent.h"
#include "EntityFactory.h"
#include "MoveSystem.h"
#include "PlayerSystem.h"
#include "MeleeSystem.h"
#include "GunSystem.h"
#include "AISystem.h"
#include "AIState.h"
#include "PhysicsSystem.h"
#include "GameOverScene.h"

USING_NS_CC;

CCScene* ArmorHome::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ArmorHome *layer = ArmorHome::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ArmorHome::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
	    return false;
    }
 	basicSetup();
	addPlayers();
    return true;
}

void ArmorHome::basicSetup()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float MARGIN = 26 / CC_CONTENT_SCALE_FACTOR();

	//nodes
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");
	_batchNodes = CCSpriteBatchNode::create("Sprites.pvr.ccz");
	this->addChild(_batchNodes);

   // Sounds
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Latin_Industries.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("bigHit.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("boom.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew2.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("smallHit.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("attack.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("defend.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("spawn.wav");

	//other UI
	CCSprite *background = CCSprite::create("helloworld.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background,-1);
    
    CCMenuItemSprite* quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(ArmorHome::quirkButtonTapped));
    CCMenuItemSprite* zapButton =  CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(ArmorHome::zapButtonTapped));
    CCMenuItemSprite* munchButton =  CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(ArmorHome::munchButtonTapped));

	CCSize contentSize =  zapButton->getContentSize();
    zapButton->setPosition (ccp(winSize.width/2, MARGIN + contentSize.height/2));
    quirkButton->setPosition (ccp(zapButton->getPosition().x - contentSize.width/2 - MARGIN - contentSize.width/2, MARGIN + contentSize.height/2));
    munchButton->setPosition ( ccp(zapButton->getPosition().x + contentSize.width/2 + MARGIN + contentSize.width/2, MARGIN + contentSize.height/2));
    
    CCSprite* quirk = CCSprite::createWithSpriteFrameName("quirk1.png");
    quirk->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
    quirkButton->addChild(quirk);
    
    CCSprite* zap = CCSprite::createWithSpriteFrameName("zap1.png");
    zap->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
    zapButton->addChild(zap);
    
    CCSprite* munch = CCSprite::createWithSpriteFrameName("munch1.png");
    munch->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
    munchButton->addChild(munch);
    
    CCLabelBMFont* quirkLabel = CCLabelBMFont::create("10","Courier.fnt");

    quirkLabel->setPosition(ccp(contentSize.width * 0.75, MARGIN*1.1));
    quirkButton->addChild(quirkLabel);
	
    CCLabelBMFont* zapLabel = CCLabelBMFont::create("25","Courier.fnt");
    zapLabel->setPosition(ccp(contentSize.width * 0.75, MARGIN*1.2));
    zapButton->addChild(zapLabel);

    CCLabelBMFont* munchLabel = CCLabelBMFont::create("50","Courier.fnt");
    munchLabel->setPosition(ccp(contentSize.width * 0.75, MARGIN*1.3));
    munchButton->addChild(munchLabel);


    _stateLabel = CCLabelBMFont::create("Idle","Courier.fnt");
    _stateLabel->setPosition ( ccp(winSize.width/2, winSize.height * 0.3));
    this->addChild(_stateLabel);
    
    CCMenu* menu = CCMenu::create(quirkButton, zapButton,  NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    CCSprite* coin1 = CCSprite::createWithSpriteFrameName("coin.png");

    contentSize = coin1->getContentSize();
    coin1->setPosition(ccp(MARGIN + contentSize.width/2, winSize.height - MARGIN - contentSize.height/2));
    this->addChild(coin1);
    
    CCSprite* coin2 = CCSprite::createWithSpriteFrameName("coin.png");
    coin2->setPosition(ccp(winSize.width - MARGIN - contentSize.width/2, winSize.height - MARGIN - contentSize.height/2));;
    this->addChild(coin2);
        
    _coin1Label = CCLabelBMFont::create("10","Courier.fnt",winSize.width * 0.25,kCCTextAlignmentLeft);
    _coin1Label->setPosition(ccp(coin1->getPosition().x + contentSize.width/2 + MARGIN/2 + _coin1Label->getContentSize().width/2, winSize.height - MARGIN*1.5));
    this->addChild(_coin1Label);
    
    _coin2Label = CCLabelBMFont::create("10","Courier.fnt",winSize.width * 0.25,kCCTextAlignmentRight);;
    _coin2Label->setPosition ( ccp(coin2->getPosition().x -  contentSize.width/2 - MARGIN/2 - _coin1Label->getContentSize().width/2, winSize.height - MARGIN*1.5));
    this->addChild(_coin2Label);
    
    this->setTouchEnabled(true);
    this->scheduleUpdate();
	_gameOver=false;
	
}
void ArmorHome::addPlayers()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	b2World* _world = new b2World(b2Vec2(0.0f,0.0f));
	_entityManager =new EntityManager();
	
	_entityFactory = new EntityFactory(_entityManager,_batchNodes,_world);

	_healthSystem =new HealthSystem(_entityManager,_entityFactory,_world);
	_moveSystem =new MoveSystem(_entityManager,_entityFactory);
	_playerSystem = new PlayerSystem(_entityManager,_entityFactory);
	_meleeSystem = new MeleeSystem(_entityManager,_entityFactory);
	_gunSystem = new GunSystem(_entityManager,_entityFactory);
	_aiSystem = new AISystem(_entityManager,_entityFactory);
	_physicsSystem = new PhysicsSystem(_entityManager,_entityFactory,_world);
	
    _aiPlayer = _entityFactory->createAIPlayer();
	_aiPlayer->retain();
    RenderComponent* aiRender =  _aiPlayer->render();
	if (aiRender) {
        aiRender->node->setPosition ( ccp(winSize.width - aiRender->node->getContentSize().width/2, winSize.height/2));
	}
	PhysicsComponent* aiPhysics = _aiPlayer->physics();
	if (aiPhysics) {
        aiPhysics->sprite->setPosition ( ccp(winSize.width - aiRender->node->getContentSize().width/2, winSize.height/2));
	}
    _humanPlayer = _entityFactory->createHumanPlayer();
	_humanPlayer->retain();
    RenderComponent* humanRender =_humanPlayer->render();
    if (humanRender) {
          humanRender->node->setPosition ( ccp(humanRender->node->getContentSize().width/2, winSize.height/2));
    }  
	PhysicsComponent* humanPhysics = _humanPlayer->physics();
	if (humanPhysics) {
        humanPhysics->sprite->setPosition (  ccp(humanRender->node->getContentSize().width/2, winSize.height/2));
	}
   
}

void ArmorHome::restartTapped(CCObject* obj){
    
    // Reload the current scene
    CCScene *scene = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipX::create(0.5,scene));
    
}
void ArmorHome::quirkButtonTapped(CCObject* obj) {    
   CCLog("Quirk button tapped!");

     PlayerComponent* humanPlayer = _humanPlayer->player();
    if (!humanPlayer) return;    
    if (humanPlayer->coins < COST_QUIRK) return;
    humanPlayer->coins -= COST_QUIRK;

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("spawn.wav");
    for (int i = 0; i < 2; ++i) {

	    Entity* entity = _entityFactory->createQuirkMonsterWithTeam(1);
	    RenderComponent* render =entity->render();
	    if (render) {        
	        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	        float randomOffset = CCRANDOM_X_Y(-winSize.height * 0.25, winSize.height * 0.25);
	        render->node->setPosition ( ccp(winSize.width * 0.25, winSize.height * 0.5 + randomOffset));
			PhysicsComponent* physics = entity->physics();
			if (physics) {
				physics->sprite->setPosition ( ccp(winSize.width * 0.25, winSize.height * 0.5 + randomOffset));
			}
		}
		

   	}
}

void ArmorHome::zapButtonTapped(CCObject* obj)  {
      CCLog("Zap button tapped!");

     PlayerComponent* humanPlayer = _humanPlayer->player();
    if (!humanPlayer) return;    
    if (humanPlayer->coins < COST_ZAP) return;
    humanPlayer->coins -= COST_ZAP;

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("spawn.wav");
    
    Entity* entity = _entityFactory->createZapMonsterWithTeam(1);
    RenderComponent* render =entity->render();
    if (render) {        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        float randomOffset = CCRANDOM_X_Y(-winSize.height * 0.25, winSize.height * 0.25);
        render->node->setPosition ( ccp(winSize.width * 0.25, winSize.height * 0.5 + randomOffset));
    	PhysicsComponent* physics = entity->physics();
		if (physics) {
			physics->sprite->setPosition ( ccp(winSize.width * 0.25, winSize.height * 0.5 + randomOffset));
		}
	}
}

void ArmorHome::munchButtonTapped(CCObject* obj)  {
    CCLog("Munch button tapped!");

     PlayerComponent* humanPlayer = _humanPlayer->player();
    if (!humanPlayer) return;    
    if (humanPlayer->coins < COST_MUNCH) return;
    humanPlayer->coins -= COST_MUNCH;

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("spawn.wav");
    
    Entity* entity = _entityFactory->createMunchMonsterWithTeam(1);
    RenderComponent* render =entity->render();
    if (render) {        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        float randomOffset = CCRANDOM_X_Y(-winSize.height * 0.25, winSize.height * 0.25);
        render->node->setPosition ( ccp(winSize.width * 0.25, winSize.height * 0.5 + randomOffset));
		PhysicsComponent* physics = entity->physics();
		if (physics) {
			physics->sprite->setPosition ( ccp(winSize.width * 0.25, winSize.height * 0.5 + randomOffset));
		}
	}
}


void ArmorHome::showRestartMenu(bool won) {
     if (_gameOver) return;
    _gameOver = true;
	 CCScene *scene = GameOverLayer::scene(won);
    CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipX::create(0.5,scene));
    /*
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCString *message;
    if (won) {
        message = ccs("You win!");
    } else {
        message = ccs("You lose!");
    }
    
    CCLabelBMFont* label = CCLabelBMFont::create(message->getCString(),"Courier.fnt");

    label->setScale ( 0.1f);
    label->setPosition ( ccp(winSize.width/2, winSize.height * 0.6));
    this->addChild(label);
    
    CCLabelBMFont *restartLabel =CCLabelBMFont::create("Restart" ,"Courier.fnt");
    
    
    CCMenuItemLabel *restartItem = CCMenuItemLabel::create(restartLabel,this,menu_selector(ArmorHome::restartTapped));
    restartItem->setScale ( 0.1f);
    restartItem->setPosition ( ccp(winSize.width/2, winSize.height * 0.4));
    
    CCMenu *menu = CCMenu::create(restartItem, NULL);
    menu->setPosition (CCPointZero);
	this->addChild(menu,10);

    
    restartItem->runAction(CCScaleTo::create(0.5,1.0));
    label->runAction(CCScaleTo::create(0.5,1.0));
    */
}


void ArmorHome::update(float delta){
    _healthSystem->update(delta);
	_moveSystem->update(delta);
	_playerSystem->update(delta);
	_meleeSystem->update(delta);
	_gunSystem->update(delta);
	_aiSystem->update(delta);
	//_physicsSystem->update(delta);
	
    // Check for game over
    HealthComponent* humanHealth = _humanPlayer->health();
    if (humanHealth) {
        if (humanHealth->curHP <= 0) {
            this->showRestartMenu(false);
        }
    }    
    HealthComponent* aiHealth = _aiPlayer->health();
    if (aiHealth) {
        if (aiHealth->curHP <= 0) {
           this->showRestartMenu(true);
        }
    }
    
    // Display coins
    PlayerComponent* humanPlayer = _humanPlayer->player();
    if (humanPlayer) {
        _coin1Label->setString(CCString::createWithFormat("%d", humanPlayer->coins)->getCString());
    }
    PlayerComponent* aiPlayer = _aiPlayer->player();
    if (aiPlayer) {
        _coin2Label->setString(CCString::createWithFormat("%d", aiPlayer->coins)->getCString());
    }
    
    // Display AI state
    AIComponent* aiComp = _aiPlayer->ai();
    if (aiComp) {
        _stateLabel->setString(aiComp->state->name()->getCString());
    }
    
}

void ArmorHome::draw(){
    _healthSystem->draw();
}
void ArmorHome::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool ArmorHome::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = this->convertTouchToNodeSpace(pTouch);
    CCLog("Touch at: %f,%f",touchPoint.x,touchPoint.y);
    
    RenderComponent* render = _humanPlayer->render();
    PlayerComponent* player = _humanPlayer->player();
    if (render && player) {
        if (render->node->boundingBox().containsPoint(touchPoint)) {
            player->attacking = !player->attacking;
        }
    }
	return true;
}

void ArmorHome::release()
{
	CCLayer::release();
	_humanPlayer->release();
	_aiPlayer->release();
	delete _entityManager;  
	delete _entityFactory; 

	delete _healthSystem; 
	delete _moveSystem; 
	delete _playerSystem; 
	delete _meleeSystem;  
	delete _gunSystem; 
	delete _physicsSystem;
}


