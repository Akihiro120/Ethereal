#include "game_state.h"
#include <typeindex>

int& GameState::GetCurrentPanel() {
    return Get().mCurrentInterface;
}

bool GameState::ShouldProcessEnd() {
    return Get().mEndProcess;
}

void GameState::EndProcess() {
    Get().mEndProcess = true;
}

void GameState::SetCurrentPanelID(std::type_index panel) {
    Get().mCurrentPanelNameID = panel;
}

void GameState::SetCurrentInterface(int i) {
    Get().mCurrentInterface = i;
}

std::type_index GameState::GetCurrentPanelID() {
    return Get().mCurrentPanelNameID;
}
