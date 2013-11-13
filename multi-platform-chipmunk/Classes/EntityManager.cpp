#include "EntityManager.h"

USING_NS_CC;

EntityManager::EntityManager()
{
	_entities = CCArray::create();
	_entities->retain();
	 _componentsByClass = CCDictionary::create();
	_componentsByClass->retain();
    _lowestUnassignedEid = 1;
}

EntityManager::~EntityManager()
{
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(_componentsByClass, pElement)
	{
	    CCDictionary* components = (CCDictionary*)pElement->getObject();
	    components->removeAllObjects();
	} 
	_componentsByClass->removeAllObjects();
	_componentsByClass->release();
	_entities->release();
	/*
	CCArray* keys = _componentsByClass->allKeys();
	for(UINT i=0;i<keys->count();++i){
		CCString* key = (CCString*)keys->objectAtIndex(i);
		
		CCDictionary* components  = (CCDictionary*)_componentsByClass->objectForKey(key->getCString());
		CCArray* _keys = components->allKeys();
	   	for(UINT j=0;j< _keys->count();j++)
   		{
			CCString* key = (CCString*)_keys->objectAtIndex(j);
			components->objectForKey(key->getCString())->release();
   		}
		components->removeAllObjects();
		//components->release();
    }
	_componentsByClass->removeAllObjects();
	_componentsByClass->release();
	_entities->release();
	*/
}

uint32_t EntityManager::generateNewEid()
{
 	if (_lowestUnassignedEid < UINT32_MAX) {
        return _lowestUnassignedEid++;
    } else {
        for (uint32_t i = 1; i < UINT32_MAX; ++i) {
            if (!_entities->containsObject(Entity::create(i,this)))
                return i;
        }
        CCLog("ERROR: No available EIDs!");
        return 0;
    }

}

Entity* EntityManager::createEntity()
{
     uint32_t eid = this->generateNewEid();
	 Entity* entity = Entity::create(eid,this);
	_entities->addObject(entity);
    CCLog("entities count:%d,%d added",_entities->count(),eid);
    return entity;
}

void EntityManager::addComponent(Component* component,Entity* entity)
{
	CCDictionary* components = ( CCDictionary* )_componentsByClass->objectForKey(component->ClassName()->getCString());
    if (!components) {
        components = CCDictionary::create();
		components->retain();
		_componentsByClass->setObject(components,component->ClassName()->getCString());
    } 
	component->retain();
	//components->setObject((CCObject*)component,CCString::createWithFormat("%d",entity->_eid)->getCString());
	components->setObject((CCObject*)component,(intptr_t)entity);
}

CCObject* EntityManager::getComponentOfClass(std::string className ,Entity *entity)
{
	CCDictionary* components = (CCDictionary*)_componentsByClass->objectForKey(className);
	if(!components)
		return NULL;
	//return components->objectForKey(CCString::createWithFormat("%d",entity->_eid)->getCString());
	return components->objectForKey((intptr_t)entity);
}

void EntityManager::removeEntity(Entity *entity)
{
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(_componentsByClass,pElement)
	{
		CCDictionary* components = (CCDictionary*) pElement->getObject();
		//components->removeObjectForKey(CCString::createWithFormat("%d",entity->_eid)->getCString());
		components->removeObjectForKey((intptr_t)entity);
	}
	
	/*
	CCArray* keys = _componentsByClass->allKeys();
	for(UINT i=0;i<keys->count();++i){
		CCString* key = (CCString*)keys->objectAtIndex(i);
		CCDictionary* components  = (CCDictionary*)_componentsByClass->objectForKey(key->getCString());
		components->removeObjectForKey(CCString::createWithFormat("%d",entity->_eid)->getCString());

    }
	*/
	_entities->removeObject(entity);
	/*
	for(UINT i =0;i<_entities->count();i++){
		if(entity->isEqual((Entity*)_entities->objectAtIndex(i)))
		{
			CCLog("remove entity comparison:%d",entity==(Entity*)_entities->objectAtIndex(i));

			_entities->removeObjectAtIndex(i);
		}
	}
	*/
	CCLog("entities count:%d,%d deleted",_entities->count(),entity->_eid);
}
CCArray* EntityManager::getAllEntitiesPosessingComponentOfClass(std::string className)
{

	CCDictionary* components = (CCDictionary* )_componentsByClass->objectForKey(className);
    if (components) {
		CCArray * retval = CCArray::create();
		CCDictElement* pElement = NULL;
		CCDICT_FOREACH(components,pElement)
		{
			//const char* key = pElement->getStrKey();
			//retval->addObject(Entity::create(atoi(key),this));
			retval->addObject((Entity*)pElement->getIntKey());
		}
		/*CCArray* keys = components->allKeys();
		if(keys){
			for(UINT i=0;i<keys->count();++i){
				CCString* key = (CCString*)keys->objectAtIndex(i);
				retval->addObject(Entity::create(key->uintValue(),this));
			}
		}*/
        return retval;
    } else {
        return CCArray::create();
    }
}


