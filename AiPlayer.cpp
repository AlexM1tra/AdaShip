//
// Created by Alex on 08/03/2021.
//

#include "AiPlayer.h"

AiPlayer::AiPlayer(std::vector<Boat> ships, PlayerType playerType) : Player(ships, playerType) {
    this->addAllShips();
}

void AiPlayer::addAllShips() {
    std::vector<BoatPosition> options;
    for (Boat& boat : this->playerBoard.boats) {
        this->_autoPlaceShip(&boat);
    }
}

Coordinate* AiPlayer::move() {
    if (_squareCache.size() != 0) {
        Coordinate* square = new Coordinate(_squareCache[_squareCache.size() - 1]);
        _squareCache.pop_back();
        return square;
    }
    return new Coordinate((rand() % SettingsIO::currentDimensions().width) + 1,
                          (rand() % SettingsIO::currentDimensions().height) + 1);
}

void AiPlayer::processTurnResult(Board::TurnResult result, Coordinate* chosenSquare) {
    if (result == Board::TurnResult::HIT) {
        if (!(chosenSquare->Column() == 1)) {
            _squareCache.push_back(Coordinate(chosenSquare->Column() - 1, chosenSquare->Row()));
        }
        if (!(chosenSquare->Row() == 1)) {
            _squareCache.push_back(Coordinate(chosenSquare->Column(), chosenSquare->Row() - 1));
        }
        if (!(chosenSquare->Column() == SettingsIO::currentDimensions().width)) {
            _squareCache.push_back(Coordinate(chosenSquare->Column() + 1, chosenSquare->Row()));
        }
        if (!(chosenSquare->Row() == SettingsIO::currentDimensions().height)) {
            _squareCache.push_back(Coordinate(chosenSquare->Column(), chosenSquare->Row() + 1));
        }
    } else if (result == Board::TurnResult::HIT_AND_SUNK) {
        _squareCache.clear();
    }
}