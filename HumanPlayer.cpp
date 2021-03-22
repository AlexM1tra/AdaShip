//
// Created by Alex on 08/03/2021.
//

#include <thread>
#include <chrono>

#include "HumanPlayer.h"
#include "Common.h"

HumanPlayer::HumanPlayer(std::vector<Boat> ships) : Player(ships) {
    this->addAllShips();
}

void HumanPlayer::addAllShips() {
    for (Boat& boat : this->playerBoard.boats) {
        addShip(&boat);
    }
}

void HumanPlayer::addShip(Boat* boat) {
    this->printShipsToPlace(boat);
    std::cout << this->playerBoard.getBoardForOwnerAsString() << "\n\n";
    std::string anchor = Common::validatedInput(
            "Enter coordinate: ",
            [](std::string input) {
                return Coordinate::isCoordinate(input)
                    && Coordinate(input).Row() <= SettingsIO::currentDimensions().height
                    && Coordinate(input).Column() <= SettingsIO::currentDimensions().width;
            });
    this->printShipsToPlace(boat);
    std::vector<BoatPosition> options = this->getPossibleShipPlacements(boat, Coordinate(anchor));
    std::cout << this->playerBoard.getBoardWithPlacementOptions(options) << "\n\n";
    std::string chosenOption = Common::validatedInput(
            "Choose one of the placement options shown above (or C to choose again): ",
            [options](std::string input){
                std::vector<std::string> optionNumbers = std::vector<std::string>{"1", "2", "3", "4"};
                return std::find(
                        optionNumbers.begin(),
                        optionNumbers.begin() + options.size(),
                        input) != optionNumbers.begin() + options.size()
                       || input == "C";
            },
            "Invalid option. Please choose one of the options shown above: ");
    if (chosenOption == "C")
        this->addShip(boat);
    else
        this->playerBoard.addBoat(boat, options[stoi(chosenOption) - 1]);
}

void HumanPlayer::printShipsToPlace(Boat* boat) {
    std::cout << Common::clearScreen;
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

void HumanPlayer::showTurnUI(std::string opponentBoard) {
    std::cout << Common::clearScreen;
    std::cout << "\n" << Common::centerHorizontally("Attack", SettingsIO::screenWidth) << "\n\n" << opponentBoard;
    std::cout << "\n" << Common::centerHorizontally("Your Board", SettingsIO::screenWidth) << "\n\n" << this->playerBoard.getBoardForOwnerAsString() << "\n" << std::endl;
}

Coordinate* HumanPlayer::move() {
    std::string chosenCoordinate = Common::validatedInput(
            "Enter coordinate: ",
            [](std::string input) {
                return Coordinate::isCoordinate(input)
                    && Coordinate(input).Row() <= SettingsIO::currentDimensions().height
                    && Coordinate(input).Column() <= SettingsIO::currentDimensions().width;
            });
    return new Coordinate(chosenCoordinate);
}

void HumanPlayer::processTurnResult(Board::TurnResult result, Coordinate *chosenSquare) {
    switch (result) {
        case Board::TurnResult::MISS:
            std::cout << Common::clearScreen << Common::centerFully(Common::miss) << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
            break;
        case Board::TurnResult::HIT:
            std::cout << Common::clearScreen << Common::centerFully(Common::hit) << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
            break;
        case Board::TurnResult::HIT_AND_SUNK:
            std::cout << Common::clearScreen << Common::centerFully(Common::hit_and_sunk) << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
            break;
        case Board::TurnResult::ALREADY_ATTACKED:
            std::cout << Common::clearScreen << Common::centerFully("You've already attacked that square!!\nTry again...") << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(2));
    }
}