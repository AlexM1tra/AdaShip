//
// Created by Alex on 08/03/2021.
//

#include "AiPlayer.h"

AiPlayer::AiPlayer(std::vector<Boat> ships, BoardDimensions dimensions) : Player(ships) {
    this->playerBoard = Board(dimensions.width, dimensions.height, ships);
    this->addAllShips();
}

void AiPlayer::addAllShips() {
    std::vector<BoatPosition> options;
    for (Boat& boat : this->playerBoard.boats) {
        options = std::vector<BoatPosition>();
        while (options.size() == 0) {
            int column = (rand() % this->playerBoard.getBoardDimensions().width) + 1;
            int row = (rand() % this->playerBoard.getBoardDimensions().height) + 1;
            options = this->getPossibleShipPlacements(&boat, Coordinate(column, row));
        }
        BoatPosition chosenOption = options[rand() % options.size()];
        this->playerBoard.addBoat(&boat, chosenOption);
    }
}

Coordinate* AiPlayer::move() {
    if (squareCache.size() != 0) {
        Coordinate* square = new Coordinate(squareCache[squareCache.size() - 1]);
        squareCache.pop_back();
        return square;
    }
    return new Coordinate((rand() % this->playerBoard.getBoardDimensions().width) + 1,
                          (rand() % this->playerBoard.getBoardDimensions().height) + 1);
}

void AiPlayer::processTurnResult(Board::TurnResult result, Coordinate* chosenSquare) {
    if (result == Board::TurnResult::HIT) {
        if (!(chosenSquare->Column() == 1)) {
            squareCache.push_back(Coordinate(chosenSquare->Column() - 1, chosenSquare->Row()));
        }
        if (!(chosenSquare->Row() == 1)) {
            squareCache.push_back(Coordinate(chosenSquare->Column(), chosenSquare->Row() - 1));
        }
        if (!(chosenSquare->Column() == this->playerBoard.getBoardDimensions().width)) {
            squareCache.push_back(Coordinate(chosenSquare->Column() + 1, chosenSquare->Row()));
        }
        if (!(chosenSquare->Row() == this->playerBoard.getBoardDimensions().height)) {
            squareCache.push_back(Coordinate(chosenSquare->Column(), chosenSquare->Row() + 1));
        }
    } else if (result == Board::TurnResult::HIT_AND_SUNK) {
        squareCache.clear();
    }
}