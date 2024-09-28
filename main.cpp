#include "src/game/game.h"

int main() {
    Game game = {};
    game.Run();
    game.CleanUp();

    return 0;
}
