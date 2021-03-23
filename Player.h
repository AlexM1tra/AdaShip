//
// Created by Alex on 05/03/2021.
//

#ifndef ADASHIPPROJECT_PLAYER_H
#define ADASHIPPROJECT_PLAYER_H

#include <stdlib.h>
#include <time.h>
#include <vector>

#include "Board.h"
#include "Common.h"
#include "SettingsIO.h"

class Player {
public:
    Board playerBoard;
    enum PlayerType {
        AI1 = 0,
        AI2 = 1,
        PLAYER1 = 2,
        PLAYER2 = 3,
    };
    virtual void addAllShips() = 0;
    virtual Coordinate* move() = 0;
    virtual void processTurnResult(Board::TurnResult result, Coordinate* chosenSquare) = 0;
    Player(Player&&) = delete;
    Player(Player const&) = delete;
    void showTurnUI(std::string);
protected:
    Player(std::vector<Boat> ships, PlayerType playerType);
    std::vector<BoatPosition> getPossibleShipPlacements(Boat* boat, Coordinate startingPoint);
    void autoPlaceShip(Boat* boat);
    PlayerType playerType;
};

#endif //ADASHIPPROJECT_PLAYER_H
