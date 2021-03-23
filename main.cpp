#include "Game.h"
#include "Common.h"

void setNewBoardDimensions() {
  std::cout << "Current board dimensions are: " << SettingsIO::getSettings().first.toString() << "\n"; 
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

void editBoats() {
  while (true) {
      std::cout << Common::clearScreen << Common::settings << "\n\n";
      std::vector<Boat> boats = SettingsIO::getSettings().second;
      std::vector<std::string> inputOptions;
      inputOptions.push_back("N");
      inputOptions.push_back("Q");
      std::cout << "Current boats are:\n";
      for (int i = 1; i <= boats.size(); i++) {
        std::cout << i << ". " << boats[i-1].Name() << ": " << boats[i-1].Length() << "\n";
        inputOptions.push_back(std::to_string(i));
      }
      std::string choice = Common::validatedInput(
        "Choose a number above to remove that boat or type N to add a new boat.\nType Q to exit: ",
        Common::isOneOf(inputOptions),
        "Invalid choice.\nPlease choose a number above or type N to add a new boat or Q to exit: ");
      if (choice == "Q") 
        break;
      else if (choice == "N") {
        std::string name = Common::validatedInput(
          "What is the name of the ship? ",
          [](std::string input) {
            bool isAlpha = true;
            for (auto& c : input)
              isAlpha = isAlpha && (isalpha(c) || c == ' ');
            return isAlpha;
          },
          "Please enter a name consisting of alphabetic characters: ");
        std::string length = Common::validatedInput(
          "How long is this ship?\n(Please choose a number less than 3/4 of the size of the board): ",
          [](std::string input) {
            bool isNum = true;
            for (auto& c : input)
              isNum = isNum && isdigit(c);
            if (isNum)
              return stoi(input) >= 1 
                  && stoi(input) <= 0.75 * std::min(
                                              SettingsIO::currentDimensions().width, 
                                              SettingsIO::currentDimensions().height);
            return false;
          },
          "Please enter a number smaller than 3/4 of the size of the board: ");
        bool nameIsUnique = true;
        for (Boat& boat : boats) 
          if (boat.Name() == name)
            nameIsUnique = false;
        if (nameIsUnique) {
          SettingsIO::addBoat(Boat(name, stoi(length)));
        } else
          std::cout << "The boat's name must be unique. Please try again";
      } else {
        SettingsIO::removeBoat(boats[stoi(choice) - 1]);
      }
  }
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
      editBoats();
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
    std::cout << "\n" << Common::centerHorizontally("2. Play a 2 player game", 54);
    std::cout << "\n" << Common::centerHorizontally("3. Open settings", 54);
    std::cout << "\n" << Common::centerHorizontally("4. Quit", 54) << "\n\n";
    std::string chosenOption = Common::validatedInput(
        "",
        Common::isOneOf(std::vector<std::string>{"1", "2", "3", "4"}),
        "Invalid option. Please choose one of the options shown above: ");
    if (chosenOption == "1") {
      Game game(1);
      game.Start();
    } else if (chosenOption == "2") {
      Game game(2);
      game.Start();
    } else if (chosenOption == "3") {
      showSettings();
    } else {
      break;
    }
  }
}

int main() {
    showMenu();
    return 0;
}