#pragma once
#include "../../interface/interface.h"
#include <ftxui/component/component_options.hpp>
#include "../../../states/game_state/game_state.h"
#include "gender_screen.h"

class NameScreen : public Interface {
public:
    NameScreen() {
        using namespace ftxui;
        auto opts = InputOption::Default();
        opts.multiline = false;
        opts.on_enter = [&] {
            GameState::SetCurrentPanelID(typeid(GenderScreen));
        };
        mInput = Input(&mName, "Enter your name...", opts);
        auto renderer = Renderer(mInput, [&] {
            return vbox({
                text("Name?"),
                text("--------------------"),
                mInput->Render()
            });
        });
        
        Interface::SetRenderer(renderer);
    }

private:
    ftxui::Component mInput;
    std::string mName = "";
};
