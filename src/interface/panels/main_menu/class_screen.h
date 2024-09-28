#pragma once
#include "../../interface/interface.h"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "../../../json/json_handler.h"

class ClassScreen : public Interface {
public:
    // define page
    ClassScreen() {
        using namespace ftxui;

        // species data
        json species_info = JSONHandler::ImportJSON("classes.json");

        // options
        auto opts = MenuOption::VerticalAnimated();
        auto entries = std::vector<std::string>{};
        for (auto s : species_info["classes"]) {
            // name
            std::string name = s["name"];
            entries.push_back(name);

            // description
            std::string desc = s["description"];
            mDescriptionEntries.push_back(desc);
        }
        opts.on_enter = [&] {
        };
        mOptions = Menu(entries, &mSelection, opts);

        // descriptions
        // mDescription = Container::Tab(
        //     mDescriptionEntries,
        //     &mSelection
        // );
        
        auto renderer = Renderer(mOptions, [&] {
            return hbox({
                vbox({
                    text("Class?"),
                    text("--------------------"),
                    mOptions->Render() | frame,
                }),
                separatorDashed(),
                hbox({
                    paragraph(mDescriptionEntries[mSelection]) | size(WIDTH, LESS_THAN, 56)  
                })
            });
        });

        // set the renderer
        Interface::SetRenderer(renderer);
    }

private:
    int mSelection = 0;
    ftxui::Component mOptions = nullptr;
    ftxui::Component mDescription = nullptr;
    std::vector<std::string> mDescriptionEntries;
};
