#include "Game.h"
#include "Common.h"

void showMenu() {
  while (true) {
    std::cout << Common::clearScreen;
    std::cout << Common::title;
    std::cout << "\n\n" << Common::centerHorizontally("Please choose an option:", 54);
    std::cout << "\n" << Common::centerHorizontally("1. Play a game against an AI", 54);
    std::cout << "\n" << Common::centerHorizontally("2. Show a game between 2 AIs", 54);
    std::cout << "\n" << Common::centerHorizontally("3. Open settings", 54) << "\n\n";
    std::string chosenOption = Common::validatedInput(
        "",
        [](std::string input){
            std::vector<std::string> options = std::vector<std::string>{"1", "2", "3"};
            return std::find(options.begin(), options.end(), input) != options.end();
        },
        "Invalid option. Please choose one of the options shown above: ");
    if (chosenOption == "1") {
      Game game(1);
      game.Start();
    } else if (chosenOption == "2") {
      Game game(0);
      game.Start();
    } else if (chosenOption == "3") {
      int i = 1;
    }
  }
}

int main() {
    showMenu();
    return 0;
}