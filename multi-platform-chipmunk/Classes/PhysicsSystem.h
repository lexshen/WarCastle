#pragma once
#include "cocos2d.h"
#include "system.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "Box2d.h"

NS_CC_BEGIN
#define PTM_RATIO 32.0
class PhysicsSystem:public System
{
public:
	b2World* _world;
	PhysicsSystem(EntityManager *entityManager,EntityFactory *entityFactory,b2World* _world);
	~PhysicsSystem();
	void update(float dt);
};

NS_CC_END
