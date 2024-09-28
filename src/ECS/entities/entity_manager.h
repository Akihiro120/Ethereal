#pragma once
#include <vector>
#include "entity.h"

/** 
a manager used to instantiate new entities all entities are empty
**/
class EntityManager {
public:
    EntityManager() = default;

    // intantiate an empty entity
    Entity InstantiateEntity() {

        // the entity itself is simply an index, we can use the size of the list to set the index
        Entity entity = mEntities.size();
        mEntities.push_back(entity);
        return entity;
    }

private:
    // list of entities
    std::vector<Entity> mEntities;
};
