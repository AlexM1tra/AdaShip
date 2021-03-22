//
// Created by Alex on 08/03/2021.
//

#include <thread>
#include <chrono>

#include "HumanPlayer.h"
#include "Common.h"

HumanPlayer::HumanPlayer(std::vector<Boat> ships, BoardDimensions dimensions) : Player(ships) {
    this->playerBoard = Board(dimensions.width, dimensions.height, ships);
    this->addAllShips();
}

void HumanPlayer::addAllShips() {
    for (Boat& boat : this->playerBoard.boats) {
        addShip(&boat);
    }
}

void HumanPlayer::addShip(Boat* boat) {
    std::cout << "\n" << this->playerBoard.getBoardForOwnerAsString() << "\n\n";
    BoardDimensions dimensions = this->playerBoard.getBoardDimensions();
    std::string anchor = Common::validatedInput(
            "Enter coordinate: ",
            [&dimensions](std::string input) {
                return Coordinate::isCoordinate(input)
                    && Coordinate(input).Row() <= dimensions.height
                    && Coordinate(input).Column() <= dimensions.width;
            });
    std::vector<BoatPosition> options = this->getPossibleShipPlacements(boat, Coordinate(anchor));
    std::cout << "\n" << this->playerBoard.getBoardWithPlacementOptions(options) << "\n";
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

void HumanPlayer::showTurnUI(std::string opponentBoard) {
    std::cout << "\nAttack\n" << opponentBoard << std::endl;
    std::cout << "Your Board\n\n" << this->playerBoard.getBoardForOwnerAsString();
}

Coordinate* HumanPlayer::move() {
    BoardDimensions dimensions = this->playerBoard.getBoardDimensions();
    std::string chosenCoordinate = Common::validatedInput(
            "Enter coordinate: ",
            [&dimensions](std::string input) {
                return Coordinate::isCoordinate(input)
                    && Coordinate(input).Row() <= dimensions.height
                    && Coordinate(input).Column() <= dimensions.width;
            });
    return new Coordinate(chosenCoordinate);
}

void HumanPlayer::processTurnResult(Board::TurnResult result, Coordinate *chosenSquare) {
    BoardDimensions dim = this->playerBoard.getBoardDimensions();
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