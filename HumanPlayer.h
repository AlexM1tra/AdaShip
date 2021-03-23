//
// Created by Alex on 08/03/2021.
//

#ifndef ADASHIPPROJECT_HUMANPLAYER_H
#define ADASHIPPROJECT_HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(std::vector<Boat> ships, PlayerType playerType);
    void addAllShips() override;
    Coordinate* move() override;
    void processTurnResult(Board::TurnResult result, Coordinate* chosenSquare) override;
private:
    /** Adds a ship to a board if the user is happy and returns a boolean indicating
      * whether the ship should be replaced elsewhere.
      **/
    bool addShip(Boat*, std::string anchor);
    void printShipsToPlace(Boat*);
};

#endif //ADASHIPPROJECT_HUMANPLAYER_H
