#include "Game.h"
#include "Common.h"

void setNewBoardDimensions() {
    std::cout << "Current board dimensions are: " << SettingsIO::currentDimensions().toString() << "\n";
    std::string whPrompt = "Enter a new board width (must be 5 - 80): ";
    std::string whError = "Invalid width, please enter a number between 5 and 80: ";
    auto whValidator = 
        [](std::string input){
            bool isNum = true;
            for (auto& c : input)
                isNum = isNum && isdigit(c);
            if (isNum)
                return stoi(input) >= 5 && stoi(input) <= 80;
            return false;
        };
    std::string newWidth = Common::validatedInput(whPrompt, whValidator, whError);
    std::string newHeight = Common::validatedInput(whPrompt, whValidator, whError);
    SettingsIO::updateBoardDimensions(BoardDimensions(stoi(newWidth), stoi(newHeight)));
}

void editBoats() {
    while (true) {
        std::cout << Common::clearScreen() << Common::settings() << "\n\n";
        std::vector<Boat> boats = SettingsIO::initialiseSettings();
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
        std::cout << Common::clearScreen()
                  << Common::settings()
                  << "\n\n" << Common::centerHorizontally("Please choose an option:", 40)
                  << "\n" << Common::centerHorizontally("1. Resize board", 40)
                  << "\n" << Common::centerHorizontally("2. Change ships", 40)
                  << "\n" << Common::centerHorizontally("3. Exit to main menu", 40) << "\n\n";
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
        std::cout << Common::clearScreen()
                  << Common::title()
                  << "\n\n" << Common::centerHorizontally("Please choose an option:", 54)
                  << "\n" << Common::centerHorizontally("1. Play a game against an AI", 54)
                  << "\n" << Common::centerHorizontally("2. Play a 2 player game", 54)
                  << "\n" << Common::centerHorizontally("3. Play a salvo game against an AI", 54)
                  << "\n" << Common::centerHorizontally("4. Play a 2 player salvo game", 54)
                  << "\n" << Common::centerHorizontally("5. Play a game with mines against an AI", 54)
                  << "\n" << Common::centerHorizontally("6. Play a 2 player game with mines", 54)
                  << "\n" << Common::centerHorizontally("7. Show an AI game with mines", 54)
                  << "\n" << Common::centerHorizontally("8. Open settings", 54)
                  << "\n" << Common::centerHorizontally("9. Quit", 54) << "\n\n";
        std::string chosenOption = Common::validatedInput(
                "",
                Common::isOneOf(std::vector<std::string>{"1", "2", "3", "4", "5", "6", "7", "8", "9"}),
                "Invalid option. Please choose one of the options shown above: ");
        if (chosenOption == "1") {
            Game game(1);
            game.start();
        } else if (chosenOption == "2") {
            Game game(2);
            game.start();
        } else if (chosenOption == "3") {
            Game game(1);
            game.salvoStart();
        } else if (chosenOption == "4") {
            Game game(2);
            game.salvoStart();
        } else if (chosenOption == "5") {
            Game game(1);
            game.startWithMines();
        } else if (chosenOption == "6") {
            Game game(2);
            game.startWithMines();
        } else if (chosenOption == "7") {
            Game game(0);
            game.startWithMines();
        } else if (chosenOption == "8")
            showSettings();
        else
            break;
    }
}

int main() {
    showMenu();
    return 0;
}