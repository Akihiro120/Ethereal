#pragma once
#include "../../interface/interface.h"
#include "../../../states/game_state/game_state.h"
#include "species_screen.h"
#include <ftxui/dom/elements.hpp>
#include "ftxui/component/component.hpp"

class GenderScreen : public Interface {
public:
    // define page
    GenderScreen() {
        using namespace ftxui;

        auto next = [&] {
            GameState::SetCurrentPanelID(typeid(SpeciesScreen));
        };
        // options
        auto opts = MenuOption::VerticalAnimated();
        auto entries = std::vector<std::string> {
            "Male",
            "Female",
            "Either"
        };
        opts.on_enter = [&] {
            switch (mSelection) {
                // new game
                case 0:
                    next();
                    break;

                // continue
                case 1:
                    next();
                    break;

                // exit
                case 2:
                    mEither = true;
                    break;
            }
        };
        mOptions = Menu(entries, &mSelection, opts);

        // either option
        auto input_opts = InputOption::Default();
        input_opts.multiline = false;
        input_opts.on_enter = [&] {
            next();
        };
        mInput = Input(&mGender, input_opts);

        auto container = Container::Horizontal({
            mOptions
            , mInput | Maybe(&mEither)
        });
        auto renderer = Renderer(container, [&] {
            return hbox({
                vbox({
                    text("Gender?"),
                    text("--------------------"),
                    mOptions->Render(),
                }),
                separatorDashed(),
                [&] { 
                    return Renderer([&] {
                        return vbox({
                            text("Enter your preferred gender"),
                            mInput->Render() | frame
                        });
                    }) | Maybe(&mEither);
                }()->Render()
            });
        });

        // set the renderer
        Interface::SetRenderer(renderer);
    }

private:
    int mSelection = 0;
    bool mEither = false;
    ftxui::Component mOptions = nullptr;
    ftxui::Component mInput = nullptr;
    std::string mGender = "";
};
