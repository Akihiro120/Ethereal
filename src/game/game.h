#pragma once
#include "../interface/manager/interface_manager.h"
#include "../states/game_state/game_state.h"

class Game {
public:
    Game();

    void Run();
    void CleanUp();

private:
    // game related
    InterfaceManager interface;

    // methods
    void RegisterPanels();
};
