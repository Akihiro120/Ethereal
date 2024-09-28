#include "interface.h"

// return the renderer
ftxui::Component Interface::GetRenderer() {
    if (mRenderer) {
        return mRenderer;
    } else {
        using namespace ftxui;
        return Renderer([&] {
            return text("Error 404: Panel not Found!!!");
        });
    }
}
    
// set the renderer
void Interface::SetRenderer(ftxui::Component renderer) {
    mRenderer = renderer;
}
