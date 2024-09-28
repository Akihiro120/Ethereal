#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include "components/component.h"
#include "../entities/entity.h"

class ComponentManager {
public:
    ComponentManager() = default;

    // add component
    template <typename T>
    void AddComponent(Entity entity, T component) {
        // does the component exist already?
        if (!mComponentMap[typeid(T)][entity]) {

            // create the component
            T* new_component = new T(component);

            // add the component to the map
            mComponentMap[typeid(T)][entity] = new_component;

            // add the entity to entity map
            mEntityMap[typeid(T)].push_back(entity);
        } else {
            std::cout << "Component already Exists" << std::endl;
        }
    }
    
    // remove component
    template <typename T>
    void RemoveComponent(Entity entity) {
        // does the component exist?
        if(mComponentMap[typeid(T)][entity]) {

            // remove the component
            delete mComponentMap[typeid(T)][entity];
            mComponentMap[typeid(T)][entity] = nullptr;

            // remove the entity
            auto& entities = mEntityMap[typeid(T)];
            for (int i = 0; i < entities.size(); i++) {

                // is the entity we are trying to remove the same?
                if (entities[i] == entity) {
                    entities.erase(entities.begin() + i);

                    // end early
                    break;
                }
            }
        } else {
            std::cout << "Component does not Exist" << std::endl;
        }
    }

    // get entities
    template <typename T>
    std::vector<Entity> GetEntities() {
        // return a list of entities
        return mEntityMap[typeid(T)];
    }

    // get component
    template <typename T>
    T* GetComponent(Entity entity) {
        // does the component exist?
        if (mComponentMap[typeid(T)][entity]) {
            // return the component at that memory address
            return mComponentMap[typeid(T)][entity];
        } else {
            std::cout << "Component does not Exist" << std::endl;
        }
    }

    // has component
    template <typename T>
    bool HasComponent(Entity entity) {
        // does the component exist?
        if (mComponentMap[typeid(T)][entity]) {
            // return the component at that memory address
            return true;
        } else {
            return false;
        }
    }

    // clean up all components
    void CleanUp() {
        // clean up all component memory allocations
        for (auto type : mComponentMap) {
            for (auto component : type.second) {
                // free the memory loc
                delete component.second;
            }
        }
    }

private:
    // containers for both component maps, and entity maps
    std::unordered_map<std::type_index, std::unordered_map<Entity, Component*>> mComponentMap;
    std::unordered_map<std::type_index, std::vector<Entity>> mEntityMap;
};

