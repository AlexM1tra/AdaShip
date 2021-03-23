//
// Created by Alex on 05/03/2021.
//

#include "Player.h"

Player::Player(std::vector<Boat> ships, PlayerType playerType) : playerBoard(Board(SettingsIO::currentDimensions().width, SettingsIO::currentDimensions().height, ships)), playerType(playerType) {
    srand(time(NULL));
}

std::vector<BoatPosition> Player::getPossibleShipPlacements(Boat *boat, Coordinate startingPoint) {
    std::vector<BoatPosition> placementOptions;
    if (startingPoint.Row() - boat->Length() >= 0) {
        bool up = true;
        for (Coordinate& c : startingPoint.getConsecutiveCoordinates(Coordinate::UP, boat->Length())) {
            if (this->playerBoard.getStatusOfSquare(c) == BoardSquare::BOAT()) {
                up = false;
            }
        }
        if (up) {
            placementOptions.push_back(
                    BoatPosition(
                            startingPoint,
                            Coordinate(startingPoint.Column(),startingPoint.Row() - boat->Length() + 1)));
        }
    }
    if (startingPoint.Row() + boat->Length() <= SettingsIO::currentDimensions().height + 1) {
        bool down = true;
        for (Coordinate& c : startingPoint.getConsecutiveCoordinates(Coordinate::DOWN, boat->Length())) {
            if (this->playerBoard.getStatusOfSquare(c) == BoardSquare::BOAT()) {
                down = false;
            }
        }
        if (down) {
            placementOptions.push_back(
                    BoatPosition(
                            startingPoint,
                            Coordinate(startingPoint.Column(), startingPoint.Row() + boat->Length() - 1)));
        }
    }
    if (startingPoint.Column() - boat->Length() >= 0) {
        bool left = true;
        for (Coordinate& c : startingPoint.getConsecutiveCoordinates(Coordinate::LEFT, boat->Length())) {
            if (this->playerBoard.getStatusOfSquare(c) == BoardSquare::BOAT()) {
                left = false;
            }
        }
        if (left) {
            placementOptions.push_back(
                    BoatPosition(
                            startingPoint,
                            Coordinate(startingPoint.Column() - boat->Length() + 1, startingPoint.Row())));
        }
    }
    if (startingPoint.Column() + boat->Length() <= SettingsIO::currentDimensions().width + 1) {
        bool right = true;
        for (Coordinate& c : startingPoint.getConsecutiveCoordinates(Coordinate::RIGHT, boat->Length())) {
            if (this->playerBoard.getStatusOfSquare(c) == BoardSquare::BOAT()) {
                right = false;
            }
        }
        if (right) {
            placementOptions.push_back(
                    BoatPosition(
                            startingPoint,
                            Coordinate(startingPoint.Column() + boat->Length() - 1, startingPoint.Row())));
        }
    }
    return placementOptions;
}

void Player::autoPlaceShip(Boat* boat) {
        std::vector<BoatPosition> options = std::vector<BoatPosition>();
        while (options.size() == 0) {
            int column = (rand() % SettingsIO::currentDimensions().width) + 1;
            int row = (rand() % SettingsIO::currentDimensions().height) + 1;
            options = this->getPossibleShipPlacements(boat, Coordinate(column, row));
        }
        BoatPosition chosenOption = options[rand() % options.size()];
        this->playerBoard.addBoat(boat, chosenOption);
}

void Player::showTurnUI(std::string opponentBoard) {
    std::cout << Common::clearScreen << this->getName();
    std::cout << "\n" << Common::centerHorizontally("Attack", SettingsIO::screenWidth) << "\n\n" << opponentBoard;
    std::cout << "\n" << Common::centerHorizontally("Your Board", SettingsIO::screenWidth) << "\n\n" << this->playerBoard.getBoardForOwnerAsString() << "\n" << std::endl;
}

std::string Player::getName() {
    switch (this->playerType) {
      case AI1:
          return Common::ai1;
      case AI2:
          return Common::ai2;
      case PLAYER1:
          return Common::player1;
      case PLAYER2:
          return Common::player2;
      default:
          return "";
    }
}