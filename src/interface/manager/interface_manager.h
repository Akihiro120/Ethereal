#pragma once
#include <ftxui/component/component.hpp>
#include <map>
#include <iostream>
#include <typeindex>
#include "../interface/interface.h"
#include "../../states/game_state/game_state.h"

class InterfaceManager {
public:
    InterfaceManager() = default;

    // get interfaces
    Interface* GetInterface(std::type_index index) {
        return mInterfaces[mKeys[index]];
    }

    void CreatePanels() {

        // panels
        mPanel = ftxui::Container::Tab(
            mComponents, 
            &GameState::GetCurrentPanel()
        );
    }

    ftxui::Component GetPanels() {
        return mPanel;
    }

    // register a new panel
    template <typename T>
    void AddInterface() {
        mInterfaces.push_back(new T());
        mKeys[typeid(T)] = mInterfaces.size() - 1;

        mComponents.push_back(mInterfaces[mInterfaces.size() - 1]->GetRenderer());
    }

    void CleanUp() {
        for (auto interface : mInterfaces) {
            delete interface;
        }
    }

    int GetKeys(std::type_index id) {
        return mKeys[id];
    }

private:
    std::vector<Interface*> mInterfaces;
    std::map<std::type_index, int> mKeys;
    std::vector<ftxui::Component> mComponents;
    ftxui::Component mPanel = nullptr;
};
