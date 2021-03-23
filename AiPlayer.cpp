//
// Created by Alex on 08/03/2021.
//

#include "AiPlayer.h"
#include "SettingsIO.h"

AiPlayer::AiPlayer(std::vector<Boat> ships, PlayerType playerType) : Player(ships, playerType) {
    this->addAllShips();
}

void AiPlayer::addAllShips() {
    std::vector<BoatPosition> options;
    for (Boat& boat : this->playerBoard.boats) {
      this->autoPlaceShip(&boat);
    }
}

Coordinate* AiPlayer::move() {
    if (squareCache.size() != 0) {
        Coordinate* square = new Coordinate(squareCache[squareCache.size() - 1]);
        squareCache.pop_back();
        return square;
    }
    return new Coordinate((rand() % SettingsIO::currentDimensions().width) + 1,
                          (rand() % SettingsIO::currentDimensions().height) + 1);
}

void AiPlayer::processTurnResult(Board::TurnResult result, Coordinate* chosenSquare) {
    if (result == Board::TurnResult::HIT) {
        if (!(chosenSquare->Column() == 1)) {
            squareCache.push_back(Coordinate(chosenSquare->Column() - 1, chosenSquare->Row()));
        }
        if (!(chosenSquare->Row() == 1)) {
            squareCache.push_back(Coordinate(chosenSquare->Column(), chosenSquare->Row() - 1));
        }
        if (!(chosenSquare->Column() == SettingsIO::currentDimensions().width)) {
            squareCache.push_back(Coordinate(chosenSquare->Column() + 1, chosenSquare->Row()));
        }
        if (!(chosenSquare->Row() == SettingsIO::currentDimensions().height)) {
            squareCache.push_back(Coordinate(chosenSquare->Column(), chosenSquare->Row() + 1));
        }
    } else if (result == Board::TurnResult::HIT_AND_SUNK) {
        squareCache.clear();
    }
}