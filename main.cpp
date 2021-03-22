#include "Game.h"
#include "Common.h"

void setNewBoardDimensions() {
  std::string newWidth = Common::validatedInput(
      "Enter a new board width (must be 5 - 80): ", 
      [](std::string input){
        bool isNum = true;
        for (auto& c : input)
          isNum = isNum && isdigit(c);
        if (isNum)
          return stoi(input) >= 5 && stoi(input) <= 80;
        return false;
      }, 
      "Invalid width, please enter a number between 5 and 80: ");

  std::string newHeight = Common::validatedInput(
      "Enter a new board height (must be 5 - 80): ", 
      [](std::string input){
        bool isNum = true;
        for (auto& c : input)
          isNum = isNum && isdigit(c);
        if (isNum)
          return stoi(input) >= 5 && stoi(input) <= 80;
        return false;
      }, 
      "Invalid height, please enter a number between 5 and 80: ");
  SettingsIO::updateBoardDimensions(BoardDimensions(stoi(newWidth), stoi(newHeight)));
}

void showSettings() {
  while (true) {
    std::cout << Common::clearScreen;
    std::cout << Common::settings;
    std::cout << "\n\n" << Common::centerHorizontally("Please choose an option:", 40);
    std::cout << "\n" << Common::centerHorizontally("1. Resize board", 40);
    std::cout << "\n" << Common::centerHorizontally("2. Change ships", 40);
    std::cout << "\n" << Common::centerHorizontally("3. Exit to main menu", 40) << "\n\n";
    std::string chosenOption = Common::validatedInput(
        "",
        Common::isOneOf(std::vector<std::string>{"1", "2", "3"}),
        "Invalid option. Please choose one of the options shown above: ");
    if (chosenOption == "1") {
      setNewBoardDimensions();
    } else if (chosenOption == "2") {
      break;
    } else {
      break;
    }
  }
}

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
        Common::isOneOf(std::vector<std::string>{"1", "2", "3"}),
        "Invalid option. Please choose one of the options shown above: ");
    if (chosenOption == "1") {
      Game game(1);
      game.Start();
    } else if (chosenOption == "2") {
      Game game(0);
      game.Start();
    } else if (chosenOption == "3") {
      showSettings();
    }
  }
}

int main() {
    showMenu();
    return 0;
}