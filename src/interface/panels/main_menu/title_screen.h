#pragma once
#include "../../interface/interface.h"
#include "../../../states/game_state/game_state.h"
#include "name_screen.h"
#include <ftxui/dom/elements.hpp>

class TitleScreen : public Interface {
public:
    // define page
    TitleScreen() {
        using namespace ftxui;

        // options
        auto opts = MenuOption::VerticalAnimated();
        auto entries = std::vector<std::string> {
            "New Game",
            "Continue",
            "Exit"
        };
        opts.on_enter = [&] {
            switch (mSelection) {
                // new game
                case 0:
                    GameState::SetCurrentPanelID(typeid(NameScreen));
                    break;

                // continue
                case 1:
                    break;

                // exit
                case 2:
                    GameState::EndProcess();
                    break;
            }
        };
        mOptions = Menu(entries, &mSelection, opts);

        auto renderer = Renderer(mOptions, [&] {
            return vbox({
                text("Ethereal"),
                text("--------------------"),
                mOptions->Render(),
                filler(),
                paragraph("Copyright (c) 2024 Firwood Studio. All Rights Reserved.")
            });
        });

        // set the renderer
        Interface::SetRenderer(renderer);
    }

private:
    int mSelection = 0;
    ftxui::Component mOptions = nullptr;
};
