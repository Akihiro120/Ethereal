#pragma once
#include <typeindex>

// singleton
class GameState {
public:
    // returns the current interface
    static void SetCurrentPanelID(std::type_index panel);
    static void SetCurrentInterface(int i);
    static int& GetCurrentPanel();
    static bool ShouldProcessEnd();
    static void EndProcess();
    static std::type_index GetCurrentPanelID();

private:
    GameState() = default;
    static GameState& Get() {
        static GameState instance;
        return instance;
    }

    bool mEndProcess = false;
    int mCurrentInterface = 0;
    std::type_index mCurrentPanelNameID = typeid(nullptr);
};
