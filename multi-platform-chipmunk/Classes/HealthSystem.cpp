#include "HealthSystem.h"

 
USING_NS_CC;
HealthSystem::HealthSystem(EntityManager *entityManager,EntityFactory* entityFactory,b2World* _world)
{
	init(entityManager,entityFactory);
	this->_world = _world;
}
void HealthSystem::update(float dt) {
 
    // 1
    CCArray * entities =this->entityManager->getAllEntitiesPosessingComponentOfClass("HealthComponent");
	/*CCObject *_object;
    CCARRAY_FOREACH (entities,_object) {
		Entity* entity = (Entity* ) _object;*/
	for(UINT i = 0;i<entities->count();i++){
		Entity* entity = (Entity* )entities->objectAtIndex(i);
		entity->retain();
        // 2
        HealthComponent * health = (HealthComponent *)this->entityManager->getComponentOfClass("HealthComponent",entity);
        RenderComponent * render = (RenderComponent *)this->entityManager->getComponentOfClass("RenderComponent",entity);
 
        // 3
        if (!health->alive) return;
        if (health->maxHP  == 0) return;
        if (health->curHP <= 0) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("boom.wav");
            health->alive = false;
 
            // 4
            if (render) {            
                render->node->runAction(
                 CCSequence::create(
                  CCFadeOut::create(0.5),
                   CCCallFuncND::create(this,callfuncND_selector(HealthSystem::clean),entity),NULL));
            } else {
            	  CCLog("Removing entity:%d",entity->_eid);
				  this->entityManager->removeEntity(entity);

					b2Body* destroy;
					for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
						if (b->GetUserData() != NULL) {
							Entity *_entity = (Entity *)b->GetUserData();
							if(_entity ==(Entity *) entity)
							{
								destroy = b;
							}
						}
					}
					_world->DestroyBody(destroy);
            }
        }
    }    
}
void HealthSystem::draw() {    
	CCArray* entities = this->entityManager->getAllEntitiesPosessingComponentOfClass("HealthComponent");
 	for(UINT i=0;i<entities->count();++i){
		Entity* entity =(Entity* )  entities->objectAtIndex(i);
	        HealthComponent* health = (HealthComponent *)this->entityManager->getComponentOfClass("HealthComponent",entity);
	        RenderComponent* render = (RenderComponent *)this->entityManager->getComponentOfClass("RenderComponent",entity);     
		 //MeleeComponent* melee = (MeleeComponent*)this->entityManager->getComponentOfClass("MeleeComponent",entity);     
	        
		if ( !health || !render) continue;
	 
	        int sX = render->node->getPosition().x - render->node->getContentSize().width/2;
	        int eX = render->node->getPosition().x + render->node->getContentSize().width/2;
	        int actualY = render->node->getPosition().y + render->node->getContentSize().height/2;
	 
	        static int maxColor = 200;
	        static int colorBuffer = 55;
			float percentage = ((float) health->curHP) / ((float) health->maxHP);
	        int actualX = ((eX-sX) * percentage) + sX;
	        int amtRed = ((1.0f-percentage)*maxColor)+colorBuffer;
	        int amtGreen = (percentage*maxColor)+colorBuffer;
	 
	        glLineWidth(7);
	        ccDrawColor4B(amtRed,amtGreen,0,255);
	        ccDrawLine(ccp(sX, actualY), ccp(actualX, actualY));
    }    
}
void HealthSystem::clean(CCNode* node,void* entity)
{
	node->removeFromParentAndCleanup(true);
	CCLog("I am not in good health, Removing entity:%d",((Entity*)entity)->_eid);
	this->entityManager->removeEntity((Entity*)entity);

	b2Body* destroy=NULL;
	for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
		if (b->GetUserData() != NULL) {
			Entity *_entity = (Entity *)b->GetUserData();
			if(_entity->_eid ==((Entity *) entity)->_eid)
			{
				destroy = b;
			}
		}
	}
	_world->DestroyBody(destroy);
}