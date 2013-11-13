#pragma once

#include "cocos2d.h"
#include "Entity.h"
#include "EntityManager.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "MoveComponent.h"
#include "GunComponent.h"
#include "PhysicsComponent.h"
#include "Box2d.h"

NS_CC_BEGIN
class Entity;
class EntityManager;


class EntityFactory:  public CCObject
{
public:
	b2World* _world;
	EntityFactory(EntityManager *entityManager,CCSpriteBatchNode *batchNode,b2World* _world);
	~EntityFactory();
	Entity* createHumanPlayer();
	Entity* createAIPlayer();
	Entity* createQuirkMonsterWithTeam(int team);
	Entity* createZapMonsterWithTeam(int team);
	Entity* createMunchMonsterWithTeam(int team);
	Entity* createLaserWithTeam(int team);
	EntityManager* _entityManager;
    CCSpriteBatchNode* _batchNode;
};

NS_CC_END