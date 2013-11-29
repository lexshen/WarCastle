#include "PhysicsSystem.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
PhysicsSystem::PhysicsSystem(EntityManager *entityManager,EntityFactory *entityFactory,b2World* _world)
{
	init(entityManager,entityFactory);
	this->_world = _world;
}
PhysicsSystem::~PhysicsSystem()
{

}
void PhysicsSystem::update(float dt){
	std::list<b2Body *> toDestroy;  

    _world->Step(dt, 10, 10);
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            Entity *entity = (Entity *)b->GetUserData();
            PhysicsComponent * physics = (PhysicsComponent *)this->entityManager->getComponentOfClass("PhysicsComponent",entity);
			CCNode* sprite = physics->sprite;
            b2Vec2 b2Position = b2Vec2(sprite->getPosition().x/PTM_RATIO,
                                       sprite->getPosition().y/PTM_RATIO);
            float32 b2Angle = -1 * CC_DEGREES_TO_RADIANS(sprite->getRotation());
 
            b->SetTransform(b2Position, b2Angle);
			//CCLog("entity:%d,x:%f,y:%f",entity->_eid,sprite->getPosition().x, sprite->getPosition().y);
        }
    }


	b2Contact* contact= _world->GetContactList();
	std::list<b2Contact*> contactList;
	while(contact)
	{
		bool contain = false;
		std::list<b2Contact*>::iterator pos =contactList.begin();
		while(pos!=contactList.end())
		{
			if((*pos)->GetFixtureA()==contact->GetFixtureA() &&
				(*pos)->GetFixtureB()==contact->GetFixtureB())
			{
				contain = true;
				break;
			}
			pos++;
		}
		if(!contain)
			contactList.push_back(contact);
		contact= contact->GetNext();
	}
	
	std::list<b2Body*> destroyList;
	
    for(std::list<b2Contact*>::iterator it = contactList.begin();it != contactList.end();++it)  
    { 
		b2Fixture* fixA = (*it)->GetFixtureA();
		b2Fixture* fixB = (*it)->GetFixtureB();
		Entity* entityA = (Entity*)fixA->GetBody()->GetUserData();
		Entity* entityB = (Entity*)fixB->GetBody()->GetUserData();
		//CCLog("a:%d,b:%d",entityA->_eid,entityB->_eid);
		
		RenderComponent * aRender = entityA->render();
        HealthComponent * aHealth = entityA->health();
      	TeamComponent* aTeam = entityA->team();
		MeleeComponent* aMelee = entityA->melee();
		BulletComponent* aBullet = entityA->bullet();
		
		RenderComponent * bRender = entityB->render();
        HealthComponent * bHealth = entityB->health();
      	TeamComponent* bTeam = entityB->team();  
		MeleeComponent* bMelee = entityB->melee();
		BulletComponent* bBullet = entityB->bullet();
		
		if(!aTeam ||!bTeam || aTeam->team==bTeam->team) 
		{
			continue;
		}
		if(aBullet && bBullet)
		{
			continue;
		}
		
		if (!bBullet && aMelee && aRender->node->boundingBox().intersectsRect(bRender->node->boundingBox())) 
		{
			bool aoeDamageCaused = FALSE;
			if(GetTickCount() - aMelee->lastDamageTime > aMelee->damageRate* 1000){
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(aMelee->sound->getCString());
                    
				if (aMelee->aoe) {
					aoeDamageCaused = true;
				} else {
					aMelee->lastDamageTime = GetTickCount();
				}
				bHealth->curHP -= aMelee->damage;
				if (bHealth->curHP < 0) {
					bHealth->curHP = 0;
				}
				if (aMelee->destroySelf) {
					aRender->node->removeFromParentAndCleanup(true);
					CCLog("Removing entity:%d, I am a bullet.",entityA->_eid);
					this->entityManager->removeEntity(entityA);
					//_world->DestroyBody(fixA->GetBody());
					destroyList.push_back(fixA->GetBody());

				}
			}
		}

		if (!aBullet && bMelee && aRender->node->boundingBox().intersectsRect(bRender->node->boundingBox())) 
		{
			bool aoeDamageCaused = FALSE;
			if(GetTickCount() - bMelee->lastDamageTime > bMelee->damageRate* 1000){
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(bMelee->sound->getCString());
                    
				if (bMelee->aoe) {
					aoeDamageCaused = true;
				} else {
					bMelee->lastDamageTime = GetTickCount();
				}
				aHealth->curHP -= bMelee->damage;
				if (aHealth->curHP < 0) {
					aHealth->curHP = 0;
				}
				if (bMelee->destroySelf) {
					bRender->node->removeFromParentAndCleanup(true);
					CCLog("Removing entity:%d, I am a bullet.",entityB->_eid);
					this->entityManager->removeEntity(entityB);
					//_world->DestroyBody(fixB->GetBody());
					destroyList.push_back(fixB->GetBody());

				}
			}
		}

    }  

	std::list<b2Body*>::iterator pos =destroyList.begin();
	while(pos!=destroyList.end())
	{
		_world->DestroyBody(*pos);
		pos++;
	}
}

