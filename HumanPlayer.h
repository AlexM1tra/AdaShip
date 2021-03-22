//
// Created by Alex on 08/03/2021.
//

#ifndef ADASHIPPROJECT_HUMANPLAYER_H
#define ADASHIPPROJECT_HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(std::vector<Boat> ships, BoardDimensions dimensions);
    void addAllShips() override;
    void showTurnUI(std::string) override;
    Coordinate* move() override;
    void processTurnResult(Board::TurnResult result, Coordinate* chosenSquare) override;
private:
    void addShip(Boat*);
};

#endif //ADASHIPPROJECT_HUMANPLAYER_H
