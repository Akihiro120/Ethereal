#pragma once
#include <ftxui/component/component.hpp>

class Interface {
public:
    Interface() = default;

    // return render component
    ftxui::Component GetRenderer();

private:
    ftxui::Component mRenderer = nullptr;

protected:
    // set renderer component
    void SetRenderer(ftxui::Component renderer);
};
