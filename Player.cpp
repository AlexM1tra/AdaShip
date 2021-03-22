//
// Created by Alex on 05/03/2021.
//

#include "Player.h"

Player::Player(std::vector<Boat> ships) : playerBoard(Board(10, 10, ships)) {
    srand(time(NULL));
}

std::vector<Boat::BoatPosition> Player::getPossibleShipPlacements(Boat *boat, Coordinate startingPoint) {
    std::vector<Boat::BoatPosition> placementOptions;
    if (startingPoint.Row() - boat->Length() >= 0) {
        bool up = true;
        for (Coordinate& c : startingPoint.getConsecutiveCoordinates(Coordinate::UP, boat->Length())) {
            if (this->playerBoard.getStatusOfSquare(c) == BoardSquare::BOAT()) {
                up = false;
            }
        }
        if (up) {
            placementOptions.push_back(
                    Boat::BoatPosition(
                            startingPoint,
                            Coordinate(startingPoint.Column(),startingPoint.Row() - boat->Length() + 1)));
        }
    }
    if (startingPoint.Row() + boat->Length() <= this->playerBoard.getBoardDimensions().height + 1) {
        bool down = true;
        for (Coordinate& c : startingPoint.getConsecutiveCoordinates(Coordinate::DOWN, boat->Length())) {
            if (this->playerBoard.getStatusOfSquare(c) == BoardSquare::BOAT()) {
                down = false;
            }
        }
        if (down) {
            placementOptions.push_back(
                    Boat::BoatPosition(
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
                    Boat::BoatPosition(
                            startingPoint,
                            Coordinate(startingPoint.Column() - boat->Length() + 1, startingPoint.Row())));
        }
    }
    if (startingPoint.Column() + boat->Length() <= this->playerBoard.getBoardDimensions().width + 1) {
        bool right = true;
        for (Coordinate& c : startingPoint.getConsecutiveCoordinates(Coordinate::RIGHT, boat->Length())) {
            if (this->playerBoard.getStatusOfSquare(c) == BoardSquare::BOAT()) {
                right = false;
            }
        }
        if (right) {
            placementOptions.push_back(
                    Boat::BoatPosition(
                            startingPoint,
                            Coordinate(startingPoint.Column() + boat->Length() - 1, startingPoint.Row())));
        }
    }
    return placementOptions;
}
