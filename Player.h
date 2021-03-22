//
// Created by Alex on 05/03/2021.
//

#ifndef ADASHIPPROJECT_PLAYER_H
#define ADASHIPPROJECT_PLAYER_H

#include <stdlib.h>
#include <time.h>
#include <vector>

#include "Board.h"
#include "SettingsIO.h"

class Player {
public:
    Board playerBoard;
    virtual void addAllShips() = 0;
    virtual void showTurnUI(std::string) = 0;
    virtual Coordinate* move() = 0;
    virtual void processTurnResult(Board::TurnResult result, Coordinate* chosenSquare) = 0;
    Player(Player&&) = delete;
    Player(Player const&) = delete;
protected:
    Player(std::vector<Boat> ships);
    std::vector<BoatPosition> getPossibleShipPlacements(Boat* boat, Coordinate startingPoint);
    void autoPlaceShip(Boat* boat);
};

#endif //ADASHIPPROJECT_PLAYER_H
