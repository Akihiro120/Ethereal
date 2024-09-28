#pragma once
#include "systems/system.h"
#include "../../data/enum/system_type.h"
#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <vector>

class SystemManager {
public:
    SystemManager() = default;

    // register system
    template <typename T>
    void RegisterSystem(SystemType type = RUNTIME, std::string name = "") {
        // allocate new system
        T* system = new T();

        // add the system to the lists
        if (type == SystemType::CUSTOM) {
            mTypeSystems[type] = system;
        } else {
            // add as custom system
            mSystems[name] = system;
        }
    }

    // update all systems with the runtime type
    void UpdateRuntimeSystems() {
        for (auto system : mTypeSystems[SystemType::RUNTIME]) {
            system->Update();
        }
    }

    // update all systems with the startup type
    void UpdateStartupSystems() {
        for (auto system : mTypeSystems[SystemType::STARTUP]) {
            system->Update();
        }
    }

    // get systems
    std::unordered_map<std::string, System*> GetSystems() {
        return mSystems;
    } 

    // clean up all systems
    void CleanUp() {
        // clear all system memory allocations
        for (auto type : mTypeSystems) {
            for (auto system : type.second) {
                // free memory
                delete system;
            }
        }
        for (auto type : mSystems) {
            // free memory
            delete type.second;
        }
    }

private:
    // container to hold all the systems
    std::unordered_map<SystemType, std::vector<System*>> mTypeSystems;
    std::unordered_map<std::string, System*> mSystems;
};
