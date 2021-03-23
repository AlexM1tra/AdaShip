//
// Created by Alex on 08/03/2021.
//

#include <thread>
#include <chrono>

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(std::vector<Boat> ships, PlayerType playerType) : Player(ships, playerType) {
    this->addAllShips();
}

void HumanPlayer::addAllShips() {
    bool autoPlaceRemaining = false;
boatPlacementStart:
    playerBoard.clear();
    for (Boat& boat : this->playerBoard.boats) {
        if (autoPlaceRemaining)
            this->autoPlaceShip(&boat);
        else {
            bool placeAgain = true;
            while (placeAgain) {
                placeAgain = false;
                this->printShipsToPlace(&boat);
                std::cout << this->playerBoard.getBoardForOwnerAsString() << "\n\n";
                std::string anchor = Common::validatedInput(
                        "A- Autoplace ship.\nA*- Autoplace all remaining ships.\nR- Reset board\n\nEnter coordinate or use one of the above options: ",
                        [](std::string input) {
                            return input == "A" || input == "A*" || input == "R" || (Coordinate::isCoordinate(input)
                                && Coordinate(input).Row() <= SettingsIO::currentDimensions().height
                                && Coordinate(input).Column() <= SettingsIO::currentDimensions().width);
                        }, 
                        "Enter coordinate or use one of the above options: ",
                        true);
                if (anchor == "A")
                  this->autoPlaceShip(&boat);
                else if (anchor == "A*") {
                  this->autoPlaceShip(&boat);
                  autoPlaceRemaining = true;
                } else if (anchor == "R")
                  goto boatPlacementStart;
                else
                  placeAgain = this->addShip(&boat, anchor);
            }
        }
    }
    this->printShipsToPlace(&(this->playerBoard.boats[this->playerBoard.boats.size() - 1]));
    std::cout << this->playerBoard.getBoardForOwnerAsString() << "\n\n\n\n\n\n";
    std::string happy = Common::validatedInput("Are you happy with the ship placements(Y/N)? ",
                                              Common::isOneOf(std::vector<std::string>{"Y", "N"}),
                                              " ",
                                              true);
    if (happy == "N") {
      autoPlaceRemaining = false;
      goto boatPlacementStart;
    }
}

bool HumanPlayer::addShip(Boat* boat, std::string anchor) {
    this->printShipsToPlace(boat);
    std::vector<BoatPosition> options = this->getPossibleShipPlacements(boat, Coordinate(anchor));
    std::cout << this->playerBoard.getBoardWithPlacementOptions(options) << "\n\n";
    std::string chosenOption = Common::validatedInput(
            "\n\nC- Choose new placement.\n\nChoose one of the placement options shown above: ",
            [options](std::string input){
                std::vector<std::string> optionNumbers = std::vector<std::string>{"1", "2", "3", "4"};
                return std::find(
                        optionNumbers.begin(),
                        optionNumbers.begin() + options.size(),
                        input) != optionNumbers.begin() + options.size()
                       || input == "C";
            },
            "Invalid option. Please choose one of the options shown above: ",
            true);
    if (chosenOption == "C")
        return true;
    else
        this->playerBoard.addBoat(boat, options[stoi(chosenOption) - 1]);
    return false;
}

void HumanPlayer::printShipsToPlace(Boat* boat) {
    std::cout << Common::clearScreen << this->getName();
    std::cout << Common::place_boat << "\n\n";
    for (Boat& otherBoat : this->playerBoard.boats) {
      if (&otherBoat == boat) {
        for (int i = 0; i < otherBoat.Length(); i++)
          std::cout << "■ ";
        std::cout << ": " << otherBoat.Name() << " <<" << std::endl;
      }
      else {
        for (int i = 0; i < otherBoat.Length(); i++)
          std::cout << "■ ";
        std::cout << ": " << otherBoat.Name() << std::endl;
      }
    }
    std::cout << "\n";
}

Coordinate* HumanPlayer::move() {
    std::string chosenCoordinate = Common::validatedInput(
            "A- Auto fire.\nQ- Quit.\n\nEnter coordinate or choose option above: ",
            [](std::string input) {
                return input == "A" || input == "Q" || (Coordinate::isCoordinate(input)
                    && Coordinate(input).Row() <= SettingsIO::currentDimensions().height
                    && Coordinate(input).Column() <= SettingsIO::currentDimensions().width);
            }, 
            "Enter coordinate or choose option above: ",
            true);
    if (chosenCoordinate == "A")
        return new Coordinate((rand() % SettingsIO::currentDimensions().width) + 1,
                              (rand() % SettingsIO::currentDimensions().height) + 1);
    else if (chosenCoordinate == "Q")
        return nullptr;
    return new Coordinate(chosenCoordinate);
}

void HumanPlayer::processTurnResult(Board::TurnResult result, Coordinate *chosenSquare) {
    switch (result) {
        case Board::TurnResult::MISS:
            std::cout << Common::clearScreen << Common::centerVertically(Common::miss, SettingsIO::screenHeight) << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
            break;
        case Board::TurnResult::HIT:
            std::cout << Common::clearScreen << Common::centerVertically(Common::hit, SettingsIO::screenHeight) << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
            break;
        case Board::TurnResult::HIT_AND_SUNK:
            std::cout << Common::clearScreen << Common::centerVertically(Common::hit_and_sunk, SettingsIO::screenHeight) << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
            break;
        case Board::TurnResult::MINE:
            std::cout << Common::clearScreen << Common::centerVertically(Common::mine, SettingsIO::screenHeight) << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
            break;
        case Board::TurnResult::ALREADY_ATTACKED:
            std::cout << Common::clearScreen << Common::centerVertically("You've already attacked that square!!\nTry again...", SettingsIO::screenHeight) << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
    }
}