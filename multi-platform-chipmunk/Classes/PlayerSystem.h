#pragma once
#include "cocos2d.h"
#include "system.h"
NS_CC_BEGIN

class PlayerSystem:public System
{
public:
	PlayerSystem(EntityManager *entityManager,EntityFactory *entityFactory);
	void handleMover(Entity *mover,bool attacking) ;
	void update(float dt);
	bool handleEconomic(PlayerComponent* player,Monster* monster);
};

NS_CC_END