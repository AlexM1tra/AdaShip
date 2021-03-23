//
// Created by Alex on 08/03/2021.
//

#ifndef ADASHIPPROJECT_AIPLAYER_H
#define ADASHIPPROJECT_AIPLAYER_H

#include "Player.h"

class AiPlayer : public Player {
public:
    AiPlayer(std::vector<Boat> ships, PlayerType playerType);
    void addAllShips() override;
    Coordinate* move() override;
    void processTurnResult(Board::TurnResult result, Coordinate* chosenSquare) override;
private:
    std::vector<Coordinate> squareCache = std::vector<Coordinate>();
};

#endif //ADASHIPPROJECT_AIPLAYER_H
