#include <iostream>

#include "include/Game.h"
#include "include/Helpers/Random.h"

int main() {
    Random::Init();
    Game game;

    while (game.getWindow().isOpen()) {
        game.update();
        game.render();
    }

    return 0;
}
