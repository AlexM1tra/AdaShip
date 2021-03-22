#include "Game.h"
#include "Common.h"

int main() {
    std::cout << Common::title;
    Game game = Game(1);
    game.Start();
    return 0;
}