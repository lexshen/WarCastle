#include "AIStateDefend.h"
#include "SimpleAudioEngine.h"
#include "AIStateRush.h"

USING_NS_CC;

CCString *AIStateDefend::name() {
    return  CCString::create("Defend");
}

void AIStateDefend::enter() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("defend.wav");
}

 void AIStateDefend::updateEntity(Entity *entity,AISystem *system) {
    
    TeamComponent* team = entity->team();
    PlayerComponent* player = entity->player();
    AIComponent* ai = entity->ai();
    if (!team || !player || !ai) return;
    
    CCArray* enemies = entity->entitiesWithinRange(200,OPPOSITE_TEAM(team->team));
    if (enemies->count() == 0) {
		system->changeStateForEntity(entity, AIStateRush::create());
        //CCLog("Rush state");
        return;
    }    
    player->attacking = false;

    if (system->aiZapValue < system->humanZapValue && player->coins > COST_ZAP) {
       system->spawnZapForEntity(entity);
    } else if (system->aiMunchValue < system->humanMunchValue && player->coins > COST_MUNCH) {
         system->spawnMunchForEntity(entity);
    } else if (system->aiQuirkValue < system->humanQuirkValue && player->coins > COST_QUIRK) {
         system->spawnQuirkForEntity(entity);
    } else if (system->humanTotalValue == 0) {
		Monster* monster = ZapMonster::create(2);
        while (player->coins > monster->coins && player->people + monster->people < player->maxPeople ) {
             //system->spawnQuirkForEntity(entity);
             system->spawnZapForEntity(entity);
        }
    }

}
