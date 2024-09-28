#include "game.h"
#include "../interface/panels/main_menu/title_screen.h"
#include "../interface/panels/main_menu/name_screen.h"
#include "../interface/panels/main_menu/gender_screen.h"
#include "../interface/panels/main_menu/species_screen.h"
#include "../interface/panels/main_menu/class_screen.h"
#include <chrono>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <thread>

Game::Game() {
    GameState::SetCurrentPanelID(typeid(TitleScreen));
    RegisterPanels();
}

void Game::Run() {
    // declare interface
    using namespace ftxui;
    auto screen = ScreenInteractive::Fullscreen();
    auto renderer = Renderer(interface.GetPanels(), [&] {
        // return interface.GetPanels()->Render();
        return interface.GetInterface(GameState::GetCurrentPanelID())->GetRenderer()->Render(); 
    }) | borderLight;

    renderer |= CatchEvent([&](Event event) {
        if (event == Event::CtrlQ) {
            GameState::EndProcess();
            return true;
        }

        return false;
    });

    auto loop = Loop(&screen, renderer);

    // render loop
    while (!GameState::ShouldProcessEnd()) {
        GameState::SetCurrentInterface(interface.GetKeys(GameState::GetCurrentPanelID()));

        // render
        loop.RunOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    } 
}

void Game::CleanUp() {
    interface.CleanUp();
}

void Game::RegisterPanels() {
    // register panels
    interface.AddInterface<TitleScreen>();
    interface.AddInterface<NameScreen>();
    interface.AddInterface<GenderScreen>();
    interface.AddInterface<SpeciesScreen>();
    interface.AddInterface<ClassScreen>();
    interface.CreatePanels();
}
