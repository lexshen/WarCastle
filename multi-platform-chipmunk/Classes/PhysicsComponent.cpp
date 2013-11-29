#include "PhysicsComponent.h"
#include "Entity.h"
USING_NS_CC;

PhysicsComponent::PhysicsComponent(Entity* entity,CCNode* sprite,b2World* _world){
	this->_world = _world;
	this->entity = entity;
	this->entity->retain();
	this->sprite = sprite;
	sprite->retain();
	this->addBody();
}

void PhysicsComponent::addBody()
{
	b2BodyDef spriteBodyDef;
    spriteBodyDef.type = b2_dynamicBody;
    spriteBodyDef.position.Set(sprite->getPosition().x/PTM_RATIO, 
        sprite->getPosition().y/PTM_RATIO);
    spriteBodyDef.userData = entity;
    spriteBody = _world->CreateBody(&spriteBodyDef);
 
    b2PolygonShape spriteShape;

	float minhw = sprite->getContentSize().width/PTM_RATIO/2;
	if(minhw*minhw<b2_epsilon)
		minhw = 0.5f;
	float minhh =  sprite->getContentSize().height/PTM_RATIO/2;
	if(minhh*minhh<b2_epsilon)
		minhh = 0.5f;
    spriteShape.SetAsBox(minhw,minhh);
    b2FixtureDef spriteShapeDef;
    spriteShapeDef.shape = &spriteShape;
    spriteShapeDef.density = 10.0;
    spriteShapeDef.isSensor = true;
    spriteBody->CreateFixture(&spriteShapeDef);
}
void PhysicsComponent::removeBody(){

	b2Body *spriteBody = NULL;
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            Entity *curSprite = (Entity *)b->GetUserData();
            if (curSprite == entity) {
                spriteBody = b;
                break;
            }
        }
    }
    if (spriteBody != NULL) {
        _world->DestroyBody(spriteBody);
    }


}

PhysicsComponent::~PhysicsComponent(){
	this->removeBody();
	this->entity->release();
	this->sprite->release();
}
CCString* PhysicsComponent::ClassName()
{
	return CCString::create("PhysicsComponent");
}
PhysicsComponent* PhysicsComponent::create(Entity* entity,CCNode* node,b2World* _world)
{
	PhysicsComponent *pRet = new PhysicsComponent(entity,node,_world); \
	if (pRet ) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \

}
