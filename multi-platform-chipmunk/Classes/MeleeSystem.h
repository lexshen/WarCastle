#pragma once
#include "cocos2d.h"
#include "System.h"

NS_CC_BEGIN
class EntityManager;
class EntityFactory;
class MeleeSystem:public System
{
public:
MeleeSystem(EntityManager *entityManager,EntityFactory *entityFactory);
void update(float dt);

};
NS_CC_END