#pragma once
#include "cocos2d.h"
#include "Component.h"
#include "Box2d.h"
//#include "Entity.h"

NS_CC_BEGIN
class Entity;
#define PTM_RATIO 32.0
class PhysicsComponent:public Component
{
public:
	Entity* entity;	
	b2World* _world;
	CCNode* sprite;
	b2Body* spriteBody;
    b2PolygonShape spriteShape;
	PhysicsComponent(Entity* entity,CCNode* node,b2World* _world);
	~PhysicsComponent();
	void addBody();
	void removeBody();
	inline bool init(){return true;}
	CCString* ClassName();
	static PhysicsComponent* create(Entity* entity,CCNode* node,b2World* _world);
	//friend class Entity;
};
NS_CC_END